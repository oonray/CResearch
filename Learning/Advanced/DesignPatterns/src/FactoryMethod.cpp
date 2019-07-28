#include <cstdio>
#include <cstring>

#include "../../../CusomHeadders/colors.h"
#include "../../../CusomHeadders/dbg.h"


class Coffe {
	private:
		char type[50];
	public:
		Coffe(){}
		char *get_type(){return _type;};
		void brew(){

		}
};

class Espesso:public Coffe{
	public:
		Espesso():Coffe(){
			strcpy(_type,"Espresso");
			brew();
			printf("Grinding Coffe beans");
		}

};

class Capuchino: public Coffe{
	public:
		Capuchino():Coffe(){
			strcpy(_type,"Capuchino");
			brew();
			printf("Adding Skimmed Milk");
		}

};

class CoffeFactory{
	private:
		Coffe *_coffe;
	public:
		Coffe *getCoffe(){
			int choice;	
			printf("Select coffe to make:\n");
			printf("\t1. Espresso \n");
			printf("\t2. Capuchino \n");
			printf("Selection:\t");
			scanf("%d",choice);
			
		}

}


