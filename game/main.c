#include <msp430.h>
#include <stdlib.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "box.h"
#include "state_machine.h"
#include "food.h"
#include "buzzer.h"

#define BG_COLOR COLOR_BLACK
#define blockColor COLOR_GREEN

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */
int redrawScreen = 1;
int max_width = screenWidth;
int max_height = screenHeight;

/// this
int blockX = screenWidth;
int blockY = screenHeight/2;
int score = 0;

/* WDT interrupt handler */
void wdt_c_handler() {

    static int sec1Count = 0;
    if (sec1Count++ >= 250) {       /* 1/sec */
        sec1Count = 0;

        blockX = box_update(&blockY);
        buzzer_set_period(0);

        redrawScreen = 1;
    }
}

void draw_border(unsigned char how_down){

  for (u_char i = 0; i <= screenWidth; i++){
    drawPixel(i, how_down, COLOR_WHITE);
  }


}

int box_col(int x1, int y1, int x2, int y2, int size_obj) {
    int x1_right = x1 + size_obj;
    int x2_right = x2 + size_obj;
    int y1_bottom = y1 + size_obj;
    int y2_bottom = y2 + size_obj;

    if (x1 < x2_right && x1_right > x2 && y1 < y2_bottom && y1_bottom > y2) {
        return 1;
    }

    return 0;
}

int get_rand_x(){
    return (rand() % ((max_width-10) - 0 + 1));
}

int get_rand_y(){
    return (rand() % ((max_height-10) - 0 + 1));
}


/* Main function */
void main() {
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init();
  box_init(max_width, max_height);
  food_init(max_width, max_height, get_rand_x(), get_rand_y());
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */

  clearScreen(BG_COLOR);
  unsigned char blockSize = get_box_size();
  fillRectangle(blockX, blockY, blockSize, blockSize, blockColor);
  draw_border(24);
  draw_border(max_height-12);

  /* Main loop */
  while (1) {
    /* Redraw screen if necessary */
    if (redrawScreen) {
        clearScreen(BG_COLOR);
        fillRectangle(blockX, blockY, blockSize, blockSize, blockColor);
        drawString5x7(2,2, "UP: S2 | DOWN: S3", COLOR_WHITE, COLOR_BLACK);
        drawString5x7(2,12, "LEFT: S1 | RIGHT: S4", COLOR_WHITE, COLOR_BLACK);
        char score_str[10];
        itoa(score, score_str, 10);
        drawString5x7(2,max_height-8, score_str, COLOR_WHITE, COLOR_BLACK);
        draw_border(24);
        draw_border(max_height-12);
        fillRectangle(get_x(), get_y(), get_food_size(), get_food_size(), COLOR_RED);
        redrawScreen = 0;
    }

    if (box_col(blockX, blockY, get_x(), get_y(), blockSize)) {
        score++;
        buzzer_set_period(2000);
        spawn_food(get_rand_x(), get_rand_y());
    }
    
    state();

    /* Turn off LED and enter low power mode */
    P1OUT &= ~LED;
    or_sr(0x10);

    /* Turn on LED when waking up */
    P1OUT |= LED;
  }
}

/* Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
