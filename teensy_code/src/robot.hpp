#pragma once
#include <math.h>
#include <Arduino.h>

struct pose_2d {
    float x = 0.0;    // Meters
    float y = 0.0;    // Meters
    float yaw = 0.0;  // Radians
};

class Robot {
    private:
        float wheel_base = 0.1275;      // 12.75 CM
        float wheel_diameter = 0.065;   // 6.5 CM
        long time = millis();
        bool initialized = false;

    public:
        double left_rpm = 0.0;
        double right_rpm = 0.0;
        pose_2d pose;
        Robot();
        void reset_pose();
        void reset_position();
        void reset_yaw();
        void forward_kin_update(double &l_rpm, double &r_rpm, const int &rate);
};