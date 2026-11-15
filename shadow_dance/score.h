#ifndef SHADOW_SCORE_H
#define SHADOW_SCORE_H

/* 对应 ScoreBoard.java。提示在屏幕上停留的帧数。 */
#define SCORE_MSG_FRAMES 30

typedef struct ScoreBoard {
    int total;
    int win_score;
    int msg_frames;
    char msg[64];
} ScoreBoard;

void score_init(ScoreBoard *board);
void score_set_win(ScoreBoard *board, int win_score);
void score_add(ScoreBoard *board, int points, const char *message);
void score_tick(ScoreBoard *board);
int score_is_win(const ScoreBoard *board);

#endif
