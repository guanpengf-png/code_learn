#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int len=10;
    int *p=(int*)malloc(sizeof(int)*len);
    void *prt=malloc(4);
    if (prt==NULL)
    {
       printf("error");
       return 0;
    }
    for (int i = 0; i < len; i++)
    {
        *(p+i)=i*10;
    }
    for (int i = 0; i < len; i++)
    {
        printf("%d\n %p\n",p[i],p+i);
    }
    free(p);
    p=NULL;
    
   
    

    return 0;
}

