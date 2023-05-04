#ifndef box_included
#define box_included

void box_init(int w_max, int h_max);
unsigned char get_box_size();
unsigned char get_dir();
int box_update(int *blockY);
void set_box_direction(unsigned char new_direction);

#endif
