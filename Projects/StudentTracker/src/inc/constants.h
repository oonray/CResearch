#define MAX_DAYS 30
#define MAX_MONTHS 12
#define MAX_STUDENTS 30
#define MAX_MAME_LENGTH 50
#define DATABASE_FILE "Database.db"

extern int LSUB = 18;
extern char *location;
extern int length;
extern int loc_size;
 
struct Day{
    int num;
    int attending;
    int schoolday;
};

struct Month{
    int num;
    struct Day *days[MAX_DAYS];
};


struct Year{
    struct Month *months[12];
};

struct Student{
    int id;
    char f_Name[MAX_MAME_LENGTH];
    char l_Name[MAX_MAME_LENGTH];
    struct Year *Years[100];

};

struct Class{
    int id;
    char Name[MAX_MAME_LENGTH];
    struct Student *students[MAX_STUDENTS];
};

struct Database{
    int size;
    struct Class *classes[50];
};

char *get_location(){
    return location;
};

void set_location(const char *arg){
    /*Cpy the location of the file name +db to create a file in the same directory*/
    memcpy(location, arg, length);
    memcpy(location, strcat(location, DATABASE_FILE), loc_size);
};

extern struct Class *alloc_Class();
extern void free_Class(struct Class *cl);

void set_LSUB(int neg){
    LSUB -= neg;
}

struct Database *alloc_db(){
    struct Database *ret = malloc(sizeof(struct Database));
    for(int i = 0; i<50;i++){
        ret->classes[i] = alloc_Class();
    };
    return ret;
};

void free_db(struct Database *db){

};

struct Class *alloc_Class(){
    /*Allocates a class and returns a pointer to it*/
    struct Class *ret = malloc(sizeof(struct Class));
    for(int i = 0; i<=MAX_STUDENTS;i++){
        ret->students[i] = malloc(sizeof(struct Student));
        for(int n = 0;n<100;n++){
            ret->students[i]->Years[n] = malloc(sizeof(struct Year));
            for(int t=0;t<12;t++){
                ret->students[i]->Years[n]->months[t] = malloc(sizeof(struct Month));
            }
        }
    }
    return ret;
};

void free_Class(struct Class *cl){
    /*Frees a class and its children*/
}