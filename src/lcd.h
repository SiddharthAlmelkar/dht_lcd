#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void lcd_init(void);
void scmd(uint8_t cmd);
void sdata(uint8_t bit);
void lcd_print(const char *str);
void lcd_printint(uint8_t val);

#endif
