#include "robot.hpp"

Robot::Robot() {
    initialized = true;
}

void Robot::reset_pose() {
    pose = pose_2d{0.0,0.0,0.0};
}

void Robot::reset_position() {
    pose.x = 0.0;
    pose.y = 0.0;
}

void Robot::reset_yaw() {
    pose.yaw = 0.0;
}

void Robot::forward_kin_update(double &l_rpm, double &r_rpm, const int &period) {
    // https://www.cs.columbia.edu/~allen/F19/NOTES/icckinematics.pdf
    double l_lin_vel = l_rpm / 60.0 * M_PI * 2.0 * (wheel_diameter / 2.0);    // linear meters per second
    double r_lin_vel = r_rpm / 60.0 * M_PI * 2.0 * (wheel_diameter / 2.0);   // linear meters per second
    float d_t = period / 1000.0;  // delta time in seconds

    //  If rotating about an ICC
    if (l_lin_vel != r_lin_vel) {
        double w = (r_lin_vel - l_lin_vel) / wheel_base;  // rate of rotation
        double R = (wheel_base/2) * ((l_lin_vel + r_lin_vel) / (r_lin_vel - l_lin_vel));  // Distance to instant. center of curv (ICC)
        double icc_x = pose.x - R * sin(pose.yaw);  // icc position x
        double icc_y = pose.y + R * cos(pose.yaw);  // icc position y
        pose.x = cos(w*d_t) * (pose.x - icc_x) + (-sin(w*d_t) * (pose.y - icc_y)) + icc_x;
        pose.y = sin(w*d_t) * (pose.x - icc_x) + cos(w*d_t) * (pose.y - icc_y) + icc_y;
        pose.yaw = pose.yaw + w*d_t;
    } else {
    // Else linear motion cause R is infinite
        double distance = l_lin_vel * d_t;
        pose.x = pose.x + cos(pose.yaw) * distance;
        pose.y = pose.y + sin(pose.yaw) * distance;
    }

    this->left_rpm = l_rpm;
    this->right_rpm = r_rpm;
}