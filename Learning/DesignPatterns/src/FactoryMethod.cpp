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


