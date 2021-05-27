#include <Wire.h>   
#include "variables.h";
int loop_count = 0;

void setup() {
  Wire.begin();
//  TWBR = 12;                                                                //Set the I2C clock speed to 400kHz.
  
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);

  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(M3,OUTPUT);
  pinMode(M4,OUTPUT);

  Serial.begin(115200);
  
  delay(5000);
  
  
  imu_setup();              //start imu communication
  
  //calibrate_imu();


  delay(5000);
/*
    analogWrite(M1,50);
    analogWrite(M2,50);
    analogWrite(M3,50);
    analogWrite(M4,50);

    delay(10000);

    analogWrite(M1,0);
    analogWrite(M2,0);
    analogWrite(M3,0);
    analogWrite(M4,0);

  
  */
  balance_test();
}

void loop() {

  delay(10);

  
}

void balance_test(){
  init_flying();

  while(millis() < 30000){
    start_flying();  
 }
 
 motor_stop();
 delay(500);
 init_flying();
 pid_p_gain_roll = 11.0;
 pid_p_gain_pitch = pid_p_gain_roll;

 while(millis() < 40000){
    start_flying();  
 }

 motor_stop();
 delay(500);
 init_flying();
 pid_p_gain_roll = 12.0;
 pid_p_gain_pitch = pid_p_gain_roll;

 while(millis() < 50000){
    start_flying();  
 }

 motor_stop();
 delay(500);
 init_flying();
 pid_p_gain_roll = 13.0;
 pid_p_gain_pitch = pid_p_gain_roll;

 while(millis() < 60000){
    start_flying();  
 }

 motor_stop();
 delay(500);
 init_flying();
 pid_p_gain_roll = 14.0;
 pid_p_gain_pitch = pid_p_gain_roll;

 while(millis() < 70000){
    start_flying();  
 }

 motor_stop();
 delay(500);
 init_flying();
 pid_p_gain_roll = 15.0;
 pid_p_gain_pitch = pid_p_gain_roll;

 while(millis() < 80000){
    start_flying();  
 }
 
 motor_stop();
}
void motor_test(){
  
  delay(2000);
  digitalWrite(LED4,HIGH);
  delay(2000);
  digitalWrite(LED3,HIGH);
  delay(2000);

 /* 96 -  37.5%
  *  112 - 43.75%
  *  128 - 50%
  *  144 - 56.25%
  *  160 - 62.5%
  *  176 - 68.75%
  *  192 - 75%
  *  208 - 81.25%
  *  224 - 87.5%
  *  240 - 93.75%
 */
  //int pwm[] = {96,112,128,144,160,176,192,208,224,240,0}; 

  int pwm[] = {100,150,200,0}; 

  for (int i=0; i<4; i++){
    analogWrite(M1,pwm[i]);
    analogWrite(M2,pwm[i]);
    analogWrite(M3,pwm[i]);
    analogWrite(M4,pwm[i]);

    delay(5000);
  }

  digitalWrite(LED4,LOW);
  digitalWrite(LED3,LOW);
}

void led_bar(){
  if (abs(angle_pitch)>10){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,HIGH);
  }
  else if (abs(angle_pitch)>7){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,HIGH);
    digitalWrite(LED4,LOW);
  }
  else if (abs(angle_pitch)>4){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,HIGH);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (abs(angle_pitch)>2){
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
  else if (abs(angle_pitch)>0){
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,LOW);
  }
}
