

struct Day{
    int num;
    bool attending;
    bool schoolday;
} Day;

struct Month{
    int num;
    struct Day *days[30];
} Month;

struct Student{
    int id;
    char *f_Name[];
    char *l_Name[];
    struct Month *months[12];

} Student;

struct Class{
    int id;
    char *Name;
    struct Student students[30];
}