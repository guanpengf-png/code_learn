#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME_LEN 32
#define DATA_FILE "student.txt"
typedef struct Student{
    int i;
    char name[NAME_LEN];
    float chinese;
    float math;
    float english;
    struct Student *next;
}Student;
static void printf_menu(void);
static float cal_avg(const Student*s);
static void clear_stdin(void);
static int read_line(char* buf,size_t n);
static Student *find_by_id(Student* head,int id);
static Student* Student_create(int id,char*name,float chinese,float math,float english);
static int list_add(Student **head,int id,const char*name,float chinese,float math,float english);
static int list_delete(Student**head,int id);
static int list_update(Student**head,int id,const char*name,float chinese,float math,float english);
static void list_print_one(const Student*s);
static void list_all_all(const Student*s);
static void list_search(Student *head,int id);
static void list_free(Student**head);
static int list_save(const Student*head,const char* path);
static int list_load(Student**head,const char* path);
static void menu_add(Student **head);
static void menu_delete(Student **head);
static void menu_update(Student *head);
static void menu_search(Student *head);
static void printf_menu(void){
    puts("1studnet manager add");
    puts("2studnet manager delete");
    puts("3studnet manager update");
    puts("4nstudnet manager search");
    puts("5studnet manager save");

    puts("6studnet manager show");
    puts("7studnet manager load");
    puts("0studnet manager tuichu");
    puts("studnet manager choice");
}
static void clear_stdin(void){
    int c;
    while ((c=getchar())!='\n'&&c!=EOF)
    {
        
    }
    
}
static int read_line(char* buf,size_t n){
    if (!fgets(buf,(int)n,stdin))
    {
    
    }
    
}


int main(){
    Student* head=NULL;
    int choice;
    int n=list_load(&head,DATA_FILE);
    if (n>0)
    {
        printf("%sload student,%d",DATA_FILE,n);
    }else{
        printf("no %s student",DATA_FILE);
    }
    for (;;)
    {
        printf_menu();
        if (scanf("%d",&choice)!=1)
        {
            printf("menu");
            clear_stdin();
            continue;
        }
        clear_stdin();
        switch (choice)
        {
        case 1:
            menu_add(&head);
            break;
        case 2:
            menu_delete(&head);
            break;
        case 3:
            menu_update(head);
            break;
        case 4:
            menu_search(head);
            break;
        case 5:
            list_print_all(head);
            break;
        case 6:
            if (list_save(head,DATA_FILE))
            {
                printf("save %s",DATA_FILE);
            }
        
            break;
        case 7:
            n=list_load(&head,DATA_FILE);
            printf("load %d",n);
        case 0:
            if (list_save(head,DATA_FILE))
            {
                printf("ready save%s",DATA_FILE);
            }
            list_free(&head);
            puts("see you");
            return 0;
            
        
        default:
            puts("no choice");
            break;
        }
        
    }
    

    

    return 0;
}