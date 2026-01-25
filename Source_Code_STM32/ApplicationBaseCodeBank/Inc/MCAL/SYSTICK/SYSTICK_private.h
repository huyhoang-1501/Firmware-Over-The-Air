/*
 * SYSTICK_private.h
 *
 *  Created on: Feb 20, 2022
 *      Author: nourhan
 */

#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_


#define SYSTICK    ((volatile SysTick_t *)0xE000E010)

typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALB;


}SysTick_t;



#define   CLEARING_REGISTER_VAL     0
#define TICK_TIME		        (1/1000000)

#define SYSTICK_SINGLE_INTERVAL     0
#define SYSTICK_PERIODIC_INTERVAL 	1

#endif /* SYSTICK_PRIVATE_H_ */
