#include "Arduino.h"
#include <Wire.h>

#define SERIAL 9600;
#define MPU 0x68;
#include "headders/mpu.h"
#include "headders/mp6050.h"

void setup(){
	register_write(registers.config_sleep,0x0);
	register_write(registers.config_acc,0x0);
	register_write(registers.config_gyro,0x0);
}

void loop(){
	struct AAC acc = calc_acc_force(read_register(registers.acc));
	struct GYRO gyr = calc_gyro_angles(read_register(registers.gyro));
	print_values("Acclerometer force",acc.force);
	print_values("Gyroscope Angles",gyr.angle);		
}
