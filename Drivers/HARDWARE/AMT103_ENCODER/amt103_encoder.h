#ifndef __AMT103_ENCODER_H__
#define __AMT103_ENCODER_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/***************/
#include "main.h"
#include "tim.h"

extern int32_t overflow;

///**************************/
void AMT103_Init(void);
int32_t AMT103_GetPulse(void);
void OverFlow(void);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
