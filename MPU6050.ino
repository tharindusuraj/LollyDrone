void imu_setup(void){
  Wire.beginTransmission(gyro_address);                        //Start communication with the MPU-6050.
  Wire.write(0x6B);                                            //We want to write to the PWR_MGMT_1 register (6B hex).
  Wire.write(0x00);                                            //Set the register bits as 00000000 to activate the gyro.
  Wire.endTransmission();                                      //End the transmission with the gyro.

  Wire.beginTransmission(gyro_address);                        //Start communication with the MPU-6050.
  Wire.write(0x1B);                                            //We want to write to the GYRO_CONFIG register (1B hex).
  Wire.write(0x08);                                            //Set the register bits as 00001000 (500dps full scale).
  Wire.endTransmission();                                      //End the transmission with the gyro.

  Wire.beginTransmission(gyro_address);                        //Start communication with the MPU-6050.
  Wire.write(0x1C);                                            //We want to write to the ACCEL_CONFIG register (1A hex).
  Wire.write(0x10);                                            //Set the register bits as 00010000 (+/- 8g full scale range).
  Wire.endTransmission();                                      //End the transmission with the gyro.

  Wire.beginTransmission(gyro_address);                        //Start communication with the MPU-6050.
  Wire.write(0x1A);                                            //We want to write to the CONFIG register (1A hex).
  Wire.write(0x03);                                            //Set the register bits as 00000011 (Set Digital Low Pass Filter to ~43Hz).
  Wire.endTransmission();                                      //End the transmission with the gyro.
}

void imu_read(void) {
  Wire.beginTransmission(gyro_address);                       //Start communication with the gyro.
  Wire.write(0x3B);                                           //Start reading @ register 43h and auto increment with every read.
  Wire.endTransmission();                                     //End the transmission.
  Wire.requestFrom(gyro_address, 14);                         //Request 14 bytes from the MPU 6050.
  acc_y = Wire.read() << 8 | Wire.read();                    //Add the low and high byte to the acc_x variable.
  acc_x = Wire.read() << 8 | Wire.read();                    //Add the low and high byte to the acc_y variable.
  acc_z = Wire.read() << 8 | Wire.read();                    //Add the low and high byte to the acc_z variable.
  temperature = Wire.read() << 8 | Wire.read(); 
  gyro_roll = Wire.read() << 8 | Wire.read();                //Read high and low part of the angular data.
  gyro_pitch = Wire.read() << 8 | Wire.read();               //Read high and low part of the angular data.
  gyro_yaw = Wire.read() << 8 | Wire.read();                 //Read high and low part of the angular data.

  gyro_pitch *= -1; 
  gyro_yaw *= -1;                                              //Invert the direction of the axis.

  calculate_roll_pitch();

  angle_pitch_acc -= manual_acc_pitch_cal_value;                         //Subtact the manual accelerometer pitch calibration value.
  angle_roll_acc -= manual_acc_roll_cal_value;                          //Subtact the manual accelerometer roll calibration value.
  gyro_roll -= manual_gyro_roll_cal_value;                     //Subtact the manual gyro roll calibration value.
  gyro_pitch -= manual_gyro_pitch_cal_value;                   //Subtact the manual gyro pitch calibration value.
  gyro_yaw -= manual_gyro_yaw_cal_value;                       //Subtact the manual gyro yaw calibration value.

}

void calibrate_imu(void) {
  int cal_int = 0;
  
  double gyro_roll_cal = 0, gyro_pitch_cal=0, gyro_yaw_cal=0;
  float accel_pitch_cal=0, accel_roll_cal=0;

  Serial.println("=======================================");
  Serial.println("Calibrating Gyro");
  Serial.println("=======================================");
  
  if (cal_int != 2000) {
    //Let's take multiple gyro data samples so we can determine the average gyro offset (calibration).
    for (cal_int = 0; cal_int < 2000 ; cal_int ++) {                                  //Take 2000 readings for calibration.
      if (cal_int % 25 == 0) {digitalWrite(LED1, !digitalRead(LED1)); digitalWrite(LED2, !digitalRead(LED1));}                    //Change the led status every 125 readings to indicate calibration.
      imu_read();                                                                //Read the gyro output.
      gyro_roll_cal += gyro_roll;                                                     //Ad roll value to gyro_roll_cal.
      gyro_pitch_cal += gyro_pitch;                                                   //Ad pitch value to gyro_pitch_cal.
      gyro_yaw_cal += gyro_yaw;                                                       //Ad yaw value to gyro_yaw_cal.

      accel_pitch_cal += double(angle_pitch_acc);
      accel_roll_cal  += double(angle_roll_acc);

      delay(4);                                                                       //Small delay to simulate a 250Hz loop during calibration.
    }
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);                                                          //Set LEDs off
    //Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
    gyro_roll_cal /= 2000;                                                            //Divide the roll total by 2000.
    gyro_pitch_cal /= 2000;                                                           //Divide the pitch total by 2000.
    gyro_yaw_cal /= 2000;                                                             //Divide the yaw total by 2000.
    accel_pitch_cal /= 2000;
    accel_roll_cal /= 2000;
    manual_gyro_pitch_cal_value = gyro_pitch_cal;                                     //Set the manual pitch calibration variable to the detected value.
    manual_gyro_roll_cal_value = gyro_roll_cal;                                       //Set the manual roll calibration variable to the detected value.
    manual_gyro_yaw_cal_value = gyro_yaw_cal;                                         //Set the manual yaw calibration variable to the detected value.
    manual_acc_roll_cal_value = float(accel_roll_cal);
    manual_acc_pitch_cal_value = float(accel_pitch_cal);

    Serial.println ("Calibration Done");
    Serial.print("GyroX - ");
    Serial.print(manual_gyro_pitch_cal_value);
    Serial.print("  GyroY - ");
    Serial.print(manual_gyro_roll_cal_value);
    Serial.print("  GyroZ - ");
    Serial.print(manual_gyro_yaw_cal_value);
    Serial.print("  Pitch - ");
    Serial.print(manual_acc_pitch_cal_value);
    Serial.print("  Roll - ");
    Serial.println(manual_acc_roll_cal_value);
    
  }
}
