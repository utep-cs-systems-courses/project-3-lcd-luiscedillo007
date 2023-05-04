#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "box.h"

unsigned char this_foodSize;
int new_food_x;
int new_food_y;

int w_max_f, h_max_f;

void food_init(int w_max_in_f, int h_max_in_f, int up_x, int up_y) {
    this_foodSize = 10;
    w_max_f = w_max_in_f;
    h_max_f = h_max_in_f;
    new_food_x = up_x;
    new_food_y = up_y;
}

void spawn_food(int up_x, int up_y){
    new_food_x = up_x;
    new_food_y = up_y;
    fillRectangle(new_food_x, new_food_y, this_foodSize, this_foodSize, COLOR_RED);
}

unsigned char get_food_size(){
    return this_foodSize;
}

int get_x(){
    return new_food_x;
}

int get_y(){
    return new_food_y;
}
