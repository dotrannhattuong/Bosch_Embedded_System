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
	//	TIM1->CCR1 = 90; //128 -> 0 deg, 22 -> max, 166 -> min, 90 ->theo cánh tay dòn
 // 80 het lai trai -> 45 ve giua
 // 25 he lai phai -> 55 ve giua
 // 50
	return -0.3 * (float)angle + 52;
}

/*********************/
void Run(float speed) {
	float acc = 100.0, dcc = 100.0;	
	Velocity.Set.Right = speed;
	if (Velocity.Set.Right > 0) {
		Acceleration(Velocity.Set.Right, &Velocity.Output.Left, acc, dcc);
		Acceleration(Velocity.Set.Right, &Velocity.Output.Right, acc, dcc);
	}
	else if (Velocity.Set.Right < 0) {
		Acceleration(Velocity.Set.Right, &Velocity.Output.Left, -acc, -dcc);
		Acceleration(Velocity.Set.Right, &Velocity.Output.Right, -acc, -dcc);
	}
	else {
		if (Velocity.Output.Right < 0) Acceleration(Velocity.Set.Right, &Velocity.Output.Right, -acc, -dcc);
		else Acceleration(Velocity.Set.Right, &Velocity.Output.Right, acc, dcc);
	}
}
