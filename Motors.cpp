/*
  Motors.cpp
  Controls all aspects of motor/esc handling
  by Brad Danielson
  Influenced heavily by Thomas Tiesberg's QC Code
*/
#include "Motors.h"
/* Constructor */
Motors::Motors() {

}
/* Deconstructor */
Motors::~Motors() {

}
/* 
   Initializes Motors
   More fuctionality should be added here as needs arise
*/
void Motors::initMotors()
{
     analogWriteResolution(16); // 16 bits of Res
	 stopAll();
}
/* 
   Sets motors to Max PWM % for 5 seconds, then low, then stops
*/
void Motors::calibrateMotors()
{
     setNS(MaxPWM,0.0,0.0) ;
     setEW(MaxPWM,0.0,0.0) ;
     delay(5000) ;
     setNS(MinPWM,0.0,0.0) ;
     setEW(MinPWM,0.0,0.0) ;
     delay(2000) ;
     stopAll() ;
}
/*
  Crudely Clamps the Motor outputs to between min and max values
*/

void Motors::clamp(float *Motor1, float *Motor2) 
{
  if(*Motor1 > MaxPWM)
    *Motor1 = MaxPWM ;
  if(*Motor1 < MinPWM)
    *Motor1 = MinPWM;
  if(*Motor2 > MaxPWM)
    *Motor2 = MaxPWM ;
  if(*Motor2 < MinPWM)
    *Motor2 = MinPWM; 
} 
/*
  Converts a floating point percent (0-100% Duty Cycle)
  to a bit value used by Teensy's analogWrite() function
  0 - 65535
*/
float Motors::percentToPWM(float percent) {
    int output = percent*bitRes/100.0 ;
    return output ;
}
/*
  Sets NS Motors in terms of base PWM and Pitch and Yaw Offsets
*/
void Motors::setNS(float base, float P_offset, float Y_offset){
     N_update = base+P_offset+Y_offset ;
     S_update = base-P_offset+Y_offset ;
     clamp(&N_update, &S_update) ;
     analogWrite(MotorN, percentToPWM(N_update)) ;
     analogWrite(MotorS, percentToPWM(S_update)) ;
}

/*
  Sets EW Motors in terms of base PWM and Roll and Yaw Offsets
*/
void Motors::setEW(float base, float R_offset, float Y_offset){
     E_update = base+R_offset-Y_offset ;
     W_update = base-R_offset-Y_offset ;
     clamp(&E_update, &W_update) ;
     analogWrite(MotorE, percentToPWM(E_update)) ;
     analogWrite(MotorW, percentToPWM(W_update)) ;
}

/*
  Sets all motors to 0 RPM w/ 0 offset
*/
void Motors::stopAll()
{
	setNS(MinPWM, 0.0, 0.0);
	setEW(MinPWM, 0.0, 0.0);
}
