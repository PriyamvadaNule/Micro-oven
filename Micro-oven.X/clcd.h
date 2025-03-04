#ifndef clcd
#define	clcd

#define _XTAL_FREQ 20000000  // freqency 20M hz

#define CLCD_DATA_DDR TRISD    //direction registers
#define CLCD_RS_DDR   TRISE2
#define CLCD_EN_DDR   TRISE1


#define CLCD_DATA PORTD       // I/O registers
#define CLCD_RS   RE2 
#define CLCD_EN   RE1

#define INST_MODE 0           // Modes
#define DATA_MODE 1

#define HI  1
#define LOW 0

#define LINE1(x) (0x80 + x)   // CLCD lines
#define LINE2(x) (0xC0 + x)
#define LINE3(x) (0x90 + x)
#define LINE4(x) (0xD0 + x)

#define EIGHT_BIT 0x33 
#define FOUR_BIT  0x02
#define CLEAR_SCREEN        0x01
#define DISP_ON_CURSOR_OFF  0x0C

#define BAR           0xFF
#define DEGREE        0xDF


void init_clcd(void);
void clcd_ch(const char data, unsigned char addr);
void clcd_print(const char *str, unsigned char addr);
void clcd_write(unsigned char byte, unsigned char mode);

#endif