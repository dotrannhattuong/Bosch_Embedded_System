#include "pid.h"

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
}

/*************************/
float PID_Process(pid *PID,
                  float Setpoint,
                  float CurrentPoint) {
										
  PID->Error = Setpoint - CurrentPoint;
  		
	PID->pPart = PID->Error * PID->Kp;
	PID->dPart = PID->Kd * (PID->Error-PID->pre_Error)*1000/PID->T;
	PID->iPart += PID->Ki * PID->T * PID->Error/1000;
	PID->Output.Current += PID->pPart + PID->dPart + PID->iPart;

  PID->pre_Error = PID->Error;
	
	/***************** Saturation *****************/								
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
		}
		else if (PID->Output.Current < (-PID->Output.Max)) {
			PID->Output.Current = -PID->Output.Max;
		}
	}
	
	return PID->Output.Current;
}

/**********************/
void PID_Reset(pid *PID) {
  PID->Error = 0;
  PID->Output.Current = 0;
  PID->pre_Error = 0;
}
