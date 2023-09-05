#include <Car_Library.h>

int Res = A0;
int steerMotor1 = 13;
int steerMotor2 = 12;
int rightMotor1 = 10;
int rightMotor2 = 11;
int leftMotor1 = 9;
int leftMotor2 = 8;

String send2arduino;
char spd[4];
char steer[4];
int speedi;
int steeri;
int echo_fr = 22;
int trig_fr = 23;
int echo_fl = 24;
int trig_fl = 25;

int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(steerMotor1, OUTPUT);
  pinMode(steerMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(trig_fr, OUTPUT);
  pinMode(echo_fr, INPUT);
  pinMode(trig_fl, OUTPUT);
  pinMode(echo_fl, INPUT);
}

int val2steer(int val){
  float steer;
  steer = (float(-8)/float(3) * float(val)) + float(976)/float(3);
  return steer;
}

void loop() {
  int fr;
  int fl;
  fr = ultrasonic_distance(trig_fr, echo_fr);
  fl = ultrasonic_distance(trig_fl, echo_fl);
  while(Serial.available()){
    char s = Serial.read();
    send2arduino.concat(s);
  }    
  if(send2arduino.length() == 7){
    if(send2arduino[0] == 'S'){
      send2arduino.substring(1,4).toCharArray(steer, 4);
      send2arduino.substring(4,7).toCharArray(spd, 4);
      steeri = atoi(steer);
      speedi = atoi(spd);
      send2arduino=""; 
    }
  }
  else if(send2arduino.length() > 7){
    send2arduino = "";
  }
  else if(send2arduino[0] != 'S'){
    send2arduino = ""; 
    //Serial.println("not exact string");
  }
  Serial.print("steer: ");
  Serial.println(steeri);
  Serial.print("speed: ");
  Serial.println(speedi);
  int val;
  val = potentiometer_Read(Res);
  int nSteer = val2steer(val);
  if(nSteer - steeri > 2.5){
    // Serial.println("left");
    motor_backward(steerMotor1, steerMotor2, 200);
  }
  else if(nSteer - steeri < 2.5){
    // Serial.println("right");
    motor_forward(steerMotor1, steerMotor2, 200);
  }
  else{
    // Serial.println("straight");
    motor_hold(steerMotor1, steerMotor2);
  }
  motor_forward(rightMotor1, rightMotor2, speedi); 
  motor_backward(leftMotor1, leftMotor2, speedi);
  if(fr <= 1300 || fl <= 1300){
    if(cnt == 0){
      int sTime = millis();
      int nTime = millis();
      while(nTime - sTime <= 3500){
        motor_backward(steerMotor1, steerMotor2, 255);
        motor_backward(leftMotor1, leftMotor2, 130);
        motor_forward(rightMotor1, rightMotor2, 130); 
        cnt = 1;
        nTime = millis();
      }
      sTime = millis();
      nTime = millis();
      while(nTime - sTime <= 2200){
        motor_forward(steerMotor1, steerMotor2, 255);
        motor_backward(leftMotor1, leftMotor2, 130);
        motor_forward(rightMotor1, rightMotor2, 130); 
        cnt = 1;
        nTime = millis();
      }
    }
    else if(cnt == 1){
      int sTime = millis();
      int nTime = millis();
      while(nTime - sTime <= 4500){
        motor_forward(steerMotor1, steerMotor2, 255);
        motor_backward(leftMotor1, leftMotor2, 130);
        motor_forward(rightMotor1, rightMotor2, 130); 
        cnt = 2;
        nTime = millis();
      }
      sTime = millis();
      nTime = millis();
      while(nTime - sTime <= 2200){
        motor_backward(steerMotor1, steerMotor2, 255);
        motor_backward(leftMotor1, leftMotor2, 130);
        motor_backward(rightMotor2, rightMotor1, 130);
        cnt = 2;
        nTime = millis();
      }
    }
  }
}

// left=137
// right=107
// mid = 122
