
 
#include <stdio.h>
int main()
{
int num[] = {10, 20, 30, 40, 50,60,70,80};
int sum=0;
int len=sizeof(num)/sizeof(num[0]);
int max_num=num[0];
int max_index=0;
int min_index=0;
int min_num=num[0];
for (int i = 0; i < len; i++)
{
    if (max_num<num[i])
    {
       max_num=num[i];
       max_index=i;
    }
    if (min_num>num[i])
    {
        min_num=num[i];
        min_index=i;
    }
    
}
    printf("%d",max_index);



  return 0;
}
