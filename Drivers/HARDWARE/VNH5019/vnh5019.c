#include "vnh5019.h"

/*************************/
void VNH5019_Init(void) {	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(INA_GPIO_Port, INA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(INB_GPIO_Port, INB_Pin, GPIO_PIN_RESET);
}

/*******************************/
void VNH5019_Run(int16_t PWM) {
	GPIO_PinState m_ina, m_inb;
	if (PWM != 0) {
		if (0 < PWM) {
			m_ina = GPIO_PIN_RESET;
		  m_inb = GPIO_PIN_SET;
		}
		else {
			m_ina = GPIO_PIN_RESET;
		  m_inb = GPIO_PIN_RESET;
		}
	}
	else {
			m_ina = GPIO_PIN_RESET;
		  m_inb = GPIO_PIN_RESET;
	}

	HAL_GPIO_WritePin(INA_GPIO_Port, INA_Pin, m_ina);
	HAL_GPIO_WritePin(INB_GPIO_Port, INB_Pin, m_inb);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, abs(PWM));
}
