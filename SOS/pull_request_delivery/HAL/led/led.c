/*
 * led.c
 *
 * Created: 01-Jun-23 4:40:44 PM
 *  Author: Zerconium
 */ 

#include "led.h"

en_led_Error_t led_on (DIO_Pin_type led)
{
	en_led_Error_t  error = LED_OK;
	if (led <32)
	{
		DIO_writepin (led,HIGH);
		error = LED_OK;
	}
	else
	{
		error = WRONG_LED_PIN;
	}
	
	return error;
}

en_led_Error_t led_off (DIO_Pin_type led)
{
	en_led_Error_t  error = LED_OK;
	if (led <32)
	{
		DIO_writepin (led,LOW);
		error = LED_OK;
	}
	else
	{
		error = WRONG_LED_PIN;
	}
	
	return error;
}


en_led_Error_t led_toggle (DIO_Pin_type led)
{	
	en_led_Error_t  error = LED_OK;
	if (led <32)
	{
		DIO_togglepin (led);
		error = LED_OK;
	}
	else
	{
		error = WRONG_LED_PIN;
	}
	
	return error;
}

