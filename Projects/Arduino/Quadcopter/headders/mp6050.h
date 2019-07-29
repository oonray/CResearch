struct xyz{
		float x;
		float y;
		float z;
};

struct AAC{
		struct xyz aac;
		struct xyz force;
		struct xyz error;
}

struct GYRO{
		struct xyz rot;
		struct xyz angle;
		struct xyz error;
}

struct TIME{
		float elapsed;
		float current;
		float previous;
}time;

struct ACC calc_acc_force(int *data){
		struct ACC bcc = {};
		bcc.acc.x = *(data);
		bcc.force.x = (bcc.rot.x/16384.0);

		bcc.acc.y = *(data+1);
		bcc.force.y = (bcc.rot.x/16384.0);

		bcc.acc.z = *(data+2);
		bcc.force.z = (bcc.rot.z)/16384.0);
		return bcc;
}

struct GYRO calc_gyro_angles(int *data){
		struct GYRO y = {.x=0.0,.y=0.0,.z=0.0};	
		y.rot.x = *(data);
		y.angle.x = (y.rot.x/131.0);

		y.rot.y = *(data+1);
		y.angle.y = (y.rot.y/131.0);

		y.rot.z = *(data+3);
		y.angle.z = (y.rot.z/131.0);
		return y;
}

int print_values(char *from,struct xyz data){
		printf("Printing values from %s\n",from);
		printf("X-value is:%f\n",data.x);
		printf("Y-value is:%f\n",data.y);
		printf("Z-value is:%f\n",data.z);
		return 0;
}
