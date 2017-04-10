
#ifndef TEXT_LCD_H_
#define TEXT_LCD_H_
#include <avr/io.h>
// uses mode 4bit and PORTB made data gate and control gate

#define RS   0
#define RW   1
#define EN   2
#define DATA_output  PORTA
#define DATA_input   PINA
#define CTRL         PORTA
#define DDR_DATA     DDRA
#define DDR_CTRL     DDRA

char read_2Nib(void);
void write_2Nib(unsigned char data);
void init_lcd(void);
void cursor_home(void);
void movecursor(uint8_t dong,uint8_t cot);
void clear_lcd(void);
void wait_lcd(void); 
void putchar_lcd(unsigned char data);
//void printnumber_lcd(unsigned int number);
int  count_number(long int number);
void putstr_lcd(unsigned char *str, unsigned int lenght);

#endif /* TEXT_LCD_H_ */