void comp_filter(){
   //65.5 = 1 deg/sec (check the datasheet of the MPU-6050 for more information).
  gyro_roll_input = (gyro_roll_input * 0.7) + (((float)gyro_roll / 65.5) * 0.3);   //Gyro pid input is deg/sec.
  gyro_pitch_input = (gyro_pitch_input * 0.7) + (((float)gyro_pitch / 65.5) * 0.3);//Gyro pid input is deg/sec.
  gyro_yaw_input = (gyro_yaw_input * 0.7) + (((float)gyro_yaw / 65.5) * 0.3);      //Gyro pid input is deg/sec.

  //Gyro angle calculations
  //0.0000611 = 1 / (250Hz / 65.5)
  angle_pitch += (float)gyro_pitch * 0.0000611;                                    //Calculate the traveled pitch angle and add this to the angle_pitch variable.
  angle_roll += (float)gyro_roll * 0.0000611;                                      //Calculate the traveled roll angle and add this to the angle_roll variable.
  
  angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;                   //Correct the drift of the gyro pitch angle with the accelerometer pitch angle.
  angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;                      //Correct the drift of the gyro roll angle with the accelerometer roll angle.
  
}

void calculate_roll_pitch(){
  
  //Accelerometer angle calculations
  acc_total_vector = (sqrt((acc_y * acc_y) + (acc_z * acc_z)));    //Calculate the total accelerometer vector.
  
  angle_roll_acc = atan2(acc_x, acc_total_vector)*57.296;              //Calculate the pitch angle.
  angle_pitch_acc = atan2(acc_y, acc_z) * 57.296;               //Calculate the roll angle.
}

void calculate_pid(){

  //Pitch correction-----------------------------------------------------------------------------------------------------------
  float curr_pitch_error = angle_pitch - pid_pitch_setpoint;
  float pitch_error_d    = (curr_pitch_error - last_pitch_error)*250;

  pitch_error_i += pid_i_gain_pitch*curr_pitch_error;
  last_pitch_error = curr_pitch_error;

  pitch_error_i = pitch_error_i > pid_max_pitch ? pid_max_pitch : pitch_error_i;
  pitch_error_i = pitch_error_i < -pid_max_pitch ? -pid_max_pitch : pitch_error_i;

  pid_output_pitch = (pid_p_gain_pitch*curr_pitch_error) + (pitch_error_i) + (pid_d_gain_pitch*pitch_error_d);


  //Roll correction-----------------------------------------------------------------------------------------------------------
  float curr_roll_error = angle_roll - pid_roll_setpoint;
  float roll_error_d    = (curr_roll_error - last_roll_error)*250;

  roll_error_i += pid_i_gain_roll*curr_roll_error;
  last_roll_error = curr_roll_error;

  roll_error_i = roll_error_i > pid_max_roll ? pid_max_roll : roll_error_i;
  roll_error_i = roll_error_i < -pid_max_roll ? -pid_max_roll : roll_error_i;

  pid_output_roll = (pid_p_gain_roll*curr_roll_error) + (roll_error_i) + (pid_d_gain_roll*roll_error_d);


  //yaw correction-----------------------------------------------------------------------------------------------------------

  float curr_yaw_error = gyro_yaw_input - pid_yaw_setpoint;
  float yaw_error_d    = (curr_yaw_error - last_yaw_error)*250;

  yaw_error_i += pid_i_gain_yaw*curr_yaw_error;
  last_yaw_error = curr_yaw_error;

  yaw_error_i = yaw_error_i > pid_max_yaw ? pid_max_yaw : yaw_error_i;
  yaw_error_i = yaw_error_i < -pid_max_yaw ? -pid_max_yaw : yaw_error_i;

  pid_output_yaw = (pid_p_gain_yaw*curr_yaw_error) + (yaw_error_i) + (pid_d_gain_yaw*yaw_error_d);
  



















  /*
  //Roll calculations
  pid_error_temp = angle_roll - pid_roll_setpoint;
  pid_i_mem_roll += pid_i_gain_roll * pid_error_temp;
  if(pid_i_mem_roll > pid_max_roll)pid_i_mem_roll = pid_max_roll;
  else if(pid_i_mem_roll < pid_max_roll * -1)pid_i_mem_roll = pid_max_roll * -1;

  pid_output_roll = pid_p_gain_roll * pid_error_temp + pid_i_mem_roll + pid_d_gain_roll * (pid_error_temp - pid_last_roll_d_error);
  if(pid_output_roll > pid_max_roll)pid_output_roll = pid_max_roll;
  else if(pid_output_roll < pid_max_roll * -1)pid_output_roll = pid_max_roll * -1;

  pid_last_roll_d_error = pid_error_temp;

  //Pitch calculations
  pid_error_temp = angle_pitch - pid_pitch_setpoint;
  pid_i_mem_pitch += pid_i_gain_pitch * pid_error_temp;
  if(pid_i_mem_pitch > pid_max_pitch)pid_i_mem_pitch = pid_max_pitch;
  else if(pid_i_mem_pitch < pid_max_pitch * -1)pid_i_mem_pitch = pid_max_pitch * -1;

  pid_output_pitch = pid_p_gain_pitch * pid_error_temp + pid_i_mem_pitch + pid_d_gain_pitch * (pid_error_temp - pid_last_pitch_d_error);
  if(pid_output_pitch > pid_max_pitch)pid_output_pitch = pid_max_pitch;
  else if(pid_output_pitch < pid_max_pitch * -1)pid_output_pitch = pid_max_pitch * -1;

  pid_last_pitch_d_error = pid_error_temp;

  //Yaw calculations
  pid_error_temp = gyro_yaw_input - pid_yaw_setpoint;
  pid_i_mem_yaw += pid_i_gain_yaw * pid_error_temp;
  if(pid_i_mem_yaw > pid_max_yaw)pid_i_mem_yaw = pid_max_yaw;
  else if(pid_i_mem_yaw < pid_max_yaw * -1)pid_i_mem_yaw = pid_max_yaw * -1;

  pid_output_yaw = pid_p_gain_yaw * pid_error_temp + pid_i_mem_yaw + pid_d_gain_yaw * (pid_error_temp - pid_last_yaw_d_error);
  if(pid_output_yaw > pid_max_yaw)pid_output_yaw = pid_max_yaw;
  else if(pid_output_yaw < pid_max_yaw * -1)pid_output_yaw = pid_max_yaw * -1;

  pid_last_yaw_d_error = pid_error_temp;*/
}
