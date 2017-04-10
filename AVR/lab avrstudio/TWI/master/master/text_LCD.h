
#ifndef TEXT_LCD_H_
#define TEXT_LCD_H_
#include <avr/io.h>
// uses mode 4bit and PORTB made data gate and control gate

char read_2Nib(void);
void write_2Nib(unsigned char data);
void init_lcd(void);
void cursor_home(void);
void movecursor(uint8_t dong,uint8_t cot);
void clear_lcd(void);
void wait_lcd(void); 
void putchar_lcd(unsigned char data);
void printnumber_lcd(unsigned int number);
int  count_number(unsigned int number);
void putstr_lcd(unsigned char *str, unsigned int lenght);
#endif /* TEXT_LCD_H_ */