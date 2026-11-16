// #include <stdio.h>
// /*
//   作用域:使用的范围:变量/常量/数组...的使用范围
//   作用域:全局作用域/局部作用域/块级作用域
//   全局作用域:指的是全局变量/全局常量/全局数组等的使用范围,整个的.c文件
//   局部作用域:指的是局部变量/局部常量/局部数组等的使用范围,函数内部
//   块级作用域:指的是块级变量/块级常量/块级数组等的使用范围,出了函数的大括号以外的大括号中
//   全局变量/全局常量/全局数组:在函数外部声明或定义的变量/常量/数组
//   局部变量/局部常量/局部数组:在函数内部声明或定义的变量/常量/数组
//   块级变量/块级常量/块级数组:在大括号中(除了函数大括号)声明的变量/常量/数组



// */
// int num = 10;              // 全局变量
// int nums[] = {10, 20, 30}; // 全局数组
// const double PI = 3.14;    // 全局常量

// void f1()
// {
//   int num2 = 10;              // 局部变量
//   int nums2[] = {10, 20, 30}; // 局部数组
//   const double PI2 = 3.14; 
//   num=20;
//   printf("%d",num);   // 局部常量
// }
// void f2()
// {
//     printf("%d",num);
 
// }
// void f3()
// {
//     num=4;
//     printf("%d",num);
 
// }
// int main()
// {
//   {
//     f1();
//     num = 100;              // 块级变量
//     int nums3[] = {10, 20, 30}; // 块级数组
//     const double PI3 = 3.14; 
//     printf("%d",num);   // 块级常量
//   }
//   if(1){
//     int a = 10; // 块级变量
//   }
//   f1();
//   f2();
//   f3();
//   return 0;
// }
#include <stdio.h>
// int num;         // 全局变量
// const double PI; // 全局常量
// char chs[10];    // 全局字符数组
// 全局变量/全局常量/全局数组声明未赋值,默认是0或者\0
// 局部变量/局部常量/局部数组声明未赋值,一般默认是垃圾值/随机值(不敢保证)
// int main()
// {
//   int num;                  // 局部变量
//   const double PI;          // 局部常量
//   char chs[100];            // 局部字符数组
//   printf("num=%d\n", num);  //
//   printf("PI=%.2lf\n", PI); //
//   printf("chs=%s\n", chs);  //
//   for (int i = 0; i < 100; i++)
//     printf("%c ", chs[i]);


//   // 全局变量/全局常量/全局数组作用域范围:在整个.c文件中,任何的函数中也访问和使用
//   // 全局变量/全局常量/全局数组只是声明未初始化,默认值是0或\0
//   // 全局变量/全局常量/全局数组在某个位置修改后,其他位置访问的时候是修改后的数据值

//   return 0;
// }
// #include <stdio.h>
// void f1()
// {

//   int num = 10;           // 局部变量
//   const double PI = 3.14; // 局部常量
//   char chs[] = "hell0";   // 局部数组
// }
// void f2()
// {
//   printf("num=%d\n", num);  //
//   printf("PI=%.2lf\n", PI); //
//   printf("chs=%s\n", chs);  //
// }
// int main()
// {
//   // 局部变量/局部常量/局部数组的使用和访问范围在当前的函数中,其他函数不能直接访问
//   // 局部变量/局部常量/局部数组只声明未赋值,默认一般都是垃圾值
//   // 函数调用结束后,这些数据会销毁和释放

//   return 0;
// }
// #include <stdio.h>
// int a = 100;
// int b = 200;
// void show_ab()
// {
//   int a = 300;
//   a += 10;
// //   int b=0;
//   b += 20;
//   printf("函数内部a = %d ,b = %d \n", a, b); // 310 220
// }
// int main()
// {
//   show_ab();
//   printf("函数外部a = %d ,b = %d \n", a, b); // 100 220 
//   return 0;
// }
// #include <stdio.h>
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
//   return 0;
// }
// #include <stdio.h>
// int main()
// {
//     int num=5;
//     const double PI=10;
//     char chs[2]={'a','1'};

//   {
//     int num;
//     const double PI;
//     char chs[100];
//     printf("num=%d\n", num);  //
//     printf("PI=%.2lf\n", PI); //
//     printf("chs=%s\n", chs);  //
//   }
//     printf("num=%d\n", num);  //
//     printf("PI=%.2lf\n", PI); //
//     printf("chs=%s\n", chs);  //

//   return 0;
// }
#include <stdio.h>
int len = 5;
int arr[5] = {10, 20, 30, 40, 50};
void fn(int num)
{
  int a = 250;
  printf("%d \n", num + a); // 270  310
}
int get_sum(int x,int y){
  return x + y;
  // printf("这是一个函数\n");
}
int main()
{
  int sum = get_sum(10,20);
  printf("结果是:%d\n",sum);
  fn(20);
  for (int i = 0; i < 5; i++)
  {
    printf("%d ", arr[i]); // 10,20,30,40,50
  }
  // printf("最终i的值是:%d\n",i);
  printf("\n============\n");
  fn(60); // 
  return 0;
}