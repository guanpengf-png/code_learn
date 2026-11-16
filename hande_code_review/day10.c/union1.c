#include <stdio.h>
#define LEN 3
struct Person{
    int id;
    char name[20];
    char gender;
    int age;
    char work;
    union 
    {
        double score;
        char course_name[20];
        
    }sc;
    

};
int main(int argc, char const *argv[])
{

    struct Person person[LEN];
    for (int i = 0; i < LEN; i++)
    {
        printf("input id%d\n",i+1);
        scanf("%d,",&person[i].id);
        printf("input name%d\n",i+1);
        scanf("%s,",person[i].name);
        getchar();
         printf("input gender%d\n",i+1);
        scanf("%c,",&person[i].gender);
        getchar();
         printf("input age%d\n",i+1);
        scanf("%d,",&person[i].age);

        printf("input work%d\n",i+1);
        scanf("%c,",&person[i].work);
        getchar();
        
        if (person[i].work=='s')
        {
            printf("input score%d\n",i+1);
            scanf("%lf,",&person[i].sc.score);
           
        }else{
            printf("input course_name%d\n",i+1);
            scanf("%s,",&person[i].sc.course_name);

        }
        


    }
    

    
    
    
    return 0;
}
