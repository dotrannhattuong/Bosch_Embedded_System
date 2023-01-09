#ifndef __KALMAN_H__
#define __KALMAN_H__
/*****************/
#ifdef __cplusplus
extern "C" {
#endif
/************************/
#include "stm32f4xx_hal.h"
/***************/
#include "math.h"

typedef struct {
	float err_measure;
	float err_estimate;
	float q;
	float current_estimate;
	float last_estimate;
	float kalman_gain;
} kalman;

void KalmanFilter_Init(kalman *Kalman, float mea_e, float est_e, float q);
float updateEstimate(kalman *Kalman, float mea);

/*****************/
#ifdef __cplusplus
}
#endif
#endif
