#include <encodermotor.h>

/* Encoder Motor */
#define encoderPin  4
#define N    40     //Slots
#define radius 0.7  // r=0.7cm

#define MotorForward      9
#define MotorBackward    10

EncoderMotor em(encoderPin,N,radius,{MotorForward,MotorBackward});

/* Setup and loop */
void setup(){
  Serial.begin(9600);
  delay(10);
  Serial.println("Initializing Encoder-Motor ...");
}

byte eventReported = 0;
void loop(){
  // Avoid using delay function. Use millis or micros instead
  em.loop();

  if(em.encoderEvent() && !eventReported){
    Serial.println("Limit reached!");
  }

  if(Serial.available()){
    char c = Serial.read();
    if(c == 'F'){
      // The motor will go forward till 100cm position
      em.setMotor(Action::Forward,100);
      eventReported = 0;
    } else if(c == 'B'){
      // The motor will go back till 0 cm position.
      em.setMotor(Action::Backward,0);
      eventReported = 0;
    } else if(c == 'S'){
      // Stops the motor. The limit could be any number.
      em.setMotor(Action::Stop,0);
      eventReported = 0;
    } else {
      Serial.println("Error: Character not valid. User F, B or S.");
    }
  }
}

