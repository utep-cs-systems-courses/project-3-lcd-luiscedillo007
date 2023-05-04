#include <msp430.h>
#include "switches.h"
#include "state_machine.h"

char switch_state_down;

static char switch_update_interrupt_sense()
{
    /* update switch interrupt sense to detect changes from current buttons */
    char p2val = P2IN;
    P2IES |= (p2val & SWITCHES);  /* if switch up, sense down */
    P2IES &= (p2val | ~SWITCHES); /* if switch down, sense up */
    return p2val;
}

void switch_init() 
{
    P2REN |= SWITCHES;		/* enables resistors for switches */
    P2IE |= SWITCHES;		/* enable interrupts from switches */
    P2OUT |= SWITCHES;		/* pull-ups for switches */
    P2DIR &= ~SWITCHES;		/* set switches' bits for input */
    P2IES |= SWITCHES;

    switch_interrupt_handler();
}

void switch_interrupt_handler() 
{
    char p2val = switch_update_interrupt_sense();
    switch_state_down = (p2val & SWITCHES) ^ SWITCHES; 
    state();
}

