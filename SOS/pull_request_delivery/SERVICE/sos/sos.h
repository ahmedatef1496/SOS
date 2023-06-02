/*
 * sos.h
 *
 * Created: 5/29/2023 2:40:32 AM
 *  Author: Amr
 */ 


#ifndef SOS_H_
#define SOS_H_

#include "../../MCAL/dio/dio.h"
#include "../../MCAL/timers/timer.h"
#include "sos_cfg.h"
#include "../../MCAL/Interrupt/exi.h"
#include "../../HAL/button/button.h"
#include "../../HAL/led/led.h"

typedef struct
{
	u16		u16_task_id;
	u16		u16_priority;
	u16		u16_periodicity;
	void (*pfTask)(void);

} str_sos_config_task_t;


typedef enum{
	 SOS_STATUS_SUCCESS,
	 SOS_STATUS_INVALID_STATE,
	 SOS_STATUS_INVALID_ARGS,
	 SOS_STATUS_TASK_ADDED,
	 SOS_STATUS_TASK_DELETED,
	 SOS_STATUS_TASK_MODIFIED,
}enu_sos_error_status_t ;



/**	
 *																												
 * @brief                                               :   Function Used to Initialize sos module				
 *																												
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation						
 *              SOS_STATUS_INVALID_STATE				:   In case the SOS is already Initialized				
 *																												
 */
enu_sos_error_status_t		sos_init				(void);


/**	
 *																												
 * @brief                                               :   Function Used to Initialize sos module				
 *																												
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation						
 *              SOS_STATUS_INVALID_STATE				:   In case the SOS is already De-Initialized or was not initialized previously.				
 *																												
 */
enu_sos_error_status_t		sos_deinit				(void);


/**
 *																												
 * @brief                                               :   Function Used to to create a certain task			
 *	
 * @param[in]   str_sos_config_task						:	Structure of the id , priority , periodicity and the address of the task to be created
 *																															
 * @return      SOS_STATUS_INVALID_ARGS		            :   In case of invalid (task id choice	, periodicity choice , priority choice , task address choice)	
 *				SOS_STATUS_TASK_ADDED					:	In case of Successful task addition				
 */																												
enu_sos_error_status_t		sos_create_task			(str_sos_config_task_t* str_sos_config_task);


/**
 *																												
 * @brief                                               :   Function Used to to delete a certain task			
 *																												
 * @param[in]   u16_task_id					            :   id for the task to be deleted
 *
 * @return	   	SOS_STATUS_INVALID_ARGS					:	In case of invalid task id								
 *				SOS_STATUS_TASK_DELETED					:	In case of Successful deletion of the task				
 */
enu_sos_error_status_t		sos_delete_task			(u16 u16_task_id);


/**
 *																												
 * @brief                                               :   Function Used to to modify a certain task			
 *	
 * @param[in]   str_sos_config_task						:	Structure of the id , priority , periodicity and the address of the task to be modified
 *																											
 * @return      SOS_STATUS_INVALID_ARGS		            :   In case of invalid (task id choice	, periodicity choice , priority choice , task address choice)	
 *				SOS_STATUS_TASK_MODIFIED				:	In case of Successful task modification				
 */
enu_sos_error_status_t		sos_modify_task			(str_sos_config_task_t* str_sos_config_task);


/**	
 *																												
 * @brief                                               :   Function Used to run and execute the tasks in the database				
 *																												
 * @return      SOS_STATUS_SUCCESS                      :   In case of Successful Operation						
 *              SOS_STATUS_INVALID_STATE				:   In case the SOS wasn't initialized				
 *																												
 */
void						sos_run					(void);


/**	
 *																												
 * @brief                                               :   Function Used to stop the SOS				
 *																															
 *																												
 */
void						sos_disable				(void);


#endif /* SOS_H_ */

