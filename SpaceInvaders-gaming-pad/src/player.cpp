#include "player.h"

void Player::setup(ofImage* _img) {
    img = _img;

    speed = 5;
    player_width = player_height = img->getWidth();
    pos.x = ofGetWidth() / 2;
    pos.y = ofGetHeight() - player_height * 2;

}

void Player::update() {
    calculate_movement();
}

void Player::draw() {
    img->draw(pos.x - player_width/2, pos.y - player_height/2);
    
}

void Player::calculate_movement() {

    // mode player to left inside the window
    if(is_left_pressed && (pos.x > 0 + player_width/2) ) {
        pos.x -= speed; 
    }

    if(is_right_pressed && (pos.x < ofGetWidth() - player_width/2) ) {
         pos.x += speed;
    }

    if(is_up_pressed && (pos.y > 0 + player_height/2) ) {
        pos.y -= speed;
    } 

    if (is_down_pressed && pos.y < ofGetHeight() - player_height/2) {
        pos.y += speed;
    }

}
