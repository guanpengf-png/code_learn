#include "score.h"

#include <stdio.h>
#include <string.h>

void score_init(ScoreBoard *board) {
    memset(board, 0, sizeof *board);
}

void score_set_win(ScoreBoard *board, int win_score) {
    board->win_score = win_score;
}

void score_add(ScoreBoard *board, int points, const char *message) {
    board->total += points;
    board->msg_frames = SCORE_MSG_FRAMES;
    if (message == NULL) {
        message = "";
    }
    snprintf(board->msg, sizeof board->msg, "%s", message);
}

/* Java 把 draw() 写在车道循环里，有几条车道，提示就少停几倍时间。
   这里每帧只减一次，30 帧大约半秒。 */
void score_tick(ScoreBoard *board) {
    if (board->msg_frames > 0) {
        board->msg_frames--;
    }
}

int score_is_win(const ScoreBoard *board) {
    return board->total >= board->win_score;
}
