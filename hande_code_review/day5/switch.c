#include <stdio.h>

int main(int argc, char const *argv[])
{
    int oil,oil_vo;
    double price=0.0;
    scanf("%d,%lf,%d",&oil,&price,&oil_vo);
    switch (oil)
    {
    case 94:
        price=5;
        if (oil_vo>40)
        {
            price=3.5;
        }
    case 96:
        price=3;
        if (oil_vo>30)
        {
            price=2.5;
        }
        
        break;
    
    default:
        printf("error");
        break;
    }
    printf("%d and price %lf",oil,price);
    return 0;
}
