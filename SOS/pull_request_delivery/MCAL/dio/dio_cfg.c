/*
 * DIO_cfg.c
 *
 * Created: 4/13/2023 8:34:55 AM
 *  Author: Amr
 */ 
#include "dio.h"

const DIO_PinStatus_type  PinsStatusArray[TOTAL_PINS]={
	INFREE,      /* Port A Pin 0 */
	INFREE,      /* Port A Pin 1 */
	INFREE,      /* Port A Pin 2 */
	INFREE,      /* Port A Pin 3 */
	INFREE,      /* Port A Pin 4 */
	INFREE,      /* Port A Pin 5 */
	INFREE,      /* Port A Pin 6 */
	INFREE,      /* Port A Pin 7 */
	OUTPUT,      /* Port B Pin 0 LED_1 */
	OUTPUT,      /* Port B Pin 1 LED_2*/
	OUTPUT,		 /* Port B Pin 2 LED_ERROR*/
	INFREE,		 /* Port B Pin 3 */
	INFREE,		 /* Port B Pin 4 */
	INFREE,		 /* Port B Pin 5 */
	INFREE,	     /* Port B Pin 6 */
	INFREE,		 /* Port B Pin 7 */
	INFREE,		 /* Port C Pin 0 */
	INFREE,		 /* Port C Pin 1 */
	INFREE,		 /* Port C Pin 2 */
	INFREE,		 /* Port C Pin 3 */
	INFREE,		 /* Port C Pin 4 */
	INFREE,		 /* Port C Pin 5 */
	INFREE,		 /* Port C Pin 6 */
	INFREE,		 /* Port C Pin 7 */
	INPULL,		 /* Port D Pin 0 BUTTON_START*/
	INFREE,		 /* Port D Pin 1 */
    INPULL,      /* Port D Pin 2 BUTTON_STOP*/
	INFREE,      /* Port D Pin 3 */
	INFREE,		 /* Port D Pin 4 */
	INFREE,		 /* Port D Pin 5 */
	INFREE,		 /* Port D Pin 6 */
	INFREE		 /* Port D Pin 7 */
};