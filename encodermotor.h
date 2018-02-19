#pragma once

enum class Action{Stop,Forward,Backward};

typedef struct {
  byte front;
  byte back;
} frontback_t;

class MotorEncoder(){
  // Encoder
  byte encoderPin;
  int encoderPostion;
  int limit;
  int N; // number or slots
  float radius;
  byte last; // last encoder read: 0 or 1
  byte event;
  
  
  // Motor
  frontback_t motorPin;
  Action act;
public:
  MotorEncoder(byte encoderPin,int N, int radius
               frontback_t motorPin);
  void setLinearPosition(float pos);
  void setMotor(Action act, int limit);
  void loop();
  bool encoderEvent();
};

