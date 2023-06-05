/*
 * led.h
 *
 * Created: 01-Jun-23 4:40:52 PM
 *  Author: Zerconium
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/dio/dio.h"

typedef enum en_led_Error_t
{
	LED_OK,
	WRONG_LED_PIN
}en_led_Error_t;


en_led_Error_t led_on (DIO_Pin_type led);
en_led_Error_t led_off (DIO_Pin_type led);
en_led_Error_t led_toggle (DIO_Pin_type led);


#endif /* LED_H_ */