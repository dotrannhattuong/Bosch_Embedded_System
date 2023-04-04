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
void Control_Angle(int8_t angle) {
	if (angle >= 25) angle=25;
	else if (angle <= -25) angle=-25;
	// 0 do: 140 
	// 25 do: 200 -> phai 
	// -25 do: 80 -> trai
	angle_pwm =  2.4 * (double)angle + 105; //from 45 to 250
	
	if (angle_pwm >= 165) angle_pwm=165;
	else if (angle_pwm <= 45) angle_pwm=45;
	
	TIM3->CCR2 = (int)angle_pwm;
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
