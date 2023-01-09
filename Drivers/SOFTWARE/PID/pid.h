#ifndef __PID_H__
#define __PID_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************/
#include "stm32f4xx_hal.h"

#define M_PI 3.14159265358979323846

/*****************/
typedef struct {
  float Kp, Ki, Kd;
  float alpha, beta, gama;
  float T;
  float E, E1, E2;
	float pPart, iPart, dPart;
  struct {
    float Max, Min;
    float Current, Last;
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
									uint8_t Enable,
                  float Setpoint,
                  float CurrentPoint);

void PID_Reset(pid *PID);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
