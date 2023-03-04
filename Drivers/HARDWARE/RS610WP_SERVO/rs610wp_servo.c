#include "rs610wp_servo.h"

/*******************************/
void RS610WP_Init(void) {	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	
	/******* SET HOME *******/
	TIM3->CCR2 = 147; // from 45 to 250
}

/*******************************/
void RS610WP_Run(int16_t PWM) {
	TIM3->CCR2 = PWM;
}
