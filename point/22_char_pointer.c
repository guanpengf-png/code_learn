/* 案例：字符指针。text 的格子里是地址，可以改去指另一串字符。
   "abc"、"hello" 这种字面量不要通过指针去改。
   word 是数组，里面的字符可以改。sizeof text 是指针 8 字节，sizeof word 是数组 4 字节。 */
#include <stdio.h>

int main(void)
{
    const char *text = "abc";     /* const 锁字符：能改 text 的指向，不能写 *text */
    char word[] = "abc";          /* 数组里有一份可以改的字符 */
    char *writable = word;        /* 指向 word，可以改字符，也可以改指向 */
    char *const fixed = word;     /* const 锁指针：fixed 一直指着 word[0]，可以写 *fixed */
    const char *view = word;      /* 能改指向，只能读字符 */
    const char *rows[2] = {"abc", "hello"};
    const char **sp = rows;       /* 指向指针数组的第一格 */
    const char **walk;

    /* text 打出 abc。text + 1 从第二个字符开始，打出 bc。text 自己还指着 'a'。 */
    printf("1. text\n");
    printf("  %s\n", text);
    printf("2. text + 1\n");
    printf("  %s\n", text + 1);
    /* 把指针格子换成 "hello" 的地址。原来的 "abc" 还在，只是 text 不再指它。 */
    text = "hello";
    printf("3. text = \"hello\"\n");
    printf("  %s\n", text);
    printf("4. sizeof text，这是指针\n");
    printf("  %zu\n", sizeof text);
    printf("5. sizeof word，这是数组\n");
    printf("  %zu\n", sizeof word);

    /* writable 和 word 指着同一份字符。writable[0] = 'A' 把数组改成 Abc。 */
    writable[0] = 'A';
    printf("6. writable[0] = 'A' 之后 word\n");
    printf("  %s\n", word);
    /* view 改去指 word + 1，打出 bc。这一步没有写字符。 */
    view = view + 1;
    printf("7. const char *view 改指向 word + 1\n");
    printf("  %s\n", view);

    /* *fixed 写进 word[0]，数组变成 Zbc。fixed 不能再赋成别的地址，它仍等于 word。 */
    *fixed = 'Z';
    printf("8. char *const fixed 写 *fixed 之后 word\n");
    printf("  %s\n", word);
    printf("9. fixed 和 word\n");
    printf("  %s\n", (fixed == word) ? "相同" : "不同");

    /* sp[0] 是 "abc"，*(sp + 1) 是 "hello"。
       *walk++ 先打出当前这串，再移到下一格。两步打出 abc 和 hello。 */
    printf("10. sp[0]、*(sp + 1)\n");
    printf("  %s %s\n", sp[0], *(sp + 1));
    printf("11. *walk++ 两串\n");
    walk = rows;
    printf("  %s\n", *walk++);
    printf("  %s\n", *walk++);
    return 0;
}
