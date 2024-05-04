#pragma once

#include "ofMain.h"

class Bullet {
public:
ofPoint pos;
float speed;
float bullet_width;
bool from_player;

void setup(bool f_p, ofPoint p, float s, ofImage* bullet_image);
void update();
void draw();

ofImage* img;

};