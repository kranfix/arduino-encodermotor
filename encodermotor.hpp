#pragma once

#include <stdint.h>

enum class Action: uint8_t{Stop,Forward,Backward};

typedef struct {
  uint8_t front;
  uint8_t back;
} frontback_t;

class EncoderMotor{
  // Encoder
  uint8_t encoderPin;
  int limit;
  int N; // number or slots
  float radius;
  float diameter;
  uint8_t last; // last encoder read: 0 or 1

  // Motor
  frontback_t motorPin;
public:
  int encoderPosition;
  Action act;
  uint8_t event;

  EncoderMotor(uint8_t encoderPin,int N, float radius, frontback_t motorPin);
  void  setLong(float pos);
  float getLong();
  void  setEncoder(int pos);
  int   getEncoder();
  void  setMotor(Action act, float limit);
  void  loop();
  bool  encoderEvent();
  Action getAction();
};
