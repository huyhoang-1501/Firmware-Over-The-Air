#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_


#define GPIOA   ((volatile GPIO_t*)0x40010800)
#define GPIOB   ((volatile GPIO_t*)0x40010C00)
#define GPIOC   ((volatile GPIO_t*)0x40011000)

#define AFIO   ((volatile AFIO_t*)0x40010000)
typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_t;

typedef struct
{
	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR1;
	volatile u32 EXTICR2;
	volatile u32 EXTICR3;
	volatile u32 EXTICR4;
	volatile u32 MAPR2;
}AFIO_t;

#define CONSTANT_PIN_CRH					8
#define CONSTANT_MODE_VALUE					4
#define CONSTANT_CNF_VALUE					2
#define CONSTANT_CLEARING_VALUE_GPIO		15


#endif /* GPIO_PRIVATE_H_ */
