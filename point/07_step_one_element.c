/* 案例：普通指针 +1，跨过一个元素。
   nums 是 {10, 20, 30, 40, 50}。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = nums;
    int *saved;
    int *walk;
    int *back;
    int *end = nums + 5;
    int i;

    printf("1. *p\n");
    printf("  %d\n", *p);
    printf("2. *(p + 1)\n");
    printf("  %d\n", *(p + 1));
    printf("3. *(p + 4)\n");
    printf("  %d\n", *(p + 4));
    printf("4. 这一步是 %zu 字节，sizeof *p 是 %zu\n",
           sizeof(int), sizeof *p);
    printf("5. p + 1 与 &nums[1]\n");
    printf("  %s\n", (p + 1 == &nums[1]) ? "相同" : "不同");

    printf("6. p 不动，*(p + i) 走完整段\n");
    printf("  ");
    for (i = 0; i < 5; i++)
        printf("%d ", *(p + i));
    printf("\n");

    saved = p;
    p = p + 1;
    printf("7. p = p + 1 之后 *p，saved 仍指着开头\n");
    printf("  %d %d\n", *p, *saved);

    printf("8. *walk++ 从前往后\n");
    printf("  ");
    walk = nums;
    while (walk < end)
        printf("%d ", *walk++);
    printf("\n");
    printf("9. end - nums\n");
    printf("  %ld\n", (long)(end - nums));

    printf("10. 从最后一个往回走\n");
    printf("  ");
    back = end;
    while (back > nums) {
        back--;
        printf("%d ", *back);
    }
    printf("\n");
    return 0;
}
