/* 
 * File:   main.h
 * Author: Harsh
 *
 * Created on 15 April, 2020, 4:36 PM
 */

#ifndef keypad
#define	keypad

#define ROWS_DDR  TRISD
#define COL_DDR   TRISB

#define R1 RD3
#define R2 RD2
#define R3 RD1
#define R4 RD0

#define C1 RB0
#define C2 RB1
#define C3 RB2

#define STATE 1
#define LEVEL 0

#define HI 1
#define LOW 0


#define RELEASED 0xFF

void init_matrix(void);
unsigned char read_key(unsigned char MODE );

#endif