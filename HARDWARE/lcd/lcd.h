#ifndef __LCD_H
#define __LCD_H	 
#include "sys.h"

//1602Һ��ָ��/����ѡ������
#define	LCD_RS_Set()	GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define	LCD_RS_Clr()	GPIO_ResetBits(GPIOC, GPIO_Pin_13)

//1602Һ����д����
#define	LCD_RW_Set()	GPIO_SetBits(GPIOC, GPIO_Pin_14)
#define	LCD_RW_Clr()	GPIO_ResetBits(GPIOC, GPIO_Pin_14)

//1602Һ��ʹ������
#define	LCD_EN_Set()	GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define	LCD_EN_Clr()	GPIO_ResetBits(GPIOC, GPIO_Pin_15)


#define	DATAOUT(x)	GPIO_Write(GPIOA, x)

void GPIO_Configuration(void);
void LCD1602_Wait_Ready(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void Clear_Screen(void);
void LCD1602_Set_Cursor(u8 x, u8 y);
void Print(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);

#endif
