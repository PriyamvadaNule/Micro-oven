/*
 * File:   clcd.c
 * Author: Harsh
 *
 * Created on 22 September, 2023, 12:52 PM
 */

#include <xc.h>
#include "clcd.h"

 void clcd_write(unsigned char byte, unsigned char mode)
{
    CLCD_RS = (__bit) mode;
    
    CLCD_DATA = byte & 0xF0; // 0x41 & 0x0F (RD7 to RD4)
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;
    
    CLCD_DATA =  (byte & 0x0F) << 4; //0000 0001 << 4 = PORTD 
    CLCD_EN = HI;
    __delay_us(100);
    CLCD_EN = LOW;
    
    __delay_us(4100); //4.1ms
}

static void init_disp_control(void)
{
    //startup time for clcd
    __delay_us(10);
    
    //startup sequence
    clcd_write(EIGHT_BIT, INST_MODE);
    __delay_us(4100);
    clcd_write(EIGHT_BIT, INST_MODE);
    __delay_us(100);
    clcd_write(EIGHT_BIT, INST_MODE);
    __delay_us(1); 
    
    
    clcd_write(FOUR_BIT,INST_MODE);
    __delay_us(100);
    clcd_write(CLEAR_SCREEN,INST_MODE);
    __delay_us(500);
    clcd_write(DISP_ON_CURSOR_OFF,INST_MODE);
    __delay_us(100);
}

void init_clcd(void)
{
    //set portD as output
    CLCD_DATA_DDR = 0x00;
    
    //set RS and En as output
    CLCD_RS_DDR = 0;
    CLCD_EN_DDR = 0;
    
    init_disp_control();
}

void clcd_ch(const char data, unsigned char addr)
{
    clcd_write(addr,INST_MODE);
    clcd_write(data,DATA_MODE);
}

void clcd_print(const char *str, unsigned char addr)
{
    clcd_write(addr,INST_MODE);
    
    while(*str != '\0')
    {
        clcd_write(*str,DATA_MODE);
        str++;
    }
    
}