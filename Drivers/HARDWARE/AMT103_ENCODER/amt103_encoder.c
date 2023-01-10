#include "amt103_encoder.h"

/*******************************/
int32_t overflow;
volatile int32_t encoder_pulse, encoder_pulse_last, v_car;

/*******************************/
void AMT103_Init(void) {	
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);
	
	overflow = -1;
}

/*******************************/
int32_t AMT103_GetPulse() {
	encoder_pulse = (overflow << 15 | TIM4->CNT);
//		if(encoder_pulse == -32768) encoder_pulse=0;
	v_car = ((encoder_pulse - encoder_pulse_last)*1000*60)/(67000*20); // RPM
	encoder_pulse_last = encoder_pulse;
	
	return v_car;
}

/*******************************/
void OverFlow(void)
{
	if((TIM4->CR1 & 0x10) == 0x10) overflow--;
	else overflow++;
}
