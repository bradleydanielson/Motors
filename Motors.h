#ifndef MOTORS_H_
#define MOTORS_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define bitRes 65535
#define MinPWM 40.0
#define MaxPWM 80.0

// Motor Pin Definitions
#define MotorN 23
#define MotorS 22
#define MotorE 21
#define MotorW 20


class Motors {
public:
	Motors();
	virtual ~Motors();
	void initMotors();
	void calibrateMotors() ;
	void setNS(float base, float P_offset, float Y_offset);
	void setEW(float base, float P_offset, float Y_offset);
	void stopAll();
private:
    float Motor1, Motor2 ;
    float N_update, W_update, E_update, S_update ;
    void clamp(float *Motor1, float *Motor2) ;
	float percentToPWM(float percent) ;
};

#endif /* MOTORS_H_ */
