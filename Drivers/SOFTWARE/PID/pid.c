#include "pid.h"

int abs(int);
double fabs(double);
uint8_t Sampling_time = 10;
uint8_t inv_Sampling_time = 100;
/*********************/
void PID_Init(pid *PID,
              float T,
              float Kp,
              float Ki,
              float Kd,
							float OutMin,
              float OutMax) {
  PID->T = T;

	PID->Output.Min = OutMin;
  PID->Output.Max = OutMax;

  PID->Kp = Kp;
  PID->Ki = Ki;
  PID->Kd = Kd;

  PID->alpha = 2 * PID->T * PID->Kp + PID->Ki * PID->T * PID->T + 2 * PID->Kd;
  PID->beta = PID->T * PID->T * PID->Ki - 4 * PID->Kd - 2 * PID->T * PID->Kp;
  PID->gama = 2 * PID->Kd;
}

/*************************/
float PID_Process(pid *PID,
									uint8_t Enable,
                  float Setpoint,
                  float CurrentPoint) {
										
  PID->E = Setpoint - CurrentPoint;
  		
	if (Enable == 0) PID->Output.Current = (PID->alpha * PID->E + PID->beta * PID->E1 + PID->gama * PID->E2 + 2 * PID->T * PID->Output.Last) / (2 * PID->T);
	else {
		PID->pPart = PID->E*PID->Kp;
		PID->dPart = PID->Kd*(PID->E-PID->E1)*inv_Sampling_time;
		PID->iPart += PID->Ki*Sampling_time*PID->E/1000;
		PID->Output.Current += PID->pPart + PID->dPart + PID->iPart;
	}

	PID->Output.Last = PID->Output.Current;
  PID->E2 = PID->E1;
  PID->E1 = PID->E;
							 
	if (PID->Output.Min != 0) {
		if (0 < PID->Output.Current && PID->Output.Current < PID->Output.Min) {
			PID->Output.Current = PID->Output.Min;
		}
		else if (-PID->Output.Min < PID->Output.Current && PID->Output.Current < 0) {
			PID->Output.Current = -PID->Output.Min;
		}
	}

	if (PID->Output.Max != 0) {
		if (PID->Output.Max < PID->Output.Current) {
			PID->Output.Current = PID->Output.Max;
			PID->Output.Last = PID->Output.Max;
		}
		else if (PID->Output.Current < (-PID->Output.Max)) {
			PID->Output.Current = -PID->Output.Max;
			PID->Output.Last = -PID->Output.Max;
		}
	}
	
	return PID->Output.Current;
}

/**********************/
void PID_Reset(pid *PID) {
  PID->E = 0;
  PID->Output.Current = 0;
  PID->Output.Last = 0;
  PID->E2 = 0;
  PID->E1 = 0;
}
