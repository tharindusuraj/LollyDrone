#define LED1 A0
#define LED2 A1
#define LED3 A2
#define LED4 A3

#define M1 9
#define M2 5
#define M3 6
#define M4 3

float pid_p_gain_roll = 8.0;               //Gain setting for the pitch and roll P-controller (default = 1.3).
float pid_i_gain_roll = 0.0;              //Gain setting for the pitch and roll I-controller (default = 0.04).
float pid_d_gain_roll = 4.0;              //Gain setting for the pitch and roll D-controller (default = 18.0).
int pid_max_roll = 400;                    //Maximum output of the PID-controller (+/-).

float pid_p_gain_pitch = pid_p_gain_roll;  //Gain setting for the pitch P-controller.
float pid_i_gain_pitch = pid_i_gain_roll;  //Gain setting for the pitch I-controller.
float pid_d_gain_pitch = pid_d_gain_roll;  //Gain setting for the pitch D-controller.
int pid_max_pitch = pid_max_roll;          //Maximum output of the PID-controller (+/-).

float pid_p_gain_yaw = 0.5;                //Gain setting for the pitch P-controller (default = 4.0).
float pid_i_gain_yaw = 0.02;               //Gain setting for the pitch I-controller (default = 0.02).
float pid_d_gain_yaw = 0.0;                //Gain setting for the pitch D-controller (default = 0.0).
int pid_max_yaw = 400;                     //Maximum output of the PID-controller (+/-).

int min_thrust  = 20;
int max_thrust  = 1000;
int base_thrust = 680;

int max_pwm = 255;
int min_pwm = 20;

int M1speed,M2speed,M3speed,M4speed;

uint8_t gyro_address = 0x68;               //The I2C address of the MPU-6050 is 0x68 in hexadecimal form.

float acc_x, acc_y, acc_z;
int temperature;
int gyro_pitch, gyro_roll, gyro_yaw;

//Manual accelerometer calibration values for IMU angles:
float manual_acc_pitch_cal_value = 2.41;
float manual_acc_roll_cal_value = -0.9;

//Manual gyro calibration values.
int manual_gyro_pitch_cal_value = 20;
int manual_gyro_roll_cal_value = 50;
int manual_gyro_yaw_cal_value = 25;
float acc_total_vector;

double loop_timer, error_timer;

float last_pitch_error = 0.0, last_roll_error = 0.0, last_yaw_error = 0.0;
float pitch_error_i = 0.0, roll_error_i = 0.0, yaw_error_i = 0.0;

float roll_level_adjust, pitch_level_adjust;
float pid_error_temp;
float pid_i_mem_roll, pid_roll_setpoint, gyro_roll_input, pid_output_roll, pid_last_roll_d_error;
float pid_i_mem_pitch, pid_pitch_setpoint, gyro_pitch_input, pid_output_pitch, pid_last_pitch_d_error;
float pid_i_mem_yaw, pid_yaw_setpoint, gyro_yaw_input, pid_output_yaw, pid_last_yaw_d_error;
float angle_roll_acc, angle_pitch_acc, angle_pitch, angle_roll;
float battery_milivoltage = 3200;
