/* 案例：字符数组。word 里有一份可以改的字符，末尾还有一个 '\0'。
   数组名在表达式里退化成 char *，指向第一个字符。
   sizeof 里的数组名不退化：word[] = "abc" 是 4 字节，big[8] 是 8 字节。
   数组名本身不能改去指别的字符串，要换起点就用另一个 char *。 */
#include <stdio.h>

int main(void)
{
    char word[] = "abc";
    char big[8] = "abc";
    char letters[] = {'a', 'b', 'c', '\0'};
    char *p;
    char *q;
    int n;

    /* "abc" 加 '\0' 一共 4 字节。下面用指针数到 '\0' 之前，个数是 3。 */
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

    /* word[0]、0[word]、*(word + 0) 都是第一个字符 'a'。
       &word[0] 和退化后的 word 是同一个地址。 */
    printf("3. word[0]、0[word]、*(word + 0)\n");
    printf("  %c %c %c\n", word[0], 0[word], *(word + 0));
    printf("4. &word[0] 和 word\n");
    printf("  %s\n", (&word[0] == word) ? "相同" : "不同");

    /* 这三步都写进 word 自己的格子：Abc，再 ABc，再 ABZ。 */
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

    /* p 重新指回开头，逐个打出 A B Z。*p++ 先读当前字符再前进，碰到 '\0' 停。 */
    printf("8. *walk 打出每个字符\n");
    printf("  ");
    p = word;
    while (*p != '\0')
        printf("%c ", *p++);
    printf("\n");

    /* big 的容量是 8，里面的内容仍是 "abc"。q = big + 1 只改 q，从 'b' 开始打出 bc。 */
    printf("9. sizeof big[8]\n");
    printf("  %zu\n", sizeof big);
    printf("10. big 里的内容\n");
    printf("  %s\n", big);
    q = big;
    q = q + 1;
    printf("11. q = big + 1\n");
    printf("  %s\n", q);

    /* 用花括号逐个放字符时，'\0' 要自己写上，否则 %s 不知道在哪停。sizeof 仍是 4。 */
    printf("12. letters\n");
    printf("  %s\n", letters);
    printf("13. sizeof letters\n");
    printf("  %zu\n", sizeof letters);
    return 0;
}
