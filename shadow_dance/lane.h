#ifndef SHADOW_LANE_H
#define SHADOW_LANE_H

#include "note.h"

#define MAX_LANES 8

/* 车道放在定长数组里，地址不会因为扩容改变。
   音符里的 Lane* 因此一直有效。音符本身会增删，所以单独 malloc。 */
struct Lane {
    LaneType type;
    Position pos;
    NoteList notes;
};

int lanes_load(Lane *lanes, int *count, int max_lanes, const char *path);
void lanes_free(Lane *lanes, int count);
void lane_remove_note(Lane *lane, Note *note);
char lane_glyph(LaneType type);

#endif
