/******************************************/
/*           广州旭东阪田电子有限公司     */
/*Project:     日产吹气装置               */
/*Guest:                                  */
/*Name:             main.c                */
/*Mcu chip:         Atmega64              */
/*Main clock:       外部晶体11.0592MHz    */
/*Rtc clock:                              */
/*Author:                                 */
/*Create date:      2018.05.24            */
/*Design date:                            */
/*Complete date:                          */
/******************************************/
#include <iom64v.h>
#include <stdio.h>
#include <macros.h>
#include <port.h>
#include <default.h>
#include <delay.h>
#include <beep.h>
#include <EEPROM.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


uchar key_now = 0;
uchar key_old = 0;
uchar key_code = 0;
uchar key_cnt = 0;
uchar count = 0;

#define KEY_COUNTER 10

char *isRunning = "false";
char *allowRun = "false";
//char* allowNext = "false";
void run(void)
{
    int i = 0;
    if(isRunning == "false")
    {
        while(i < 8)
        {
            set_bit(PORTD, bell);
            delay_nms(500);
            clr_bit(PORTD, bell);
            delay_nms(100);
			i++;
        }
		allowRun = "false";
		isRunning = "true";
    }
}

//定时中断函数(自动检测用)
#pragma interrupt_handler timer1_count_isr:15
void timer1_count_isr(void)
{
    TCNT1 = 65536 - CRYSTAL / 8 / 2 * 0.5; //0.5s定时
	if(allowRun == "true")
	{
	    if((PINC & (1 << 0)) == 0)
		{
		    return;
		}
	}
	if(isRunning == "true") 
	{
	    if((PINC & (1 << 0)) != 0)
		{
		    isRunning = "false";
		}
	}
	
}
//定时器1初始化
void init_TIMER1_OVF(void)
{
    TCCR1B = 0x02; //8分频
    TCNT1 = 65536 - CRYSTAL / 8 / 2 * 0.5; //0.5s定时
    TIMSK |= (1 << TOIE1); //定时器使能
    SREG = 0x80;    //全局使能中断
}
/***************系统初始化函数 start ***********/
void init_cpu(void)
{
    EIMSK = 0x00; //屏蔽INT0~INT1的所有外部中断
    clr_bit(SFIOR, PUD); //设置输入上拉电阻有效
    DDRA = 0xff; //1是输出，0是输入
    PORTA = 0x00; //控制PINC与PINF通路切换

    DDRB = 0xff; //1是输出，0是输入
    PORTB = 0x00;

    DDRC = 0x00;
    PORTC = 0xff;

    DDRD  = 0x4c; //PIND0/1/4/5
    PORTD = 0xb3;  //外接上拉，按键带上拉
    DDRE = 0xfe; //RXD0输入，且上拉有效
    PORTE = 0x01; //TXD0输出

    DDRF = 0xff; //PINF全是输出
    PORTF = 0x00;

    DDRG = 0xff;
    PORTG = 0x00; //PING口全输出

    SEI();

    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flagerr = 0;
}
/***************系统初始化函数 end ***********/
//按键处理函数===============================================
void key_scan(void)
{
    if((flag1 && (1 << keyprq_flag1)) == 0)  //如果没有按键按下
    {
        if((PINC & (1 << 0)) == 0) //启动测试按键
        {
            key_now = 1;
        }
        else
        {
            key_now = 0;
            key_old = 0;
            key_code = 0;
        }
        if(key_now != 0)
        {
            if(key_now != key_code)
            {
                key_code = key_now;
                key_cnt = 0;
            }
            else
            {
                key_cnt++;
                if(key_cnt >= KEY_COUNTER)
                {
                    set_bit(flag1, keyprq_flag1);
                }
            }
        }
    }
}
//按键处理函数===============================================
void key_process(void)
{
    if((flag1 & (1 << keyprq_flag1)) != 0)
    {
        clr_bit(flag1, keyprq_flag1);
        if(key_code == key_old)
        {
            ; //do nothing~
        }
        else
        {
            key_old = key_code;
            set_bit(flag1, keyeff_flag1);  //按键有效
        }
        if((flag1 & (1 << keyeff_flag1)) != 0)
        {
            clr_bit(flag1, keyeff_flag1);
            switch(key_old)
            {
            case 1:
            {
			    allowRun = "true";
				run();
            } break;
            default:
                break;
            }
        }
    }
}
/***************主函数 start *******************/
void main(void)
{
    init_cpu();    //初始化CPU
    init_TIMER1_OVF();
    while(1)
    {
        key_scan();
        key_process();
        delay_nms(10);
    }
}