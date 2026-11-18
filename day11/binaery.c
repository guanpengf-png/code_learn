#include<stdio.h>
int binary_search(int *arr,int len,int target){
    int start=0;
    int end=len-1;
    int mid=(start+end)/2;
    while (start<=end)
    {
        if (target>arr[mid])
    {
        start=mid+1;
    }else if(target<arr[mid])
    {
       end=mid-1;
    }else{
        return mid;
    }
}
    // }}
    
    // if (target>arr[mid])
    // {
    //     start=mid+1;
    // }else if(target<arr[mid])
    // {
    //    end=mid-1;
    // }else{
    //     return target;
    // }
    
    return -1;
}
int main(int argc, char const *argv[])
{
    int nums[]={1,2,34,45,34,56};
    int len=sizeof(nums)/sizeof(nums[0]);
    int target=34;
    int mid=binary_search(nums,len,target);
    printf("%d",nums[mid]);


    return 0;
}
