#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    for (int i = 1; i <=9; i++)
    {
        for (int j = 1; j<=i; j++)
        {
            printf("%d*%d=%d",i,j,i*j);
        }
        printf("\n");
        
    }
    for (int i = 9; i >=1; i--)
    {
        for (int j = 1; j<=i; j++)
        {
            printf("%d*%d=%d",i,j,i*j);
        }
        printf("\n");
        
    }
    for (int i = 9; i >=1; i--)
    {
        for (int j = 1; j<=i; j++)
        {
            printf("%d*%d=%d",j,i,i*j);
        }
        printf("\n");
        
    }
    // 编写程序，要求输入一个数字，判断该数字是否是质数(素数)。
  // 说明：质数指只能被1和自身整除且大于1的数字。
    // int primer_num;
    // scanf("%d",&primer_num);
    // bool flag=primer_num>1?true:false;
    // for (int i = 0; i < primer_num/2; i++)
    // {
    //    if (primer_num%i==0)
    //    {
    //     flag=false;
    //     break;
    //    }

       

    // }
    // if (flag)
    // {
    //    printf("primer_num%d",primer_num);
    // }
     // 输出100以内（包括100）的数字，跳过那些7的倍数或包含7的数字
     for (int i = 0; i <=100; i++)
     {
        if (i%7==0||i%10==7||i/10==7)
        {
            printf("%d\n",i);
        }
        
     }
     int l=0;
     a:
        if (l<4)
        {
            printf("%d",l);
            l++;
            goto a;
        }
        
     
    
    
    




    

    
    
    

    
    return 0;

}
