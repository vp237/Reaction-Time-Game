#include <MK64F12.h>
#include "utils.h"
#include <stdlib.h> 

/*----------------------------------------------------------------------------
  Global variables
 *----------------------------------------------------------------------------*/

unsigned int PRESSED = 0; /* Whether a button is pressed or not */
unsigned int FALSE_START = 0; /* Whether a player false-starts */
unsigned int WHITE_PRESSED = 0; /* Whether a player presses the button when the LED turns white */
unsigned int PLAYER1 = 100; /* Player 1's score */
unsigned int PLAYER2 = 100; /* Player 2's score */

/*----------------------------------------------------------------------------
  Setting up the game (LEDs and Buttons)
 *----------------------------------------------------------------------------*/

void game_setup(void) {
	LED_Initialize();
	Switch_Initialize();
}	

/*----------------------------------------------------------------------------
  Displaying the result (winner) of the game
 *----------------------------------------------------------------------------*/

void game_result(void) {
	if (PLAYER1 > PLAYER2) { /* If Player 1 wins */
		LEDPurple_On();
	}
	else if (PLAYER1 < PLAYER2) { /* If Player 2 wins */
		LEDCyan_On();
	}
	else { /* If there is a tie */
		LEDYellow_On();
	}
}	

/*----------------------------------------------------------------------------
  Interrupt Handler for SW3
 *----------------------------------------------------------------------------*/

void PORTA_IRQHandler(void) {
	if (PRESSED == 0) {
		LEDBlue_Toggle();
		delaybetween();
		LEDBlue_Toggle();
		delaybetween();
		if ((FALSE_START == 1) | (WHITE_PRESSED == 1)) {
			PLAYER2 -= 1;
		}	
		else {
			PLAYER2 += 1;
		}	
		PRESSED = 1;
	}	
	PORTA_ISFR = PORT_ISFR_ISF(0x10); /* Clear the interrupt status flag */ 
}

/*----------------------------------------------------------------------------
  Interrupt Handler for SW2
 *----------------------------------------------------------------------------*/

void PORTC_IRQHandler(void) { 
	if (PRESSED == 0) {
		LEDGreen_Toggle();
		delaybetween();
		LEDGreen_Toggle();
		delaybetween();
		if ((FALSE_START == 1) | (WHITE_PRESSED == 1)) {
			PLAYER1 -= 1;
		}
		else {
			PLAYER1 += 1;
		}	
		PRESSED = 1;
	}	
	PORTC_ISFR = PORT_ISFR_ISF(0x40); /* Clear the interrupt status flag */
}	

/*----------------------------------------------------------------------------
  Easy Round (Round 1)
 *----------------------------------------------------------------------------*/

void easy(void) {
	for (int i = 0; i < 2; i++) {
		FALSE_START = 1;
		LEDRed_Toggle();
		delayeasy();
		LEDRed_Toggle();
		FALSE_START = 0;
		delayeasy();
		PRESSED = 0;
	}	
}	

/*----------------------------------------------------------------------------
  Medium Round (Round 2)
 *----------------------------------------------------------------------------*/

void medium(void) {
	for (int i = 0; i < 2; i++) {
		int white_red = rand();
		if (white_red % 2 == 1) {
			WHITE_PRESSED = 0;
			FALSE_START = 1;
			LEDRed_Toggle();
			delaymedium();
			LEDRed_Toggle();
			FALSE_START = 0;
			delaymedium();
		}
		else {
			WHITE_PRESSED = 1;
			LEDWhite_Toggle();
			delaymedium();
			LEDWhite_Toggle();
			delaymedium();
		}
		PRESSED = 0;
	}	
}	

/*----------------------------------------------------------------------------
  Hard Round (Round 3)
 *----------------------------------------------------------------------------*/

void hard(void) {
	for (int i = 0; i < 2; i++) {
		int white_red = rand();
		if (white_red % 2 == 1) {
			WHITE_PRESSED = 0;
			FALSE_START = 1;
			LEDRed_Toggle();
			delayhard();
			LEDRed_Toggle();
			FALSE_START = 0;
			delayhard();
		}
		else {
			WHITE_PRESSED = 0;
			LEDWhite_Toggle();
			delayhard();
			LEDWhite_Toggle();
			delayhard();
		}
		PRESSED = 0;
	}	
}		

/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/

int main(void) {
	game_setup();
	FALSE_START = 1;
	easy();
	FALSE_START = 1;
	medium();
	FALSE_START = 1;
	hard();
	game_result();
	while (1) {}
}	

