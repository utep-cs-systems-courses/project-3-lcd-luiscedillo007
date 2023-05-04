#include <msp430.h>
#include "box.h"

unsigned char this_blockSize, moveSpeed, left_right, cur_dir;
int cur_blockX;
int cur_blockY;
int w_max, h_max;

void box_init(int w_max_in, int h_max_in) {
    this_blockSize = 10;
    moveSpeed = 15;
    left_right = 0;
    cur_blockY = h_max_in/2;
    cur_blockX = w_max_in; 
    cur_dir = 3;
    w_max = w_max_in;
    h_max = h_max_in;
}

unsigned char get_box_size(){
    return this_blockSize;
}

unsigned char get_dir(){
    return cur_dir;
}

int box_update(int *blockY) {
    switch (cur_dir) {
        case 0:
            cur_blockX -= moveSpeed;
            break;
        case 1:
            cur_blockY -= moveSpeed;
            break;
        case 2:
            cur_blockY += moveSpeed;
            break;
        case 3:
            cur_blockX += moveSpeed;
            break;
    }

    if (cur_blockX < 0) {
        cur_blockX = 0;
    } else if (cur_blockX >= w_max - this_blockSize) {
        cur_blockX = w_max - this_blockSize;
    }

    if (cur_blockY < 0) {
        cur_blockY = 0;
    } else if (cur_blockY >= h_max - this_blockSize) {
        cur_blockY = h_max - this_blockSize;
    }

    *blockY = cur_blockY;
    return cur_blockX;
}

void set_box_direction(unsigned char new_direction) {
    if (new_direction != cur_dir) {
        cur_dir = new_direction;
    }
}
