#include "enemy.h"

#include <math.h>
#include <stdlib.h>

double position_distance(Position a, Position b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void enemy_spawn(EnemyList *list) {
    if (list->len >= MAX_ENEMIES) {
        return;
    }
    /* Java 写成 MIN + nextInt(MAX + 1)，上界算大了，敌人可能生到轨道外面。
       这里用闭区间，横坐标 100..900，纵坐标 100..500。 */
    Enemy *enemy = &list->items[list->len];
    enemy->pos.x = ENEMY_X_MIN + rand() % (ENEMY_X_MAX - ENEMY_X_MIN + 1);
    enemy->pos.y = ENEMY_Y_MIN + rand() % (ENEMY_Y_MAX - ENEMY_Y_MIN + 1);
    enemy->dir_left = (rand() % 2) == 0;
    list->len++;
}

void enemy_move(Enemy *enemy) {
    if (enemy->pos.x < ENEMY_X_MIN) {
        enemy->dir_left = 0;
    }
    if (enemy->pos.x > ENEMY_X_MAX) {
        enemy->dir_left = 1;
    }
    if (enemy->dir_left) {
        enemy->pos.x -= ENEMY_SPEED;
    } else {
        enemy->pos.x += ENEMY_SPEED;
    }
}

int enemy_hits_note(const Enemy *enemy, const Note *note) {
    return position_distance(enemy->pos, note->pos) <= ENEMY_NOTE_DIST;
}

int guardian_fire(const Guardian *guardian, const EnemyList *enemies, ProjectileList *shots) {
    if (enemies->len == 0 || shots->len >= MAX_PROJECTILES) {
        return 0;
    }

    int nearest = 0;
    double best = position_distance(guardian->pos, enemies->items[0].pos);
    for (int i = 1; i < enemies->len; i++) {
        double dist = position_distance(guardian->pos, enemies->items[i].pos);
        if (dist < best) {
            best = dist;
            nearest = i;
        }
    }
    if (best == 0.0) {
        return 0;
    }

    double dx = enemies->items[nearest].pos.x - guardian->pos.x;
    double dy = enemies->items[nearest].pos.y - guardian->pos.y;
    Projectile *shot = &shots->items[shots->len];
    shot->pos = guardian->pos;
    shot->cos_v = dx / best;
    shot->sin_v = dy / best;
    shots->len++;
    return 1;
}

void projectile_move(Projectile *shot) {
    shot->pos.x += PROJECTILE_SPEED * shot->cos_v;
    shot->pos.y += PROJECTILE_SPEED * shot->sin_v;
}

int projectile_out(const Projectile *shot) {
    return shot->pos.x < 0 || shot->pos.x > WINDOW_WIDTH ||
           shot->pos.y < 0 || shot->pos.y > WINDOW_HEIGHT;
}

int projectile_hits(const Projectile *shot, const Enemy *enemy) {
    return position_distance(shot->pos, enemy->pos) <= PROJECTILE_HIT;
}
