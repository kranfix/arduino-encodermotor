#include <Arduino.h>
#include "encodermotor.h"

EncoderMotor::EncoderMotor(uint8_t encoderPin,int N, int radius,
               frontback_t motorPin){
  this->encoderPin = encoderPin;
  this->N = N;
  this->radius = radius;

  this->motorPin   = motorPin;

  pinMode(encoderPin,    INPUT);
  pinMode(motorPin.front,OUTPUT);
  pinMode(motorPin.back, OUTPUT);

  last = digitalRead(encoderPin);

  setMotor(Action::Stop,0);
}

void EncoderMotor::setLinearPosition(float pos){

}

void EncoderMotor::setMotor(Action _act, float limit){
  act = _act;
  digitalWrite(motorPin.front, act == Action::Forward);
  digitalWrite(motorPin.back,  act == Action::Backward);
}

void EncoderMotor::loop(){
  uint8_t now = digitalRead(encoderPin);
  if(last != now){
    if(act == Action::Forward){
      encoderPosition++;
    } else if(act == Action::Backward){
      encoderPosition--;
    }
  }
  last = now;
}

bool EncoderMotor::encoderEvent(){
  return event;
}


//eventBack = (analogRead(irPin.back) >= irLevel);
//eventFront = (analogRead(irPin.front) >= irLevel);
