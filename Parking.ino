#include "Car_Library.h"

int Res = A0;
int steerMotor1 = 13;
int steerMotor2 = 12;
int rightMotor1 = 11;
int rightMotor2 = 10;
int leftMotor1 = 9;
int leftMotor2 = 8;

int echo_fr = 22;
int trig_fr = 23;
int echo_fl = 24;
int trig_fl = 25;
int echo_sfr = 26;
int trig_sfr = 27;
//int echo_sfl = 28;
//int trig_sfl = 29;
int echo_srr = 30;
int trig_srr = 31;
//int echo_srl = 32;
//int trig_srl = 33;

String send2arduino;
char spd[4];
char steer[4];
int speedi;
int steeri;

int first = 0;
int count = 0;

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
  pinMode(trig_sfr, OUTPUT);
  pinMode(echo_sfr, INPUT);
  pinMode(trig_srr, OUTPUT);
  pinMode(echo_srr, INPUT);
}

int val2steer(int val){
  float steer;
  steer = (float(-8)/float(3) * float(val)) + float(976)/float(3);
  return steer;
}
void set_straight(int val){
  
  if(val > 121){
    motor_forward(steerMotor1, steerMotor2, 255);
  }
  
  else if(val < 119){
    motor_backward(steerMotor1, steerMotor2, 255);
  }
  else{
    motor_hold(steerMotor1, steerMotor2);
  }
}

void set_straight2(int val){
  if(val < 117){
    while(val < 117){
      motor_forward(steerMotor1, steerMotor2, 255);
      val = potentiometer_Read(Res);
    }
  } 
  else if(val > 123){
    while(val > 123){
     motor_forward(steerMotor1, steerMotor2, 255);
     val = potentiometer_Read(Res);
    }
  }
  else{
    motor_hold(steerMotor1, steerMotor2);
  }
}

void set_straight3(int val){
  Serial.print("set_st3");
  while( val != 121){
  if(val > 121){
    motor_forward(steerMotor1, steerMotor2, 160);
  }
  
  else if(val < 119){
    motor_backward(steerMotor1, steerMotor2, 160);
  }
  else{
    motor_hold(steerMotor1, steerMotor2);
    break;
  }
  val = potentiometer_Read(Res);
  }
}

void loop() {
  int val;
  val = potentiometer_Read(Res);
  set_straight(val);
  set_straight3(val);
  Serial.println(val);
  if(first == 0){
    set_straight(val);
    first = 1;
  }
  
//  if(send2arduino[0] == 'P'){
    int dist_sfr, dist_srr;
    dist_sfr = ultrasonic_distance(trig_sfr, echo_sfr);
    dist_srr = ultrasonic_distance(trig_srr, echo_srr);
    Serial.print("sfr: ");
    Serial.println(dist_sfr);
    Serial.print("srr: ");
    Serial.println(dist_srr);
    Serial.print("count: ");
    Serial.println(count);
     
    if (dist_sfr <= 1000 && dist_srr <= 1000)//Obstacle detection
    {
      count = 1;
      Serial.print("count: ");
      Serial.println(count);
    }
    else if (count == 0)//Go straight
    {
      Serial.println("parking start");
      motor_hold(steerMotor1, steerMotor2);
      drive_forward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 100);
    }
    else if ( count == 1 && dist_sfr >= 1500 && dist_srr >= 1500)//parking
    {
      count = 2;
      Serial.print("count : ");
      Serial.println(count);
      set_straight(val);
      drive_forward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 100);
      delay(500);
      motor_backward(steerMotor1, steerMotor2, 155);//left
      delay(5700);
      drive_stop(leftMotor1, leftMotor2, rightMotor2, rightMotor1);//stop
      motor_forward(steerMotor1, steerMotor2, 255);//right
      delay(1000);
      drive_backward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 100);//back
      delay(7200);
      drive_stop(leftMotor1, leftMotor2, rightMotor2, rightMotor1);
      delay(1000);
      val = potentiometer_Read(Res);
      Serial.println("Before straight");
      set_straight3(val);
      delay(1000);
      drive_backward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 100);//back
      delay(2500);
      drive_stop(leftMotor1, leftMotor2, rightMotor2, rightMotor1);
      delay(3000);
      // parking finish
      drive_forward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 100);
      delay(2500);
      drive_forward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 100);
      motor_backward(steerMotor1, steerMotor2, 255);//right
      delay(11300);
      drive_stop(leftMotor1, leftMotor2, rightMotor2, rightMotor1);
      delay(1000);
      val = potentiometer_Read(Res);
      set_straight3(val);
      delay(1000);
      val = potentiometer_Read(Res);
      set_straight3(val);
      Serial.println(val);
      delay(1000);
      drive_forward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 255);
      delay(20000);
    }
    else if(count == 2)//escape
    {
      Serial.print("count: ");
      Serial.println(count);
      drive_forward(leftMotor1, leftMotor2, rightMotor2, rightMotor1, 160);
      delay(2000);
      motor_backward(steerMotor1, steerMotor2, 255);//left
      delay(4000);
      
      val = potentiometer_Read(Res);
      while(val > 122){
        motor_forward(steerMotor1, steerMotor2, 160);//right
        val = potentiometer_Read(Res);
      }
      delay(5000);
      drive_stop(leftMotor1, leftMotor2, rightMotor2, rightMotor1);
    }
//  }

}

// left=137
// right=107
// mid = 122
