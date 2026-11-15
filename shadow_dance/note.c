#include "note.h"

#include "lane.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 和 Java 常量相同。长按音符的图高 229，普通音符的图高 64。 */
#define NORMAL_START_Y 100
#define HOLD_START_Y 24
#define START_SPEED 2
#define NORMAL_HEIGHT 64
#define HOLD_HEIGHT 229
#define HOLD_OFFSET 82
#define DOUBLE_SCORE_FRAMES 480
#define EFFECT_SCORE 15

void *xmalloc(size_t bytes) {
    void *p = malloc(bytes);
    if (p == NULL) {
        fprintf(stderr, "内存不足\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

static double absolute(double value) {
    return value < 0 ? -value : value;
}

static double normal_distance(const Note *note) {
    return absolute(note->pos.y - STATIONARY_NOTE_Y);
}

static double hold_distance(const Note *note) {
    double y = note->pressed ? note->pos.y - HOLD_OFFSET : note->pos.y + HOLD_OFFSET;
    return absolute(y - STATIONARY_NOTE_Y);
}

static int score_from_distance(double dist) {
    if (dist <= DIST_PERFECT) {
        return SCORE_PERFECT;
    }
    if (dist <= DIST_GOOD) {
        return SCORE_GOOD;
    }
    if (dist <= DIST_BAD) {
        return SCORE_BAD;
    }
    return SCORE_MISS;
}

static const char *message_from_distance(double dist) {
    if (dist <= DIST_PERFECT) {
        return "PERFECT";
    }
    if (dist <= DIST_GOOD) {
        return "GOOD";
    }
    if (dist <= DIST_BAD) {
        return "BAD";
    }
    return "MISS";
}

/* 普通音符和长按音符共用这几个函数。
   真正的距离通过 note->vt->get_distance 找回去：
   这就是 Java 里 this.getDistance() 的动态绑定。 */
static int shared_can(const Note *note) {
    return note->vt->get_distance(note) <= DIST_ACTIVATE;
}

static int shared_score(const Note *note) {
    return score_from_distance(note->vt->get_distance(note));
}

static const char *shared_message(const Note *note) {
    return message_from_distance(note->vt->get_distance(note));
}

static void base_activated(Note *note, ScoreBoard *board, Note **notes, int note_count) {
    (void)notes;
    (void)note_count;
    int points = note->vt->get_score(note);
    if (note->double_score_frames > 0) {
        points *= 2;
    }
    score_add(board, points, note->vt->get_message(note));
}

static int special_can(const Note *note) {
    return normal_distance(note) <= DIST_SPECIAL;
}

static int special_score(const Note *note) {
    if (note->effect == EFFECT_SPEEDUP || note->effect == EFFECT_SLOWDOWN) {
        return EFFECT_SCORE;
    }
    return 0;
}

static const char *special_message(const Note *note) {
    switch (note->effect) {
    case EFFECT_2X:
        return "Double Score";
    case EFFECT_SPEEDUP:
        return "Speed Up";
    case EFFECT_SLOWDOWN:
        return "Slow Down";
    case EFFECT_BOMB:
        return "Lane Clear";
    default:
        return "";
    }
}

static void special_activated(Note *note, ScoreBoard *board, Note **notes, int note_count) {
    NoteEffect effect = note->effect;
    Lane *lane = note->lane;
    base_activated(note, board, notes, note_count);

    if (effect == EFFECT_BOMB) {
        /* clear 会 free 掉这条车道上的全部音符，包括 note 自己。
           所以 effect 和 lane 必须事先拷出来，函数到这里就返回。 */
        note_list_clear(&lane->notes);
        return;
    }
    if (notes == NULL) {
        return;
    }
    for (int i = 0; i < note_count; i++) {
        if (effect == EFFECT_2X) {
            notes[i]->double_score_frames = DOUBLE_SCORE_FRAMES;
        } else if (effect == EFFECT_SPEEDUP) {
            notes[i]->speed++;
        } else if (effect == EFFECT_SLOWDOWN && notes[i]->speed > 1) {
            notes[i]->speed--;
        }
    }
}

/* 字段顺序要和 NoteVTable 的声明一致。 */
static const NoteVTable VT_NORMAL = {
    normal_distance,
    shared_can,
    shared_score,
    shared_message,
    base_activated
};

static const NoteVTable VT_HOLD = {
    hold_distance,
    shared_can,
    shared_score,
    shared_message,
    base_activated
};

static const NoteVTable VT_SPECIAL = {
    normal_distance,
    special_can,
    special_score,
    special_message,
    special_activated
};

static int same_word(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        char ca = *a;
        char cb = *b;
        if (ca >= 'A' && ca <= 'Z') {
            ca = (char)(ca - 'A' + 'a');
        }
        if (cb >= 'A' && cb <= 'Z') {
            cb = (char)(cb - 'A' + 'a');
        }
        if (ca != cb) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

Note *note_create(Lane *lane, const char *note_type, int frame) {
    if (lane == NULL || note_type == NULL) {
        return NULL;
    }

    const NoteVTable *vt = NULL;
    NoteKind kind = NOTE_NORMAL;
    NoteEffect effect = EFFECT_2X;
    int height = NORMAL_HEIGHT;
    int start_y = NORMAL_START_Y;
    char glyph = lane_glyph(lane->type);

    if (same_word(note_type, "Normal")) {
        vt = &VT_NORMAL;
        kind = NOTE_NORMAL;
    } else if (same_word(note_type, "Hold")) {
        vt = &VT_HOLD;
        kind = NOTE_HOLD;
        height = HOLD_HEIGHT;
        start_y = HOLD_START_Y;
    } else if (same_word(note_type, "DoubleScore")) {
        vt = &VT_SPECIAL;
        kind = NOTE_SPECIAL;
        effect = EFFECT_2X;
        glyph = '2';
    } else if (same_word(note_type, "SpeedUp")) {
        vt = &VT_SPECIAL;
        kind = NOTE_SPECIAL;
        effect = EFFECT_SPEEDUP;
        glyph = '+';
    } else if (same_word(note_type, "SlowDown")) {
        vt = &VT_SPECIAL;
        kind = NOTE_SPECIAL;
        effect = EFFECT_SLOWDOWN;
        glyph = '-';
    } else if (same_word(note_type, "Bomb")) {
        vt = &VT_SPECIAL;
        kind = NOTE_SPECIAL;
        effect = EFFECT_BOMB;
        glyph = 'B';
    } else {
        return NULL;
    }

    Note *note = xmalloc(sizeof *note);
    memset(note, 0, sizeof *note);
    note->vt = vt;
    note->kind = kind;
    note->effect = effect;
    note->lane = lane;
    note->start_frame = frame;
    note->speed = START_SPEED;
    note->height = height;
    note->pos.x = lane->pos.x;
    note->pos.y = start_y;
    note->glyph = glyph;
    return note;
}

int note_visible(const Note *note, int frames) {
    return frames >= note->start_frame;
}

int note_out_of_window(const Note *note) {
    return (note->pos.y - note->height / 2.0) > WINDOW_HEIGHT;
}

void note_move(Note *note) {
    note->pos.y += note->speed;
    if (note->double_score_frames > 0) {
        note->double_score_frames--;
    }
}

double note_mark_y(const Note *note) {
    if (note->kind != NOTE_HOLD) {
        return note->pos.y;
    }
    if (note->pressed) {
        return note->pos.y - HOLD_OFFSET;
    }
    return note->pos.y + HOLD_OFFSET;
}

void note_list_push(NoteList *list, Note *note) {
    if (list->len >= list->cap) {
        int cap = list->cap > 0 ? list->cap * 2 : 8;
        Note **grown = realloc(list->items, (size_t)cap * sizeof *grown);
        if (grown == NULL) {
            fprintf(stderr, "内存不足\n");
            exit(EXIT_FAILURE);
        }
        list->items = grown;
        list->cap = cap;
    }
    list->items[list->len++] = note;
}

void note_list_remove_at(NoteList *list, int index) {
    if (index < 0 || index >= list->len) {
        return;
    }
    free(list->items[index]);
    for (int i = index + 1; i < list->len; i++) {
        list->items[i - 1] = list->items[i];
    }
    list->len--;
}

void note_list_clear(NoteList *list) {
    for (int i = 0; i < list->len; i++) {
        free(list->items[i]);
        list->items[i] = NULL;
    }
    list->len = 0;
}

void note_list_free(NoteList *list) {
    note_list_clear(list);
    free(list->items);
    list->items = NULL;
    list->cap = 0;
}
