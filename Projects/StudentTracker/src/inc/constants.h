#define MAX_DAYS 30
#define MAX_MONTHS 12
#define MAX_STUDENTS 30
#define MAX_MAME_LENGTH 50
#define DATABASE_FILE "Database.db"

extern int LSUB = 18;
extern char *location;
extern int length;
extern int loc_size;
extern char *argv0;
 
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
    struct Year Years[100];

};

struct Class{
    int id;
    char Name[MAX_MAME_LENGTH];
    struct Student *students[];
};

struct Database{
    int size;
    struct Class *classes[];
};

char *get_location(){
    return location;
};

void set_location(){
    /*Cpy the location of the file name +db to create a file in the same directory*/
    memcpy(location, argv0, length);
    memcpy(location, strcat(location, DATABASE_FILE), loc_size);
};

void set_LSUB(int neg){
    LSUB -= neg;
}



