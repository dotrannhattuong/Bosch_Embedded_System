#include "tesla.h"

/*********************/
velocity Velocity;
double T=0.1;
double fabs(double);

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
	TIM3->CCR2 = 90; //from 45 to 250
	return -0.3 * (float)angle + 52;
}

/*********************/
void Run(float speed) {
	float acc = 1.0, dcc = 1.0;	
	Velocity.Set= speed;
	if (Velocity.Set > 0) Acceleration(Velocity.Set, &Velocity.Output, acc, dcc);
	else if (Velocity.Set < 0)Acceleration(Velocity.Set, &Velocity.Output, -acc, -dcc);
	else {
		if (Velocity.Output < 0) Acceleration(Velocity.Set, &Velocity.Output, -acc, -dcc);
		else Acceleration(Velocity.Set, &Velocity.Output, acc, dcc);
	}
}
