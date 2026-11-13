/* 案例：二维数组的行。grid + 1 跨过一整行。 */
#include <stdio.h>

int main(void)
{
    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("第一行第一个 = %d\n", grid[0][0]);
    printf("grid + 1 落到第二行，第一个 = %d\n", (*(grid + 1))[0]);
    printf("一行是 %zu 字节\n", sizeof(grid[0]));
    return 0;
}
