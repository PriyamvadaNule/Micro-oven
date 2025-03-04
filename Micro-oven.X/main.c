/*
 * File:   main.c
 * Author: Harsh
 *
 * Created on 20 September, 2023, 7:35 PM
 */


#include "main.h"

#pragma config WDTE= OFF //watchdog timer off

unsigned char sec = 0,min = 0 , flag = 0 ;
int operation_flag = POWER_SCREEN; // power on screenr

 void init_config(void) {
    init_clcd();
    init_matrix();
    FAN_DDR = 0;
    FAN = 0;
    BUZZER_DDR = 0;
    BUZZER = 0;
    init_timer2();
    GIE = 1;
    PEIE = 1;
}

 
void main(void) {

    init_config();
    unsigned char key;
    int reset_flag;
    while(1)
    {
        key = read_key(STATE);
        if(operation_flag == MENU)
        {
        //SW1 is pressed 
        if (key == 1)
        {
            operation_flag = MICRO_MODE; //mode 1
            reset_flag = RESET_MODE;
            clear_screen();
            __delay_ms(250);
            clcd_print("  POWER = 900W  ",LINE2(0));
            __delay_ms(2000);
            clear_screen();
        }
        
        //SW2 grill mode
        else if(key == 2)
        {
            clear_screen();
            operation_flag = GRILL_MODE;
            reset_flag = RESET_MODE;
 
        }
        
        //SW3 convection mode
        else if(key == 3)
        {
            clear_screen();
            operation_flag = CONVECTION_MODE;
            reset_flag = RESET_MODE;
        }
        
        //SW4 start mode
        else if(key == 4)
        {
            clear_screen();
            sec = 30;
            min = 0;
            FAN = 1;
            TMR2ON = 1;
            operation_flag = TIME_DISPLAY;
        }    
        }
        
        else if(operation_flag == TIME_DISPLAY)
        {
            if(key == 4) //start
            {
                sec = sec + 30;
                if(sec > 59)
                {
                    min++;
                    sec = sec - 60 ;
                }
            }
            
            else if(key == 5) //pause
            {
                operation_flag = PAUSE;
            }
            
            else if(key == 6) //stop 
            {
                operation_flag = STOP;
            }
        }
        
        else if(operation_flag == PAUSE)
        {
            //resume
            if(key == 4)
            {
                FAN = 1;
                TMR2ON = 1;
                operation_flag = TIME_DISPLAY;
            }
        }
        
        
        
        switch(operation_flag)
        {
            case POWER_SCREEN: 
                power_screen();
                operation_flag = MENU; // for next screen
                clear_screen();
                break;
                
            case MENU:
                menu();
                break;
                
            case MICRO_MODE:
                set_time(key,reset_flag);
                break;
                
             case GRILL_MODE:
                set_time(key,reset_flag);
                break;
                
            case CONVECTION_MODE:
                if(flag == 0)
                {
                    set_temp(key,reset_flag);
                    if(flag == 1)
                    {
                        reset_flag = RESET_MODE;
                        continue;
                    }
                }
                else
                {
                    set_time(key,reset_flag);
                }
                
                break;
                
            case TIME_DISPLAY:
                time_screen();
                break;
                
            case PAUSE:
                FAN = 0;
                TMR2ON = 0;
                break;
                      
            case STOP:
                clear_screen();
                FAN = 0;
                TMR2ON = 0;
                operation_flag = MENU;
                break;
               
              
        }
    
        reset_flag = RESET_NOTHING; 
    }
    
    
    return ;
    
}

//clears the screen
void clear_screen(void)
{
    clcd_write(CLEAR_SCREEN,INST_MODE);
    __delay_us(500);
}


// power screen when starts
void power_screen(void)
{
    unsigned char i;
    for(i=0; i<16; i++)
    {
        clcd_ch(BAR,LINE1(i));
      __delay_ms(100);
    }
    clcd_print("  POWERING ON   ",LINE2(0));
    clcd_print(" MICROWAVE OVEN ",LINE3(0));
    for(i=0; i<16; i++)
    {
        clcd_ch(BAR,LINE4(i));
      __delay_ms(100);
    }
    //delay
 __delay_ms(1000);
}


// menu to choose
void menu(void)
{
    clcd_print("1.MICRO",LINE1(0));
    clcd_print("2.GRILL",LINE2(0));
    clcd_print("3.CONVECTION",LINE3(0));
    clcd_print("4.START",LINE4(0));
    
    
}


//mode 1 
void set_time(unsigned char key, int reset_flag)
{
    static unsigned char key_count,blink_pos,blink;
    static int wait;
    
    if(reset_flag == RESET_MODE)
    {
        key_count = 0;
        sec = 0;
        min = 0;
        blink_pos = 0;
        wait = 0;
        blink = 0;
        key = RELEASED;
        clcd_print("SET TIME (MM:SS)",LINE1(0));
        clcd_print("TIME - ",LINE2(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));
    }
   
    if((key != '*') && (key != '#') && (key != RELEASED))
    {
        key_count++;
        
        //to read sec
        if(key_count <=2)
        {
             sec = sec * 10 + key;
             blink_pos = 0;
        }
       //to read min
        else if(key_count>2 && key_count<=4)
        {
            min = min * 10 + key ;
            blink_pos =  1;
        }
    }
    
    else if(key == '*')
    {
        if(blink_pos == 0) // clears sec
        {
            sec = 0;
            key_count = 0;
        }
        else
        {
            min = 0;
            key_count = 2;
        }
    }
    
    else if(key == '#')
    {
        clear_screen();
        operation_flag = TIME_DISPLAY;
        FAN = 1;
        TMR2ON = 1; // timer starts
        
        
    }
    
    if(wait++ == 20) //creates blinking of time
    {
        wait = 0;
        blink = !blink;
        
        //printing sec and min on time screen
    //MIN
    clcd_ch(min/10 + '0', LINE2(7));
    clcd_ch(min%10 + '0', LINE2(8));
    
    clcd_ch(':', LINE2(9));

    //SEC
    clcd_ch(sec/10 + '0', LINE2(10));
    clcd_ch(sec%10 + '0', LINE2(11));  
    }
    
    if (blink)
    {
        switch(blink_pos)
        {
            case 0:                      //sec
                clcd_print("  ",LINE2(10));
                break;
            case 1:                      //min
                clcd_print("  ",LINE2(7));
                break;
        }
    }
        
}


void time_screen(void)
{
    clcd_print("TIME = ",LINE1(0));
     //printing sec and min on time screen
    //MIN
    clcd_ch(min/10 + '0', LINE1(8));
    clcd_ch(min%10 + '0', LINE1(9));
    
    clcd_ch(':', LINE1(10));

    //SEC
    clcd_ch(sec/10 + '0', LINE1(11));
    clcd_ch(sec%10 + '0', LINE1(12));  
    
    clcd_print("4.START/RESUME",LINE2(0));
    clcd_print("5.PAUSE",LINE3(0));
    clcd_print("6.STOP",LINE4(0));
    
    if(sec == 0 && min == 0)
    {
        clear_screen();
        clcd_print("   TIME UP!!   ",LINE2(0));
        BUZZER = 1;
        __delay_ms(3000); // buzzer on for 3sec
        clear_screen();
        FAN = 0;
        BUZZER = 0;
        TMR2ON = 0; //turns off the timer
        operation_flag = MENU;
        
    }
}


void set_temp(unsigned char key, int reset_flag)
{
    static unsigned char key_count,blink,temp;
    static int wait;
    if(reset_flag == RESET_MODE)
    {
        key_count = 0;
        wait = 0;
        blink = 0;
        temp = 0;
        key = RELEASED; 
        
        clcd_print(" SET TEMP( C) ",LINE1(0));
        clcd_ch(DEGREE,LINE1(10));
        clcd_print(" TEMP = ",LINE2(0));
        clcd_print("*:CLEAR  #:ENTER",LINE4(0));  
    }
    
    if (blink)
    {
        clcd_print("   ",LINE2(8));
    }     
    
    if((key != '*') && (key != '#') && (key != RELEASED))
    {
        key_count++;
        
        //to read sec
        if(key_count <=3)
        {
             temp = temp * 10 + key;   
        }
        
    }
    else if(key == '*')
    {
        
            temp = 0;
            key_count = 0;
        }
    
    else if (temp <= MAX_TEMP)
    {
        if(key == '#')
    {
        clear_screen();
        clcd_print("  PRE-HEATING ",LINE1(0));
        clcd_print("TIME REM. = ",LINE3(0));
        sec = 18; //pre heating period
        TMR2ON = 1;
        while(sec != 0)
        {
        clcd_ch((sec/100) + '0',LINE3(12));
        clcd_ch((sec/10)%10 + '0',LINE3(13));
        clcd_ch((sec%10) + '0',LINE3(14)); 
        }
        
        if(sec == 0)
        {
            clear_screen();
            flag = 1;
            TMR2ON = 0;
        }
        
    }
    
    if(wait++ == 20) //creates blinking of time
    {
        wait = 0;
        blink = !blink;
        
        //printing temp on  screen
        clcd_ch((temp/100) + '0',LINE2(8));
        clcd_ch(((temp/10)%10) + '0',LINE2(9));
        clcd_ch( (temp%10) + '0',LINE2(10));
    
    }
    }
    else if(temp > MAX_TEMP )
    {
        temp = 0;
        key_count = 0;
    }
    
     
}