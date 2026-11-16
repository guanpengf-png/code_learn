#include <stdio.h>
#define TOTAL 2
struct Person
{
    int id;
    char* name;
    char gender;
    char* work;
    union 
    {
        float score;
        char *coursename;

        
    }score_course;
    

}s,t;

int main(int argc, char const *argv[])
{
    struct Person group[TOTAL];

    ///scanf("%d %s %c %s",&group.id,s.name,&s.gender,s.work);
    for ( int i=0; i <TOTAL; i++)
    {
        scanf("%d %s %c %s",&group[i].id,group[i].name,&group[i].gender,group[i].work);
        printf("\n");
        
        if (group[i].work=="student")
        {
        //    scanf("%d %s %c %s",&s.id,s.name,&s.gender,s.work);
                scanf("%f",&group[i].score_course.score);
        }else{
            scanf("%f",&group[i].score_course.score);
        }
        
       //scanf("%d %s %c %s",&s.id,s.name,&s.gender,s.work);
    }
    
    

    return 0;
}
