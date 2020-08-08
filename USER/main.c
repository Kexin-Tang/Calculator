/*奇葩错误！出现cannot access memory，检测是否需要把数组等置为全局变量!!*/
#include "stdlib.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "lcd.h"
#include "sys.h"
#include "key.h"
#include "delay.h"
#include "calculator.h"

#define wrong -99   //定义错误
#define right 99     //定义正确

typedef struct TAB{
        int number;
        char ch;
}Book;

Book book[20];

extern int flag;
extern int num;

char enter[100];   //用于存放输入

//定义了键盘的功能
//  = -> =
//  ~ -> CE
//  # -> ANS
char sym[20]="()~/789*456-123+.0#=";    

//初始化整个键盘
void Init(void)
{
    int i=0;
    for(;i<20;i++)
    {
        book[i].number=i;
        book[i].ch=sym[i];
    }
}

float ans=0;  //保存上一次的结果
int over=0;   //标记是否按下了=
int ce=0;     //标记是否按下了CE
char out[20];   //一定要设置成全局变量！！
int main(void)
{
    int i=0,k=0;
    delay_init();
    Key_Init();
    GPIO_Configuration();
    LCD1602_Init();
    Init();
    
    while(1)
    {
        while((over == 0) && ce==0)    //是否按下了=结束输入且未按下CE
        {
            while(flag == 0&&ce==0)
            {
                delay_ms(30);
                Key_Scan();
            }
            flag=0;
            enter[i++]=book[num].ch;
            //把相应内容显示在屏幕上
            if(book[num].ch == '#')
            {
                //显示ans
                Print(k++,0,"ans");
                k+=3;
            }
            else
            {
                //正常显示
                Print(k++,0,&book[num].ch);
            }
        }
        
        //如果输入正常没有按ce
        if(ce == 0)
        {
            ans = Output();
            for(i=0;i<100;i++)
                enter[i]=0;
            
            if(ans == wrong)
            {
                //如果出错
                Clear_Screen();
                ans = 0;
            }
            else
            {
                sprintf(out,"%10.6f",ans);
                Print(0,1,out);
            }
            
            k=i=0;
            over = 0;   //预备下一次输入
            
            //上一次输出完成后，如果再按键开始下一次时要清屏
            while(flag == 0&&ce==0)
            {
                delay_ms(30);
                Key_Scan();
            }
            Clear_Screen();
            flag=0;
            enter[i++]=book[num].ch;
            //把相应内容显示在屏幕上
            if(book[num].ch == '#')
            {
                //显示ans
                Print(k++,0,"ans");
                k+=3;
            }
            else if(book[num].ch == '~')
            {
                //按下了清屏
                Clear_Screen();
                for(i=0;i<100;i++)
                    enter[i]=0;
                k=i=0;
                over=0;
                flag=0;
                ce=0;
            }
            else
            {
                //正常显示
                Print(k++,0,&book[num].ch);
            }
        }
        
        //否则按下了CE
        else
        {
            Clear_Screen();
            for(i=0;i<100;i++)
                enter[i]=0;
            k=i=0;
            over=0;
            flag=0;
            ce=0;
        }
    }
    
}

