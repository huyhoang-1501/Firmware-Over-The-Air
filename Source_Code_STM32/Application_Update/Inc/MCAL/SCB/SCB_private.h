#ifndef SCB_PRIVATE_H_
#define SCB_PRIVATE_H_


#define SCB     ((volatile SCB_t*)0xE000ED00)

typedef struct
{
volatile u32 CPUID;
volatile u32 ICSR;
volatile u32 VTOR;
volatile u32 AIRCR;
volatile u32 SCR;
volatile u32 CCR;
volatile u32 SHPR1;
volatile u32 SHPR2;
volatile u32 SHPR3;
volatile u32 SHCRS;
volatile u32 CFSR;
volatile u32 HFSR;
volatile u32 Reserved;
volatile u32 MMAR;
volatile u32 BFAR;
}SCB_t;




#endif /* SCB_PRIVATE_H_ */
