/* 案例：数组指针 +1，跨过整段数组。
   table 有 2 行，每行 5 个 int。block 一步跨过一整行。 */
#include <stdio.h>

int main(void)
{
    int table[2][5] = {
        {10, 20, 30, 40, 50},
        {60, 70, 80, 90, 100}
    };
    int (*block)[5] = table;
    int *one = table[0];
    int c;

    printf("一个 int %zu 字节，block 一步 %zu 字节，整张表 %zu 字节\n",
           sizeof *one, sizeof *block, sizeof table);

    printf("1. (*block)[0]\n");
    printf("  %d\n", (*block)[0]);
    printf("2. (*(block + 1))[0]\n");
    printf("  %d\n", (*(block + 1))[0]);
    printf("3. (*(block + 1))[2]\n");
    printf("  %d\n", (*(block + 1))[2]);
    printf("4. block[1][1]\n");
    printf("  %d\n", block[1][1]);

    printf("5. 第一行 (*block)[c]\n");
    printf("  ");
    for (c = 0; c < 5; c++)
        printf("%d ", (*block)[c]);
    printf("\n");
    printf("6. 第二行 (*(block + 1))[c]\n");
    printf("  ");
    for (c = 0; c < 5; c++)
        printf("%d ", (*(block + 1))[c]);
    printf("\n");

    printf("7. int *one 一步跨过一个 int，*(one + 1)\n");
    printf("  %d\n", *(one + 1));
    printf("8. one 仍在第一行，*(one + 4)\n");
    printf("  %d\n", *(one + 4));

    block = block + 1;
    printf("9. block = block + 1 之后 (*block)[0]\n");
    printf("  %d\n", (*block)[0]);
    return 0;
}
