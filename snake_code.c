#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAP_W 24
#define MAP_H 24
#define INIT_CAP 16

// position
typedef struct {
    int x;
    int y;
} Point;

// snake status
typedef struct {
    // snake body
    Point *body;
    int len;
    int cap;
    Point dir;
} Snake;

// game status
typedef struct {
    Snake snake;
    Point food;
    // cell
    char *cell;
    int score;
    int alive;
} Game;

static int snake_reserve(Point **body, int *cap, int need);
static int occupied_by_snake(const Snake *s, const Point *pt);
static void spawn_food(Game *g);
static void game_tick(Game *g);

static int idx(int x, int y) {
    return y * MAP_W + x;
}

static char *cell_at(Game *g, int x, int y) {
    return g->cell + idx(x, y);
}

static void clear_cell(Game *g) {
    memset(g->cell, ' ', (size_t)MAP_H * MAP_W);
}

static void paint(Game *g) {
    clear_cell(g);
    if (g->food.x >= 0 && g->food.x < MAP_W &&
        g->food.y >= 0 && g->food.y < MAP_H) {
        *cell_at(g, g->food.x, g->food.y) = '*';
    }

    // get snake body
    const Point *p = g->snake.body;
    const Point *end = g->snake.body + g->snake.len;

    // draw head
    if (p < end) {
        *cell_at(g, p->x, p->y) = '@';
    }

    // draw body
    for (p = g->snake.body + 1; p < end; p++) {
        *cell_at(g, p->x, p->y) = 'o';
    }
}

static int snake_reserve(Point **body, int *cap, int need) {
    if (need <= *cap) {
        return 1;
    }
    int new_cap = *cap ? *cap * 2 : INIT_CAP;
    while (new_cap < need) {
        new_cap *= 2;
    }
    Point *p = realloc(*body, (size_t)new_cap * sizeof *p);
    if (!p) {
        return 0;
    }
    *body = p;
    *cap = new_cap;
    return 1;
}

static void snake_init(Snake *s, int x, int y) {
    s->body = NULL;
    s->len = 0;
    s->cap = 0;
    s->dir = (Point){1, 0};
    if (!snake_reserve(&s->body, &s->cap, 4)) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    s->body[0] = (Point){x, y};
    s->body[1] = (Point){x - 1, y};
    s->body[2] = (Point){x - 2, y};
    s->len = 3;
}

static void snake_free(Snake *s) {
    free(s->body);
    s->body = NULL;
    s->len = 0;
    s->cap = 0;
}

static int point_eq(const Point *a, const Point *b) {
    return a->x == b->x && a->y == b->y;
}

static int inbound(const Point *p) {
    return p->x >= 0 && p->x < MAP_W && p->y >= 0 && p->y < MAP_H;
}

static int occupied_by_snake(const Snake *s, const Point *pt) {
    const Point *p = s->body;
    const Point *end = s->body + s->len;
    for (; p < end; p++) {
        if (point_eq(p, pt)) {
            return 1;
        }
    }
    return 0;
}

static int snake_hit_self(const Snake *s, const Point *head) {
    const Point *p = s->body + 1;
    const Point *end = s->body + s->len;
    for (; p < end; p++) {
        if (point_eq(p, head)) {
            return 1;
        }
    }
    return 0;
}

static void spawn_food(Game *g) {
    Point cand;
    int placed = 0;

    for (int i = 0; i < 10000; i++) {
        cand.x = rand() % MAP_W;
        cand.y = rand() % MAP_H;
        if (!occupied_by_snake(&g->snake, &cand)) {
            placed = 1;
            break;
        }
    }

    // 随机没找到就顺序扫描一遍，避免死循环
    if (!placed) {
        for (int y = 0; y < MAP_H && !placed; y++) {
            for (int x = 0; x < MAP_W && !placed; x++) {
                Point p = {x, y};
                if (!occupied_by_snake(&g->snake, &p)) {
                    cand = p;
                    placed = 1;
                }
            }
        }
    }

    if (!placed) {
        // 蛇占满整个地图，通关
        g->alive = 0;
        return;
    }
    g->food = cand;
}

static void snake_step(Snake *s, int grow) {
    Point new_head = {
        s->body[0].x + s->dir.x,
        s->body[0].y + s->dir.y,
    };

    if (grow) {
        if (!snake_reserve(&s->body, &s->cap, s->len + 1)) {
            fprintf(stderr, "realloc failed\n");
            exit(1);
        }
        // 整体后移一格，尾部保留
        for (int i = s->len; i > 0; i--) {
            s->body[i] = s->body[i - 1];
        }
        s->len++;
    } else {
        // 整体后移一格，尾部丢弃
        for (int i = s->len - 1; i > 0; i--) {
            s->body[i] = s->body[i - 1];
        }
    }
    s->body[0] = new_head;
}

static void game_init(Game *g) {
    g->cell = malloc((size_t)MAP_H * MAP_W);
    if (!g->cell) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    snake_init(&g->snake, MAP_W / 2, MAP_H / 2);
    g->score = 0;
    g->alive = 1;
    spawn_food(g);
}

static void game_free(Game *g) {
    snake_free(&g->snake);
    free(g->cell);
    g->cell = NULL;
}

typedef void (*Dirhandle)(Snake *s);
typedef struct {
    char key;
    Dirhandle fn;
} KeyBind;

static void go_up(Snake *s) {
    if (s->dir.y != 1) {
        s->dir = (Point){0, -1};
    }
}

static void go_down(Snake *s) {
    if (s->dir.y != -1) {
        s->dir = (Point){0, 1};
    }
}

static void go_right(Snake *s) {
    if (s->dir.x != -1) {
        s->dir = (Point){1, 0};
    }
}

static void go_left(Snake *s) {
    if (s->dir.x != 1) {
        s->dir = (Point){-1, 0};
    }
}

static const KeyBind BINDS[] = {
    {'w', go_up},
    {'k', go_up},
    {'s', go_down},
    {'j', go_down},
    {'a', go_left},
    {'d', go_right},
    {'l', go_right},
};

static void game_tick(Game *g) {
    if (!g->alive) {
        return;
    }
    Point next = {
        g->snake.body[0].x + g->snake.dir.x,
        g->snake.body[0].y + g->snake.dir.y,
    };
    if (!inbound(&next) || snake_hit_self(&g->snake, &next)) {
        g->alive = 0;
        return;
    }

    int grow = point_eq(&next, &g->food);
    snake_step(&g->snake, grow);
    if (grow) {
        g->score += 10;
        spawn_food(g);
    }
}

static int handle_key(Game *g, int ch) {
    ch = tolower(ch);
    if (ch == 'q') {
        return 0;
    }
    const KeyBind *b = BINDS;
    const KeyBind *end = BINDS + sizeof BINDS / sizeof *BINDS;
    for (; b < end; b++) {
        if (b->key == ch) {
            b->fn(&g->snake);
            break;
        }
    }
    game_tick(g);
    return 1;
}

static void draw(const Game *g) {
    printf("\033[2J\033[H");
    printf("score=%d len=%d wasd/hjkl move q quit\n", g->score, g->snake.len);

    printf("+");
    for (int i = 0; i < MAP_W; i++) {
        putchar('-');
    }
    printf("+\n");

    const char *row = g->cell;
    for (int y = 0; y < MAP_H; y++) {
        putchar('|');
        fwrite(row, 1, MAP_W, stdout);
        putchar('|');
        putchar('\n');
        row += MAP_W;
    }

    // bottom
    putchar('+');
    for (int i = 0; i < MAP_W; i++) {
        putchar('-');
    }
    printf("+\n");

    if (!g->alive) {
        printf("game over, score=%d\n", g->score);
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    Game game;
    game_init(&game);

    printf("press Enter to start, wasd/hjkl move, q quit\n");
    fflush(stdout);

    // 吃掉起始提示后的一整行，避免残留字符被当成移动指令
    int ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    while (game.alive) {
        paint(&game);
        draw(&game);
        printf("> ");
        fflush(stdout);

        ch = getchar();
        if (ch == EOF) {
            break;
        }
        if (ch == '\n') {
            game_tick(&game);
            continue;
        }

        int rest;
        do {
            rest = getchar();
        } while (rest != '\n' && rest != EOF);

        if (!handle_key(&game, ch)) {
            break;
        }
    }

    paint(&game);
    draw(&game);
    game_free(&game);

    return 0;
}
