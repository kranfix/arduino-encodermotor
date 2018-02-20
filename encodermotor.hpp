#pragma once

#include <stdint.h>

enum class Action{Stop,Forward,Backward};

typedef struct {
  uint8_t front;
  uint8_t back;
} frontback_t;

class EncoderMotor{
  // Encoder
  uint8_t encoderPin;
  int encoderPosition;
  int limit;
  int N; // number or slots
  float radius;
  float diameter;
  uint8_t last; // last encoder read: 0 or 1
  uint8_t event;

  // Motor
  frontback_t motorPin;
  Action act;
public:
  EncoderMotor(uint8_t encoderPin,int N, int radius, frontback_t motorPin);
  void  setMeters(float pos);
  float getMeters();
  void  setEncoder(int pos);
  int   getEncoder();
  void  setMotor(Action act, float limit);
  void  loop();
  bool  encoderEvent();
  Action getAction();
};
