#ifndef __PID_H__
#define __PID_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************/
#include "stm32f4xx_hal.h"

extern int32_t overflow;

/*****************/
typedef struct {
  float Kp, Ki, Kd;
  float T;
  float Error, pre_Error;
	float pPart, iPart, dPart;
  struct {
    float Max, Min;
    float Current;
  } Output;
} pid;

/*****************/

void PID_Init(pid *PID,
              float T,
              float Kp,
              float Ki,
              float Kd,
							float OutMin,
              float OutMax);

float PID_Process(pid *PID,
                  float Setpoint,
                  float CurrentPoint);

void PID_Reset(pid *PID);
/*****************/
#ifdef __cplusplus
}
#endif
#endif
