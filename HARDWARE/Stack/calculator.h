#ifndef __CAL_H
#define __CAL_H

#include "sys.h"

typedef struct Data_Struct //����ջ
{
    float inf[100];
    int top;
} Data;

typedef struct Symbol_Struct //������ջ
{
    char inf[100];
    int top;
} Sym;

/***********************Define ADT****************************/
void Init_Data_Struct(Data *data);  //��ʼ������ջ
void Init_Sym_Struct(Sym *sym);     //��ʼ��������ջ
int Push_Data(Data *data,float num);//����ѹ��ջ
int Push_Sym(Sym *sym, char op);    //��������ջ
float Pop_Data(Data *data);         //���ݳ�ջ
char Pop_Sym(Sym *sym);             //��������ջ
float Read_Data(Data *data);        //������ջ
char Read_Sym(Sym *sym);            //��������ջ
int Judge(char ch);                 //�ж��Ƿ�Ϊ������
float Calculate(float num1,char op,float num2); //���м���
char Op_Compare(char op1,char op2); //�������������ȼ��Ƚ�
float Output(void);                 //���ռ������

#endif

