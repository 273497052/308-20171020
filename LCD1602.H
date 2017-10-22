#ifndef __LCD1602_H__
#define __LCD1602_H__

#define u8 unsigned char 
#define u16 unsigned int

void delay(int x);
int LCD_1602_Read();
void LCD_1602(int com,Data);
void LCD_1602_inti();
void LCD_ShowString(u8 x,u8 y,const u8 *p);

#endif