#include "lane.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char lane_glyph(LaneType type) {
    switch (type) {
    case LANE_LEFT:
        return '<';
    case LANE_RIGHT:
        return '>';
    case LANE_UP:
        return '^';
    case LANE_DOWN:
        return 'v';
    case LANE_SPECIAL:
        return '*';
    default:
        return '?';
    }
}

static void trim_line(char *s) {
    size_t n = strlen(s);
    while (n > 0) {
        char c = s[n - 1];
        if (c != '\n' && c != '\r' && c != ' ' && c != '\t') {
            break;
        }
        s[--n] = '\0';
    }
}

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

static LaneType parse_lane_type(const char *s) {
    if (same_word(s, "left")) {
        return LANE_LEFT;
    }
    if (same_word(s, "right")) {
        return LANE_RIGHT;
    }
    if (same_word(s, "up")) {
        return LANE_UP;
    }
    if (same_word(s, "down")) {
        return LANE_DOWN;
    }
    if (same_word(s, "special")) {
        return LANE_SPECIAL;
    }
    return LANE_NONE;
}

static Lane *find_lane(Lane *lanes, int count, LaneType type) {
    for (int i = 0; i < count; i++) {
        if (lanes[i].type == type) {
            return &lanes[i];
        }
    }
    return NULL;
}

/* qsort 的比较函数拿到的是“指向数组元素的指针”。
   数组元素本身是 Note*，所以这里要解两层。 */
static int cmp_note_frame(const void *pa, const void *pb) {
    const Note *a = *(const Note *const *)pa;
    const Note *b = *(const Note *const *)pb;
    if (a->start_frame < b->start_frame) {
        return -1;
    }
    if (a->start_frame > b->start_frame) {
        return 1;
    }
    return 0;
}

static int load_fail(FILE *fp, Lane *lanes, int *count) {
    lanes_free(lanes, *count);
    *count = 0;
    fclose(fp);
    return -1;
}

int lanes_load(Lane *lanes, int *count, int max_lanes, const char *path) {
    *count = 0;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof line, fp) != NULL) {
        trim_line(line);
        if (line[0] == '\0') {
            continue;
        }

        char field0[32];
        char field1[32];
        int value = 0;
        if (sscanf(line, "%31[^,],%31[^,],%d", field0, field1, &value) != 3) {
            continue;
        }

        if (same_word(field0, "Lane")) {
            if (*count >= max_lanes) {
                return load_fail(fp, lanes, count);
            }
            LaneType type = parse_lane_type(field1);
            if (type == LANE_NONE) {
                return load_fail(fp, lanes, count);
            }
            Lane *lane = &lanes[*count];
            memset(lane, 0, sizeof *lane);
            lane->type = type;
            lane->pos.x = value;
            lane->pos.y = LANE_Y;
            (*count)++;
            continue;
        }

        /* Java 的 readLanesFromFile 先把一行读出来再判断。
           读到第一条音符时，这行已经被 Scanner 拿走了，于是每个谱面的
           第一条音符会丢。这里整行判断，音符不会丢。 */
        LaneType type = parse_lane_type(field0);
        Lane *lane = find_lane(lanes, *count, type);
        if (lane == NULL) {
            return load_fail(fp, lanes, count);
        }
        Note *note = note_create(lane, field1, value);
        if (note == NULL) {
            return load_fail(fp, lanes, count);
        }
        note_list_push(&lane->notes, note);
    }

    fclose(fp);
    for (int i = 0; i < *count; i++) {
        if (lanes[i].notes.len > 1) {
            qsort(lanes[i].notes.items, (size_t)lanes[i].notes.len, sizeof(Note *), cmp_note_frame);
        }
    }
    return 0;
}

void lanes_free(Lane *lanes, int count) {
    for (int i = 0; i < count; i++) {
        note_list_free(&lanes[i].notes);
    }
}

void lane_remove_note(Lane *lane, Note *note) {
    if (lane == NULL || note == NULL) {
        return;
    }
    for (int i = 0; i < lane->notes.len; i++) {
        if (lane->notes.items[i] == note) {
            note_list_remove_at(&lane->notes, i);
            return;
        }
    }
}
