
/******************************************/
/*           ����������������޹�˾     */
/*Project:      FCT��������               */
/*Guest:                                  */
/*Name:             beep.c                */
/*Mcu chip:         Atmega64              */
/*Main clock:       �ڲ�����8MHz          */
/*Rtc clock:                              */
/*Author:           Jack.Fu               */
/*Create date:      2008.11.20            */
/*Design date:                            */
/*Complete date:                          */
/******************************************/

#include <iom64v.h>
#include <macros.h>
#include <delay.h>
#include <port.h>
#include <default.h>

/*------------------------------------------*/
void setBEEP(void)
{
  clr_bit(PORTD,bell);
}
void rstBEEP(void)
{
  set_bit(PORTD,bell);
}
/***************beep1s���� start ************/
void beep1s(void)
{
    clr_bit(PORTD,bell);
    delay_nms(1000);
    set_bit(PORTD,bell);
}
/***************beep1s���� end ***************/
/*-------------------------------------------*/

/***************beep ns���� start ************/
void beep3s(void)
{
    clr_bit(PORTD,bell);
    delay_nms(3000);
    set_bit(PORTD,bell);
}
/***************beep ns���� end ***************/

/*---------------------------------------------*/
/***************beep500ms���� start ************/
void beep500ms(void)
{
    clr_bit(PORTD,bell);
    delay_nms(500);
    set_bit(PORTD,bell);
}
/***************beep500ms���� end ***************/
/*-------------------------------------------*/

/*------------------------------------------*/
/***************beeperr3���� start ************/
void beeperr3(void)
{
    clr_bit(PORTD,bell);
    delay_nms(200);
    set_bit(PORTD,bell);
    delay_nms(80);
    clr_bit(PORTD,bell);
    delay_nms(200);
    set_bit(PORTD,bell);
    delay_nms(80);
    clr_bit(PORTD,bell);
    delay_nms(200);
    set_bit(PORTD,bell);
}
/***************beeperr3���� end ***************/
/*-------------------------------------------*/