void calculate_motor_speeds(){
    M1speed = base_thrust - pid_output_pitch + pid_output_roll - pid_output_yaw;        //Calculate the pulse for M1 (front-right - CCW).
    M2speed = base_thrust + pid_output_pitch + pid_output_roll + pid_output_yaw;        //Calculate the pulse for M2 (rear-right - CW).
    M3speed = base_thrust + pid_output_pitch - pid_output_roll - pid_output_yaw;        //Calculate the pulse for M3 (rear-left - CCW).
    M4speed = base_thrust - pid_output_pitch - pid_output_roll + pid_output_yaw;        //Calculate the pulse for M4 (front-left - CW).

    if (M1speed > max_thrust) M1speed = max_thrust;
    if (M1speed < min_thrust) M1speed = min_thrust;
    if (M2speed > max_thrust) M2speed = max_thrust;
    if (M2speed < min_thrust) M2speed = min_thrust;
    if (M3speed > max_thrust) M3speed = max_thrust;
    if (M3speed < min_thrust) M3speed = min_thrust;
    if (M4speed > max_thrust) M4speed = max_thrust;
    if (M4speed < min_thrust) M4speed = min_thrust;

    M1speed = map_motor_speed(M1speed);
    M2speed = map_motor_speed(M2speed);
    M3speed = map_motor_speed(M3speed);
    M4speed = map_motor_speed(M4speed);

    if (M1speed > max_pwm) M1speed = max_pwm;
    if (M1speed < min_pwm) M1speed = min_pwm;
    if (M2speed > max_pwm) M2speed = max_pwm;
    if (M2speed < min_pwm) M2speed = min_pwm;
    if (M3speed > max_pwm) M3speed = max_pwm;
    if (M3speed < min_pwm) M3speed = min_pwm;
    if (M4speed > max_pwm) M4speed = max_pwm;
    if (M4speed < min_pwm) M4speed = min_pwm;
    
}

float map_motor_speed(int Mspeed){
  float thrust = Mspeed*0.06;                                       //(Mspeed/maximum pid value)*60g
  float x1 = thrust*88;
  float x2 = thrust*thrust*-0.624;            
  float milivolts = (x1+x2);      //(-0.000624 * (thrust * thrust)) + (0.088 * thrust);
  float percentage = milivolts / battery_milivoltage;
  percentage = percentage > 1.0 ? 1.0 : percentage;
  return round(percentage * 255);
}

void set_motor_speed(){
  analogWrite(M1, (int)M1speed);
  analogWrite(M2, (int)M2speed);
  analogWrite(M3, (int)M3speed);
  analogWrite(M4, (int)M4speed);
}

void motor_stop(){
  analogWrite(M1, 0);
  analogWrite(M2, 0);
  analogWrite(M3, 0);
  analogWrite(M4, 0);
}

void start_motors(){

  for (int p=0; p < 60; p++){
  analogWrite(M1,p);
  analogWrite(M2,p);
  analogWrite(M3,p);
  analogWrite(M4,p);
  delay(20);
  }
}


void print_motor_speed(){
  if (loop_count%25 == 0){
    //Serial.print(angle_pitch);
    //Serial.print("  ");
    //Serial.print(angle_roll);
    //Serial.print("  ");
    Serial.print(M1speed);
    Serial.print("  ");
    Serial.print(M2speed);
    Serial.print("  ");
    Serial.print(M3speed);
    Serial.print("  ");
    Serial.print(M4speed);
    Serial.println("  ");
    
    loop_count = 0;
  }
  loop_count = loop_count+1;

}
