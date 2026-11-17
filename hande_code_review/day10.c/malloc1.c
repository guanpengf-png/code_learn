// // // // // // #include <stdio.h>
// // // // // // #include <stdlib.h>
// #include <string.h>


// // // // // // int main(int argc, char const *argv[])
// // // // // // {
// // // // // //     int len=10;
// // // // // //     int *p=(int*)malloc(sizeof(int)*len);
// // // // // //     void *prt=malloc(4);
// // // // // //     if (prt==NULL)
// // // // // //     {
// // // // // //        printf("error");
// // // // // //        return 0;
// // // // // //     }
// // // // // //     for (int i = 0; i < len; i++)
// // // // // //     {
// // // // // //         *(p+i)=i*10;
// // // // // //     }
// // // // // //     for (int i = 0; i < len; i++)
// // // // // //     {
// // // // // //         printf("%d\n %p\n",p[i],p+i);
// // // // // //     }
// // // // // //     free(p);
// // // // // //     p=NULL;
    
   
    

// // // // // //     return 0;
// // // // // // }

// // // // // #include <stdio.h>

// // // // // int main()
// // // // // {

// // // // //   {
// // // // //     // 短整型 short,分为有符号的short和无符号的short
// // // // //     signed short s1 = -10;   // 声明一个有符号的short类型的变量,起名为s1,并赋值为-10
// // // // //     unsigned short s2 = 20u; // 声明一个无符号的short类型的变量,起名为s2,并赋值为20
// // // // //     // unsigned short s2 = 20; // 声明一个无符号的short类型的变量,起名为s2,并赋值为20
// // // // //     short s3 = -20; // 声明一个有符号的short类型的变量,起名为s3,并赋值为-20
// // // // //     // signed表示有符号的,声明变量的时候signed可以省略,默认就是有符号的
// // // // //     // 无符号的数据值后面的后缀是u/U,也可以省略
// // // // //     // 有符号的short类型的数据输出使用的格式占位符是%hd,无符号的short类型的数据输出使用的是%hu
// // // // //     // 无论是有符号的还是无符号的short类型数据都可以使用%d格式占位符,但是建议使用各自
// // // // //     printf("s1变量的值是:%hd\n", s1);
// // // // //     printf("s2变量的值是:%hu\n", s2);
// // // // //     printf("s3变量的值是:%hd\n", s3);
// // // // //     printf("s1=%d,s2=%d,s3=%d\n", s1, s2, s3);
// // // // //   }
// // // // //   printf("\n================================\n");
// // // // //   {
// // // // //     // 整型int,分为:有符号的和无符号的int
// // // // //     signed int num1 = -100;  // 声明一个有符号的int类型的变量,起名为num1,并赋值-100
// // // // //     unsigned int num2 = 200; // 声明一个无符号的int类型的变量,起名为num2,并赋值200
// // // // //     int num3 = -200;         // 声明一个有符号的int类型的变量,起名为num3,并赋值-200
// // // // //     // 有符号的signed也是可以省略的
// // // // //     // 有符号的int类型的数据输出使用的是%d格式占位符,无符号的int类型的数据输出使用的是%u格式占位符
// // // // //     // 无论是有符号的int还是无符号的int类型的数据输出都可以使用%d,建议还是各自的格式占位符
// // // // //     printf("num1=%d\n", num1);
// // // // //     printf("num2=%u\n", num2);
// // // // //     printf("num3=%d\n", num3);
// // // // //     printf("num1=%d,num2=%d,num3=%d\n", num1, num2, num3);
// // // // //   }
// // // // //   printf("\n================================\n");
// // // // //   {
// // // // //     // 长整型 long,分为有符号的long和无符号的long
// // // // //     signed long l1 = -1000L;   // 声明一个有符号的long类型的变量,起名为l1,并赋值为-1000
// // // // //     unsigned long l2 = 2000LU; // 声明一个无符号的long类型的变量,起名为l2,并赋值2000
// // // // //     long l3 = -2000L;          // 声明一个有符号的long类型的变量,起名为l3,并赋值为-2000
// // // // //     // 有符号的long类型的数据值的后缀是l/L
// // // // //     // 无符号的long类型的数据值的后缀是lu/LU/ul/UL
// // // // //     // long类型的数据值的后缀无论是L还是LU都可以省略,不是很建议
// // // // //     // signed关键字也可以省略
// // // // //     // 赋值的时候的后缀在输出的时候后缀是没有的
// // // // //     // 有符号的long类型的数据输出使用的格式占位符是%ld,无符号的格式占位符是%lu
// // // // //     // long类型的数据输出的时候也可以使用%d格式占位符,建议使用各自的
// // // // //     printf("l1的值是:%ld\n", l1);
// // // // //     printf("l2的值是:%lu\n", l2);
// // // // //     printf("l3的值是:%ld\n", l3);
// // // // //     printf("l1=%d,l2=%d,l3=%d\n",l1,l2,l3);
// // // // //   }
// // // // //   printf("\n================================\n");
// // // // //   {
// // // // //     // 长长整型 long long,也分为有符号的和无符号的
// // // // //     signed long long ll1 = -10LL; // 声明一个有符号的long long类型的变量,起名为ll1,赋值-10
// // // // //     unsigned long long ll2 = 20LLU; // 声明一个无符号的long long类型的变量,起名为ll2,赋值20
// // // // //     long long ll3 = -20LL; //  声明一个有符号的long long类型的变量,起名为ll3,赋值-20
// // // // //     // 有符号的long long类型的数据值的后缀是ll/LL,建议使用大写
// // // // //     // 无符号的long long类型的数据值的后缀是llu/ull/LLU/ULL
// // // // //     //后缀也可以省略,不是很建议
// // // // //     // signed也可以省略
// // // // //     // 有符号的long long类型的数据输出使用的格式占位符是%lld
// // // // //     // 无符号的long long类型的数据输出使用的格式占位符是%llu
// // // // //     // 无论是有符号的long long还是无符号的long long类型的数据也可以使用%d格式占位符,但是建议使用各自的
// // // // //     printf("ll1变量的值是:%lld\n",ll1);
// // // // //     printf("ll2变量的值是:%llu\n",ll2);
// // // // //     printf("ll3变量的值是:%lld\n",ll3);
// // // // //     printf("ll1=%d,ll2=%d,ll3=%d\n",ll1,ll2,ll3);
// // // // //   }

// // // // //   return 0;
// // // // // #include <stdio.h>
// // // // // int main(int argc, char const *argv[])
// // // // // {
// // // // //     for (int i = 9; i >1; i--)
// // // // //     {
// // // // //        for (int j = 1;  j< i; j++)
// // // // //        {
// // // // //         printf("%d*%d=%d\t", j, i, i * j);
// // // // //        }
// // // // //        printf("\n");

       
// // // // //     }
    
// // // // //     return 0;
// // // // // }
// // // // #include <stdio.h>
// // // // /*
// // // //  * 练习：判断闰年
// // // //  * 知识点：
// // // //  *   能被 4 整除但不能被 100 整除，是闰年。
// // // //  *   能被 400 整除，也是闰年。1900 不是，2000 是。
// // // //  *   两个条件用 || 连接。% 用来判断整除，余数是 0 才算整除。
// // // //  */
// // // // int is_leadyear(int year){
// // // //     if ((year%4==0&&year%100!=0)||(year%400==0))
// // // //     {
// // // //        printf("year is leayear%d",year);
// // // //     }
// // // //     printf("year is no leayear%d",year);
    
// // // // }
// // // // int is_day(int year,int month){
// // // //     switch (month)
// // // //     {
// // // //         case 1:
// // // //         case 3:
// // // //         case 5:
// // // //         case 7:
// // // //         case 8:
// // // //         case 10:
// // // //         case 12:
// // // //         return 31;
// // // //         case 4:
// // // //         case 6:
// // // //         case 9:
// // // //         case 11:
// // // //         return 30;
// // // //         case 2:
// // // //             is_leadyear(year);
// // // //         default:
// // // //             break;

       
       
// // // //     }

// // // // }
// // // // int is_follow(int num){
// // // //     int a=(num/100)*(num/100)*(num/100)+(num%10/10)*(num%10/10)*(num%10/10)+(num%10)*(num%10)*(num%10);
// // // //     if (a==num)
// // // //     {
// // // //        printf("year nor%d",(num/100)*(num/100)*(num/100)+(num%10/10)*(num%10/10)*(num%10/10)+(num%10)*(num%10)*(num%10));
// // // //     }
// // // //     printf("year or%d",num);
    
// // // // }
// // // // //求出1-1/2+1/3-1/4…..1/100的和
// // // // int main(int argc, char const *argv[])
// // // // {
// // // //     double sum=1;
// // // //     for (int i = 1; i <=100; i++)
// // // //     {
// // // //         if (i%2==0)
// // // //         {
// // // //            sum-=1.0/i;
// // // //         }else{
// // // //             sum+=1.0/i;
// // // //         }
        
// // // //     }
// // // //     printf("%lf",sum);
    
// // // //     is_leadyear(1900);
// // // //     is_follow(153);
// // // //     is_day(2024,10);
// // // //     for (char i = 'a'; i < 'z'; i++)
// // // //     {
// // // //         printf("%c",i);
// // // //     }
// // // //     for (char i = 'Z'; i > 'A'; i--)
// // // //     {
// // // //         printf("%c",i);
// // // //     }
    
// // // //     return 0;
// // // // }
// // // // //判断一个整数是否是水仙花数，所谓水仙花数是指一个3位数，其各个位上数字立方和等于其本身，例如：153 = 1*1*1 + 5*5*5 + 3*3*3。
// // // // /*
// // // //  * 练习：按年份和月份求天数
// // // //  * 知识点：
// // // //  *   把 switch 的穿透和闰年判断合在一起。
// // // //  *   大月 31 天，小月 30 天。
// // // //  *   2 月：闰年 29 天，平年 28 天。
// // // //  */
// // // // //输出小写的a-z以及大写的Z—A。
// // // #include <stdio.h>
// // // int main()
// // // {
// // //   // c中数组的长度是否可变 长度一旦确定后不可变,长度没有确定前是可以改变的

// // //   // int nums[3] = {10,20,30}; // 数组的长度是3

// // //   // int nums[3]; // 声明了一个int[3]类型的数组,起名为nums,长度是3

// // // //   int len = 3;
// // // //   int nums[len];  // 可以的
// // // //   len = 10;
// // // //请求出一个数组的最小值，并得到对应的索引。


// // //   // int nums[] = {10,20,30,40};

// // //   // int len = 3;
// // //   // int nums[len] = {10,20,30};
  
// // //   // 数组的长度一旦确定后就不能更改
// // // //   int nums[] = {10,20,30,40,5,50,60};
// // // //   int min_index=nums[0];
// // // //   for (int i = 0; i < sizeof(nums)/sizeof(nums[0]); i++)
// // // //   {
// // // //     if (nums[i]<min_index)
// // // //     {
// // // //        min_index=nums[i];
// // // //     }
// // // //     //printf("%d",min_index);
    
// // // //   }
// // // //    printf("%d",min_index);
  

// // //   return 0;
// // // }
// // #include <stdio.h>
// // // （1）定义函数，实现求两个double数字的最大值，并返回。(要求用户输入两个小数)
// // double get_max_number(double x,double y){
// //   return x > y ? x : y;
// // }
// // void swap(int*a,int*b){
// //     int tmp=*a;
// //     tmp=*a;
// //     *a=*b;
// //     *b=tmp;

// // }
// // int sum_tree(int a,int b,int c){
// //     return a+b+c;
    
// // }
// // // （2）交换两个变量的值
// // // （3）定义函数，求出三个int 类型数的和，并返回。
// // int get_sum(int x,int y,int z){
// //   return x + y + z;
// // }
// // // （4）定义函数，判断一个数字是否是质数。
// // // （5）定义一个函数,实现年月日,是今年的第多少天
// // // （6）找某个数据在数组中是否存在,存在则返回索引,否则返回-1
// // // （7）函数实现实心三角形
// // int is_leadyear(int year){
// //     if ((year%4==0&&year%100!=0)||(year%400==0))
// //     {
// //       // printf("year is leayear%d",year);
// //        return 2;
// //     }
// //    // printf("year is no leayear%d",year);
// //     return 1;
    
// // }
// // int day_sum(int a[],int year,int month,int day){
// //     int total=0;
// //     for (int i = 1; i < month-1; i++)
// //     {
// //         total+=a[i];
// //     }
// //     total+=day;
// //     if (is_leadyear(year)==2)
// //     {
// //         total+=2;
// //     }else{
// //         total+=1;
// //     }
// //     return total;
    
    

// // }
// // void draw_tringle(){
// //     for (int i = 1; i < 8; i++)
// //     {
// //         for (int j = 1; j<8-i; j++)
// //         {
// //            printf(" ");
// //         }
// //         for (int j = 1; j < 2*i-1; j++)
// //         {
// //             printf("*");
// //         }
// //         printf("\n");
        
        
// //     }
    
// // }
// // int main()
// // {
// //     int a=10;
// //     int b=11;
// //     swap(&a,&b);
// //     printf("%d %d",a,b); 
// //     int d=sum_tree(1,2,3);
// //     printf("%d\n ",d); 
// //      int days_in_month[] = {31, 28, 31, 30, 31, 30,
// //                            31, 31, 30, 31, 30, 31};
    
    
// //    int total= day_sum(days_in_month,2034,10,5);
// //    printf("%d ",total); 
// //    draw_tringle();
// //   return 0;
// // }
// #include <stdio.h>
// #include <time.h>
// int main()
// {
//   int a;
//   double d;
//   char ch;
//   int nums[3];
//   char chs[3];
//   printf("a = %d,d = %.2f,ch = %c \n", a, d, ch);
//   int len1 = sizeof nums / sizeof nums[0];
//   int len2 = sizeof chs / sizeof chs[0];
//   for (int i = 0; i < len1; i++)
//   {
//     printf("nums[%d] = %d ", i, nums[i]);
//   }
//   printf("\n=========\n");
//   for (int i = 0; i < len2; i++)
//   {
//     printf("chs[%d] = %c ", i, chs[i]);
//   }
//   char chs1[] = "abc";
//   char chs2[] = "def";
//   printf("chs1的字节数:%zu,长度:%zuchs2的字节数:%zu,长度:%zu\n",sizeof(chs1),strlen(chs1),sizeof(chs2),strlen(chs2));
// //   strcat(chs1,chs2);
//   printf("chs1=%s\n",chs1); // abcdef
//   printf("chs2=%s\n",chs2); // def
//   printf("chs1的字节数:%zu,长度:%zu\n",sizeof(chs1),strlen(chs1));
//   char aa[]="asdasda 1";
//   char s ;
//   sscanf(aa,"asdasd%c 1",&s);
//   printf("chs[] = %c ",s);
//   {
//     char chs[100];       // 字符数组容器
//     char name[] = "tom"; // 名字
//     int age = 12;        // 年龄
//     char gender = 'm';   // 性别
//     sprintf(chs, "name is %s,age is %d,gender is %c", name, age, gender);
//     // 把指定格式的字符串数据写入到字符数组中
//     printf("chs=%s\n", chs);
//   }
//   time_t start,end;
//   time(&start);
//   int asas=0;
//   time(&end);
//   double diff=difftime(start,end);
//   printf("result %lf",diff);


//   return 0;
// }
#include <stdio.h>
int main()
{
  int nums[] = {10, 20, 30, 40, 50};
  int len = sizeof(nums) / sizeof(int); // 计算数组长度
  for (int i = 0; i < len; i++)
    printf("索引:%d,元素值:%d,对应的内存地址:%p\n", i, nums[i], &nums[i]);
  printf("\n========================\n");
  int *ptr1 = &nums[0];
  int *ptr2 = &nums[3];
  // 相差了3个元素数/相差了12个字节
  printf("ptr1-ptr2=%td\n",ptr1-ptr2); // -3
  printf("ptr2-ptr1=%td\n",ptr2-ptr1); // 3

  double d1 = 12.34;
  double d2 = 23.45;
  double *ptr3 = &d1;
  double *ptr4 = &d2; 
  printf("ptr3-ptr4=%td\n",ptr3-ptr4); // 1
  printf("ptr4-ptr3=%td\n",ptr4-ptr3); // -1
  int numsa[] = {10, 20, 30};
printf("数组的内存地址:%p\n", &numsa);
    int(*arr_ptr)[3] = &numsa; // 声明了一个数组指针,类型是int(*)[3] ,并设置其指向为数组的内存地址
    printf("数组指针指向的内存地址:%p\n", arr_ptr);
    printf("数组指针指向的内存地址:%p\n", &arr_ptr+1);
    // 数组的内存地址+1,实际上是向后移动一个单位,也就是数组的总字节数
    printf("&nums+1指向的地址:%p\n", arr_ptr + 1);  
    printf("&nums+1指向的地址:%p\n", arr_ptr + 2);    // 向后移动一个单位(12个字节)
    printf("arr_ptr+1指向的地址:%p\n", &numsa + 1);
    printf("arr_ptr+1指向的地址:%p\n", &numsa + 2);
    printf("arr_ptr+1指向的地址:%p\n", numsa + 1); 
    printf("arr_ptr+1指向的地址:%p\n", numsa + 2);// 向后移动一个单位(12个字节)


  return 0;
}