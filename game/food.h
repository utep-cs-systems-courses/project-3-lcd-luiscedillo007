#ifndef food_included
#define food_included

void food_init(int w_max, int h_max, int up_x, int up_y);
void spawn_food(int up_x, int up_y);
unsigned char get_food_size();
int get_x();
int get_y();

#endif
