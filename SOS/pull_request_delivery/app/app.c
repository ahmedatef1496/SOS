/*
 * app.c
 *
 * Created: 5/29/2023 2:13:47 PM
 *  Author: Amr
 */ 


#include "app.h"

void Task1(void)
{
	led_toggle(LED_0);
}
void Task2(void)
{
	led_toggle(LED_1);
}

void app_init()
{
	GLOBALE_ENABLE();
	
	if (SOS_STATUS_SUCCESS != sos_init() )
	{
		//handle initialization fail scenario
	}
	
	str_sos_config_task_t	str_task1_config	= {1,1,3,Task1};
	str_sos_config_task_t	str_task2_config	= {2,2,5,Task2};
	
	
	if (SOS_STATUS_TASK_ADDED  != sos_create_task(&str_task1_config) )
	{
		//handle task creation fail scenario
	}
	if (SOS_STATUS_TASK_ADDED  != sos_create_task(&str_task2_config) )
	{
		//handle task creation fail scenario
	}



// 	sos_delete_task(2);										//delete task test
// 	sos_create_task(&str_task2_config);											

// 	str_sos_config_task_t	str_task2_edit_config	= {2,2,20,Task2};				//modify task test
// 	sos_modify_task(&str_task2_edit_config);


	sos_run();

}


/*
void app_start()
{
	//nothing
}
*/
