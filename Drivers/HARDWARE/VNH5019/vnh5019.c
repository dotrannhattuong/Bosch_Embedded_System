#include "vnh5019.h"

/*************************/
//void IR2104_Left_Init(void) {	
//	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
//	////////////////////////////////////////////////////////////////////////////////////
//	HAL_GPIO_WritePin(IR2184_LEFT_SDAB_GPIO_Port, IR2184_LEFT_SDAB_Pin, GPIO_PIN_RESET);
//}

///*******************************/
//void IR2104_Left_Run(int16_t PWM) {
//	GPIO_PinState PinState;
//	int16_t pwm[2];
//	if (PWM != 0) {
//		if (0 < PWM) {
//			pwm[0] = 0;
//		  pwm[1] = PWM;
//		}
//		else {
//			pwm[0] = -PWM;
//		  pwm[1] = 0;
//		}
//		PinState = GPIO_PIN_SET;
//	}
//	else {
//		pwm[0] = 0;
//		pwm[1] = 0;
////		PinState = GPIO_PIN_RESET; // Tha troi
//		PinState = GPIO_PIN_SET; // Brake
//	}
//	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, pwm[0]);
//	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pwm[1]);
//	HAL_GPIO_WritePin(IR2184_LEFT_SDAB_GPIO_Port, IR2184_LEFT_SDAB_Pin, PinState);
//}

///**************************/
//void IR2104_Right_Init(void) {	
//	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
//	//////////////////////////////////////////////////////////////////////////////////////
//	HAL_GPIO_WritePin(IR2184_RIGHT_SDAB_GPIO_Port, IR2184_RIGHT_SDAB_Pin, GPIO_PIN_RESET);
//}

///********************************/
//void IR2104_Right_Run(int16_t PWM) {
//	GPIO_PinState PinState;
//	int16_t pwm[2];
//	if (PWM != 0) {
//		if (0 < PWM) {
//			pwm[0] = 0;
//		  pwm[1] = PWM;
//		}
//		else {
//			pwm[0] = -PWM;
//		  pwm[1] = 0;
//		}
//		PinState = GPIO_PIN_SET;
//	}
//	else {
//		pwm[0] = 0;
//		pwm[1] = 0;
////		PinState = GPIO_PIN_RESET; // Tha troi
//		PinState = GPIO_PIN_SET; // Brake
//	}
//	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pwm[0]);
//	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pwm[1]);
//	HAL_GPIO_WritePin(IR2184_RIGHT_SDAB_GPIO_Port, IR2184_RIGHT_SDAB_Pin, PinState);
//}
