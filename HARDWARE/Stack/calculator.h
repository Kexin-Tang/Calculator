#ifndef __CAL_H
#define __CAL_H

#include "sys.h"

typedef struct Data_Struct //数据栈
{
    float inf[100];
    int top;
} Data;

typedef struct Symbol_Struct //操作符栈
{
    char inf[100];
    int top;
} Sym;

/***********************Define ADT****************************/
void Init_Data_Struct(Data *data);  //初始化数据栈
void Init_Sym_Struct(Sym *sym);     //初始化操作符栈
int Push_Data(Data *data,float num);//数据压入栈
int Push_Sym(Sym *sym, char op);    //操作符入栈
float Pop_Data(Data *data);         //数据出栈
char Pop_Sym(Sym *sym);             //操作数出栈
float Read_Data(Data *data);        //读数据栈
char Read_Sym(Sym *sym);            //读操作数栈
int Judge(char ch);                 //判断是否为操作符
float Calculate(float num1,char op,float num2); //进行计算
char Op_Compare(char op1,char op2); //两个操作数优先级比较
float Output(void);                 //最终计算输出

#endif

