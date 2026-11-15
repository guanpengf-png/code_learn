
#include <stdio.h>
int main()
{
  

  // int sum = 0;
  // for (int i = 0; i < 5;i++){
  //   sum += i;
  // }
  // printf("结果:%d\n",sum);
  // printf("结果:%d\n",sum);
  // printf("结果:%d\n",sum);
  printf("%d,%p\n",((int[]){10,20}[0]),&((int[]){10,20}[0]));
  int nums[5] = {10, 20, 30, 40, 50}; // 声明一个int[5]的数组,起名为nums,并赋值
  printf("索引:0,对应位置的元素值:%d\n", nums[0]);
  nums[0] = 100; // 把索引为0的位置的数据重新赋值为100
  printf("索引:0,对应位置的元素值:%d\n", nums[0]);
  nums[0] = nums[0] + 10; // 把索引为0的位置的数据取出来加10,然后重新赋值
  printf("索引:0,对应位置的元素值:%d\n", nums[0]);
  nums[0] += 10;
//   printf("索引:0,对应位置的元素值:%d\n", nums[60]);
int num[] = {10, 20, 30, 40, 50,60,70,80};
int len=sizeof(num)/sizeof(int);
for (int i = 0; i < len; i++)
{
    printf("%d",num[i]);
}

  return 0;
}
