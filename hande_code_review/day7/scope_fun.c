// // #include <stdio.h>
// // double price = 200.0;
// // void test01()
// // {
// //   printf("%.2f \n", price);
// // }
// // void test2()
// // {
// //   price = 250.0;
// //   printf("%.2f \n", price);
// // }
// // int main()
// // {
// //   printf("%.2f \n", price); // 200.00
// //   test01(); // 200.00
// //   test2(); // 250.00
// //   test01(); // 250.00
// //   return 0;
// // }


// // #include <stdio.h>
// // int a = 10;
// // void func1()
// // {
// //   int a = 20;
// //   printf("func1 a = %d \n", a);
// // }
// // void func2(int a)
// // {
// //   printf("func2 a = %d \n", a); // 30
// // }
// // void func3()
// // {
// //   printf("func3 a = %d \n", a);
// // }
// // int main()
// // {
// //   int a = 30;
// //   func1(); // 20
// //   func2(a); // 30
// //   func3(); // 10 
// //   {
// //     int a = 40;
// //     printf("block a = %d \n", a); // 40
// //   }
// //   printf("main a = %d \n", a); // 30
// //   return 0;
// // }
// #include <stdio.h>
// /*
//   函数的返回值:函数的返回值的类型不是void,函数内部应该有return关键字,并且后面有明确的数据,该函数就是有返回值的

//   函数的返回值:1.函数无返回值
//               2.函数有返回值
//               3.函数没有明确的返回值


//   1. 函数无返回值,类型是void
//   void---无类型---没有意义的类型----空类型,这种类型是不能定义或声明变量的
//   当一个函数的返回值类型是void,该函数没有返回值
//   即使该函数中有return,或者return后面有没有数据值,或者该函数中没有return,都没有关系

//   2. 函数有返回值,函数的返回值类型不是void
//   该函数的返回值类型不是void,并且该函数内部有return,且return后面有明确的数据值

//   3.函数没有明确的返回值,函数的返回值类型不是void,
//   该函数内部没有return,或者return后面没有明确的数据值



// */
// // 函数声明或定义
// // void func1()
// // {
// //   printf("func1函数\n");
// //   // return 100;
// // }
// // // 函数声明或定义
// // int get_sum()
// // {
// //   return 10 + 20;
// // }

// // // 函数声明或定义
// // void get_sub(){
// //   // int sub = 100 - 20;
// //   int sub = 100 - 20;
// //   return;
// // }
// // int main()
// // {
// //   //  void result= func1(); // 函数调用
// //   // int sum = get_sum();
// //   // printf("结果是:%d\n", sum);
// //   int sub = get_sub();
// //   printf("结果是:%d\n",sub);

// //   return 0;
// // }
// // #include <stdio.h>
// // int num = 10; // 全局变量
// // int main()
// // {
// //   // int num = 10;
// //   // int num = 20;
// //   // 同一个作用域(同一个范围)中不能声明同名的标识符
// //   // 就近原则:在一个范围内(作用域)访问一个数据的时候(变量/常量/数组)优先在当前作用域中查找其声明,找到则直接使用,找不到则继续向上一个作用域中,找到则使用,找不到则继续向上找,找到则使用,找不到最终报错
// //   int num = 20; // 局部变量
// //   {
// //     int num = 30;
// //     printf("num=%d\n", num);
// //   }

// //   return 0;
// // }
// // #include <stdio.h>
// // // int num;         // 全局变量
// // // const double PI; // 全局常量
// // // char chs[10];    // 全局字符数组
// // // 全局变量/全局常量/全局数组声明未赋值,默认是0或者\0
// // // 局部变量/局部常量/局部数组声明未赋值,一般默认是垃圾值/随机值(不敢保证)
// // int main()
// // {
// //   int num;                  // 局部变量
// //   const double PI;          // 局部常量
// //   char chs[100];            // 局部字符数组
// //   printf("num=%d\n", num);  //
// //   printf("PI=%.2lf\n", PI); //
// //   printf("chs=%s\n", chs);  //
// //   for (int i = 0; i < 100; i++)
// //     printf("%c ", chs[i]);


// //   // 全局变量/全局常量/全局数组作用域范围:在整个.c文件中,任何的函数中也访问和使用
// //   // 全局变量/全局常量/全局数组只是声明未初始化,默认值是0或\0
// //   // 全局变量/全局常量/全局数组在某个位置修改后,其他位置访问的时候是修改后的数据值

// //   return 0;
// // }
// // #include <stdio.h>
// // int num = 10;           // 局部变量
// // const double PI = 3.14; // 局部常量
// // char chs[] = "hell0";   // 局部数组
// // void f1()

// // {

// //   int num = 10;           // 局部变量
// //   const double PI = 3.14; // 局部常量
// //   char chs[] = "hell0";   // 局部数组
// // }
// // void f2()
// // {
// //   printf("num=%d\n", num);  //
// //   printf("PI=%.2lf\n", PI); //
// //   printf("chs=%s\n", chs);  //
// // }
// // int main()
// // {
// //     void f2();
// //   // 局部变量/局部常量/局部数组的使用和访问范围在当前的函数中,其他函数不能直接访问
// //   // 局部变量/局部常量/局部数组只声明未赋值,默认一般都是垃圾值
// //   // 函数调用结束后,这些数据会销毁和释放

// //   return 0;
// // }
// #include <stdio.h>
// int a = 100;
// int b = 200;
// int c=9;
// void show_ab()
// {
//   int a = 300;
//   a += 10;
//   b += 20;
//   printf("函数内部a = %d ,b = %d,%d \n", a, b,c); // 310 220
// }
// int main()
// {
//   show_ab();
//   printf("函数外部a = %d ,b = %d \n", a, b); // 100 220 
//   return 0;
// }
#include <stdio.h>
int main()
{
  // 数组指针:就是指针变量,指向的是数组的内存地址
  // 数组指针的声明或定义的语法:
  // 数据类型名 (* 数组指针变量名)[长度] = 数组的内存地址;
  // 数组的内存地址是不能进行相加赋值/相减赋值整数运算的,可以进行加减整数运算,因为不会改变指向
  // 数组指针和数组内存地址进行加1运算,都是向后移动一个单位,也就是数组的总字节数
  // int nums[] = {10, 20, 30};
  // printf("数组的内存地址:%p\n", &nums);
  // int(*arr_ptr)[3] = &nums; // 声明了一个数组指针,类型是int(*)[3] ,并设置其指向为数组的内存地址
  // printf("数组指针指向的内存地址:%p\n", arr_ptr);
  // // 数组的内存地址+1,实际上是向后移动一个单位,也就是数组的总字节数
  // printf("&nums+1指向的地址:%p\n", &nums + 1);     // 向后移动一个单位(12个字节)
  // printf("arr_ptr+1指向的地址:%p\n", arr_ptr + 1); // 向后移动一个单位(12个字节)
  // // nums和&nums[0] 等价关系 向后移动1个单位就是4个字节,&nums不是等价关系,向后移动1个单位,越界位置的地址
  // // 不可以,原因:不是指针
  // // &nums += 1;
  // // &nums++;
  // // &nums = &nums + 1;
  // // 可以----原因:arr_ptr是数组指针---也是指针,可以改变指向
  // // arr_ptr += 1; //
  // // arr_ptr++;
  // // arr_ptr = arr_ptr + 1;
  // printf("\n============\n");
  // for (int i = 0; i < 3; i++)
  // {
  //   printf("索引:%d,元素值:%d,内存地址:%p\n", i, nums[i], &nums[i]);
  // }
  // printf("\n============\n");
  // printf("数组的内存地址:%p\n", &nums);
  // printf("数组名对应的内存地址:%p\n", nums);
  // printf("数组中第一个元素的内存地址:%p\n", &nums[0]);

  // printf("\n============\n");
  // printf("向后移动1个单位后的内存地址:%p\n", &nums + 1);
  // printf("向后移动1个单位后的内存地址:%p\n", nums + 1);
  // printf("向后移动1个单位后的内存地址:%p\n", &nums[0] + 1);

  // &nums和nums和&nums[0]都不是指针
  // &nums------数组的内存地址,&nums+1,向后移动1个单位(数组的总字节数),不可以:&nums++/&nums+=1/&nums=&nums+1
  // nums-------第一个元素内存地址,nums+1,向后移动1个单位(4个字节)不可以:nums++/nums+=1/nums=nums+1
  // &nums[0]----第一个元素内存地址,&nums[0]+1,向后移动1个单位(4个字节)不可以:&nums[0]++/&nums[0]+=1/&nums[0]=&nums[0]+1

  {
    int nums[] = {10, 20, 30};
    printf("数组的内存地址:%p\n", &nums);
    int(*arr_ptr)[3] = &nums; // 声明了一个数组指针,类型是int(*)[3] ,并设置其指向为数组的内存地址
    printf("数组指针指向的内存地址:%p\n", arr_ptr);
    // 数组的内存地址+1,实际上是向后移动一个单位,也就是数组的总字节数
    printf("&nums+1指向的地址:%p\n", &nums + 1);     // 向后移动一个单位(12个字节)
    printf("arr_ptr+1指向的地址:%p\n", arr_ptr[0] + 1); // 向后移动一个单位(12个字节)
    int num=5;
    int *p=&num;
    printf("%zu\n",sizeof(&p));
    printf("%zu\n",sizeof(p));
    int *p2=p+4;
    printf("%d",p2-p);

    
    printf("\n============\n");
    for (int i = 0; i < 3; i++)
      printf("索引:%d,元素值:%d,内存地址:%p\n", i, nums[i], &nums[i]);
    printf("\n============\n");
    printf("数组的内存地址:%p\n", &nums);
    printf("数组名对应的内存地址:%p\n", nums);
    printf("数组中第一个元素的内存地址:%p\n", &nums[0]);

    printf("\n============\n");
    printf("向后移动1个单位后的内存地址:%p\n", &nums + 1);
    printf("向后移动1个单位后的内存地址:%p\n", nums + 1);
    printf("向后移动1个单位后的内存地址:%p\n", &nums[0] + 1);
    // nums和&nums[0] 等价关系 向后移动1个单位就是4个字节,&nums不是等价关系,向后移动1个单位,越界位置的地址
  }

  return 0;
}