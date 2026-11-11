#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME_LEN 32
#define DATA_FILE "student.txt"
typedef struct Student{
    int id;
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
        return 0;
    }
    size_t len = strlen(buf);
    if (len>0&&buf[len-1]=='\n')
    {
        buf[len-1]='\0';
    }
    return 1;
    
    
}
static Student* Student_create(int id,char*name,float chinese,float math,float english){
    Student *node=(Student*)malloc(sizeof(Student));
    if (!node)
    {
        return NULL;
    }
    node->id=id;
    strncpy(node->name,name,NAME_LEN-1);
    node->name[NAME_LEN-1]='\0';
    node->chinese=chinese;
    node->english=english;
    node->math=math;
    node->next=NULL;
    return node;

    
}
static float cal_avg(const Student*s){
    return (s->chinese+s->math+s->english)/3.0;
}
static int list_add(Student **head,int id,const char*name,float chinese,float math,float english){
    if (find_by_id(*head,id)!=NULL)
    {
        printf("have studnet");
        return 0;
    }
    Student *node=Student_create(id,name,chinese,math,english);
    if (!node)
    {
        printf("error");
        return 0;
    }
    node->next=*head;
    *head=node;
    return 1;
    
    
}
static int list_delete(Student**head,int id){
    Student* cur=*head;
    Student* prev=NULL;
    while (cur!=NULL)
    {
        if (cur->id==id)
        {
            if (prev==head)
            {
                *head=cur->next;
            }
            else{
                prev->next=cur->next;
            }
            free(cur);
            return 1;
            
        }
        prev=cur;
        cur=cur->next;
        
    }
    return 0;
    

}
static int list_update(Student**head,int id,const char*name,float chinese,float math,float english){
    Student* s=find_by_id(head,id);
    if (!s)
    {
        return 0;
    }
    strncpy(s->name,name,NAME_LEN-1);
    s->name[NAME_LEN-1]='\0';
    s->chinese=chinese;
    s->math=math;
    s->english=english;
    return 1;


    
}
static void list_print_one(const Student*s){
    printf("%-6d id,%-10s,%f chinese,%f math,%f english",s->english,s->chinese,s->math,s->english);
}
static void list_all_all(const Student*s){
    if (!s)
    {
        printf("no student");
        return;
    }
    printf("all studnet");
    const Student*p=s;
    int n=0;
    while (p!=NULL)
    {
        list_print_one(p);
        p=p->next;
        n++;
    }
    printf("%d,\n",n);

    
    
}
static void list_search(Student *head,int id){
    Student*p=find_by_id(head,id);
    if (!p)
    {
        printf("no student id%d",id);
        return;
    }
    printf("result");
    list_print_one(p);
    
}

static Student *find_by_id(Student* head,int id){
    Student* q=head;
    if (q!=NULL)
    {
        if (q->id==id)
        {
            return q;
        }
        q=q->next;
    }
    retur NULL;
    
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