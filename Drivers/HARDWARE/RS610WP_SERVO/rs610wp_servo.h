#ifndef __RS610WP_SERVO_H__
#define __RS610WP_SERVO_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/***************/
#include "main.h"
#include "tim.h"

///**************************/
void RS610WP_Init(void);
void RS610WP_Run(int16_t PWM);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
