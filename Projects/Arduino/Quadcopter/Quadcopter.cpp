#include "Arduino.h"
#include <Wire.h>

#define SER 9600
#define MPU 0x68
#define FORCE 16384.0
#define ANGLE 131.0

#include "headders/mpu.h"
#include "headders/mp6050.h"

void setup(){
	Serial.begin(SER);
	register_write(registers.config_sleep,0x0);
	register_write(registers.config_acc,0x0);
	register_write(registers.config_gyro,0x0);
}

void loop(){
	print_values("Acclerometer force",process_data(calc_data(read_register(registers.acc)),FORCE));
	print_values("Gyroscope angles",process_data(calc_data(read_register(registers.gyro)),ANGLE));
}
