#include <Arduino.h>
#include "encodermotor.h"
#include <math.h>

EncoderMotor::EncoderMotor(uint8_t encoderPin,int N, int radius,
               frontback_t motorPin){
  this->encoderPin = encoderPin;
  this->N = N;
  this->radius = radius;
  this->diameter = 2*radius;
  this->motorPin   = motorPin;

  pinMode(encoderPin,    INPUT);
  pinMode(motorPin.front,OUTPUT);
  pinMode(motorPin.back, OUTPUT);

  last = digitalRead(encoderPin);

  setMotor(Action::Stop,0);
}

void EncoderMotor::setMeters(float pos){
  encoderPosition = pos * N / (PI * diameter);
}

float EncoderMotor::getMeters(){
  return encoderPosition * (PI * diameter) / N;
}

void EncoderMotor::setEncoder(int pos){
  encoderPosition = pos;
}

int EncoderMotor::getEncoder(){
  return encoderPosition;
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

Action EncoderMotor::getAction(){
  return act;
}
