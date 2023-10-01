#include <Arduino.h>
#include <Metro.h>
#include "encoders.hpp"
#include "robot.hpp"

// Robot Object
Robot robot;
int odom_period = 25;  // Period in ms, 25ms = 40hz

// LED 
const int led_pin = 13;
bool led_state = true;

// Timers
Metro odom_timer = Metro(odom_period);
Metro led_timer = Metro(1000);     // 1hz
Metro info_timer = Metro(250);     // 4hz
 
void setup() {
  // Pin Setups
  encoder_init();
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  robot = Robot();
  delay(100);
}

void loop() {

  // RPM TIMER
  if (odom_timer.check()) {
    double l_rpm = get_left_rpm(odom_period);
    double r_rpm = get_right_rpm(odom_period);
    robot.forward_kin_update(l_rpm, r_rpm, odom_period);
  }

  // LED TIMER
  if (led_timer.check()) {
    digitalWrite(led_pin, led_state);
    led_state = true != led_state;
  }

  // INFO TIMER
  if (info_timer.check()) {
    Serial.printf("X: %f  Y: %f  YAW: %f L_RPM: %lf R_RPM: %lf \n", robot.pose.x, 
                                                                    robot.pose.y, 
                                                                    robot.pose.yaw, 
                                                                    robot.left_rpm,
                                                                    robot.right_rpm);
  }
}