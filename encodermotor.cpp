#include "encodermotor.h"
 
MotorEncoder::MotorEncoder(byte encoderPin,int N, int radius
               frontback_t motorPin){
  this->encoderPin = encoderPin;
  this->N = N;
  this->radius = radius;
  
  this->motorPin   = motorPin;

  pinMode(encoderPin,    INPUT);
  pinMode(motorPin.front,OUTPUT);
  pinMode(motorPin.back, OUTPUT);
  
  setMotor(Action::Stop,0);
}

void MotorEncoder::setLinearPosition(int pos){
  
}

void MotorEncoder::setMotor(Action _act){
  act = _act;
  digitalWrite(motorPin.front, act == Action::Forward);
  digitalWrite(motorPin.back,  act == Action::Backward);
}

void MotorEncoder::loop(){
  byte now = digitalRead(encoderPin);
  if(last != now){
    if(act == Action::Forward){
      encoderPosition++;
    } else if(act == Action::Backward){
      encoderPosition--;
    }
  }
  last = now;
}

//eventBack = (analogRead(irPin.back) >= irLevel);
//eventFront = (analogRead(irPin.front) >= irLevel);
