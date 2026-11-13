/* 案例：二维数组的行。grid + 1 跨过一整行。
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
    int (*row)[3] = grid;
    int *flat = &grid[0][0];
    int (*block)[2][3] = &grid;
    int r;
    int c;
    int n;

    printf("一个 int %zu 字节，一行 %zu 字节，整张表 %zu 字节\n",
           sizeof(grid[0][0]), sizeof(grid[0]), sizeof(grid));

    /* 1. 两个下标。 */
    printf("1. grid[r][c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", grid[r][c]);
        printf("\n");
    }

    /* 2. 下标对调。c[r[grid]]、r[grid][c]、c[grid[r]] 是同一个元素。 */
    printf("2. c[r[grid]]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", c[r[grid]]);
        printf("\n");
    }

    /* 3. 先按行偏移，再按列偏移。grid + r 的类型是 int (*)[3]。 */
    printf("3. *(*(grid + r) + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(*(grid + r) + c));
        printf("\n");
    }

    /* 4. 行指针解开后，再用下标取列。 */
    printf("4. (*(grid + r))[c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", (*(grid + r))[c]);
        printf("\n");
    }

    /* 5. 行用下标，列用偏移。grid[r] 退化成 int *。 */
    printf("5. *(grid[r] + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(grid[r] + c));
        printf("\n");
    }

    /* 6. 行首地址。&grid[r][0] 和退化后的 grid[r] 是同一个地址。 */
    printf("6. *(&grid[r][0] + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(&grid[r][0] + c));
        printf("\n");
    }

    /* 7. *grid 落到第 0 行，再退化成 int *，一步跨一个 int。
       下标写成 r * 3 + c，才能从第 0 行走到后面的行。 */
    printf("7. *(*grid + r * 3 + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(*grid + r * 3 + c));
        printf("\n");
    }

    /* 8. 复制出一行指针，类型是 int (*)[3]。按下标走，row 自己不动。 */
    printf("8. row[r][c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", row[r][c]);
        printf("\n");
    }

    /* 9. 行指针自己往前走。row++ 跨过一整行。 */
    printf("9. (*row)[c] 然后 row++\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", (*row)[c]);
        printf("\n");
        row++;
    }

    /* 10. 摊成一串 int *。元素在内存里挨着放，flat + 1 跨一个 int。 */
    printf("10. *(flat + r * 3 + c)\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", *(flat + r * 3 + c));
        printf("\n");
    }

    /* 11. 这串指针自己往前走，6 个数连成一行。 */
    printf("11. *flat++\n");
    printf("  ");
    for (n = 0; n < 6; n++)
        printf("%d ", *flat++);
    printf("\n");

    /* 12. 数组指针包住整张表。block 一步跨过 2 行，
       (*block)[r][c] 才是里面的元素。block[0][r][c] 是同一写法。 */
    printf("12. (*block)[r][c]\n");
    for (r = 0; r < 2; r++) {
        printf("  ");
        for (c = 0; c < 3; c++)
            printf("%d ", (*block)[r][c]);
        printf("\n");
    }

    return 0;
}
