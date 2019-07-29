#include "headders/globals.h"
#include "headders/debug.h"


const char *MY_NAME = "Alexander Bjornsrud";

void scope_demo(int count)
{
    log_info("count id %d",count);
    if(count > 10){
        count = 100;
        log_info("count in this scope is %d",count);
    }
    log_info("Count on exit: %d",count);

    count = 3000;
    log_info("Count after assignment %d", count);

}


int main(int argc, char *argv[]){
    log_info("My name: %s, age: %d", MY_NAME, get_age());
    set_age(100);
    double *pointer = update_ratio(5.0);
    printf("Poniter to ratio: %f\n", *pointer);

    log_info("My age now is %d",get_age());
    log_info("The size is: %d",THE_SIZE);

    print_size();

    THE_SIZE=9;
    log_info("THE_SIZE id: %d",THE_SIZE);
    print_size();
    log_info("Ratio at first: %f",*update_ratio(2.0));
    log_info("Ratio again: %f", *update_ratio(10.0));
    log_info("Ratio once more: %f", *update_ratio(300.0));

    int count = 4;
    scope_demo(count);
    scope_demo(count*20);
    log_info("count after calling scope_demo %d",count);
    
    return 0;
}