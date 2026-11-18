
#include <stdio.h>
void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void swap2(int*a,int *b){
    *a=*a+*b;//30
    *b=*a-*b;//10
    *a=*a-*b;//30-10 

} 
void swap3(int *a,int*b){
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}
int main(void)
{
    int a=10;
    int b=20;
    swap(&a,&b);
    printf("after swap : a=%d, b=%d\n",a,b);

    int c=10;
    int d=20;
    swap2(&c,&d);
    printf("after swap2: c=%d, d=%d\n",c,d);

    int e=10;
    int f=20;
    swap3(&e,&f);
    printf("after swap3: e=%d, f=%d\n",e,f);
    return 0;
}
