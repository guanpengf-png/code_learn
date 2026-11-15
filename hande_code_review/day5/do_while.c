#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i=0;
    int day=10;

    do
    {
        printf("eat food%d day and food number%d",i+1,i+1);
        i++;
    } while (i<10);
    printf("\n");
    //7-15
    int num=7;
    do
    {
       num=num+1;
       

    } while (num<15);
    printf("%d",num);
    {
        int i=53;
        do
        {
            /* code */
            i--;
            printf("%d",i);
        } while (i>48);
    {
        //even number from 1 to 10
        int i=0;
        do
        {
            if (i%2==0)
            {
                printf("%d",i);
            }
            i++;
            

            /* code */
        } while (i<10);
        
    }
    {
        int i=0;
        int sum=0;
        do
        {
            sum+=i;
            i++;
            /* code */
            
        } while (i<=100);
        printf("%d",sum);
    }
        

    }
    {
        int i=0;
        int odd=0;
        do
        {
            if (i%2!=0)
            {
               odd+=i;
            }
            i++;
            
        } while (i<100);
        printf("%d\n",odd);
        
    }
    int sum=0;
    for (int i = 0; i < 100; i++)
    {
        if (i%2==0)
        {
            sum+=i;
        }
        
    }
    // printf("%d",sum);
    // for (int i = 0; i!=123; )
    // {
    //     scanf("%d",&i);
    // }
    
    int n=0;
    for (; n<9; n++)
    {
        printf("%d",n);
    }
    // for (int i = 0, j=0,l=0; i < 1&&j<3&&l<5; i++,j++,l++)
    // {
    //     printf("x=%d,j=%d,l=%d");
    // }
    for (int x = 0, y = 0, z = 0; x < 3 && y < 4 && z < 5; x++, y++, z++)
    printf("x=%d,y=%d,z=%d\n", x, y, z);

    
    
    

    
    return 0;

}
