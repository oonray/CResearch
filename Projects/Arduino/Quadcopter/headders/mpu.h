struct REGISTERS{
		const int config_sleep = 0x6B;
		const int config_gyro = 0x1B;
		const int config_acc = 0x1C;
		const int acc = 0x3B;
		const int gyro = 0x43;
} registers;

int register_write(int reg,int val){
	    Wire.beginTransmission(MPU);
		Wire.write(reg);
		Wire.write(val);
		Wire.endTransmission();
		return 0;
}

int *read_register(int reg){
    static int regval[3];
    Wire.beginTransmission(MPU);
	Wire.write(reg);
	Wire.endTransmission();
	Wire.requestFrom(MPU,6);
	while(Wire.available() < 6){
		regval[0] = Wire.read()<<8 | Wire.read();
		regval[1] = Wire.read()<<8 | Wire.read();
	    regval[2] = Wire.read()<<8 | Wire.read();
		}
    return regval;
}



