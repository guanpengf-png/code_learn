/* 案例：普通指针 +1，跨过一个元素。
   类型是 int *，一步是 sizeof(int)，也是 sizeof *p，这里是 4 字节。
   p + 1 算出新地址，并不自动改 p。 */
#include <stdio.h>

int main(void)
{
    int nums[5] = {10, 20, 30, 40, 50};
    int *p = nums;
    int *saved;
    int *walk;
    int *back;
    int *end = nums + 5; /* 最后一格的后面。可以形成这个地址，不要 *end */
    int i;

    /* p 指着 10，这次读取没有改 p。 */
    printf("1. *p\n");
    printf("  %d\n", *p);
    /* 算出下一格的地址再读，p 仍指着 10。 */
    printf("2. *(p + 1)\n");
    printf("  %d\n", *(p + 1));
    printf("3. *(p + 4)\n");
    printf("  %d\n", *(p + 4));
    printf("4. 这一步是 %zu 字节，sizeof *p 是 %zu\n",
           sizeof(int), sizeof nums);
    /* p + 1 和 &nums[1] 是同一格。 */
    printf("5. p + 1 与 &nums[1]\n");
    printf("  %s\n", (p + 1 == &nums[1]) ? "相同" : "不同");

    /* 循环只改 i，没有给 p 赋值。 */
    printf("6. p 不动，*(p + i) 走完整段\n");
    printf("  ");
    for (i = 0; i < 5; i++)
        printf("%d ", *(p + i));
    printf("\n");

    /* saved 留在 10。p = p + 1 才把 p 自己改到 20。 */
    saved = p;
    p = p + 1;
    printf("7. p = p + 1 之后 *p，saved 仍指着开头\n");
    printf("  %d %d\n", *p, *saved);

    /* *walk++ 是 *(walk++)：先读当前 int，再让 walk 前进。
       walk < end 时才读，所以不会读 end 那一格。 */
    printf("8. *walk++ 从前往后\n");
    printf("  ");
    walk = nums;
    while (walk < end)
        printf("%d ", *walk++);
    printf("\n");
    /* 指针相减得到元素个数 5，不是字节数。 */
    printf("9. end - nums\n");
    printf("  %ld\n", (long)(end - nums));

    /* back 先放在 end。循环先 back-- 再读，第一次读到 50，最后读到 10。
       这样不会把指针移到数组开头的前面。 */
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
