#include<stdio.h>
#include<stdlib.h>
#include "calculator.h"
#include "key.h"
#include "lcd.h"
#include "delay.h"

#define wrong -99    //定义错误
#define right 99     //定义正确

extern int flag,num;
extern float ans;

typedef struct TAB{
        int number;
        char ch;
}Book;

extern Book book[20];
extern char enter[1000];

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


/***********************Implement ADT*************************/
//初始化数据栈
void Init_Data_Struct(Data *data)
{
    data->top = -1;
}

//初始化操作符栈
void Init_Sym_Struct(Sym *sym)
{
    sym->top = -1;
}

//数据压入栈
int Push_Data(Data *data,float num)
{
    if(data->top == 100)
        return wrong;   //出现了溢出
    data->top ++;
    data->inf[data->top] = num;
    return right;
}

//操作符入栈
int Push_Sym(Sym * sym,char op)
{
    if(sym->top == 100)
        return wrong;
    sym->top ++;
    sym->inf[sym->top] = op;
    return right;
}

//数据出栈
float Pop_Data(Data *data)
{
    float num;
    num = data->inf[data->top];
    data->top --;
    return num;
}

//操作数出栈
char Pop_Sym(Sym * sym)
{
    char op;
    op = sym->inf[sym->top];
    sym->top--;
    return op;
}

//读数据栈
float Read_Data(Data * data)
{
    return data->inf[data->top];
}

//读操作数栈
char Read_Sym(Sym *sym)
{
    return sym->inf[sym->top];
}

//判断是否为操作符
int Judge(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '=' || ch == '~' || ch == '#')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//进行计算
float Calculate(float num1, char op, float num2)
{
    float res;  //结果
    switch(op)
    {
        case '+':
        {
            res = num1 + num2;      break;
        }

        case '-':
        {
            res = num1 - num2;      break;
        }

        case '*':
        {
            res = num1 * num2;      break;
        }

        case '/':
        {
            if(!num2)   //不能除0
            {
                return wrong;
            }
            res = num1 / num2;      break;
        }
    }
    return res;
}

/*********************************************
*   op1     操作符栈顶操作符                  
*   op2     与栈顶比较的操作符，即新取的操作符
*********************************************/
//操作符优先级比较
char Op_Compare(char op1,char op2)
{
    switch(op2)
    {
        case '(':                   //(一般都要直接压入栈
            if(op1 == ')')
            {
                return wrong;
            }
            else
            {
                return '<';
            }

        case '+':
        case '-':                   //+、-是倒数第二优先级
            return (op1 == '(' || op1 == '=') ?  '<' : '>';
        
        case '*':
        case '/':                   //*、/有较高的优先级
            return (op1 == '*' || op1 == '/' || op1 == ')') ? '>' : '<';
        
        case '=':                   //出现=的情况即压入一个），而要一直Pop符号栈直到出现（
            {
                switch(op1)
                {
                    case '=':return '=';
                    case '(':return wrong;
                    default :return '>';
                }
            }

        case ')':
            {
                switch(op1)
                {
                    case '(':return '=';
                    case '=':return wrong;
                    default :return '>';
                }
            }
    }
}



char ch;    //为什么ch一定要放成全局变量？？？不科学啊？？？
//进行最终的出栈入栈和计算工作
float Output()
{
    int i=0;
    Data data;  //声明两个栈
    Sym  symbol;
    int cnt;                //记录输入的个数
    float num1,num2;        //num为操作数


    Init_Data_Struct(&data);
    Init_Sym_Struct(&symbol);
    
    Push_Sym(&symbol,'='); 
    
    ch = enter[i];
    
    while((symbol.top != -1))
    {
        if(Judge(ch) == 0)     //即如果输入的为数字，则不断接收直到出现操作符，然后把数据atof存入数据栈
        {
            char *str = (char *)malloc(sizeof(char) * 20); //用于存放键盘输入的数据
            do
            {
                *str = ch;
                str++;
                cnt++;
                i++;
                ch = enter[i];
            } while (Judge(ch) == 0);
            *str = '\0';    //插入\0来标志输入的结束
            str = str-cnt;
            Push_Data(&data,atof(str));
            free(str);
            cnt = 0;
        }
        
        else if(ch == '#')  //如果输入ans
        {
            Push_Data(&data,ans);
            i++;
            ch=enter[i];
        }

        else                    //如果输入为操作符，则判断优先级来控制出入栈
        {
            switch(Op_Compare(symbol.inf[symbol.top],ch))
            {
                case '>':
                {
                    num2=Pop_Data(&data);   //由于先入后出，所以先取出的是num2！！
                    num1=Pop_Data(&data);
                    num1=Calculate(num1,Pop_Sym(&symbol),num2);
                    if(num1 == wrong)
                    {
                        Clear_Screen();
                        Print(0,0,"Error");
                        delay_ms(1000);
                        return wrong;
                    }
                    else
                        Push_Data(&data,num1);    //把计算的值压入栈
                    //此时不要getchar()，因为弹出栈顶后还要比较新的栈顶的优先级
                    break;
                }
                case '<':
                {
                    Push_Sym(&symbol,ch);
                    i++;
                    ch = enter[i];
                    break;
                }
                case '=':
                {
                    Pop_Sym(&symbol);      //出现=是因为栈内有（，而匹配到）时弹出（并收取下一个输入
                    i++;
                    ch = enter[i];
                    break;
                }
                
                case wrong:
                {
                    return wrong;
                }
            }
        }
    }
    return data.inf[data.top];
}
