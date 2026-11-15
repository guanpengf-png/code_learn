#ifndef SHADOW_GAME_H
#define SHADOW_GAME_H

#include <stddef.h>

/* 这些数字和 Java 版一致。Bagel 窗口是 1024x768，判定线在 y = 657。 */
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define STATIONARY_NOTE_Y 657
#define LANE_Y 384

#define SCORE_PERFECT 10
#define SCORE_GOOD 5
#define SCORE_BAD (-1)
#define SCORE_MISS (-5)

typedef enum {
    LANE_NONE = -1,
    LANE_LEFT = 0,
    LANE_RIGHT,
    LANE_UP,
    LANE_DOWN,
    LANE_SPECIAL
} LaneType;

/* Java 的 Position 类。这里按值传递会复制一份 x、y。
   坐标不大，只读的时候这样最省事。要改原来那份，就传 Position *。 */
typedef struct {
    double x;
    double y;
} Position;

double position_distance(Position a, Position b);

/* 分配失败就退出。定义在 note.c。 */
void *xmalloc(size_t bytes);

#endif
