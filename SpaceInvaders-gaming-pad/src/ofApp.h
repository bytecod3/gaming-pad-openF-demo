#pragma once
#pragma once


#include "ofMain.h"
#include "player.h"
#include "enemy.h"
#include "life.h"
#include "bullet.h"
#include "level_controller.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// set up font
	ofTrueTypeFont font;
	ofTrueTypeFont font_small;

	// serial data
	ofSerial serial;
	string com_port = "";
	int baud_rate;
	float time_last_try_connect = 0; // time we last tried reconnecting to serial device
	float read_time; // when did we last read
	int lx,ly,rx,ry;
	vector <string> coords; // to hold the splitted lx,ly,rx,ry coordinates
	int coordinates[4];

	// currently connected serial devices 
	vector <ofSerialDeviceInfo> device_list;

	// store received data to split it later 
	string serial_read_string = "";
	vector <string> received_serial_messages; 
	ofBuffer serial_read_buffer;
	int erase_index;

	// game structure
	string game_state;
	int score;
	Player player_1;
	LevelController level_controller;

	float max_enemy_amplitude;
	float max_enemy_shoot_interval;

	ofImage player_image;
	ofImage enemy_image;
	ofImage player_bullet_image;
	ofImage enemy_bullet_image;
	ofImage splash_screen;
	ofImage end_screen;

	vector<Bullet> bullets; // a vector to hold all the bullets
	vector<Enemy> enemies; // a vector to hold the enemies

	// my functions
	void update_bullets();
	void check_bullet_collisions();
	void draw_score();

};
