#ifndef SHADOW_ENEMY_H
#define SHADOW_ENEMY_H

#include "game.h"
#include "note.h"

/* 对应 Enemy.java、Guardian.java、Projectile.java。只在第 3 关出现。 */

#define ENEMY_INTERVAL 600
#define ENEMY_SPEED 1
#define ENEMY_X_MIN 100
#define ENEMY_X_MAX 900
#define ENEMY_Y_MIN 100
#define ENEMY_Y_MAX 500
#define ENEMY_NOTE_DIST 104
#define PROJECTILE_SPEED 6
#define PROJECTILE_HIT 62
#define GUARDIAN_X 800
#define GUARDIAN_Y 600
#define MAX_ENEMIES 64
#define MAX_PROJECTILES 32

typedef struct {
    Position pos;
    int dir_left;
} Enemy;

typedef struct {
    Position pos;
    double sin_v;
    double cos_v;
} Projectile;

typedef struct {
    Position pos;
} Guardian;

typedef struct {
    Enemy items[MAX_ENEMIES];
    int len;
} EnemyList;

typedef struct {
    Projectile items[MAX_PROJECTILES];
    int len;
} ProjectileList;

void enemy_spawn(EnemyList *list);
void enemy_move(Enemy *enemy);
int enemy_hits_note(const Enemy *enemy, const Note *note);

int guardian_fire(const Guardian *guardian, const EnemyList *enemies, ProjectileList *shots);
void projectile_move(Projectile *shot);
int projectile_out(const Projectile *shot);
int projectile_hits(const Projectile *shot, const Enemy *enemy);

#endif
