/*
 * SYSTICK_interface.h
 *
 *  Created on: Feb 20, 2022
 *      Author: nourhan
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_


Errorstatus SYSTICK_ErrorstatusConfiguration(void);

Errorstatus SYSTICK_ErrorstatusEnable(void);

Errorstatus SYSTICK_ErrorstatusDisable(void);

Errorstatus SYSTICK_ErrorstatusPreLoadSet(u32 copy_u32PreLoadValue);

void SYSTICK_voidSetBusyWait(u32 copy_u32TickNumber);

void SYSTICK_voidDelay_ms(u32 Time_MilliSecond);

void SYSTICK_voidSetIntervalSingle(u32 copy_u32TickNumber,void(*Ptr)(void));

void SYSTICK_voidSetIntervalPeriodic(u32 copy_u32TickNumber,void(*Copy_Ptr)(void));

void SYSTICK_SetCallBackFunction(u32 *copy_Ptrfunc);

u32 SYSTICK_voidGetRemainingTime(void);

u32 SYSTICK_voidGetElapsedTime(void);

void SYSTICK_voidStopInterval(void);

#endif /* SYSTICK_INTERFACE_H_ */
