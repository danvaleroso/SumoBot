#include "NewPing.h"

int RtrigPin = 6;
int RechoPin = 7;
int FtrigPin = 4;
int FechoPin = 5;
int LtrigPin = 2;
int LechoPin = 3;
int BtrigPin = A1;
int BechoPin = A0;
#define maxdistance 70
NewPing sonar1(RtrigPin, RechoPin, maxdistance);
NewPing sonar2(FtrigPin, FechoPin, maxdistance);
NewPing sonar3(LtrigPin, LechoPin, maxdistance);
NewPing sonar4(BtrigPin, BechoPin, maxdistance);
float Rdistance, Rduration,Ldistance, Lduration,Fdistance, Fduration,Bdistance, Bduration;


int onstate = LOW;

int enA = 13;
int in1 = 12;
int in2 = 11;
int enB = 8;
int in3 = 10;
int in4 = 9;

int Lsen1 = A5 ;
int Lsen2 = A4 ;
int Lsen3 = A3 ;
int Lsen4 = A2;
int x = A6;
int y = A7;
int LDR1;
int LDR2;
int LDR3;
int LDR4;

int maxrange = 60;

unsigned long previousMillis = 0; 
const long interval = 30;
const long interval2 = 500;

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(Lsen1,INPUT);
  pinMode(Lsen2,INPUT);
  pinMode(Lsen3,INPUT);
  pinMode(Lsen4,INPUT);
  pinMode(x,INPUT);
  pinMode(y,INPUT);
  delay(3000); 

 Serial.begin (9600);
}
void motorcontrol(int m1,boolean f1,boolean b1,boolean f2,boolean b2, int m2)
{
  digitalWrite(in1,f1 );
  digitalWrite(in2, b1);
  analogWrite(enA, m1);
  digitalWrite(in3, f2);
  digitalWrite(in4, b2);
  analogWrite(enB, m2);
 
}
void STOP(){
  motorcontrol(255,LOW,LOW,LOW,LOW,255);
}
void FORWARD(){
  
  motorcontrol(255,HIGH,LOW,HIGH,LOW,255);
 
}
void BACKWARD(){
  motorcontrol(255,LOW,HIGH,LOW,HIGH,255);

}
void ROTATELEFT(){
  motorcontrol(255,HIGH,LOW,LOW,HIGH,255);

}
void ROTATERIGHT(){
  motorcontrol(255,LOW,HIGH,HIGH,LOW,255);

}
void LEFT(){
  motorcontrol(255,HIGH,LOW,LOW,LOW,255);
  
}
void LEFTBACK(){
  motorcontrol(255,LOW,HIGH,LOW,LOW,255);
  
}
void RIGHT(){
  motorcontrol(255,LOW,LOW,HIGH,LOW,255);
   
}
void RIGHTBACK(){
  motorcontrol(255,LOW,LOW,LOW,HIGH,255);
   
}






void FORWARD1(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (onstate == LOW) {
      onstate = HIGH;
      FORWARD();
    } else {
      onstate = LOW;
      STOP();
    }
  }
}
void BACKWARD1(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (onstate == LOW) {
      onstate = HIGH;
      BACKWARD();
    } else {
      onstate = LOW;
      STOP();
    }
  }
}
void ROTATELEFT1(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (onstate == LOW) {
      onstate = HIGH;
      ROTATELEFT();
    } else {
      onstate = LOW;
      STOP();
    }
  }
}
void ROTATERIGHT1(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    
    previousMillis = currentMillis;

    if (onstate == LOW) {
      onstate = HIGH;
      ROTATERIGHT();
    } else {
      onstate = LOW;
      STOP();
    }
  }
}





void UsensorR(){
  Rduration = sonar1.ping();
  Rdistance = (Rduration/2)*0.0343; 
}

void UsensorF(){
  Fduration = sonar2.ping();
  Fdistance = (Fduration/2)*0.0343; 
}

void UsensorL(){
  Lduration = sonar3.ping();
  Ldistance = (Lduration/2)*0.0343; 
}

void UsensorB(){
  Bduration = sonar4.ping();
  Bdistance = (Bduration/2)*0.0343; 
}


void movement(){
  if (Fdistance == 0 && Bdistance == 0 && Ldistance == 0 && Rdistance == 0){
  ROTATELEFT1();}
  if(Fdistance < maxrange && Fdistance > 0){
    FORWARD();
  }else if(Rdistance < maxrange && Rdistance > 0){
    ROTATERIGHT();
  }else if(Ldistance < maxrange && Ldistance > 0){
    ROTATELEFT();
  }else if(Bdistance < maxrange && Bdistance > 0){
    ROTATERIGHT();
    delay(250);
  }else if (Fdistance == 0 && Bdistance == 0 && Ldistance == 0 && Rdistance == 0){
  ROTATELEFT1();
  }else {
    STOP();
  }  
}
void loop()

{

 UsensorL();
 UsensorB();
 UsensorF();
 UsensorR();
 LDR1 = digitalRead(Lsen1);
 LDR2 = digitalRead(Lsen2);
 LDR3 = digitalRead(Lsen3);
 LDR4 = digitalRead(Lsen4);

  if(LDR1 == 0 && LDR2 == 0){
    BACKWARD();
    delay(300);
    movement();
  }else if(LDR1 == 0 && LDR3 == 0){
    LEFTBACK();
    delay(200);
     movement();
  } else if(LDR2 == 0 && LDR4 == 0){
    RIGHTBACK();
    delay(200);
     movement();
  }else if(LDR1 == 0){
    BACKWARD();
    delay(200);
     movement();
  }else if(LDR2 == 0){
    BACKWARD();
    delay(200);
     movement();
  }else if(LDR3 == 0){
    FORWARD1();
    delay(200);
     movement();
  }else if(LDR4 == 0){
    FORWARD1();
    delay(200);
     movement();
  }else if (LDR1 == 0 && LDR2 == 0 && LDR3 == 0 &&LDR4 == 0 &&){
  STOP();
 }
}

 
