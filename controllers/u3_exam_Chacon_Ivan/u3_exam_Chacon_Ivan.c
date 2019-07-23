/*
 * File:          u3_exam_Chacon_Ivan.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/keyboard.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>

#include <stdio.h>
#include <math.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

#define PI 3.1416
#define OBSTACLE_DISTANCE 400.0

static void print_keyboard_help() {
  printf(" 'Up Arrow' key to move forward linearly at 0.3 m/s\n");
  printf(" 'Down Arrow' key to move backward linearly at 0.3 m/s\n");
  printf(" 'Left Arrow' key to move linearly to the left at 0.3 m/s\n");
  printf(" 'Right Arrow' key to move linearly to the right at 0.3 m/s\n");
  printf(" 'A' key to turn the robot left at 45 degrees/s\n");
  printf(" 'S' key to turn the robot right at 45 degrees/s\n");
  printf(" 'G' key to start Autonomous Mode for the robot\n");
  printf(" 'W' key to start Manual Mode\n");

}





/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
  /* necessary to initialize webots stuff */
  wb_robot_init();
  wb_keyboard_enable(TIME_STEP);
  print_keyboard_help();

  int pressed_key;

  float distance_left = 0;
  float distance_right = 0;
  float Encoder1 = 0;
   //float Encoder2 = 0;
   //float Encoder3 = 0;
  float Comparador = 0;
  int turn_left = 0;
  int turn_right = 0;
   //int turn_left2 = 0;
   //int turn_right2 = 0;
  int n = 1;
  int m = 0;

  // Encoder devices
 WbDeviceTag encoder1 = wb_robot_get_device("encoder_1");
 wb_position_sensor_enable(encoder1, TIME_STEP);
 //WbDeviceTag encoder2 = wb_robot_get_device("encoder_2");
 //wb_position_sensor_enable(encoder2, TIME_STEP);
 //WbDeviceTag encoder3 = wb_robot_get_device("encoder_3");
 //wb_position_sensor_enable(encoder3, TIME_STEP);


  //
   WbDeviceTag wheel_left = wb_robot_get_device("motor1");
   WbDeviceTag wheel_right = wb_robot_get_device("motor2");
   WbDeviceTag wheel_back = wb_robot_get_device("motor3");

   wb_motor_set_position(wheel_left, INFINITY);
   wb_motor_set_position(wheel_right, INFINITY);
   wb_motor_set_position(wheel_back, INFINITY);

   //Distance sensor
   WbDeviceTag sensor_left = wb_robot_get_device("distance_sensor1");
   WbDeviceTag sensor_right = wb_robot_get_device("distance_sensor2");
   wb_distance_sensor_enable(sensor_left, TIME_STEP);
   wb_distance_sensor_enable(sensor_right, TIME_STEP);




void manual(){

     //Distance Read
     distance_left = wb_distance_sensor_get_value(sensor_left);
     distance_right = wb_distance_sensor_get_value(sensor_right);

     Encoder1 = wb_position_sensor_get_value(encoder1);
     //Encoder2 = wb_position_sensor_get_value(encoder2);
     //Encoder3 = wb_position_sensor_get_value(encoder3);

     if(pressed_key == WB_KEYBOARD_UP){
       wb_motor_set_velocity(wheel_left, -5);
       wb_motor_set_velocity(wheel_right, 5);
       wb_motor_set_velocity(wheel_back, 0);
     }

     else if(pressed_key == WB_KEYBOARD_DOWN){
       wb_motor_set_velocity(wheel_left, 5);
       wb_motor_set_velocity(wheel_right, -5);
       wb_motor_set_velocity(wheel_back, 0);
     }

     else if(pressed_key == WB_KEYBOARD_LEFT){
       wb_motor_set_velocity(wheel_left, 0);
       wb_motor_set_velocity(wheel_right, -5);
       wb_motor_set_velocity(wheel_back, 5);
     }

     else if(pressed_key == WB_KEYBOARD_RIGHT){
       wb_motor_set_velocity(wheel_left, 0);
       wb_motor_set_velocity(wheel_right, 5);
       wb_motor_set_velocity(wheel_back, -5);
     }

     else if(pressed_key == 'S' ){
       Comparador = Encoder1 + 0.785398; //.75 = 45 degrees to the left
       turn_left = 1;
     }

     else if(turn_left == 1){

       if(Encoder1 <= Comparador){
       wb_motor_set_velocity(wheel_left, 5);
       wb_motor_set_velocity(wheel_right, 5);
       wb_motor_set_velocity(wheel_back, 5);
     }

       else{
       wb_motor_set_velocity(wheel_left, 0);
       wb_motor_set_velocity(wheel_right, 0);
       wb_motor_set_velocity(wheel_back, 0);
       turn_left = 0;
       }

     }

     else if(pressed_key == 'A' ){
     Comparador = Encoder1 - 0.785398; // 45 degrees to the right
     turn_right = 1;
     }

     else if(turn_right == 1){

        if(Encoder1 >= Comparador){
         wb_motor_set_velocity(wheel_left, -5);
         wb_motor_set_velocity(wheel_right, -5);
         wb_motor_set_velocity(wheel_back, -5);
        }
        else{
         wb_motor_set_velocity(wheel_left, 0);
         wb_motor_set_velocity(wheel_right, 0);
         wb_motor_set_velocity(wheel_back, 0);
         turn_right = 0;
        }
     }

     else{
       wb_motor_set_velocity(wheel_left, 0);
       wb_motor_set_velocity(wheel_right, 0);
       wb_motor_set_velocity(wheel_back, 0);
     }
   }

void automatic(){

          //Distance Read
    distance_left = wb_distance_sensor_get_value(sensor_left);
    distance_right = wb_distance_sensor_get_value(sensor_right);

    Encoder1 = wb_position_sensor_get_value(encoder1);
    //Encoder2 = wb_position_sensor_get_value(encoder2);
    //Encoder3 = wb_position_sensor_get_value(encoder3);


    wb_motor_set_velocity(wheel_left, -6.66);
    wb_motor_set_velocity(wheel_right, 6.66);
    wb_motor_set_velocity(wheel_back, 0);

   if(distance_left < distance_right && distance_left < OBSTACLE_DISTANCE){

    wb_motor_set_velocity(wheel_left, -6.66);
    wb_motor_set_velocity(wheel_right, -6.66);
    wb_motor_set_velocity(wheel_back, -6.66);
   }

   else if(distance_left > distance_right && distance_right < OBSTACLE_DISTANCE){
    wb_motor_set_velocity(wheel_left, 6.66);
    wb_motor_set_velocity(wheel_right, 6.66);
    wb_motor_set_velocity(wheel_back, 6.66);
   }

}


  wb_motor_set_velocity(wheel_left, 0);
  wb_motor_set_velocity(wheel_right, 0);
  wb_motor_set_velocity(wheel_back, 0);



while (wb_robot_step(TIME_STEP) != -1) {


    /* Process sensor data here */
  pressed_key = wb_keyboard_get_key();


  if(pressed_key == 'W'){
    m = 1;
    n = 0;
    printf("Manual mode \n");
  }


  else if (pressed_key == 'G'){
    n = 1;
    m = 0;
   printf("Automatic mode \n");
  }

  if(m == 1){
  manual();
  }

  if(n == 1){
  automatic();
  }

};

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();


  return 0;
}
