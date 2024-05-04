#pragma once
#pragma once


#include "ofMain.h"
#include "player.h"
#include "enemy.h"
#include "life.h"
#include "bullet.h"

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

	// game structure
	string game_state;
	int score;
	Player player_1;

	float max_enemy_amplitude;
	float max_enemy_shoot_interval;

	ofImage player_image;
	ofImage enemy_image;
	ofImage player_bullet_image;
	ofImage enemy_bullet_image;

	vector<Bullet> bullets; // a vector to hold all the bullets
	vector<Enemy> enemies; // a vector to hold the enemies

	void update_bullets();

};
