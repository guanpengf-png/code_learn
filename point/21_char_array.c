/* 案例：字符数组。word 里有一份可以改的字符，含结尾的 \\0。
   数组名放在表达式里会退化成 char *。 */
#include <stdio.h>

int main(void)
{
    char word[] = "abc";
    char big[8] = "abc";
    char letters[] = {'a', 'b', 'c', '\0'};
    char *p;
    char *q;
    int n;

    printf("1. sizeof word，含结尾的 \\0\n");
    printf("  %zu\n", sizeof word);
    n = 0;
    p = word;
    while (*p != '\0') {
        n++;
        p++;
    }
    printf("2. 用指针数到 \\0 之前\n");
    printf("  %d\n", n);

    printf("3. word[0]、0[word]、*(word + 0)\n");
    printf("  %c %c %c\n", word[0], 0[word], *(word + 0));
    printf("4. &word[0] 和 word\n");
    printf("  %s\n", (&word[0] == word) ? "相同" : "不同");

    word[0] = 'A';
    printf("5. word[0] = 'A'\n");
    printf("  %s\n", word);
    p = word;
    p[1] = 'B';
    printf("6. p[1] = 'B'\n");
    printf("  %s\n", word);
    *(p + 2) = 'Z';
    printf("7. *(p + 2) = 'Z'\n");
    printf("  %s\n", word);

    printf("8. *walk 打出每个字符\n");
    printf("  ");
    p = word;
    while (*p != '\0')
        printf("%c ", *p++);
    printf("\n");

    printf("9. sizeof big[8]\n");
    printf("  %zu\n", sizeof big);
    printf("10. big 里的内容\n");
    printf("  %s\n", big);
    q = big;
    q = q + 1;
    printf("11. q = big + 1\n");
    printf("  %s\n", q);

    printf("12. letters\n");
    printf("  %s\n", letters);
    printf("13. sizeof letters\n");
    printf("  %zu\n", sizeof letters);
    return 0;
}
