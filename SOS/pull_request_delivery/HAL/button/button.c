/*
 * button.c
 *
 * Created: 4/14/2023 8:18:20 AM
 *  Author: Amr
 */ 
 #include "button.h"
en_buttonError_t BUTTON_init( DIO_Pin_type button)
{
	en_buttonError_t  error = BUTTON_OK;
	
	if (button <32)
	{
				DIO_initpin(button,INPULL);
				error = BUTTON_OK;
	}
	else
	{
              error = WRONG_BUTTON_PIN;
	}
	
	return error;
}

en_buttonError_t BUTTON_read(DIO_Pin_type button , DIO_PinVoltage_type *buttonState)
{
	en_buttonError_t  error = BUTTON_OK;
	
	if (button <32)
	{
		DIO_readpin(button,buttonState);
		error = BUTTON_OK;
	}
	else
	{
		error = WRONG_BUTTON_PIN;
	}
	
	return error;
} 

