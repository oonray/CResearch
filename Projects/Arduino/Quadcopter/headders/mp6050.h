int scl = 12;
int sda = 13;
const int MPU = 0x68;

struct ERROR{
		float x;
		float y;
		float z;
};

struct ANGLE{
		float x;
		float y;
		float z;
};

struct AAC{
		float x;
		float y;
		float z;
		struct ANGLE angle;
		struct ERROR error;
}acc;

struct GYRO{
		float x;
		float y;
		float z;
		struct ANGLE angle;
		struct ERROR error;
}gyro;

struct TIME{
		float elapsed;
		float current;
		float previous;
}time;

void calculate_mpu_error(){
		int c = 0;
		while (c < 200) {
				Wire.beginTransmission(MPU);
				Wire.write(0x3B);
				Wire.endTransmission(false);
				Wire.requestFrom(MPU, 6, true);
				acc.x = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
				acc.y = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
				acc.z = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
			// Sum all readings
				acc.error.x = acc.error.x + ((atan((acc.y) / sqrt(pow((acc.x), 2) + pow((acc.z), 2))) * 180 / PI));
				acc.error.y = acc.error.y + ((atan(-1 * (acc.x) / sqrt(pow((acc.y), 2) + pow((acc.z), 2))) * 180 / PI));
			c++;
		}
		  //Divide the sum by 200 to get the error value
		acc.error.x = acc.error.x / 200;
		acc.error.y = acc.error.y / 200;
		c = 0;
		
		// Read gyro values 200 times
		while (c < 200) {
			Wire.beginTransmission(MPU);
			Wire.write(0x43);
			Wire.endTransmission(false);
			Wire.requestFrom(MPU, 6, true);
			gyro.x = Wire.read() << 8 | Wire.read();
			gyro.y = Wire.read() << 8 | Wire.read();
			gyro.z = Wire.read() << 8 | Wire.read();
			// Sum all readings
			gyro.error.x = gyro.error.x + (gyro.x / 131.0);
			gyro.error.y = gyro.error.y + (gyro.x / 131.0);
			gyro.error.z = gyro.error.z + (gyro.x / 131.0);
			c++;
		  }
		  //Divide the sum by 200 to get the error value
		  gyro.error.x = gyro.error.x / 200;
		  gyro.error.y = gyro.error.y / 200;
		  gyro.error.z = gyro.error.z / 200;
		  // Print the error values on the Serial Monitor
		  Serial.print("AccErrorX: ");
		  Serial.println(acc.error.x);
		  Serial.print("AccErrorY: ");
		  Serial.println(acc.error.y);
		  Serial.print("GyroErrorX: ");
		  Serial.println(gyro.error.x);
		  Serial.print("GyroErrorY: ");
		  Serial.println(gyro.error.y);
		  Serial.print("GyroErrorZ: ");
		  Serial.println(gyro.error.z);
}
