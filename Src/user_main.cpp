#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"
#include "PIDAUTOTUNER/pidautotuner.h"
#include "VNH5019/vnh5019.h"
#include "AMT103_ENCODER/amt103_encoder.h"

PIDAutotuner tuner = PIDAutotuner();
double kp, ki, kd;
bool start=0;

void user_setup(int16_t target) {
	// Set the target value to tune to
	// This will depend on what you are tuning. This should be set to a value within
	// the usual range of the setpoint. For low-inertia systems, values at the lower
	// end of this range usually give better results. For anything else, start with a
	// value at the middle of the range.
	tuner.setTargetInputValue(target); // value at the middle of the range.

	// Set the loop interval in microseconds
	// This must be the same as the interval the PID control loop will run at
	tuner.setLoopInterval(20000);

	// Set the output range
	// These are the minimum and maximum possible output values of whatever you are
	// using to control the system (Arduino analogWrite, for example, is 0-255)
	tuner.setOutputRange(0, 30);

	// Set the Ziegler-Nichols tuning mode
	// Set it to either PIDAutotuner::ZNModeBasicPID, PIDAutotuner::ZNModeLessOvershoot,
	// or PIDAutotuner::ZNModeNoOvershoot. Defaults to ZNModeNoOvershoot as it is the
	// safest option.
	tuner.setZNMode(PIDAutotuner::ZNModeBasicPID);
	
	// Set Tunning Cycles
	tuner.setTuningCycles(10);
	
	// This must be called immediately before the tuning loop
	// Must be called with the current time in microseconds
	tuner.startTuningLoop(micros());

	// Run a loop until tuner.isFinished() returns true
	long microseconds;
	while (!tuner.isFinished()) {

			// This loop must run at the same speed as the PID control loop being tuned
			// long prevMicroseconds = microseconds;
			microseconds = micros();

			// Get input value here (temperature, encoder position, velocity, etc)
			double input = AMT103_GetPulse();

			// Call tunePID() with the input value and current time in microseconds
			double output = tuner.tunePID(input, microseconds);

			// Set the output - tunePid() will return values within the range configured
			// by setOutputRange(). Don't change the value or the tuning results will be
			// incorrect.
			VNH5019_Run(output); // output

			// This loop must run at the same speed as the PID control loop being tuned
			while (micros() - microseconds < 20000) HAL_Delay(1);
	}
	// Turn the output off here.
	VNH5019_Run(0);

	// Get PID gains - set your PID controller's gains to these
	kp = tuner.getKp();
	ki = tuner.getKi();
	kd = tuner.getKd();
	
	start=1;
}

void user_loop() {

}


