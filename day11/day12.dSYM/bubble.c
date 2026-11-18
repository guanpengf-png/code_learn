#include <stdio.h>
//swap
//bubble
void swap(int *a,int*b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
void bubble(int arr[],int len){
    for (int i = 0; i < len-1; i++)
    {
       for (int j = 0; j <len-1-i; j++)
       {
        if (arr[j]>arr[j+1])
        {
            swap(&arr[j],&arr[j+1]);
        }
        

       }
       
    }
    

}
int main(int argc, char const *argv[])
{
    
    int nums[]={231,324,4534,676,324667,3,242,324324,32,432,4};
    int len=sizeof(nums)/sizeof(nums[0]);
    bubble(nums,len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ",nums[i]);
    }
    printf("\n");
    
    return 0;
}
