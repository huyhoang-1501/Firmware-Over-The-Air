#ifndef SYSTICK_CONFIGURATION_H_
#define SYSTICK_CONFIGURATION_H_


#define DISABLE      		0
#define ENABLE       		1

#define INT_EN      		ENABLE

#define SYSTICK_SELECT 		ENABLE

#define CLK_SOUCRE    		AHB_DIVIDED_BY_8

#define  AHB				0
#define AHB_DIVIDED_BY_8    1

#define SYSTICKEN_BIT		0
#define INTEN_BIT			1
#define CLK_SOURCE_BIT      2
#define UNDER_FLOW_FLAG     16

#define PRELOAD_EN		    ENABLE

#define PRELOAD_VALUE      50000

/**************************************************/
/*Option Configured for Function Set pre-load value*/
/**************************************************/

#define PRELOAD_SELECT     IMMEDIATE

#define	IMMEDIATE			1
#define NOT_IMMEDIATE		0


#endif /* SYSTICK_CONFIGURATION_H_ */
