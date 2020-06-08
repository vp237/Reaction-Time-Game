#include <MK64F12.h>
#include "utils.h"
#include <stdlib.h> 

/*----------------------------------------------------------------------------
  Function that initializes switches
 *----------------------------------------------------------------------------*/

void Switch_Initialize(void) {
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTC_MASK; /* Enable Clock to Port A and C */ 
	PORTA->PCR[4] = PORT_PCR_MUX(1); /* Pin PTA4 (SW3) is GPIO */
	PORTC->PCR[6] |= PORT_PCR_MUX(1); /* Pin PTC6 (SW2) is GPIO */
	PORTA->PCR[4] |= PORT_PCR_IRQC(1001); /* Connect SW3 as interrupt on rising edge */
	PORTC->PCR[6] |= PORT_PCR_IRQC(1001); /* Connect SW2 as interrupt on rising edge */
	PTA->PDDR &= ~GPIO_PDDR_PDD(1<<4); /* Assign SW3 to input */
	PTC->PDDR &= ~GPIO_PDDR_PDD(1<<6); /* Assign SW2 to input */
	NVIC_EnableIRQ(PORTA_IRQn); /* Enable interrupts for SW3 */
	NVIC_EnableIRQ(PORTC_IRQn); /* Enable interrupts for SW2 */
	NVIC_SetPriority(PORTC_IRQn, 0); /* Set Priority for Port C IRQ Handler (SW2) (Highest Priority) */
	NVIC_SetPriority(PORTA_IRQn, 1); /* Set Priority for Port A IRQ Handler (SW3) */
}	

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void LED_Initialize(void) {
  SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK; /* Enable Clock to Port B & E */ 
  PORTB->PCR[22] |= PORT_PCR_MUX(1); /* Pin PTB22 is GPIO */
  PORTB->PCR[21] |= PORT_PCR_MUX(1); /* Pin PTB21 is GPIO */
  PORTE->PCR[26] |= PORT_PCR_MUX(1); /* Pin PTE26  is GPIO */
  PTB->PDOR = (1 << 21 | 1 << 22 ); /* Switch Red/Green LED off  */
  PTB->PDDR = (1 << 21 | 1 << 22 ); /* Enable PTB18/19 as Output */
  PTE->PDOR = 1 << 26; /* Switch Blue LED off  */
  PTE->PDDR = 1 << 26; /* Enable PTE26 as Output */
}

/*----------------------------------------------------------------------------
  Function that toggles the Red LED
 *----------------------------------------------------------------------------*/

void LEDRed_Toggle(void) {
	PTB->PTOR = 1 << 22; /* Red LED Toggle */
}

/*----------------------------------------------------------------------------
  Function that toggles the Blue LED
 *----------------------------------------------------------------------------*/
void LEDBlue_Toggle(void) {
	PTB->PTOR = 1 << 21; /* Blue LED Toggle */
}

/*----------------------------------------------------------------------------
  Function that toggles the Green LED
 *----------------------------------------------------------------------------*/
void LEDGreen_Toggle(void) {
	PTE->PTOR = 1 << 26; /* Green LED Toggle */
}

/*----------------------------------------------------------------------------
  Function that toggles the Red, Blue, Green LEDs (to produce White)
 *----------------------------------------------------------------------------*/
void LEDWhite_Toggle(void) {
	PTB->PTOR = (1 << 22) | (1 << 21) ; /* Red and Blue LEDs Toggle */
	PTE->PTOR = 1 << 26; /* Green LED Toggle */
}

/*----------------------------------------------------------------------------
  Function that turns on Red and Green LEDs (making Yellow)
 *----------------------------------------------------------------------------*/
void LEDYellow_On(void) {
	/* Save and disable interrupts (for atomic LED change) */
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
  PTB->PCOR   = 1 << 22; /* Red LED On*/
  PTB->PSOR   = 1 << 21; /* Blue LED Off*/
  PTE->PCOR   = 1 << 26; /* Green LED On*/
	/* Restore interrupts */
	__set_PRIMASK(m);
}

/*----------------------------------------------------------------------------
  Function that turns on Red and Blue LEDs (making Purple)
 *----------------------------------------------------------------------------*/
void LEDPurple_On(void) {
	/* Save and disable interrupts (for atomic LED change) */
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
  PTB->PCOR   = 1 << 22; /* Red LED On*/
  PTB->PCOR   = 1 << 21; /* Blue LED On*/
  PTE->PSOR   = 1 << 26; /* Green LED Off*/
	/* Restore interrupts */
	__set_PRIMASK(m);
}

/*----------------------------------------------------------------------------
  Function that turns on Blue and Green LEDs (making Cyan)
 *----------------------------------------------------------------------------*/
void LEDCyan_On(void) {
	/* Save and disable interrupts (for atomic LED change) */
	uint32_t m;
	m = __get_PRIMASK();
	__disable_irq();
  PTB->PSOR   = 1 << 22; /* Red LED Off*/
  PTB->PCOR   = 1 << 21; /* Blue LED On*/
  PTE->PCOR   = 1 << 26; /* Green LED On*/
	/* Restore interrupts */
	__set_PRIMASK(m);
}

/*----------------------------------------------------------------------------
  Function that generates a random time for delay (easy round)
 *----------------------------------------------------------------------------*/
int rand_generator_easy(void) {
	int lower = 2000000/2;
	int upper = 2000000;
	return (rand() % (upper - lower + 1)) + lower; 
}	

/*----------------------------------------------------------------------------
  Function that generates a random time for delay (medium round)
 *----------------------------------------------------------------------------*/
int rand_generator_medium(void) {
	int lower = 2000000/4;
	int upper = 2000000/2;
	return (rand() % (upper - lower + 1)) + lower; 
}

/*----------------------------------------------------------------------------
  Function that generates a random time for delay (hard round)
 *----------------------------------------------------------------------------*/
int rand_generator_hard(void) {
	int lower = 2000000/8;
	int upper = 2000000/4;
	return (rand() % (upper - lower + 1)) + lower; 
}


/*----------------------------------------------------------------------------
  Function that generates a delay for game (easy round)
 *----------------------------------------------------------------------------*/

void delayeasy(void) {
	for (int j = 0; j < rand_generator_easy(); j++);
}

/*----------------------------------------------------------------------------
  Function that generates a delay for game (medium round)
 *----------------------------------------------------------------------------*/

void delaymedium(void) {
	for (int j = 0; j < rand_generator_medium(); j++);
}

/*----------------------------------------------------------------------------
  Function that generates a delay for game (hard round)
 *----------------------------------------------------------------------------*/

void delayhard(void) {
	for (int j = 0; j < rand_generator_hard(); j++);
}

/*----------------------------------------------------------------------------
  Function that generates a delay in between for LEDs
 *----------------------------------------------------------------------------*/

void delaybetween(void){
	for (int j = 0; j < 1000000; j++);
}

