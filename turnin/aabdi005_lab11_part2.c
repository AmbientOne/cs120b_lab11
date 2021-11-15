/*	Author: Abdirahman Abdi
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *  Demo: https://youtu.be/sQBVbEvQe4s
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <io.h>
#include "timer.h"
#include "scheduler.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


static task LCDTask;
task *tasks[] = { &LCDTask };
const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
const char start = -1;
unsigned short i;

enum States {LCD};
unsigned char pos = 0x00;
unsigned char text[52]={'C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' ',' ',' ', ' ', ' ',' '};
unsigned char display[16];


int Tick(int state){
	switch(state){
		case LCD:
			state = LCD;
			break;
		default:
			state = LCD;
			break;
	}
	switch(state){
		case LCD:
			for (int i = 0; i < 16; i++){
				display[i] = text[(i + pos)%52];
			}
			LCD_DisplayString(1, display);
			pos = ((pos + 1)%52);
			break;
		default:
			break;
	}
	return state;
}

void funct(){
     for (i = 0; i < numTasks; i++ ) {
            if (tasks[i]->elapsedTime == tasks[i]->period) {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 0;
            }
            tasks[i]->elapsedTime += 1;
	}
    while(!TimerFlag);
    TimerFlag = 0;
     
}


int main(void) {
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    LCDTask.state = start;
    LCDTask.period = 20;
    LCDTask.elapsedTime = LCDTask.period;
    LCDTask.TickFct = &Tick;

    TimerSet(20);
    TimerOn();
    LCD_init();


    while (1) {
        funct();
    }
    return 0;
}
