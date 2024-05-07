#pragma once
#include "ofMain.h"

class Player {
    public:
    ofPoint pos;
    float player_width, player_height, speed;
    int lives;
    
    bool is_left_pressed, is_right_pressed, is_up_pressed, is_down_pressed;
    void setup(ofImage* _img);
    void update();
    void draw();
    void shoot();
    int interpolate_speed(int, int, int, int, int);

    void calculate_movement();
    bool check_can_shoot();
    ofImage* img;
};