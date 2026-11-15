
#include <stdio.h>
int main()
{
    // 现在有三个班，每个班五名同学，用二维数组保存他们的成绩，并求出每个班级平均分、以及所有班级平均分，数据要求从控制台输入。
    int rows=3;
    int col=5;
    int score[rows][col];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("nums%dand%d",i+1,j+1);
            scanf("%d",&score[i][j]);
        
    }
    int class_num=0;
    int all_class_sum=0;
    for (int i = 0; i < rows; i++)
    {
        class_num=0;
        for (int j = 0; j< col; j++)
        {
            class_num+=score[i][j];

        }
        all_class_sum+=class_num;
    }
    
    
    printf("nums%lf",all_class_sum*1.0/(rows)*(col));


    return 0;}}