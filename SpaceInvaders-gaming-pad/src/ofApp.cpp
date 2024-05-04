#include "ofApp.h"
#include <string.h>

//--------------------------------------------------------------
void ofApp::setup(){
	// set window title 
	ofSetWindowTitle("Space Invaders - v1.0, 2024");

	game_state = "start";

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

	// set up player
	player_1.setup(&player_image);
	

}

//--------------------------------------------------------------
void ofApp::update() {

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

		// level controller
		Enemy e;
		e.setup(max_enemy_amplitude, max_enemy_shoot_interval, &enemy_image);
		enemies.push_back(e);

	} else if(game_state == "end" ) {
		
	} 
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	int i;
	if(game_state == "start" ) {

	} else if(game_state == "game" ) {
		ofBackground(0,0,0); // black background TODO: add a space bg
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

	// collision
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
void ofApp::keyReleased(int key){
	// when player is on start screen and releases the space key, the game starts
	if(game_state == "start") {
		game_state = "game";
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
