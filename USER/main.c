/*������󣡳���cannot access memory������Ƿ���Ҫ���������Ϊȫ�ֱ���!!*/
#include "stdlib.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "lcd.h"
#include "sys.h"
#include "key.h"
#include "delay.h"
#include "calculator.h"

#define wrong -99   //�������
#define right 99     //������ȷ

typedef struct TAB{
        int number;
        char ch;
}Book;

Book book[20];

extern int flag;
extern int num;

char enter[100];   //���ڴ������

//�����˼��̵Ĺ���
//  = -> =
//  ~ -> CE
//  # -> ANS
char sym[20]="()~/789*456-123+.0#=";    

//��ʼ����������
void Init(void)
{
    int i=0;
    for(;i<20;i++)
    {
        book[i].number=i;
        book[i].ch=sym[i];
    }
}

float ans=0;  //������һ�εĽ��
int over=0;   //����Ƿ�����=
int ce=0;     //����Ƿ�����CE
char out[20];   //һ��Ҫ���ó�ȫ�ֱ�������
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
        while((over == 0) && ce==0)    //�Ƿ�����=����������δ����CE
        {
            while(flag == 0&&ce==0)
            {
                delay_ms(30);
                Key_Scan();
            }
            flag=0;
            enter[i++]=book[num].ch;
            //����Ӧ������ʾ����Ļ��
            if(book[num].ch == '#')
            {
                //��ʾans
                Print(k++,0,"ans");
                k+=3;
            }
            else
            {
                //������ʾ
                Print(k++,0,&book[num].ch);
            }
        }
        
        //�����������û�а�ce
        if(ce == 0)
        {
            ans = Output();
            for(i=0;i<100;i++)
                enter[i]=0;
            
            if(ans == wrong)
            {
                //�������
                Clear_Screen();
                ans = 0;
            }
            else
            {
                sprintf(out,"%10.6f",ans);
                Print(0,1,out);
            }
            
            k=i=0;
            over = 0;   //Ԥ����һ������
            
            //��һ�������ɺ�����ٰ�����ʼ��һ��ʱҪ����
            while(flag == 0&&ce==0)
            {
                delay_ms(30);
                Key_Scan();
            }
            Clear_Screen();
            flag=0;
            enter[i++]=book[num].ch;
            //����Ӧ������ʾ����Ļ��
            if(book[num].ch == '#')
            {
                //��ʾans
                Print(k++,0,"ans");
                k+=3;
            }
            else if(book[num].ch == '~')
            {
                //����������
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
                //������ʾ
                Print(k++,0,&book[num].ch);
            }
        }
        
        //��������CE
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

