#include "ofApp.h"
#include <string.h>

//--------------------------------------------------------------
void ofApp::setup(){
	// set window title 
	ofSetWindowTitle("Space Invaders - v1.0, 2024");

	// window size
	ofSetWindowShape(1000, 800);
    ofSetWindowPosition(50, 50);

	// set up font
	font_small.load("DIN.otf", 12);
	font.load("DIN.otf", 15);	

	// get serial data
	com_port = "COM10";
	baud_rate = 115200;
	serial.listDevices();
	device_list = serial.getDeviceList();

	// try connecting to serial device
	if(com_port != "") {
		serial.setup(com_port, baud_rate);
	} else {
		// try connect to the first device it finds 
		serial.setup(0, baud_rate);
	}

	// store this time we just tried to connect to device
	time_last_try_connect = ofGetElapsedTimef();	

	game_state = "start";

	// init score as 0
	score = 0;

	// add player image
	player_image.load("player_image.png");

	// add enemy image
	max_enemy_amplitude = 3.0;
	max_enemy_shoot_interval = 1.5; // shoot after every 1.5 frames
	enemy_image.load("enemy_image.png");

	// add player bullet image
	player_bullet_image.load("player_bullet_image.png");

	// add enemy bullet image
	enemy_bullet_image.load("enemy_bullet_image.png");

	// splash screen
	splash_screen.load("start-screen.png");

	// end screen
	end_screen.load("end_screen.png");

	// set up player
	player_1.setup(&player_image);
	
}

//--------------------------------------------------------------
void ofApp::update() {

	// check gaming pad initialization on serial
	if(serial.isInitialized()) {

		// number of bytes to read from serial
		int num_bytes_to_read = serial.available();

		// cap the number of bytes to 512
		if(num_bytes_to_read > 512) {
			num_bytes_to_read = 512;
		}

		if(num_bytes_to_read > 0) {
			serial_read_buffer.clear();
			serial.readBytes(serial_read_buffer, num_bytes_to_read);
			serial_read_string += serial_read_buffer.getText();

			// a temporary string to populate from the read string
			string full_message = "";
			
			// go through each character and look for return char
			for(int i=0; i<serial_read_string.length(); i++) {
				unsigned char character =  serial_read_string[i];
				if(character == '\n' || character == '\r' || character == '\t') {
					if(full_message.length() > 0) {
						// store the new message in a vector
						received_serial_messages.push_back(full_message);
						erase_index = i;
					}
				}
				full_message += character;
			}

			if(erase_index > -1) {
				serial_read_string = serial_read_string.substr(erase_index);
			}

		}

	} else {
		// try reconnecting
		float etimef = ofGetElapsedTimef();
		if(etimef - time_last_try_connect > 10.0) {
			// refresh device list
			device_list = serial.getDeviceList();
			time_last_try_connect = etimef;
			
			if(com_port != "") {
				ofLogNotice("Attempting to connect to serial device: ") << com_port;
				serial.setup(com_port, baud_rate);
			} else {
				// open first device 
				serial.setup(0, baud_rate);
			}
		}

	}

	// delete out older serial messages
	if(received_serial_messages.size() > 10) {
		received_serial_messages.erase(received_serial_messages.begin());
	}

	read_time = ofGetElapsedTimef();


	// update game data
	if(game_state == "start" ) {
		
	} else if(game_state == "game" ) {
		player_1.update();
		update_bullets();

		for (int i = 0; i < enemies.size(); i++){
			enemies[i].update();
			if(enemies[i].time_to_shoot() ) {
				Bullet b;
				b.setup(false, enemies[i].pos, enemies[i].speed, &enemy_bullet_image);
				bullets.push_back(b);
			}
		}

		// check for collisions using the level controller
		if(level_controller.should_spawn()) {

			Enemy e;
			e.setup(max_enemy_amplitude, max_enemy_shoot_interval, &enemy_image);
			enemies.push_back(e);	

		}

	} else if(game_state == "end" ) {

	} 
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	// render game graphics
	int i;
	ofBackground(0,0,0); 
	if(game_state == "start" ) {
		splash_screen.draw(0, 0);

	} else if(game_state == "game" ) {

		ofSetColor(0, 255, 0);
		// print gaming pad coordinates on screen
		
		font_small.drawString("Gaming pads detected: "+ofToString(serial.isInitialized()), 50, 50);
		string device_string = "[lx, lr, rx, ry]\n";
		font_small.drawString(device_string, 50, 30);

		ofSetColor(255);

		// ---------------Render gaming pad serial data ------------------
		float posY = 70;

		char buff[10];
		font_small.drawString(received_serial_messages[received_serial_messages.size() - 1], 50, posY);

		if(received_serial_messages.size() > 0) {
			// sprintf(buff, "%lu\n", received_serial_messages.size());
			// font_small.drawString(buff, 50, posY);
			// for(int i= (int) received_serial_messages.size()-1; i >= 0; i--) {
			// 	// if(i == (int) received_serial_messages.size()-1 &&  ((ofGetElapsedTimef() - read_time) < 0.1f)){
			// 	// 	ofSetColor(255);
			// 	// }

			// 	// draw the data on screen
			// 	font_small.drawString(received_serial_messages[i], 50, posY);
			// 	posY+=20;

			// }
		}

		// ----------------------------------

		player_1.draw();

		// generate enemies 
		for (i = 0; i < enemies.size(); i++) {
			enemies[i].draw();
		}

		// draw bullets on screen
		for(i = 0; i < bullets.size(); i++) {
			bullets[i].draw();
		}

	} else if(game_state == "end" ) {
		end_screen.draw(0,0);
	} 
	
}

//--------------------------------------------------------------
void ofApp::update_bullets() {
	int i;
	for(i=0; i < bullets.size(); i++) {
		bullets[i].update();

		if(bullets[i].pos.y - bullets[i].bullet_width / 2 <0 || bullets[i].pos.y + bullets[i].bullet_width/2 > ofGetHeight() ) {
			bullets.erase(bullets.begin() + i);
		}

	}

	check_bullet_collisions();

}

//--------------------------------------------------------------
void ofApp::check_bullet_collisions() {
	for(int i = 0; i < bullets.size(); i++) {
		if(bullets[i].from_player) {
			// if bullet is from the player

			// check if it overlaps with any of the enemies 
			for(int e = enemies.size()-1; e >= 0; e--) {
				if(ofDist(bullets[i].pos.x, bullets[i].pos.y, enemies[e].pos.x, enemies[e].pos.y) < (enemies[e].enemy_width + bullets[i].bullet_width/2) ) {
					// enemy hit, delete enemy and the bullet
					enemies.erase(enemies.begin() + e);
					bullets.erase(bullets.begin() +i );
					
					// increment the score
					score += 10;
				}
			}
		} else {
			// if bullet is from the enemy
			// if player hit, subtract the player's life and erase the bullet
			if(ofDist(bullets[i].pos.x, bullets[i].pos.y, player_1.pos.x, player_1.pos.y) < (bullets[i].bullet_width + player_1.player_width)/2 ) {
				bullets.erase(bullets.begin() + i);
				player_1.lives--;

				// // TODO: about to die
				// if(player_1.lives <= 0) {
				// 	game_state = "end";
				// }

			}

		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if(game_state == "game") {
		if(key == OF_KEY_LEFT) {
			player_1.is_left_pressed = true;
		}

		if(key == OF_KEY_RIGHT) {
			player_1.is_right_pressed = true;
		}

		if(key == OF_KEY_UP) {
			player_1.is_up_pressed = true;
		}

		if(key == OF_KEY_DOWN) {
			player_1.is_down_pressed = true;
		}

		if (key == ' ') {
			cout<<"fire\n"<<endl;
			// spawn a bullet
			Bullet b;
			b.setup(true, player_1.pos, player_1.speed, &player_bullet_image);
			bullets.push_back(b);
		}

	}

}

//--------------------------------------------------------------
void ofApp::draw_score() {
	if (game_state == "game") {
		ofDrawBitmapString("SCORE", ofGetWindowWidth()-50, 20 );
	} else if(game_state == "end") {
		// TODO: show score on game over
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// when player is on start screen and releases the space key, the game starts
	if(game_state == "start") {
		game_state = "game";
		level_controller.setup(ofGetElapsedTimeMillis());
		
	} else if (game_state == "game") {

		if(key == OF_KEY_LEFT) {
			player_1.is_left_pressed = false;
		}

		if(key == OF_KEY_RIGHT) {
			player_1.is_right_pressed = false;
		}

		if(key == OF_KEY_UP) {
			player_1.is_up_pressed = false;
		}

		if(key == OF_KEY_DOWN) {
			player_1.is_down_pressed = false;
		}

	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
