/* Shadow Dance 的 C 语言版。
 *
 * 原项目是 Java，用 Bagel 画图片。这里改成终端里的字符，判定规则保持一致：
 * 音符从上往下掉，到达判定线时按对应的键。
 *
 * 建议顺着这个顺序读，每一份对应原来的一类：
 *   game.h    常量和坐标。Java 里那些 static final。
 *   score.c   ScoreBoard。最简单的结构体。
 *   note.c    Note / NormalNote / HoldNote / SpecialNote。
 *             Java 的抽象方法，这里写成结构体里的函数指针。
 *   lane.c    Lane，以及读 csv。练 fopen、sscanf、realloc。
 *   enemy.c   Enemy、Guardian、Projectile。
 *   main.c    游戏循环、键盘和画面，对应 ShadowDance.java。
 *
 * 在本目录编译运行：
 *   make
 *   ./shadow_dance
 *   make test
 *
 * 操作：1 / 2 / 3 选关。方向键或 WASD 打四条轨，空格打特殊轨。
 * 长按音符敲两下（终端读不到松手，所以第二次敲当作松键）。
 * 第 3 关按 F 射箭，对应 Java 的左 Shift。Q 或 Esc 退出。
 * 谱面默认是 res/test1.csv 到 test3.csv。完整谱在 res/level1.csv 起。
 */

#include "enemy.h"
#include "lane.h"
#include "note.h"
#include "score.h"

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <termios.h>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#define FRAME_NS 16666667L
#define MAX_NOTE_PTRS 256

enum {
    COL_DEFAULT = 0,
    COL_DIM,
    COL_LEFT,
    COL_RIGHT,
    COL_UP,
    COL_DOWN,
    COL_SPECIAL,
    COL_TEXT,
    COL_GOOD,
    COL_BAD,
    COL_PERFECT,
    COL_MISS,
    COL_ENEMY,
    COL_GUARD,
    COL_TITLE
};

typedef struct {
    int rows;
    int cols;
    char *ch;
    unsigned char *color;
} Screen;

typedef struct {
    int left, right, up, down, space;
    int n1, n2, n3;
    int fire;
    int quit;
} Keys;

typedef struct {
    Lane lanes[MAX_LANES];
    int lane_count;
    EnemyList enemies;
    ProjectileList shots;
    Guardian guardian;
    int level;
    int started;
    int finished;
    int frames;
    ScoreBoard score;
    char status[160];
} Game;

static const char *const LEVEL_FILE[] = {
    NULL,
    "res/test1.csv",
    "res/test2.csv",
    "res/test3.csv"
};

static const int LEVEL_WIN[] = {0, 150, 400, 350};

static struct termios g_orig;
static int g_raw = 0;
static volatile sig_atomic_t g_stop = 0;
static char g_hold[8];
static int g_hold_len = 0;

static void restore_term(void) {
    if (!g_raw) {
        return;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &g_orig);
    fputs("\033[?25h\033[0m\033[?1049l", stdout);
    fflush(stdout);
    g_raw = 0;
}

static void on_signal(int sig) {
    (void)sig;
    g_stop = 1;
}

static void goto_exe_dir(void) {
    char path[PATH_MAX];
    char resolved[PATH_MAX];
#if defined(__APPLE__)
    uint32_t size = (uint32_t)sizeof path;
    if (_NSGetExecutablePath(path, &size) != 0) {
        return;
    }
#elif defined(__linux__)
    ssize_t n = readlink("/proc/self/exe", path, sizeof path - 1);
    if (n < 0) {
        return;
    }
    path[n] = '\0';
#else
    return;
#endif
    if (realpath(path, resolved) == NULL) {
        return;
    }
    char *slash = strrchr(resolved, '/');
    if (slash == NULL) {
        return;
    }
    *slash = '\0';
    (void)chdir(resolved);
}

static int enter_raw(void) {
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)) {
        fprintf(stderr, "请在终端里运行 ./shadow_dance\n");
        return 0;
    }
    if (tcgetattr(STDIN_FILENO, &g_orig) != 0) {
        return 0;
    }
    struct termios raw = g_orig;
    raw.c_lflag &= ~(tcflag_t)(ICANON | ECHO);
    raw.c_iflag &= ~(tcflag_t)(IXON | ICRNL);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) != 0) {
        return 0;
    }
    g_raw = 1;
    atexit(restore_term);
    fputs("\033[?1049h\033[?25l", stdout);
    fflush(stdout);

    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = on_signal;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    return 1;
}

static int screen_fit(Screen *s) {
    struct winsize ws;
    int rows = 24;
    int cols = 80;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        if (ws.ws_row > 0) {
            rows = ws.ws_row;
        }
        if (ws.ws_col > 0) {
            cols = ws.ws_col;
        }
    }
    if (s->ch != NULL && s->rows == rows && s->cols == cols) {
        return 1;
    }
    free(s->ch);
    free(s->color);
    s->rows = rows;
    s->cols = cols;
    s->ch = xmalloc((size_t)rows * (size_t)cols);
    s->color = xmalloc((size_t)rows * (size_t)cols);
    return 1;
}

static void screen_free(Screen *s) {
    free(s->ch);
    free(s->color);
    s->ch = NULL;
    s->color = NULL;
}

static void screen_clear(Screen *s) {
    size_t n = (size_t)s->rows * (size_t)s->cols;
    memset(s->ch, ' ', n);
    memset(s->color, 0, n);
}

static void putc_at(Screen *s, int x, int y, char ch, int color) {
    if (x < 0 || y < 0 || x >= s->cols || y >= s->rows) {
        return;
    }
    int i = y * s->cols + x;
    s->ch[i] = ch;
    s->color[i] = (unsigned char)color;
}

static void text_at(Screen *s, int x, int y, const char *text, int color) {
    for (int i = 0; text[i] != '\0'; i++) {
        putc_at(s, x + i, y, text[i], color);
    }
}

static const char *ansi(int color) {
    switch (color) {
    case COL_DIM:
        return "\033[2m";
    case COL_LEFT:
        return "\033[36m";
    case COL_RIGHT:
        return "\033[33m";
    case COL_UP:
        return "\033[32m";
    case COL_DOWN:
        return "\033[35m";
    case COL_SPECIAL:
        return "\033[31m";
    case COL_TEXT:
        return "\033[37m";
    case COL_GOOD:
        return "\033[1;33m";
    case COL_BAD:
        return "\033[1;35m";
    case COL_PERFECT:
        return "\033[1;97;42m";
    case COL_MISS:
        return "\033[1;31m";
    case COL_ENEMY:
        return "\033[1;31m";
    case COL_GUARD:
        return "\033[1;32m";
    case COL_TITLE:
        return "\033[1;37m";
    default:
        return "\033[0m";
    }
}

static void screen_present(const Screen *s) {
    fputs("\033[H", stdout);
    int current = -1;
    for (int r = 0; r < s->rows; r++) {
        printf("\033[%d;1H", r + 1);
        current = -1;
        int limit = s->cols;
        if (r == s->rows - 1 && limit > 0) {
            limit--;
        }
        for (int c = 0; c < limit; c++) {
            int i = r * s->cols + c;
            int color = s->color[i];
            if (color != current) {
                fputs(ansi(color), stdout);
                current = color;
            }
            fputc(s->ch[i], stdout);
        }
    }
    fputs("\033[0m", stdout);
}

static int display_width(const char *s) {
    int width = 0;
    const unsigned char *p = (const unsigned char *)s;
    while (*p != '\0') {
        if (*p < 0x80) {
            width += 1;
            p += 1;
        } else if ((*p & 0xE0) == 0xC0 && p[1] != '\0') {
            width += 2;
            p += 2;
        } else if ((*p & 0xF0) == 0xE0 && p[1] != '\0' && p[2] != '\0') {
            width += 2;
            p += 3;
        } else if ((*p & 0xF8) == 0xF0 && p[1] != '\0' && p[2] != '\0' && p[3] != '\0') {
            width += 2;
            p += 4;
        } else {
            width += 1;
            p += 1;
        }
    }
    return width;
}

static void line_center(int cols, int rows, int row, const char *text, const char *color) {
    if (row < 1 || row > rows || cols < 2) {
        return;
    }
    int width = display_width(text);
    /* 写满最后一列时，终端会换行，整屏往上滚一格。 */
    if (width > cols - 1) {
        return;
    }
    int pad = (cols - 1 - width) / 2;
    printf("\033[%d;1H\033[K", row);
    printf("\033[%d;%dH%s%s\033[0m", row, pad + 1, color, text);
}

static void clear_rows(int rows) {
    for (int r = 1; r <= rows; r++) {
        printf("\033[%d;1H\033[K", r);
    }
}

static void input_poll(Keys *keys) {
    memset(keys, 0, sizeof *keys);
    char buf[128];
    char data[160];
    int len = 0;
    if (g_hold_len > 0) {
        memcpy(data, g_hold, (size_t)g_hold_len);
        len = g_hold_len;
        g_hold_len = 0;
    }

    int got = 0;
    for (;;) {
        ssize_t n = read(STDIN_FILENO, buf, sizeof buf);
        if (n < 0) {
            if (errno == EINTR) {
                if (g_stop) {
                    break;
                }
                continue;
            }
            break;
        }
        if (n == 0) {
            break;
        }
        got = 1;
        if (len + (int)n > (int)sizeof data) {
            n = (int)sizeof data - len;
        }
        if (n <= 0) {
            break;
        }
        memcpy(data + len, buf, (size_t)n);
        len += (int)n;
    }

    if (!got && len > 0 && data[0] == '\033') {
        keys->quit = 1;
        return;
    }

    int i = 0;
    while (i < len) {
        unsigned char c = (unsigned char)data[i];
        if (c == '\033') {
            if (i + 1 >= len) {
                break;
            }
            if (data[i + 1] == '[' || data[i + 1] == 'O') {
                if (i + 2 >= len) {
                    break;
                }
                char dir = data[i + 2];
                if (dir == 'A') {
                    keys->up = 1;
                } else if (dir == 'B') {
                    keys->down = 1;
                } else if (dir == 'C') {
                    keys->right = 1;
                } else if (dir == 'D') {
                    keys->left = 1;
                } else {
                    i += 1;
                    continue;
                }
                i += 3;
                continue;
            }
            keys->quit = 1;
            i += 1;
            continue;
        }
        if (c == 'q' || c == 'Q') {
            keys->quit = 1;
        } else if (c == ' ') {
            keys->space = 1;
        } else if (c == '1') {
            keys->n1 = 1;
        } else if (c == '2') {
            keys->n2 = 1;
        } else if (c == '3') {
            keys->n3 = 1;
        } else if (c == 'f' || c == 'F') {
            keys->fire = 1;
        } else if (c == 'a' || c == 'A') {
            keys->left = 1;
        } else if (c == 'd' || c == 'D') {
            keys->right = 1;
        } else if (c == 'w' || c == 'W') {
            keys->up = 1;
        } else if (c == 's' || c == 'S') {
            keys->down = 1;
        }
        i += 1;
    }

    if (i < len) {
        g_hold_len = len - i;
        if (g_hold_len > (int)sizeof g_hold) {
            g_hold_len = (int)sizeof g_hold;
        }
        memcpy(g_hold, data + i, (size_t)g_hold_len);
    }
}

static void game_clear(Game *g) {
    lanes_free(g->lanes, g->lane_count);
    g->lane_count = 0;
    g->enemies.len = 0;
    g->shots.len = 0;
    g->started = 0;
    g->finished = 0;
    g->frames = 0;
    g->level = 0;
    score_init(&g->score);
    g->status[0] = '\0';
}

static int game_start(Game *g, int level) {
    game_clear(g);
    if (level < 1 || level > 3) {
        return 0;
    }
    int count = 0;
    if (lanes_load(g->lanes, &count, MAX_LANES, LEVEL_FILE[level]) != 0) {
        snprintf(g->status, sizeof g->status, "打不开 %s", LEVEL_FILE[level]);
        return 0;
    }
    g->lane_count = count;
    g->level = level;
    g->started = 1;
    g->frames = 0;
    score_set_win(&g->score, LEVEL_WIN[level]);
    g->guardian.pos.x = GUARDIAN_X;
    g->guardian.pos.y = GUARDIAN_Y;
    return 1;
}

static int collect_notes(const Game *g, Note **out, int max_count) {
    int n = 0;
    for (int i = 0; i < g->lane_count; i++) {
        for (int j = 0; j < g->lanes[i].notes.len; j++) {
            if (n >= max_count) {
                return n;
            }
            out[n++] = g->lanes[i].notes.items[j];
        }
    }
    return n;
}

static LaneType key_lane(const Keys *keys) {
    if (keys->left) {
        return LANE_LEFT;
    }
    if (keys->right) {
        return LANE_RIGHT;
    }
    if (keys->up) {
        return LANE_UP;
    }
    if (keys->down) {
        return LANE_DOWN;
    }
    if (keys->space) {
        return LANE_SPECIAL;
    }
    return LANE_NONE;
}

static Lane *find_lane(Game *g, LaneType type) {
    for (int i = 0; i < g->lane_count; i++) {
        if (g->lanes[i].type == type) {
            return &g->lanes[i];
        }
    }
    return NULL;
}

static void handle_key(Game *g, LaneType pressed) {
    if (pressed == LANE_NONE) {
        return;
    }
    Lane *lane = find_lane(g, pressed);
    if (lane == NULL || lane->notes.len == 0) {
        return;
    }

    /* 只看这条车道上最早的那一个，和 Java 的 iterator.next() 一样。 */
    Note *note = lane->notes.items[0];
    if (!note_visible(note, g->frames)) {
        return;
    }

    if (note->kind == NOTE_HOLD && note->pressed) {
        note->vt->activated(note, &g->score, NULL, 0);
        note_list_remove_at(&lane->notes, 0);
        return;
    }
    if (!note->vt->can_activate(note)) {
        return;
    }

    Note *all[MAX_NOTE_PTRS];
    int count = collect_notes(g, all, MAX_NOTE_PTRS);
    NoteKind kind = note->kind;
    NoteEffect effect = note->effect;
    note->vt->activated(note, &g->score, all, count);

    if (kind == NOTE_SPECIAL && effect == EFFECT_BOMB) {
        return;
    }
    if (kind == NOTE_HOLD) {
        note->pressed = 1;
        return;
    }
    note_list_remove_at(&lane->notes, 0);
}

static void advance_notes(Game *g) {
    for (int li = 0; li < g->lane_count; li++) {
        NoteList *list = &g->lanes[li].notes;
        for (int i = 0; i < list->len;) {
            Note *note = list->items[i];
            if (!note_visible(note, g->frames)) {
                break;
            }
            note_move(note);
            if (note_out_of_window(note)) {
                /* 掉出屏幕固定扣 5 分，不受双倍分影响。特殊音符不扣分。 */
                if (note->kind == NOTE_NORMAL || note->kind == NOTE_HOLD) {
                    score_add(&g->score, SCORE_MISS, "MISS");
                }
                note_list_remove_at(list, i);
            } else {
                i++;
            }
        }
    }
}

static void update_level3(Game *g, const Keys *keys) {
    if (g->frames % ENEMY_INTERVAL == 0) {
        enemy_spawn(&g->enemies);
    }
    if (keys->fire) {
        guardian_fire(&g->guardian, &g->enemies, &g->shots);
    }

    for (int i = 0; i < g->shots.len;) {
        if (projectile_out(&g->shots.items[i])) {
            g->shots.items[i] = g->shots.items[g->shots.len - 1];
            g->shots.len--;
            continue;
        }
        i++;
    }
    for (int i = 0; i < g->shots.len; i++) {
        projectile_move(&g->shots.items[i]);
        for (int e = 0; e < g->enemies.len;) {
            if (projectile_hits(&g->shots.items[i], &g->enemies.items[e])) {
                g->enemies.items[e] = g->enemies.items[g->enemies.len - 1];
                g->enemies.len--;
            } else {
                e++;
            }
        }
    }

    Note *visible[MAX_NOTE_PTRS];
    int visible_count = 0;
    for (int li = 0; li < g->lane_count; li++) {
        NoteList *list = &g->lanes[li].notes;
        for (int n = 0; n < list->len; n++) {
            if (!note_visible(list->items[n], g->frames)) {
                break;
            }
            if (visible_count < MAX_NOTE_PTRS) {
                visible[visible_count++] = list->items[n];
            }
        }
    }

    for (int e = 0; e < g->enemies.len; e++) {
        enemy_move(&g->enemies.items[e]);
        for (int i = 0; i < visible_count;) {
            Note *note = visible[i];
            if (enemy_hits_note(&g->enemies.items[e], note)) {
                lane_remove_note(note->lane, note);
                visible[i] = visible[visible_count - 1];
                visible_count--;
            } else {
                i++;
            }
        }
    }
}

static void update_play(Game *g, const Keys *keys) {
    score_tick(&g->score);
    if (g->level == 3) {
        update_level3(g, keys);
    }
    handle_key(g, key_lane(keys));
    advance_notes(g);

    g->finished = 1;
    for (int i = 0; i < g->lane_count; i++) {
        if (g->lanes[i].notes.len > 0) {
            g->finished = 0;
            break;
        }
    }
    g->frames++;
}

static int col_from_x(const Screen *s, double x) {
    if (s->cols <= 1) {
        return 0;
    }
    int col = (int)(x / (double)WINDOW_WIDTH * (s->cols - 1));
    if (col < 0) {
        return 0;
    }
    if (col >= s->cols) {
        return s->cols - 1;
    }
    return col;
}

static int row_from_y(const Screen *s, double y) {
    int top = 1;
    int bot = s->rows - 2;
    if (bot < top) {
        return top;
    }
    return top + (int)(y / (double)WINDOW_HEIGHT * (bot - top));
}

static void put_world(Screen *s, double x, double y, char ch, int color) {
    if (y < 0 || y > WINDOW_HEIGHT) {
        return;
    }
    int row = row_from_y(s, y);
    if (row < 1 || row > s->rows - 2) {
        return;
    }
    putc_at(s, col_from_x(s, x), row, ch, color);
}

static int lane_color(LaneType type) {
    switch (type) {
    case LANE_LEFT:
        return COL_LEFT;
    case LANE_RIGHT:
        return COL_RIGHT;
    case LANE_UP:
        return COL_UP;
    case LANE_DOWN:
        return COL_DOWN;
    default:
        return COL_SPECIAL;
    }
}

static int mark_color(const Note *note) {
    double dist = note->vt->get_distance(note);
    int base = lane_color(note->lane->type);
    if (dist <= DIST_PERFECT) {
        return COL_PERFECT;
    }
    if (dist <= DIST_GOOD) {
        return COL_GOOD;
    }
    if (dist <= DIST_BAD) {
        return COL_BAD;
    }
    if (dist <= DIST_ACTIVATE && note->kind != NOTE_SPECIAL) {
        return COL_MISS;
    }
    return base;
}

static int message_color(const char *msg) {
    if (strcmp(msg, "PERFECT") == 0) {
        return COL_PERFECT;
    }
    if (strcmp(msg, "GOOD") == 0) {
        return COL_GOOD;
    }
    if (strcmp(msg, "BAD") == 0) {
        return COL_BAD;
    }
    if (strcmp(msg, "MISS") == 0) {
        return COL_MISS;
    }
    return COL_TITLE;
}

static void draw_note(Screen *s, const Note *note) {
    int color = lane_color(note->lane->type);
    int marked = mark_color(note);
    if (note->kind == NOTE_HOLD) {
        double y0 = note->pos.y - note->height / 2.0;
        double y1 = note->pos.y + note->height / 2.0;
        int span = s->rows > 3 ? s->rows - 3 : 1;
        double step = (double)WINDOW_HEIGHT / (double)span;
        if (step < 1) {
            step = 1;
        }
        for (double y = y0; y <= y1; y += step) {
            put_world(s, note->pos.x, y, '|', color);
        }
        put_world(s, note->pos.x, note_mark_y(note), note->glyph, marked);
        return;
    }
    put_world(s, note->pos.x, note->pos.y, note->glyph, marked);
}

static void draw_play(Screen *s, const Game *g) {
    screen_clear(s);
    int judge = row_from_y(s, STATIONARY_NOTE_Y);
    for (int c = 0; c < s->cols; c++) {
        putc_at(s, c, judge, '-', COL_DIM);
    }
    for (int i = 0; i < g->lane_count; i++) {
        const Lane *lane = &g->lanes[i];
        int col = col_from_x(s, lane->pos.x);
        int color = lane_color(lane->type);
        for (int r = 1; r <= s->rows - 2; r++) {
            putc_at(s, col, r, '|', COL_DIM);
        }
        putc_at(s, col, judge, lane_glyph(lane->type), color);
    }

    for (int i = 0; i < g->lane_count; i++) {
        const NoteList *list = &g->lanes[i].notes;
        for (int n = list->len - 1; n >= 0; n--) {
            const Note *note = list->items[n];
            if (note_visible(note, g->frames)) {
                draw_note(s, note);
            }
        }
    }
    for (int i = 0; i < g->enemies.len; i++) {
        put_world(s, g->enemies.items[i].pos.x, g->enemies.items[i].pos.y, 'E', COL_ENEMY);
    }
    for (int i = 0; i < g->shots.len; i++) {
        put_world(s, g->shots.items[i].pos.x, g->shots.items[i].pos.y, '*', COL_TITLE);
    }
    if (g->level == 3) {
        put_world(s, g->guardian.pos.x, g->guardian.pos.y, 'G', COL_GUARD);
    }

    char hud[64];
    snprintf(hud, sizeof hud, "SCORE %d / %d", g->score.total, g->score.win_score);
    text_at(s, 1, 0, hud, COL_TEXT);
    snprintf(hud, sizeof hud, "LV%d", g->level);
    text_at(s, s->cols - (int)strlen(hud) - 1, 0, hud, COL_TEXT);
    if (g->score.msg_frames > 0) {
        int y = s->rows / 2;
        int x = (s->cols - (int)strlen(g->score.msg)) / 2;
        text_at(s, x, y, g->score.msg, message_color(g->score.msg));
    }
    screen_present(s);

    const char *help = "ARROWS/WASD  SPACE  F  Q";
    if (s->cols >= 74) {
        help = "方向键/WASD 敲音符  空格特殊轨  长按敲两下  绿底=PERFECT  F射箭  Q退出";
    } else if (s->cols >= 44) {
        help = "方向键敲音符  空格特殊轨  F射箭  Q退出";
    }
    line_center(s->cols, s->rows, s->rows, help, "\033[2m");
    fflush(stdout);
}

static void draw_menu(const Screen *s, const Game *g) {
    clear_rows(s->rows);
    int mid = s->rows / 2;
    line_center(s->cols, s->rows, mid - 6, "SHADOW DANCE", "\033[1;37m");
    line_center(s->cols, s->rows, mid - 4, "用数字键选关", "\033[37m");
    line_center(s->cols, s->rows, mid - 2, "1       2       3", "\033[1;37m");
    line_center(s->cols, s->rows, mid, "方向键或 WASD 敲击音符，空格敲特殊轨", "\033[37m");
    line_center(s->cols, s->rows, mid + 1, "长按音符敲两下：对准头部一下，对准尾部再一下", "\033[37m");
    line_center(s->cols, s->rows, mid + 2, "字符变成绿底时按下，就是 PERFECT", "\033[37m");
    line_center(s->cols, s->rows, mid + 3, "第 3 关按 F 射箭，消灭抢走音符的敌人", "\033[37m");
    line_center(s->cols, s->rows, mid + 5, "Q 或 Esc 退出", "\033[2m");
    if (g->status[0] != '\0') {
        line_center(s->cols, s->rows, mid + 7, g->status, "\033[1;31m");
    }
    fflush(stdout);
}

static void draw_end(const Screen *s, const Game *g) {
    clear_rows(s->rows);
    int mid = s->rows / 2;
    const char *title = score_is_win(&g->score) ? "CLEAR!" : "TRY AGAIN";
    const char *color = score_is_win(&g->score) ? "\033[1;32m" : "\033[1;31m";
    char line[64];
    snprintf(line, sizeof line, "SCORE %d / %d", g->score.total, g->score.win_score);
    line_center(s->cols, s->rows, mid - 1, title, color);
    line_center(s->cols, s->rows, mid + 1, line, "\033[1;37m");
    line_center(s->cols, s->rows, mid + 3, "PRESS SPACE TO RETURN TO LEVEL SELECTION", "\033[37m");
    fflush(stdout);
}

static void sleep_frame(struct timespec *next) {
    next->tv_nsec += FRAME_NS;
    if (next->tv_nsec >= 1000000000L) {
        next->tv_sec++;
        next->tv_nsec -= 1000000000L;
    }
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    if (now.tv_sec > next->tv_sec || (now.tv_sec == next->tv_sec && now.tv_nsec > next->tv_nsec)) {
        *next = now;
        return;
    }
    struct timespec req;
    req.tv_sec = next->tv_sec - now.tv_sec;
    req.tv_nsec = next->tv_nsec - now.tv_nsec;
    if (req.tv_nsec < 0) {
        req.tv_sec--;
        req.tv_nsec += 1000000000L;
    }
    nanosleep(&req, NULL);
}

static int g_fail = 0;

static void expect_int(const char *name, int got, int want) {
    if (got != want) {
        fprintf(stderr, "不对 %s：得到 %d，应该是 %d\n", name, got, want);
        g_fail++;
    }
}

static void expect_true(const char *name, int cond) {
    if (!cond) {
        fprintf(stderr, "不对 %s\n", name);
        g_fail++;
    }
}

static Lane *lane_of(Lane *lanes, int count, LaneType type) {
    for (int i = 0; i < count; i++) {
        if (lanes[i].type == type) {
            return &lanes[i];
        }
    }
    return NULL;
}

static int count_notes(const Lane *lanes, int count) {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += lanes[i].notes.len;
    }
    return total;
}

static int run_tests(void) {
    double dist = position_distance((Position){0, 0}, (Position){3, 4});
    expect_true("距离 3-4-5", dist > 4.999 && dist < 5.001);

    Lane lane;
    memset(&lane, 0, sizeof lane);
    lane.type = LANE_UP;
    lane.pos.x = 432;
    lane.pos.y = LANE_Y;

    Note *normal = note_create(&lane, "Normal", 100);
    expect_true("能创建普通音符", normal != NULL);
    if (normal == NULL) {
        return 1;
    }
    expect_int("普通音符初速", normal->speed, 2);
    normal->pos.y = STATIONARY_NOTE_Y;
    expect_int("距离 0 可打", normal->vt->can_activate(normal), 1);
    expect_int("距离 0 分数", normal->vt->get_score(normal), SCORE_PERFECT);
    expect_true("距离 0 提示", strcmp(normal->vt->get_message(normal), "PERFECT") == 0);

    normal->pos.y = STATIONARY_NOTE_Y + DIST_PERFECT;
    expect_int("15 仍是 PERFECT", normal->vt->get_score(normal), SCORE_PERFECT);
    normal->pos.y = STATIONARY_NOTE_Y + DIST_PERFECT + 1;
    expect_int("16 是 GOOD", normal->vt->get_score(normal), SCORE_GOOD);
    normal->pos.y = STATIONARY_NOTE_Y + DIST_GOOD;
    expect_int("50 是 GOOD", normal->vt->get_score(normal), SCORE_GOOD);
    normal->pos.y = STATIONARY_NOTE_Y + DIST_BAD;
    expect_int("100 是 BAD", normal->vt->get_score(normal), SCORE_BAD);
    normal->pos.y = STATIONARY_NOTE_Y + DIST_BAD + 1;
    expect_int("101 是 MISS", normal->vt->get_score(normal), SCORE_MISS);
    expect_int("101 仍能按下", normal->vt->can_activate(normal), 1);
    normal->pos.y = STATIONARY_NOTE_Y + DIST_ACTIVATE + 1;
    expect_int("201 按不中", normal->vt->can_activate(normal), 0);

    normal->pos.y = 800;
    expect_int("y=800 还在窗口内", note_out_of_window(normal), 0);
    normal->pos.y = 801;
    expect_int("y=801 出窗口", note_out_of_window(normal), 1);
    normal->pos.y = 100;
    normal->double_score_frames = 2;
    note_move(normal);
    expect_true("下落 2 像素", normal->pos.y > 101.9 && normal->pos.y < 102.1);
    expect_int("双倍帧递减", normal->double_score_frames, 1);
    free(normal);

    Note *hold = note_create(&lane, "Hold", 0);
    expect_true("能创建长按", hold != NULL);
    if (hold != NULL) {
        hold->pos.y = STATIONARY_NOTE_Y - 82;
        expect_int("长按头部距离", (int)(hold->vt->get_distance(hold) + 0.5), 0);
        hold->pressed = 1;
        expect_int("松手后改判尾部", (int)(hold->vt->get_distance(hold) + 0.5), 164);
        free(hold);
    }

    ScoreBoard board;
    score_init(&board);
    Note *speed = note_create(&lane, "SpeedUp", 0);
    Note *later = note_create(&lane, "Normal", 500);
    expect_true("速度音符", speed != NULL && later != NULL);
    if (speed != NULL && later != NULL) {
        note_list_push(&lane.notes, speed);
        note_list_push(&lane.notes, later);
        speed->pos.y = STATIONARY_NOTE_Y;
        Note *all[2] = {speed, later};
        speed->vt->activated(speed, &board, all, 2);
        expect_int("加速加 15 分", board.total, 15);
        expect_true("加速提示", strcmp(board.msg, "Speed Up") == 0);
        expect_int("还没出场的音符也会加速", later->speed, 3);
        expect_int("50 以内才能打特殊音符", speed->vt->can_activate(speed), 1);
        speed->pos.y = STATIONARY_NOTE_Y + DIST_SPECIAL + 1;
        expect_int("超过 50 打不中特殊音符", speed->vt->can_activate(speed), 0);
    }
    note_list_free(&lane.notes);

    score_init(&board);
    Note *slow = note_create(&lane, "SlowDown", 0);
    Note *slow_target = note_create(&lane, "Normal", 10);
    if (slow != NULL && slow_target != NULL) {
        slow_target->speed = 1;
        Note *all[2] = {slow, slow_target};
        slow->pos.y = STATIONARY_NOTE_Y;
        slow->vt->activated(slow, &board, all, 2);
        expect_int("速度最低是 1", slow_target->speed, 1);
        free(slow);
        free(slow_target);
    }

    score_init(&board);
    Note *doubler = note_create(&lane, "DoubleScore", 0);
    Note *boosted = note_create(&lane, "Normal", 20);
    if (doubler != NULL && boosted != NULL) {
        doubler->pos.y = STATIONARY_NOTE_Y;
        Note *all[2] = {doubler, boosted};
        doubler->vt->activated(doubler, &board, all, 2);
        expect_int("双倍分本身不加分", board.total, 0);
        expect_int("双倍持续 480 帧", boosted->double_score_frames, 480);
        boosted->pos.y = STATIONARY_NOTE_Y;
        boosted->vt->activated(boosted, &board, NULL, 0);
        expect_int("双倍时 PERFECT 是 20", board.total, 20);
        free(doubler);
        free(boosted);
    }

    score_init(&board);
    memset(&lane, 0, sizeof lane);
    lane.type = LANE_RIGHT;
    lane.pos.x = 742;
    lane.pos.y = LANE_Y;
    Note *bomb = note_create(&lane, "Bomb", 0);
    Note *victim = note_create(&lane, "Normal", 30);
    if (bomb != NULL && victim != NULL) {
        note_list_push(&lane.notes, bomb);
        note_list_push(&lane.notes, victim);
        bomb->pos.y = STATIONARY_NOTE_Y;
        Note *all[2] = {bomb, victim};
        bomb->vt->activated(bomb, &board, all, 2);
        expect_int("炸弹清空整条车道", lane.notes.len, 0);
        expect_true("炸弹提示", strcmp(board.msg, "Lane Clear") == 0);
        note_list_free(&lane.notes);
    }

    expect_true("未知音符", note_create(&lane, "Nope", 0) == NULL);

    Lane chart[MAX_LANES];
    int count = 0;
    expect_int("缺失文件", lanes_load(chart, &count, MAX_LANES, "res/missing.csv"), -1);

    memset(chart, 0, sizeof chart);
    expect_int("读 test1", lanes_load(chart, &count, MAX_LANES, "res/test1.csv"), 0);
    expect_int("test1 四条轨", count, 4);
    expect_int("test1 十八条音符", count_notes(chart, count), 18);
    Lane *up = lane_of(chart, count, LANE_UP);
    expect_true("有上轨", up != NULL);
    if (up != NULL && up->notes.len > 0) {
        expect_int("第一条音符还在（Java 会丢掉它）", up->notes.items[0]->start_frame, 100);
        expect_int("上轨横坐标", (int)up->pos.x, 432);
        for (int i = 1; i < up->notes.len; i++) {
            expect_true("按出场帧排序",
                        up->notes.items[i]->start_frame >= up->notes.items[i - 1]->start_frame);
        }
    }
    lanes_free(chart, count);

    memset(chart, 0, sizeof chart);
    expect_int("读 test2", lanes_load(chart, &count, MAX_LANES, "res/test2.csv"), 0);
    expect_int("test2 音符数", count_notes(chart, count), 28);
    lanes_free(chart, count);

    memset(chart, 0, sizeof chart);
    expect_int("读 test3", lanes_load(chart, &count, MAX_LANES, "res/test3.csv"), 0);
    expect_int("test3 音符数", count_notes(chart, count), 21);
    lanes_free(chart, count);

    EnemyList enemies;
    memset(&enemies, 0, sizeof enemies);
    ProjectileList shots;
    memset(&shots, 0, sizeof shots);
    Guardian guardian;
    guardian.pos.x = GUARDIAN_X;
    guardian.pos.y = GUARDIAN_Y;
    expect_int("没有敌人就不射", guardian_fire(&guardian, &enemies, &shots), 0);

    enemies.len = 1;
    enemies.items[0].pos.x = 100;
    enemies.items[0].pos.y = GUARDIAN_Y;
    expect_int("朝最近的敌人射", guardian_fire(&guardian, &enemies, &shots), 1);
    expect_true("子弹朝左", shots.items[0].cos_v < 0);
    double before = shots.items[0].pos.x;
    projectile_move(&shots.items[0]);
    expect_true("子弹往左飞", shots.items[0].pos.x < before);

    memset(&lane, 0, sizeof lane);
    lane.type = LANE_LEFT;
    lane.pos.x = 100;
    lane.pos.y = LANE_Y;
    Note *prey = note_create(&lane, "Normal", 0);
    expect_true("能拿来做碰撞", prey != NULL);
    if (prey != NULL) {
        prey->pos.x = 100;
        prey->pos.y = 200;
        note_list_push(&lane.notes, prey);
        Enemy near_enemy;
        near_enemy.pos.x = 100;
        near_enemy.pos.y = 200;
        near_enemy.dir_left = 0;
        expect_int("贴在一起算撞上", enemy_hits_note(&near_enemy, prey), 1);
        lane_remove_note(prey->lane, prey);
        expect_int("撞掉之后从车道删掉", lane.notes.len, 0);
        note_list_free(&lane.notes);
    }

    Enemy enemy;
    enemy.pos.x = 99;
    enemy.pos.y = 200;
    enemy.dir_left = 1;
    enemy_move(&enemy);
    expect_true("碰到左边界就回头", enemy.pos.x >= ENEMY_X_MIN && !enemy.dir_left);

    if (g_fail == 0) {
        printf("全部通过：谱面、判定、双倍分、变速、炸弹、射箭\n");
        return 0;
    }
    fprintf(stderr, "失败 %d 项\n", g_fail);
    return 1;
}

int main(int argc, char **argv) {
    goto_exe_dir();
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        return run_tests();
    }
    if (!enter_raw()) {
        return 1;
    }
    srand((unsigned)time(NULL));

    Game game;
    memset(&game, 0, sizeof game);
    score_init(&game.score);

    Screen screen;
    memset(&screen, 0, sizeof screen);

    struct timespec next;
    clock_gettime(CLOCK_MONOTONIC, &next);
    int dirty = 1;
    int seen_rows = -1;
    int seen_cols = -1;

    while (!g_stop) {
        if (!screen_fit(&screen)) {
            break;
        }
        if (screen.rows != seen_rows || screen.cols != seen_cols) {
            dirty = 1;
            seen_rows = screen.rows;
            seen_cols = screen.cols;
        }
        Keys keys;
        input_poll(&keys);
        if (keys.quit) {
            break;
        }

        if (!game.started) {
            if (keys.n1) {
                dirty = 1;
                game_start(&game, 1);
            } else if (keys.n2) {
                dirty = 1;
                game_start(&game, 2);
            } else if (keys.n3) {
                dirty = 1;
                game_start(&game, 3);
            }
            if (!game.started && dirty) {
                draw_menu(&screen, &game);
                dirty = 0;
            }
        }

        if (game.started && game.finished) {
            if (keys.space) {
                game_clear(&game);
                dirty = 1;
            } else if (dirty) {
                draw_end(&screen, &game);
                dirty = 0;
            }
        } else if (game.started) {
            update_play(&game, &keys);
            if (game.finished) {
                draw_end(&screen, &game);
                dirty = 0;
            } else {
                draw_play(&screen, &game);
            }
        }

        sleep_frame(&next);
    }

    game_clear(&game);
    screen_free(&screen);
    return 0;
}
