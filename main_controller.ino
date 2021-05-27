void start_flying(){
  //Serial.print(micros());
  //Serial.print("  ");
  imu_read();
  comp_filter();

  calculate_pid();

  calculate_motor_speeds();
  set_motor_speed();
  //print_motor_speed();

  if (abs(angle_pitch) > 75.0 or abs(angle_roll)>75.0){
     motor_stop();
     digitalWrite(LED1, HIGH);
     digitalWrite(LED2, LOW);
     digitalWrite(LED3, LOW);
     digitalWrite(LED4, LOW);
     while(1);
  }
  led_bar();
  //Serial.println(micros());
  automatic_delay();
}

void init_flying(){


    //Reset the PID controllers for a bumpless start.
    pid_i_mem_roll = 0;
    pid_last_roll_d_error = 0;
    pid_i_mem_pitch = 0;
    pid_last_pitch_d_error = 0;
    pid_i_mem_yaw = 0;
    pid_last_yaw_d_error = 0;

    pitch_error_i = 0;
    last_pitch_error = 0;
    roll_error_i = 0;
    last_roll_error = 0;
    yaw_error_i = 0;
    last_yaw_error = 0;

    pid_roll_setpoint = 2.0;
    pid_pitch_setpoint = 4.0;
    pid_yaw_setpoint = 0.0;

    
    start_motors();                                               //set initial motor speeds
    imu_read();
    angle_pitch = angle_pitch_acc;                                                 //Set the gyro pitch angle equal to the accelerometer pitch angle when the quadcopter is started.
    angle_roll = angle_roll_acc;                                                   //Set the gyro roll angle equal to the accelerometer roll angle when the quadcopter is started.
    update_angles();                                              //run the filter for 1 second
    delay(100);
    loop_timer = micros();                                        //Set the timer for the first loop.
}

void update_angles(){
  for(int i=0; i<250;i++){
    imu_read();
    comp_filter();
    delay(4);
  }
}


void automatic_delay(){
  if (micros() - loop_timer > 4050){                                      //Turn on the LED if the loop time exceeds 4050us.
    motor_stop();
    while(1){
      digitalWrite(LED4,HIGH);
      delay(50);
    }
  }
  while (micros() - loop_timer < 4000){}                                            //We wait until 4000us are passed.
  loop_timer = micros();   
}
