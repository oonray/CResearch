
typedef void (*function)(const char *name);

struct Arg1{
    char *name;
    int position;
    function func;
};

struct Arg2{
    char *name;
    char *value;
};

int set_argument1(struct Arg1 *target,const char *name, int position, function func){
    target->name = strdup(name);
    target->position = position;
    target->func = func;
}

int set_argument2(struct Arg2 *target,const char *name, const char *value){
    target->name = strdup(name);
    target->value = strdup(value);
}