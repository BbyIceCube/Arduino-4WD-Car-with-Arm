#include <Servo.h>
#include <SoftwareSerial.h>
#define trig A1
#define echo A0
SoftwareSerial myBt(10,11);

Servo wrist;
Servo elbow;
Servo base;
Servo hand;
int bAngle = 0;
int eAngle = 90;
int wAngle = 180;
int hAngle = 90;

bool isAuto = false;

int in1=9;
int in2=8;
int in3=7;
int in4=6;
char data;

void setup() {
  Serial.begin(9600);
  myBt.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  wrist.attach(5);
  elbow.attach(4);
  hand.attach(2);
  base.attach(3);
  wrist.write(wAngle);
  elbow.write(eAngle);
  hand.write(hAngle);
  base.write(bAngle);

  stop();
  delay(500);
  digitalWrite(trig,LOW);

}

void loop() {
  if(myBt.available()>0){
    data = myBt.read();
    Serial.println(data);

    if(data == 'A'){
      isAuto = true;
      stop();
      Serial.println("AutoMode");
    }
    if(data == 'B'){
      isAuto = false;
      stop();
      Serial.println("ManualMode");
    }
    
  if(data == '#'){
      if(bAngle > 180){
        bAngle = 180;
      }
      bAngle+=10;
      base.write(bAngle);
    }

    if(data == 'D'){
      if(bAngle < 0){
        bAngle = 0;
      }
      bAngle-=10;
      base.write(bAngle);
    }

    if(data == '7'){
      if(eAngle > 150){
        eAngle = 150;
      }
      eAngle+=10;
      elbow.write(eAngle);
    }

    if(data == '1'){
      if(eAngle < 30){
        eAngle = 30;
      }
      eAngle-=10;
      elbow.write(eAngle);
    }

    if(data == '3'){
      if(wAngle > 180){
        wAngle = 180;
      }
      wAngle+=10;
      wrist.write(wAngle);
    }

    if(data == '9'){
      if(wAngle < 0){
        wAngle = 0;
      }
      wAngle-=10;
      wrist.write(wAngle);
    }

    if(data == '*'){
      if(hAngle > 120){
        hAngle = 120;
      }
      hAngle+=10;
      hand.write(hAngle);
    }

    if(data == '0'){
      if(hAngle < 40){
        hAngle = 40;
      }
      hAngle-=10;
      hand.write(hAngle);
    }
  }

  // Auto
  if(isAuto){
    float dis = getDistance();
  Serial.println(dis);
  if(dis > 0 && dis <= 13.0){
    stop();
    delay(200);

    left();
    delay(1600);
    stop();
    delay(300);

    dis = getDistance();
    Serial.print("Left check: ");
    Serial.println(dis);

    if(dis < 0 || dis > 13.0){
      forward();
      delay(500);
      return;
    }

    right();
    delay(2500);
    stop();
    delay(300);

    dis = getDistance();
    Serial.print("Right Check: ");
    Serial.println(dis);

    if(dis < 0 || dis > 13.0){
      forward();
      delay(500);
      return;
    }

    right();
    delay(1000);
    stop();
    delay(300);

    forward();
    delay(500);
  }else {
    forward();
  }
  delay(100);
  return;
  }
  
  if(data == '2'){
    forward();
  }
  if(data == '5'){
    backward();
  }
  if(data == '4'){
    left();
  }
  if(data == '6'){
    right();
  }
  if(data == '8'){
    stop();
  }
}

void left(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void forward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

float getDistance(){
  digှitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);

  if(duration == 0) return -1;

  float distance = (duration * 0.0343) /2.0;
  return distance;
}
