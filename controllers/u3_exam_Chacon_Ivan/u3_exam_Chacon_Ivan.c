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
#define OBSTACLE_DISTANCE 20.0


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

  int pressed_key;

  //

   float distance_left = 0;
   float distance_right = 0;
   float Encoder1 = 0;
   float Encoder2 = 0;
   float Encoder3 = 0;
   float Comparador = 0;
   int gira_izq = 0;
   int gira_der = 0;

  // Encoder devices
 WbDeviceTag encoder1 = wb_robot_get_device("encoder_1");
 wb_position_sensor_enable(encoder1, TIME_STEP);
 WbDeviceTag encoder2 = wb_robot_get_device("encoder_2");
 wb_position_sensor_enable(encoder2, TIME_STEP);
 WbDeviceTag encoder3 = wb_robot_get_device("encoder_3");
 wb_position_sensor_enable(encoder3, TIME_STEP);


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






  while (wb_robot_step(TIME_STEP) != -1) {



    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */

    /* Process sensor data here */
  pressed_key = wb_keyboard_get_key();

  //Distance Read
  distance_left = wb_distance_sensor_get_value(sensor_left);
  distance_right = wb_distance_sensor_get_value(sensor_right);

  Encoder1 = wb_position_sensor_get_value(encoder1);
  Encoder2 = wb_position_sensor_get_value(encoder2);
  Encoder3 = wb_position_sensor_get_value(encoder3);

  printf("distance_left: %lf\r\n", distance_left);
  printf("distance_right: %lf\r\n", distance_right);
  printf("Encoder1: %lf\r\n", Encoder1);
  printf("Encoder2: %lf\r\n", Encoder2);
  printf("Encoder3: %lf\r\n", Encoder3);
  printf("Comparador: %lf\n",Comparador );
  // detect obsctacles
  //bool right_obstacle = distance_right <= OBSTACLE_DISTANCE;
 // bool left_obstacle = distance_left <= OBSTACLE_DISTANCE;




  if(pressed_key == WB_KEYBOARD_UP){
     
    wb_motor_set_velocity(wheel_left, -6.36);
    wb_motor_set_velocity(wheel_right, 6.36);
    wb_motor_set_velocity(wheel_back, 0);
  }
  else if(pressed_key == WB_KEYBOARD_DOWN){
    wb_motor_set_velocity(wheel_left, 6.36);
    wb_motor_set_velocity(wheel_right, -6.36);
    wb_motor_set_velocity(wheel_back, 0);
     
  }
  else if(pressed_key == WB_KEYBOARD_LEFT){
    wb_motor_set_velocity(wheel_left, 0);
    wb_motor_set_velocity(wheel_right, -6.36);
    wb_motor_set_velocity(wheel_back, 6.36);

  }
  else if(pressed_key == WB_KEYBOARD_RIGHT){
    wb_motor_set_velocity(wheel_left, 0);
    wb_motor_set_velocity(wheel_right, 6.36);
    wb_motor_set_velocity(wheel_back, -6.36);


  }
  else if(pressed_key == 'S' ){
    Comparador = Encoder1 + 0.785398;
    gira_izq = 1;
  }

  else if(gira_izq == 1){

    if(Encoder1 <= Comparador){
    wb_motor_set_velocity(wheel_left, 6.36);
    wb_motor_set_velocity(wheel_right, 6.36);
    wb_motor_set_velocity(wheel_back, 6.36);
  }
  else{
    wb_motor_set_velocity(wheel_left, 0);
    wb_motor_set_velocity(wheel_right, 0);
    wb_motor_set_velocity(wheel_back, 0);
    gira_izq = 0;
  }

}

  else if(pressed_key == 'A' ){
  Comparador = Encoder1 - 0.785398;
  gira_der = 1;
  
  }
   else if(gira_der == 1){

    if(Encoder1 >= Comparador){
    wb_motor_set_velocity(wheel_left, -6.36);
    wb_motor_set_velocity(wheel_right, -6.36);
    wb_motor_set_velocity(wheel_back, -6.36);
  }
  else{
    wb_motor_set_velocity(wheel_left, 0);
    wb_motor_set_velocity(wheel_right, 0);
    wb_motor_set_velocity(wheel_back, 0);
    gira_der = 0;
  }
    
  }
  else{
    wb_motor_set_velocity(wheel_left, 0);
    wb_motor_set_velocity(wheel_right, 0);
    wb_motor_set_velocity(wheel_back, 0);
  }
  };

  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
