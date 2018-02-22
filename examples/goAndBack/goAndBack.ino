#include <encodermotor.h>

/* Encoder Motor */
#define encoderPin  4
#define N    40     //Slots
#define radius 0.7  // r=0.7cm

#define MotorForward      9
#define MotorBackward    10

EncoderMotor em(encoderPin,N,radius,{MotorForward,MotorBackward});

unsigned long last,now;

/* Setup and loop */
void setup(){
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(10);
  Serial.println("Initializing Encoder-Motor ...");
  now = millis();
  last = now;
}

byte eventReported = 0;
void loop(){
  // Avoid using delay function. Use millis or micros instead
  em.loop();

  if(em.encoderEvent() && !eventReported){
    Serial.println("Limit reached!");
    eventReported = true;
  }

  if(Serial.available()){
    char c = Serial.read();
    if(c == 'F'){
      // The motor will go forward till 100cm position
      em.setMotor(Action::Forward,100);
      eventReported = false;
    } else if(c == 'B'){
      // The motor will go back till 0 cm position.
      em.setMotor(Action::Backward,0);
      eventReported = false;
    } else if(c == 'S'){
      // Stops the motor. The limit could be any number.
      em.setMotor(Action::Stop,0);
      eventReported = false;
    } else {
      Serial.println("Error: Character not valid. User F, B or S.");
    }
  }

  em.loop();
  now = millis();
  if(now-last >= 1000){
    last = now;
    Serial.println();
    Serial.print("Encoder: ");
    Serial.print(em.getEncoder());
    Serial.print(" Slots <> ");
    Serial.print(em.getLong());
    Serial.println("cm");
    Serial.print("Evento[");
    Serial.print((int)em.getAction());
    Serial.print("]: ");
    Serial.println(em.encoderEvent());
  }
}
