#ifndef __gyro_h_
    #define __gyro_h_
#endif

#define DEGREE 65.5
#define CALSTEPS 2000
#define OFFSETT 0.0000611
#define OFFSETTZ 0.000001066
#define MPUADDR 68

#include <Wire.h>
#include <stdio.h>
#include <string.h>

int calcRPY();
int calibrate();
int read_values();
void setup_registers();

struct gyro{
    float x, y, z;
    float pitch;
    float roll;
    float yaw;
    float cal_x, cal_y, cal_z;
} gy;

struct acclerometer{
    float x, y, z;
} acc;

struct temperature{
    float c, f;
} tmp;
