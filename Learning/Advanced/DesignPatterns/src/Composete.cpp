#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../../../CustomHeadders/colors.h"
class Entre{
    protected:
        char _entre[50];
    public:
        char *getEntre(){return _entre;}
};
class Side{
    protected:
        char _side[50];
    public:
        char *getSide(){return _side;}
};
class Drink{
    protected:
        char _drink[50];
    public:
        char *getDrink(){return _drink;};

        Drink(){
            printf("%s Filing cup with soda\n",KINF);
            strcpy(_drink,"soda");
        }
};

class mealCombo{
    private:
        Entre *entre;
        Side *side;
        Drink *drink;
        char _bag[100];
    public:
        mealCombo(const char *type){
            sprintf(_bag,"%s meal type \n",type);

        }
        void setEntre(Entre *e){
            entre = e;
        }
        void setSide(Side *s){
            side = s;
        }
        void setDrink(Drink *d){
            drink = d;
        }

	void open_bag(){
	    sprintf(_bag,"%s %s %s %s",_bag,entre->getEntre(),drink->getDrink(),side->getSide());
	    return _bag;
	}

};


