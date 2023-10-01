#pragma once
#include <Arduino.h>

const float ticks_per_rev = 960.0;

// Left Wheel
const byte left_a = 2;
const byte left_b = 3;
int left_ticks = 0;


// Right Wheel
const byte right_a = 5;
const byte right_b = 4;
int right_ticks = 0;

void get_ticks_left()
{
  if(digitalRead(left_b) == HIGH) {
    left_ticks++;
  } else {
    left_ticks--;
  }
}

void get_ticks_right()
{
  if(digitalRead(right_b) == HIGH) {
    right_ticks++;
  } else {
    right_ticks--;
  }
}

void encoder_init()
{
  pinMode(left_a,INPUT);
  pinMode(left_b,INPUT);
  pinMode(right_a,INPUT);
  pinMode(right_b,INPUT);
  attachInterrupt(left_a, get_ticks_left, RISING);
  attachInterrupt(right_a, get_ticks_right, RISING);
}

double get_left_rpm(const int &period) 
{
  double rpm = left_ticks / ticks_per_rev / (period / 60000.0);
  left_ticks = 0;
  return rpm;
}

double get_right_rpm(const int &period) 
{
  double rpm = right_ticks / ticks_per_rev / (period / 60000.0);
  right_ticks = 0;
  return rpm;
}