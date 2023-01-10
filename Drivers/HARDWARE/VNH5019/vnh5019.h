#ifndef __VNH5019_H__
#define __VNH5019_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/***************/
#include "main.h"
/**************/
#include "tim.h"

///**************************/
void VNH5019_Init(void);
void VNH5019_Run(int16_t PWM);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
