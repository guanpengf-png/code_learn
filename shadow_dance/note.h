#ifndef SHADOW_NOTE_H
#define SHADOW_NOTE_H

#include "game.h"
#include "score.h"

/* 对应 Note.java 以及它的三个子类。
   Java 用 extends 表达“是一种音符”。C 没有类，用 kind 区分种类，
   用函数指针表达每种音符不同的算法。 */

typedef enum {
    NOTE_NORMAL = 0,
    NOTE_HOLD,
    NOTE_SPECIAL
} NoteKind;

typedef enum {
    EFFECT_2X = 0,
    EFFECT_SPEEDUP,
    EFFECT_SLOWDOWN,
    EFFECT_BOMB
} NoteEffect;

/* 和判定线的纵向距离。画面上的变色用的也是这几个数。 */
#define DIST_PERFECT 15
#define DIST_GOOD 50
#define DIST_BAD 100
#define DIST_ACTIVATE 200
#define DIST_SPECIAL 50

typedef struct Note Note;
typedef struct Lane Lane;

typedef struct NoteVTable {
    double (*get_distance)(const Note *note);
    int (*can_activate)(const Note *note);
    int (*get_score)(const Note *note);
    const char *(*get_message)(const Note *note);
    void (*activated)(Note *note, ScoreBoard *board, Note **notes, int note_count);
} NoteVTable;

struct Note {
    const NoteVTable *vt;
    NoteKind kind;
    NoteEffect effect;
    Lane *lane;
    int start_frame;
    int double_score_frames;
    int speed;
    int height;
    int pressed;
    Position pos;
    char glyph;
};

/* 列表里存 Note*，不存 Note 本体。
   Java 的 ArrayList<Note> 存的也是引用，改 speed 会改到车道上的那一个。
   如果这里改成 Note items[]，推进去的是副本，加速和双倍分都会失效。 */
typedef struct {
    Note **items;
    int len;
    int cap;
} NoteList;

Note *note_create(Lane *lane, const char *note_type, int frame);
int note_visible(const Note *note, int frames);
int note_out_of_window(const Note *note);
void note_move(Note *note);
double note_mark_y(const Note *note);

void note_list_push(NoteList *list, Note *note);
void note_list_remove_at(NoteList *list, int index);
void note_list_clear(NoteList *list);
void note_list_free(NoteList *list);

#endif
