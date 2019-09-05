/******************************************/
/*           ����������������޹�˾     */
/*Project:     �ղ�����װ��               */
/*Guest:                                  */
/*Name:             main.c                */
/*Mcu chip:         Atmega64              */
/*Main clock:       �ⲿ����11.0592MHz    */
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

//��ʱ�жϺ���(�Զ������)
#pragma interrupt_handler timer1_count_isr:15
void timer1_count_isr(void)
{
    TCNT1 = 65536 - CRYSTAL / 8 / 2 * 0.5; //0.5s��ʱ
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
//��ʱ��1��ʼ��
void init_TIMER1_OVF(void)
{
    TCCR1B = 0x02; //8��Ƶ
    TCNT1 = 65536 - CRYSTAL / 8 / 2 * 0.5; //0.5s��ʱ
    TIMSK |= (1 << TOIE1); //��ʱ��ʹ��
    SREG = 0x80;    //ȫ��ʹ���ж�
}
/***************ϵͳ��ʼ������ start ***********/
void init_cpu(void)
{
    EIMSK = 0x00; //����INT0~INT1�������ⲿ�ж�
    clr_bit(SFIOR, PUD); //������������������Ч
    DDRA = 0xff; //1�������0������
    PORTA = 0x00; //����PINC��PINFͨ·�л�

    DDRB = 0xff; //1�������0������
    PORTB = 0x00;

    DDRC = 0x00;
    PORTC = 0xff;

    DDRD  = 0x4c; //PIND0/1/4/5
    PORTD = 0xb3;  //�������������������
    DDRE = 0xfe; //RXD0���룬��������Ч
    PORTE = 0x01; //TXD0���

    DDRF = 0xff; //PINFȫ�����
    PORTF = 0x00;

    DDRG = 0xff;
    PORTG = 0x00; //PING��ȫ���

    SEI();

    flag1 = 0;
    flag2 = 0;
    flag3 = 0;
    flagerr = 0;
}
/***************ϵͳ��ʼ������ end ***********/
//����������===============================================
void key_scan(void)
{
    if((flag1 && (1 << keyprq_flag1)) == 0)  //���û�а�������
    {
        if((PINC & (1 << 0)) == 0) //�������԰���
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
//����������===============================================
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
            set_bit(flag1, keyeff_flag1);  //������Ч
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
/***************������ start *******************/
void main(void)
{
    init_cpu();    //��ʼ��CPU
    init_TIMER1_OVF();
    while(1)
    {
        key_scan();
        key_process();
        delay_nms(10);
    }
}