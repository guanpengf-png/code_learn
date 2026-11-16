// #include <stdio.h>
// // 函数的声明或定义
// void say_hi(){
//   printf("您好\n");
// }
// // 函数的声明或定义
// int get_sub(int x,int y){
//   return x - y;
// }
// // 函数的声明或定义
// double get_sum(double x,double y,double z){
//   return x + y + z;
// }
// int main()
// {
//   // 需求1:调用函数实现打招呼
//   say_hi(); // 调用函数
//   // 需求2:调用函数实现两个整数数字的差
//   int sub = get_sub(100,30); // 调用函数
//   printf("结果是:%d\n",sub);
//   // 需求3:调用函数实现三个小数的和
//   double sum = get_sum(12.34,34.56,56.78); // 调用函数
//   printf("结果是:%.2lf\n",sum);

//   return 0;
// }
#include <stdio.h>
// 主函数的理解
// 一个c程序必须有一个且只能有一个主函数,否则程序无法编译及运行
// 主函数就是程序的主入口
// 主函数是不需要手动调用的,是在运行期间自动调用的,其他的函数需要调用才能执行里面代码
// 不要在其他函数中调用主函数,否则其他函数调用就会形成死循环
// 主函数不要调用主函数自己,否则也是死循环
// 主函数的返回值是int类型,参数有两个
// 主函数的返回值return 0,建议自己书写,0表示程序运行成功,非0表示运行失败
// void f1(){
//   printf("f1函数\n");
//   // main(); // 调用主函数
// }

int main(int argc, char const *argv[])
{
  printf("argc value is:%d\n",argc); // 参数的个数
  for (int i = 0; i < argc;i++){
    printf("argv[%d] value is:%s\n",i,argv[i]); // 默认的exe程序所在的绝对路径
  }
    // printf("主函数\n");
    return 1;
  return 0;
}
// argc---argument count---参数的个数
// argv---argument value--参数的数据值----字符串数组
// int main(int argc, char const *argv[])
// {
//   printf("argc value is:%d\n",argc); // 参数的个数
//   for (int i = 0; i < argc;i++){
//     printf("argv[%d] value is:%s\n",i,argv[i]); // 默认的exe程序所在的绝对路径
//   }
//     // printf("主函数\n");
//     return 1;
// }