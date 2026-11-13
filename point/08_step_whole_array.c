/* 案例：数组指针 +1，跨过整段数组。
   block 的类型是 int (*)[5]，一步 20 字节，跨过一整行。
   one 的类型是 int *，一步 4 字节，只跨过一个 int。
   两个指针从同一个字节出发，步长不同。 */
#include <stdio.h>

int main(void)
{
    int table[2][5] = {
        {10, 20, 30, 40, 50},
        {60, 70, 80, 90, 100}
    };
    int (*block)[5] = table; /* table 退化成指向第 0 行的指针 */
    int *one = table[0];     /* 指向 10 */
    int c;

    /* 一个 int 4 字节，一行 20 字节，整张表 40 字节。 */
    printf("一个 int %zu 字节，block 一步 %zu 字节，整张表 %zu 字节\n",
           sizeof *one, sizeof *block, sizeof table);

    /* (*block) 是第 0 行，[0] 取到 10。block 自己没动。 */
    printf("1. (*block)[0]\n");
    printf("  %d\n", (*block)[0]);
    /* block + 1 先跨过一整行，再取那一行的第 0 个，是 60。 */
    printf("2. (*(block + 1))[0]\n");
    printf("  %d\n", (*(block + 1))[0]);
    /* 第 1 行第 2 个是 80。 */
    printf("3. (*(block + 1))[2]\n");
    printf("  %d\n", (*(block + 1))[2]);
    /* block[1] 就是 *(block + 1)。 */
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

    /* one + 1 只跨 4 字节，读到 20。one + 4 还在第 0 行的最后一个。 */
    printf("7. int *one 一步跨过一个 int，*(one + 1)\n");
    printf("  %d\n", *(one + 1));
    printf("8. one 仍在第一行，*(one + 4)\n");
    printf("  %d\n", *(one + 4));

    /* 这一次 block 自己跨过 20 字节，站到第 1 行。one 仍指着 10。 */
    block = block + 1;
    printf("9. block = block + 1 之后 (*block)[0]\n");
    printf("  %d\n", (*block)[0]);
    return 0;
}
