struct XYZ{
		float x;
		float y;
		float z;
};


struct XYZ aac;
struct XYZ force;

struct XYZ rot;
struct XYZ angle;

float elapsed;
float current;
float previous;

struct XYZ create_xyz(){
		return (struct XYZ){.x=0,.y=0,.z=0};
}

struct XYZ calc_data(int *data){
		struct XYZ n = create_xyz();
		n.x =*(data);
		n.y =*(data+1);
		n.z =*(data+2);
		return n;
}

struct XYZ process_data(struct XYZ p,float by){
		struct XYZ n = create_xyz();
		n.x = (p.x/by);
		n.y = (p.y/by);
		n.z = (p.z/by);
		return n;
};

int print_values(char *from,struct XYZ data){
		printf("Printing values from %s\n",from);
		printf("X-value is:%f\n",data.x);
		printf("Y-value is:%f\n",data.y);
		printf("Z-value is:%f\n",data.z);
		return 0;
}
