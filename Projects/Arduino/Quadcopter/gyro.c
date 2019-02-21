
#include "libraries/gyro/gyro.h"

float aideg(float raw){
    return raw/DEGREE; 
}

int calcRPY(){
    gy.x -= gy.cal_x;
    gy.y -= gy.cal_y;
    gy.z -= gy.cal_z;

    gy.pitch += gy.roll * OFFSETT;                                   
    gy.roll += gy.pitch * OFFSETT;         

    gy.pitch -= gy.roll * sin(gy.z * OFFSETTZ);
    gy.roll += gy.pitch * (gy.z * OFFSETTZ);
    return 0;
}
 
int calibrate(){
    for(int cal = 0; cal < CALSTEPS; cal++){
        read_values();
        gy.cal_x+=gy.x;
        gy.cal_y+=gy.y;
        gy.cal_z+=gy.z;
    }

    gy.cal_x /= CALSTEPS;
    gy.cal_y /= CALSTEPS;
    gy.cal_z /= CALSTEPS;
    return 0;
} 

int read_values(){
    Wire.beginTransmission(MPUADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPUADDR,14);
    while(Wire.available() < 14){
        acc.x = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_x variable
        acc.y = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_y variable
        acc.z = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_z variable
        tmp.c = Wire.read()<<8|Wire.read();                            //Add the low and high byte to the temperature variable
        gy.x = Wire.read()<<8|Wire.read();                             //Add the low and high byte to the gyro_x variable
        gy.y = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_y variable
        gy.z = Wire.read()<<8|Wire.read();                                 //Add the low and high byte to the gyro_z variable
    }
}

void print_values(){
    char *temperature;
    char *speed;
    char *angle;
    sprintf(temperature, "Temperatiure %s *C\n",tmp.c);
    sprintf(speed,"Acclerometer x: %f, y: %f, z: %f\n",acc.x,acc.y,acc.z);
    sprintf(angle,"Gyroscope x: %f, y: %f, z: %f\n",aideg(gy.x),aideg(gy.y),aideg(gy.z));

    Serial.print(temperature);
    Serial.print(speed);
    Serial.print(angle);

}

void setup_registers(){
  //Activate the MPU-6050
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x10);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1B);                                                    //Send the requested starting register
  Wire.write(0x08);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);   
  Serial.print("Starting!");  
  Serial.print("Setting Registers!");
  setup_registers();
  Serial.print("Calibrating!");
  calibrate();
  Serial.print("Calibrated!");
}

void loop() {
    read_values();
    print_values();
    delay(100);
}