/* 案例：二维数组的行。grid 是 int[2][3]，6 个数在内存里挨着放。
   一个 int 4 字节。grid + 1 的类型是 int (*)[3]，一步跨过一整行 12 字节。
   flat 是 int *，一步只跨 4 字节，所以下标要写成 r * 3 + c。
   block 是 int (*)[2][3]，一步跨过整张表 24 字节。
   下面每一种都打出
     1 2 3
     4 5 6 */
#include <stdio.h>

int main(void)
{
    int grid[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int (*row)[3] = grid;          /* 指向第 0 行，和退化后的 grid 同一类型 */
    int *flat = &grid[0][0];       /* 指向 1。flat + 1 到 2，不是到 4 */
    int (*block)[2][3] = &grid;    /* 指向整张表 */
    int r;
    int c;
    int n;

    printf("一个 int %zu 字节，一行 %zu 字节，整张表 %zu 字节\n",
           sizeof(grid[0][0]), sizeof(grid[0]), sizeof(grid));

    /* 行、列都用下标。grid[1][2] 是 6。 */
    printf("1. grid[r][c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", grid[r][c]);
        printf("\n");
    }

    /* r[grid] 先变成第 r 行，再退化成 int *。c[那一行] 就是 *(那一行 + c)。
       r[grid][c]、c[grid[r]] 也到同一格。 */
    printf("2. c[r[grid]]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", c[r[grid]]);
        printf("\n");
    }

    /* grid + r 先跨 r 行。再 + c 在那一行里跨 c 个 int，两层 * 读出元素。 */
    printf("3. *(*(grid + r) + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(*(grid + r) + c));
        printf("\n");
    }

    /* 行用偏移解开，列用下标。(*(grid + 1))[0] 就是第 1 行的 4。 */
    printf("4. (*(grid + r))[c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", (*(grid + r))[c]);
        printf("\n");
    }

    /* grid[r] 是第 r 行，在这里退化成 int *，再按列偏移。 */
    printf("5. *(grid[r] + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(grid[r] + c));
        printf("\n");
    }

    /* &grid[r][0] 是这一行第一个 int 的地址，和退化后的 grid[r] 相同。 */
    printf("6. *(&grid[r][0] + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(&grid[r][0] + c));
        printf("\n");
    }

    /* *grid 先落到第 0 行，再退化成 int *，一步只跨一个 int。
       第 1 行的第一个数在第 0 行后面 3 个 int 的位置，所以写成 r * 3 + c。 */
    printf("7. *(*grid + r * 3 + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(*grid + r * 3 + c));
        printf("\n");
    }

    /* row 是 grid 的副本，类型写明是 int (*)[3]。这个循环不改 row。 */
    printf("8. row[r][c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", row[r][c]);
        printf("\n");
    }

    /* (*row)[c] 读当前这一行。row++ 再跨过 12 字节，站到下一行。 */
    printf("9. (*row)[c] 然后 row++\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", (*row)[c]);
        printf("\n");
        row++;
    }

    /* flat 从第一个字节按 int 往前数。第 r 行第 c 列是第 r * 3 + c 个 int。 */
    printf("10. *(flat + r * 3 + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(flat + r * 3 + c));
        printf("\n");
    }

    /* *flat++ 先读再前进。6 次把两行连成 1 2 3 4 5 6。走完 flat 停在表的后面。 */
    printf("11. *flat++\n");
    printf("  ");
    for (n = 0; n < 6; n++)
        printf("%d ", *flat++);
    printf("\n");

    /* *block 取出整张表，再按 [r][c] 取元素。block + 1 会跨过全部 24 字节。
       block[0][r][c] 和 (*block)[r][c] 是同一写法。 */
    printf("12. (*block)[r][c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", (*block)[r][c]);
        printf("\n");
    }

    return 0;
}
