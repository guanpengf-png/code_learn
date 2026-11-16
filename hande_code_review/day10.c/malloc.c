#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    void *prt=malloc(4);
    if (prt==NULL)
    {
       printf("error");
       return 0;
    }
    //printf("%d",*prt);
    int *prt1=(int *)prt;
    *prt1=100;
    printf("\n%p and data %d",prt1,*prt1);
    free(prt1);
    prt1=NULL;
    printf("%d",*prt1);

    return 0;
}

