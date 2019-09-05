
/******************************************/
/*           ����������������޹�˾     */
/*Project:      FCT��������               */
/*Guest:                                  */
/*Name:             port.h                */
/*Mcu chip:         Atmega64              */
/*Main clock:       �ⲿ����11.0592MHz    */
/*Rtc clock:                              */
/*Author:           Jack.Fu               */
/*Create date:      2008.11.20            */
/*Design date:                            */
/*Complete date:                          */
/******************************************/

#ifndef _PORT_H
#define _PORT_H

//extern unsigned char read_flash(unsigned int add);

/*================================================*/
/************����MCU I/O�� start*******************/
//1�������0������
//PORTA  �������
#define LCD_data PORTA

//PORTB  �������
#define relay1   0
#define relay2   1
#define relay3   2
#define relay4   3
#define relay5   4
#define relay6   5
#define relay7   6
#define relay8   7  
#define relay_1_8_PORT PORTB
#define relay_9_16_PORT PORTC

//PORTC  �������
#define PC0    0
#define PC1    1
#define PC2    2
#define PC3    3
#define PC4    4
#define PC5    5
#define PC6    6
#define PC7    7 

//PORTD
#define K19  0  //�̵���
#define relay26  1  //�����̵���
#define rxd1     2  //RXD���룬��������Ч      ;USART1�������ڽ�PC������
#define txd1     3  //TXD���                  ����USART1�����ݿں�ʱ�ӿ�
#define key1 4  //�Զ����Կ�ʼ�İ���,����
#define key2 5  //��ͣ����������
#define bell 6  //���������ƣ�pnp�ܣ��͵�ƽ��Ч��  ���
#define relay27 7  //�̵���
 
//PORTE
#define rxd0     0  //RXD���룬��������Ч      ;USART0�������ڽ�FLUKE���ñ�ĸ��
#define txd0     1  //TXD���                  ����USART0�����ݿں�ʱ�ӿ�
#define LCD_RS   2
#define LCD_EN   3  //LCD�Ŀ��ƿڣ����
#define relay28  4
#define relay29  5
#define relay30  6
#define relay31  7  //4���̵������ƣ����

//PORTF
#define K8 0
#define K7 1
#define K6 2
#define K5 3
#define K4 4
#define K3 5
#define K2 6
#define K1 7

//PORTG
#define relay32 0
#define relay33 1  
#define relay34 2  
#define LED2 3
#define K20 4  

/************����MCU I/O�� end*********************/
/*================================================*/

/*================================================*/
/************����MCU Flag��־λ start**************/
#pragma global_register flag1:20 flag2:21 flag3:22 flagerr:23
unsigned char flag1;
#define keyprq_flag1     0	//�м����±�־λ
#define keyeff_flag1     1	//������Ч��־λ
#define Usart0_RECVFlag1 2 //=1��ʾ����0���յ���һ�����������ݰ�
#define Usart1_RECVFlag1 3 //=1��ʾ����1���յ���һ�����������ݰ�
#define error_flag1      4   //ͨ�Ŵ����־λ
#define AD0_RECVFlag1    5 //=1��ʾADC0���յ���һ�����������ݰ�
#define time_goFlag1     6
#define recv_okFlag1     7

unsigned char flag2;

unsigned char flag3;
unsigned char flagerr;


/************����MCU Flag��־λ end****************/
/*================================================*/

#endif

