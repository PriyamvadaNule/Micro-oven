/*
 * File:   keypad.c
 * Author: Harsh
 *
 * Created on 25 September, 2023, 8:24 PM
 */


#include <xc.h>
#include"matrix_keypad.h"

void init_matrix(void)
{
    COL_DDR = COL_DDR | 0x07 ;
    ROWS_DDR = ROWS_DDR & 0xF0 ;
    nRBPU = 0;
    
    R1 = HI ;
    R2 = HI;
    R3 = HI;
    R4 = HI;
    
}

static unsigned char scan_key(void)
{
    int i;
    
    R1 = LOW;
    R2 = HI;
    R3 = HI;
    R4 = HI;   
    
    for (i = 100; i--; );
    
    if (C1 == LOW)
    {
        return 1;
    }
    else if (C2 == LOW)
    {
        return 2;
    }
    else if (C3 == LOW)
    {
        return 3;
    }
    
    R1 = HI;
    R2 = LOW;
    R3 = HI;
    R4 = HI;   
    
   for (i = 100; i > 0; i--)
       ;
    
    if (C1 == LOW)
    {
        return 4;
    }
    else if (C2 == LOW)
    {
        return 5;
    }
    else if (C3 == LOW)
    {
        return 6;
    }
    
    R1 = HI;
    R2 = HI;
    R3 = LOW;
    R4 = HI;   

    for (i = 100; i > 0; i--);
    
    if (C1 == LOW)
    {
        return 7;
    }
    else if (C2 == LOW)
    {
        return 8;
    }
    else if (C3 == LOW)
    {
        return 9;
    }
    
    R1 = HI;
    R2 = HI;
    R3 = HI;
    R4 = LOW;   

    for (i = 100; i > 0; i--);
    
    if (C1 == LOW)
    {
        return '*';
    }
    else if (C2 == LOW)
    {
        return 0;
    }
    else if (C3 == LOW)
    {
        return '#';
    }
    
    return RELEASED;
    
}

unsigned char read_key(unsigned char MODE )
{
    static unsigned int once = 1;
    unsigned char key;
    key = scan_key();
    if(MODE == LEVEL)
    {
        return key;
    }
    else
    {
        if(key!=RELEASED && once)
        {
            once = 0;
            return key;
        }
        else if(key == RELEASED)
        {
            once = 1;
        }
        
    }
    return RELEASED;
}