#include <msp430.h>
#include "state_machine.h"
#include "switches.h"
#include "box.h"

unsigned char get_state()
{
    if (switch_state_down & SW1)     // bit corresponding to switch -> switch is pressed
    {
        return 1;
    } 
    else if (switch_state_down & SW2) 
    {
        return 2;
    } 
    else if (switch_state_down & SW3) 
    {
        return 3;
    } 
    else if (switch_state_down & SW4) 
    {
        return 4;
    }else {
        return 0;
    }
}

void state() 
{
    unsigned char this_state = get_state();
    unsigned char direct; // 0 down, 1 up, 2 left, 3 right

    switch (this_state) 
    {
        case 1:
            direct = 0;
            break;
        case 2:
            direct = 1;
            break;
        case 3:
            direct = 2;
            break;
        case 4:
            direct = 3;
            break;
        default:
            direct = get_dir();
    }

    set_box_direction(direct);
}
