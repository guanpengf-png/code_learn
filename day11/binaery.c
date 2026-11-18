#include<stdio.h>
int binary_search(int *arr,int len,int target){
    int start=0;
    int end=len-1;
    while (start<=end)
    {
        // mid 必须在循环里跟着 start/end 一起变
        int mid=start+(end-start)/2;   // 不用 (start+end)/2, 防止溢出
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
    int nums[]={1,2,34,34,45,56};          // 二分查找要求数组有序
    int len=sizeof(nums)/sizeof(nums[0]);
    int target=34;
    int index=binary_search(nums,len,target);
    if (index>=0)
    {
        printf("找到 %d, 下标是 %d\n",target,index);
    }
    else
    {
        printf("没找到 %d\n",target);
    }


    return 0;
}
