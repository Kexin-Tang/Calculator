#include "key.h"
#include "delay.h"

extern int over;

void Key_Init()
{
    GPIO_InitTypeDef    KEY;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    /*PB5~9 Ϊ�������*/
    KEY.GPIO_Mode=GPIO_Mode_Out_PP;
    KEY.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    KEY.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&KEY);
    
    /*PB12~15 Ϊ��������*/
    KEY.GPIO_Mode=GPIO_Mode_IPU;
    KEY.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    KEY.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&KEY);
}


/*
*           PB12    PB13    PB14    PB15
*            0       1       2       3      PB5
*            4       5       6       7      PB6
*            8       9       10      11     PB7
*            12      13      14      15     PB8
*            16      17      18      19     PB9
*/
int num;
int flag=0;
extern int ce;
void Key_Scan()
{
    u8 cnt=0;
    flag = 0;
    if( (GPIO_ReadInputData(GPIOB)&0xf000) != 0xf000)   //��ȡIPU���ŵĵ�ƽ����������ű�������˵���а���������
    {
        delay_ms(30);
        if( (GPIO_ReadInputData(GPIOB)&0xf000) != 0xf000)
        {
            /*�����⵽�������£���ʼѭ��ɨ��PB3~7*/
            GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
            GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            switch(GPIO_ReadInputData(GPIOB)&0xf000)
            {
                case 0x7000:{num=0;  break;}
                case 0xb000:{num=1;  break;}
                case 0xd000:{num=2; ce=1;  break;}
                case 0xe000:{num=3;  break;}
                default:    {num=num;break;}
            }
            
            GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
            GPIO_ResetBits(GPIOB,GPIO_Pin_6);
            switch(GPIO_ReadInputData(GPIOB)&0xf000)
            {
                case 0x7000:{num=4;  break;}
                case 0xb000:{num=5;  break;}
                case 0xd000:{num=6;  break;}
                case 0xe000:{num=7;  break;}
                default:    {num=num;break;}
            }
            
            GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_9);
            GPIO_ResetBits(GPIOB,GPIO_Pin_7);
            switch(GPIO_ReadInputData(GPIOB)&0xf000)
            {
                case 0x7000:{num=8;  break;}
                case 0xb000:{num=9;  break;}
                case 0xd000:{num=10;  break;}
                case 0xe000:{num=11;  break;}
                default:    {num=num;break;}
            }
            
            GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9);
            GPIO_ResetBits(GPIOB,GPIO_Pin_8);
            switch(GPIO_ReadInputData(GPIOB)&0xf000)
            {
                case 0x7000:{num=12;  break;}
                case 0xb000:{num=13;  break;}
                case 0xd000:{num=14;  break;}
                case 0xe000:{num=15;  break;}
                default:    {num=num;break;}
            }
            
            GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
            GPIO_ResetBits(GPIOB,GPIO_Pin_9);
            switch(GPIO_ReadInputData(GPIOB)&0xf000)
            {
                case 0x7000:{num=16;  break;}
                case 0xb000:{num=17;  break;}
                case 0xd000:{num=18;  break;}
                case 0xe000:{num=19; over=1;  break;}
                default:    {num=num;break;}
            }
            
            GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
            GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);
            
            while( (cnt<50) && ((GPIO_ReadInputData(GPIOB)&0xf000)!=0xf000) )
            {
                cnt++;
                delay_ms(10);
            }
            flag = 1;
        }
    }
}


//void exit15_12_init()
//{
//    NVIC_InitTypeDef NVIC_InitStructure;
//    EXTI_InitTypeDef EXTI_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
//    
//    //PB12~15 ΪIPU����NVIC
//    NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    //  PB12 �ж���
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
//    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//    
//    //  PB13 �ж���
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
//    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//    
//    //  PB14 �ж���
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
//    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//    
//    //  PB15 �ж���
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);
//    EXTI_InitStructure.EXTI_Line = EXTI_Line15;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//}


///*�жϷ�����*/
//void EXTI15_10_Handler()
//{
//    
//}
