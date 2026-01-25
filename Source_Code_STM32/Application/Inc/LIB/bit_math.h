#ifndef BIT_MATH_H
#define BIT_MATH_H

#define  CLEAR_BIT(reg,bit)        reg=reg&~(1<<bit)
#define  SET_BIT(reg,bit)          reg=reg|(1<<bit)
#define  TOGGLE_BIT(reg,bit)       reg=reg^(1<<bit)
#define  GET_BIT(reg,bit)         ((reg>>bit)& 0x01)
#define  SET_BYTE(reg,value)      (reg = value)


#define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0)  CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0
#endif
