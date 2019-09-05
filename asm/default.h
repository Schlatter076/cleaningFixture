
/******************************************/
/*           ����������������޹�˾     */
/*Project:      FCT��������               */
/*Guest:                                  */
/*Name:             default.h             */
/*Mcu chip:         Atmega64              */
/*Main clock:       �ⲿ����11.0592MHz    */
/*Rtc clock:                              */
/*Author:           Jack.Fu               */
/*Create date:      2008.11.20            */
/*Design date:                            */
/*Complete date:                          */
/******************************************/

#ifndef _DEFAULT_H
#define _DEFAULT_H

#define uchar unsigned char
#define uint unsigned int

#define FIRST_TEXT   0xf3
#define SECOND_TEXT  0xf4
#define END_TEXT    0x0a  //�����ֽ�

#define BAUD 9600           //�����ʲ���9600b/s
#define CRYSTAL 11059200    //ϵͳʱ��11.0592M
 
//����Ͷ��岨�������ò���
#define BAUD_SETTING (unsigned int) ((unsigned long)CRYSTAL/(16*(unsigned long)BAUD)-1)
#define BAUD_H (unsigned char)(BAUD_SETTING>>8)
#define BAUD_L (unsigned char)(BAUD_SETTING)

//USART0
#define USART0_FRAMING_ERROR (1<<FE0)
#define USART0_PARITY_ERROR (1<<PE0)  //PE
#define USART0_DATA_OVERRUN (1<<DOR0)
#define USART0_DATA_REGISTER_EMPTY (1<<UDRE0)

//USART1
#define USART1_FRAMING_ERROR (1<<FE1)
#define USART1_PARITY_ERROR (1<<PE1)  //PE
#define USART1_DATA_OVERRUN (1<<DOR1)
#define USART1_DATA_REGISTER_EMPTY (1<<UDRE1)

#define set_bit(x,y) (x|=(1<<y)) //��1����
#define clr_bit(x,y) (x&=~(1<<y)) //��0����
#define xor_bit(x,y) (x^=(1<<y)) //ȡ������
#define bit(x) (1<<x)            //��ĳλ����
#define get_bit(x,y) (x&=(1<<y)) //ȡ��ĳλ 


#endif
