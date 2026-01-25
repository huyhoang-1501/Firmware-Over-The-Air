/*Include Standard libraries*/
#include "../Inc/LIB/bit_math.h"
#include "../Inc/LIB/std_types.h"

/*Include header files of NVIC */

#include "../Inc/MCAL/SCB/SCB_interface.h"
#include "../Inc/MCAL/SCB/SCB_private.h"
#include "../Inc/MCAL/SCB/SCB_configuration.h"


void MSCB_voidSystemPrioritySet(u8 copy_PriorityType)
{
	SCB->AIRCR=((0x5FA <<16)|(copy_PriorityType<<8));
}

void Reset_system(void)
{
SCB->AIRCR=( (0x5FA <<16) |(SCB->AIRCR & (0x700)) |(1<<2));
while(1);
}
