#define MAX_DAYS 30
#define MAX_MONTHS 12
#define MAX_STUDENTS 30
#define MAX_MAME_LENGTH 50
#define DATABASE_FILE "Database.db"
#define LSUB 18

char *location;
int length;
int loc_size;
char *argv0;
int n;

void create_database();
void *open_database();
int get_LSUB(int neg);

void set_location();
void print_database();

void print_class();

void add_class(const char *name);
void set_arg0(const char *inp);

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
    char name[MAX_MAME_LENGTH];
    struct Student *students[];
};

struct Database{
    int size;
    FILE *f;
    struct Class *classes[];
};




