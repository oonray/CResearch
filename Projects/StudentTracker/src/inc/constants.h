#define MAX_DAYS 30
#define MAX_MONTHS 12
#define MAX_STUDENTS 30
#define MAX_MAME_LENGTH 50
#define DATABASE_FILE "Database.db"

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
    struct Student students[MAX_STUDENTS];
};
