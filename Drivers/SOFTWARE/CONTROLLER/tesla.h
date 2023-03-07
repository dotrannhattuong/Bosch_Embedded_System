#ifndef __TESLA_H__
#define __TESLA_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************/
#include "stm32f4xx_hal.h"
#include "math.h"
	
#define Lw 57 // Chieu dai xe
#define dw 31 // Chieu ngang xe
#define V_PI (double)3.14159265358979323846
	
/*****************/
typedef struct {
  float Output;
  float Set;
} velocity;
/*****************/
extern velocity Velocity;

/*****************/
void Run(float speed);
void Control_Angle(int8_t angle);
	
/*****************/
#ifdef __cplusplus
}
#endif
#endif
