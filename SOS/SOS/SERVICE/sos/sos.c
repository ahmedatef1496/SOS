/*
 * os.c
 *
 * Created: 5/28/2023 1:52:21 PM
 *  Author: Amr
 */ 

#include "sos.h"

static u8 u8_g_init_counter;
static u64 u64_g_periodic_check_time;
static u8 u8_check_flag;
static u8 u8_g_start_flag = HIGH;
static str_sos_config_task_t g_database [NO_OF_TASKS] ;


/**	
 *																												
 * @brief                                               :   Callback function for timer to generate a SOS_SCHEDULER_TICK every 100 ms				
 *																															
 */
void sos_scheduler (void)
{
	static u8 u8_counter = INITIAL_START;

	
	if (u8_counter == SOS_SCHEDULER_TICK)
	{	
		u64_g_periodic_check_time ++;
		u8_counter = INITIAL_START;
		u8_check_flag = HIGH;
	}
	u8_counter++;
}


/**	
 *																												
 * @brief                                               :   Function Used to Initialize sos module				
 *																												
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation						
 *              SOS_STATUS_INVALID_STATE				:   In case the SOS is already Initialized				
 *																												
 */
enu_sos_error_status_t sos_init	(void)
{
	enu_sos_error_status_t sos_error_status = SOS_STATUS_SUCCESS;
	
	if (u8_g_init_counter == INITIAL_START)
	{
		TIMER0_Init(TIMER0_NORMAL_MODE);
		TIMER0_OV_InterruptEnable();
		TIMER0_OV_SetCallBack(sos_scheduler);		
		DIO_Init_All();
		
		EXI_Init();
		EXI_Enable(EX_INT0);
		EXI_TriggerEdge(EX_INT0,FALLING_EDGE);
		EXI_SetCallBack(EX_INT0,sos_disable);
		
		u8_g_init_counter ++;
	}
	else
	{
		enu_sos_error_status_t sos_error_status = SOS_STATUS_INVALID_STATE;		
	}
	
	return sos_error_status;
}


/**	
 *																												
 * @brief                                               :   Function Used to de-initialize sos module				
 *																												
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation						
 *              SOS_STATUS_INVALID_STATE				:   In case the SOS is already De-Initialized or was not initialized previously.				
 *																												
 */
enu_sos_error_status_t sos_deinit (void)
{
	enu_sos_error_status_t sos_error_status = SOS_STATUS_SUCCESS;
	
	if (u8_g_init_counter == INIT_SUCCESS)
	{
		TIMER0_OV_SetCallBack(NULLPTR);
		EXI_Disable(EX_INT0);
		u8_g_init_counter --;
		
		for (u8 L_index = INITIAL_START; L_index < NO_OF_TASKS; L_index++)
		{
			g_database[L_index].pfTask = NULLPTR;
			g_database[L_index].u16_task_id += NO_OF_TASKS;
			g_database[L_index].u16_periodicity = INVALID_PERIODICITY;
			g_database[L_index].u16_priority = INVALID_PRIORITY;
		}			
	}
	else
	{
		enu_sos_error_status_t sos_error_status = SOS_STATUS_INVALID_STATE;
	}
	
	return sos_error_status;
}



/**
 *																												
 * @brief                                               :   Function Used to to create a certain task			
 *	
 * @param[in]   str_sos_config_task						:	Structure of the id , priority , periodicity and the address of the task to be created
 *																															
 * @return      SOS_STATUS_INVALID_ARGS		            :   In case of invalid (task id choice	, periodicity choice , priority choice , task address choice)	
 *				SOS_STATUS_TASK_ADDED					:	In case of Successful task addition				
 */	

enu_sos_error_status_t sos_create_task (str_sos_config_task_t* str_sos_config_task)
{
	enu_sos_error_status_t  sos_error_status = SOS_STATUS_TASK_ADDED;
	
	if (u8_g_init_counter == INIT_SUCCESS)																//check on SOS initialization
	{
		if (str_sos_config_task != NULLPTR)																//check on passing nullptr
		{
			if ( (str_sos_config_task->u16_periodicity == INVALID_PERIODICITY)		||					//check on arguments validation
			(str_sos_config_task->pfTask == NULLPTR)							||
			(str_sos_config_task->u16_priority > NO_OF_TASKS)					||
			(str_sos_config_task->u16_task_id > NO_OF_TASKS) )
			{
				sos_error_status = SOS_STATUS_INVALID_ARGS;
			}
			
			for (u8 L_index = INITIAL_START; L_index < NO_OF_TASKS; L_index++)
			{
				if (g_database[L_index].u16_task_id == str_sos_config_task->u16_task_id)				//check that the id is not used before
				{
					sos_error_status = SOS_STATUS_INVALID_ARGS;
					break;
				}
			}
			if (sos_error_status == SOS_STATUS_TASK_ADDED)
			{
				g_database[str_sos_config_task->u16_task_id] = *str_sos_config_task;
			}
		}
		else
		{
			 sos_error_status = SOS_STATUS_INVALID_ARGS;
		}
	}
	else
	{
		 sos_error_status = SOS_STATUS_INVALID_STATE;
	}
	
	return sos_error_status;
}



/**	
 *																												
 * @brief                                               :   Function Used to run and execute the tasks in the database				
 *																												
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation						
 *              SOS_STATUS_INVALID_STATE				:   In case the SOS wasn't initialized				
 *																												
 */

void sos_run (void)
{
	
	if (u8_g_init_counter == INIT_SUCCESS)
	{
		timer_start(TIMER0_SCALER_64);
		
		while (1)
		{
			sos_start_check();
			if (u8_check_flag == HIGH && u8_g_start_flag == HIGH)
			{
				for (u8 L_index = INITIAL_START; L_index < NO_OF_TASKS; L_index++)
				{
				
					if (g_database[L_index].pfTask != NULLPTR)
					{
						if ( u64_g_periodic_check_time % g_database[L_index].u16_periodicity == LOW)
						{
							g_database[L_index].pfTask();						
						}
					}
				
				}
				u8_check_flag = LOW;
			}
			
		}
	}
	else
	{
		//Do nothing
	}
}



/**
 *																												
 * @brief                                               :   Function Used to to delete a certain task			
 *																												
 * @param[in]   u16_task_id					            :   id for the task to be deleted
 *
 * @return	   	SOS_STATUS_INVALID_ARGS					:	In case of invalid task id								
 *				SOS_STATUS_TASK_DELETED					:	In case of Successful deletion of the task				
 */

enu_sos_error_status_t sos_delete_task (u16 u16_task_id)
{
	enu_sos_error_status_t sos_error_status = SOS_STATUS_TASK_DELETED ;
	
	if (u8_g_init_counter == INIT_SUCCESS)																//check on SOS initialization
	{
		if (u16_task_id < NO_OF_TASKS)																	//check that the id is valid
		{
			for (u8 L_index = INITIAL_START; L_index < NO_OF_TASKS; L_index++)							//check that the id exists in database
			{
				if (g_database[L_index].u16_task_id == u16_task_id)
				{
					g_database[L_index].pfTask = NULLPTR;
					g_database[L_index].u16_task_id += NO_OF_TASKS ;
					sos_error_status = SOS_STATUS_TASK_DELETED ;
					break;
				}
				else
				{
					sos_error_status = SOS_STATUS_INVALID_ARGS;
				}
			}
		}
		else
		{
			sos_error_status = SOS_STATUS_INVALID_ARGS;
		}
	}
	else
	{
		sos_error_status = SOS_STATUS_INVALID_STATE;
	}	
	
	return sos_error_status;
}



/**
 *																												
 * @brief                                               :   Function Used to to modify a certain task			
 *	
 * @param[in]   str_sos_config_task						:	Structure of the id , priority , periodicity and the address of the task to be modified
 *																											
 * @return      SOS_STATUS_INVALID_ARGS		            :   In case of invalid (task id choice	, periodicity choice , priority choice , task address choice)	
 *				SOS_STATUS_TASK_MODIFIED				:	In case of Successful task modification				
 */

enu_sos_error_status_t sos_modify_task (str_sos_config_task_t* str_sos_config_task)
{
	enu_sos_error_status_t sos_error_status = SOS_STATUS_TASK_MODIFIED;
	
	if (u8_g_init_counter == INIT_SUCCESS)																//check on SOS initialization
	{
		if (str_sos_config_task != NULLPTR)																//check on passing nullptr
		{
			for (u8 L_index = INITIAL_START; L_index < NO_OF_TASKS; L_index++)										
			{
				if (g_database[L_index].u16_task_id == str_sos_config_task->u16_task_id)				//check that the id exists in database
				{
					sos_error_status = SOS_STATUS_TASK_MODIFIED;
			
					if ( (str_sos_config_task->u16_periodicity == INVALID_PERIODICITY)			||		//check on arguments validation
						 (str_sos_config_task->pfTask == NULLPTR)								||
						 (str_sos_config_task->u16_priority > NO_OF_TASKS)						||
						 (str_sos_config_task->u16_task_id > NO_OF_TASKS) )
					{
						sos_error_status = SOS_STATUS_INVALID_ARGS;
					}

					if (sos_error_status == SOS_STATUS_TASK_MODIFIED)
					{
						g_database[str_sos_config_task->u16_task_id] = *str_sos_config_task;
					}
					break;	
				}
				else
				{
					sos_error_status = SOS_STATUS_INVALID_ARGS;
				}
			}
		}
		else
		{
			sos_error_status = SOS_STATUS_INVALID_ARGS;
		}
	}
	else
	{
		sos_error_status = SOS_STATUS_INVALID_STATE;
	}
	
	return sos_error_status;
}



 /**	
 *																												
 * @brief                                               :   Function Used to stop the SOS							
 *																												
 */
 void sos_disable(void)
 {
	 if (u8_g_init_counter == INIT_SUCCESS)
	 {
		 u8_g_start_flag=LOW;
		timer_stop(); 
	 }
 }


/**	
 *																												
 * @brief                                               :   local function to check for start button press and resumes the timer counting				
 *																															
 */
 void sos_start_check (void)
 {
	 u8 u8_state;
	 BUTTON_read(BUTTON0,&u8_state);
	 if (u8_state==LOW)
	 {
		 timer_start(TIMER0_SCALER_64);
		 u8_g_start_flag=HIGH;
		 
		 while (u8_state==LOW)
		 {
			 BUTTON_read(BUTTON0,&u8_state);
		 }
	 }
 }
 
 
 
