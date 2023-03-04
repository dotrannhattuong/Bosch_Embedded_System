#include "tesla.h"
/*********************/
velocity Velocity;
double T=0.1;
float angle_pwm=0;

/************************/
void Acceleration(float V_want, float *vout, float _acc, float _dcc) {	
	if(fabs(*vout) < fabs(V_want)) {
    *vout += _acc*T;
		if(fabs(*vout) >= fabs(V_want)) *vout = V_want;
   }
  if(fabs(*vout) > fabs(V_want)) {
     *vout -= _dcc*T;	
		if (_dcc >= 0) {
			if(*vout <= V_want) *vout = V_want;
		}
		else if(*vout >= V_want) *vout = V_want;
  }
}

/*********************/
uint16_t Control_Angle(int8_t angle) {
	if (angle >= 25) angle=25;
	else if (angle <= -25) angle=-25;
	// 0 do: 147 
	// 25 do: 200 -> phai 
	// -25 do: 100 -> trai
	angle_pwm =  2.12 * (float)angle + 147; //from 45 to 250
	TIM3->CCR2 =	angle_pwm;
}

/*********************/
void Run(float speed) {
	float acc = 100.0, dcc = 100.0;	
	Velocity.Set= speed;
	if (Velocity.Set > 0) Acceleration(Velocity.Set, &Velocity.Output, acc, dcc);
	else if (Velocity.Set < 0)Acceleration(Velocity.Set, &Velocity.Output, -acc, -dcc);
	else {
		if (Velocity.Output < 0) Acceleration(Velocity.Set, &Velocity.Output, -acc, -dcc);
		else Acceleration(Velocity.Set, &Velocity.Output, acc, dcc);
	}
}
