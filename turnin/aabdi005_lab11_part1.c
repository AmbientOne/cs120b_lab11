/*	Author: Abdirahman Abdi
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <io.h>
#include "keypad.h"
#include "timer.h"
#include "scheduler.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

static task keypadTask;
task *tasks[] = { &keypadTask };
const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
const char start = -1;
unsigned short i;

enum States {Keypad};
unsigned char keypad = 0x00;
unsigned char input = 0x00;
int Tick(int state){
	input = GetKeypadKey();
	switch(state){
		case Keypad:
			state = Keypad;
			break;
		default:
			state = Keypad;
			break;
	}
	switch(state){
		case Keypad:
			switch(input){
				case '\0':
					keypad = 0x1F;
					break;
				case '1':
					keypad = 0x01;
					break;
				case '2':
					keypad = 0x02;
					break;
				case '3':
					keypad = 0x03;
					break;
				case '4':
					keypad = 0x04;
					break;
				case '5':
					keypad = 0x05;
					break;
				case '6':
					keypad = 0x06;
					break;
				case '7':
					keypad = 0x07;
					break;
				case '8':
					keypad = 0x08;
					break;
				case '9':
					keypad = 0x09;
					break;
				case 'A':
					keypad = 0x0A;
					break;
				case 'B':
					keypad = 0x0B;
					break;
				case 'C':
					keypad = 0x0C;
					break;
				case 'D':
					keypad = 0x0D;
					break;
				case '*':
					keypad = 0x0E;
					break;
				case '0':
					keypad = 0x00;
					break;
				case '#':
					keypad = 0x0F;
					break;
				default:
					keypad = 0x1B;
					break;
			}
			PORTB = keypad;
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
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;

    keypadTask.state = start;
    keypadTask.period = 50;
    keypadTask.elapsedTime = keypadTask.period;
    keypadTask.TickFct = &Tick;

    TimerSet(50);
    TimerOn()

    while (1) {
		funct();
    }

    return 0;
}
