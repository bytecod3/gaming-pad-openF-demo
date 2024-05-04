#pragma once 

#include "ofMain.h"

class LevelController {
public:
float start_time;
float interval_time;

void setup(float e);
bool should_spawn();

};