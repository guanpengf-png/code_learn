#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAP_W 24
#define MAP_H 24
#define INIT_CAP 16
//position
typedef struct{
    int x;
    int y;

} Point;
//snake status
typedef struct{
    //snake body
    Point *body;
    int len;
    int cap;
    Point dir;

} Snake;
//game status
typedef struct{
    Snake snake;
    Point food;
    //cell
    char* cell;
    int score;
    int alive;
} Game;
static int idx(int x,int y){
    return y*MAP_W+x;

}
static char* cell_at(Game* g,int x ,int y){
    return g->cell+idx(x,y);

}
static void clear_cell(Game* g){
    memset(g->cell,' ',(size_t)MAP_H*MAP_W);

}

static void paint(Game* g){
    clear_cell(g);
    *cell_at(g,g->food.x,g->food.y)='*';
    //get snake body;
    Point *p=g->snake.body;
    Point *end=g->snake.body+g->snake.len;
    if(p<end){
        *cell_at(g,p->x,p->y)='@';
    }

    //draw body
    for (p=g->snake.body+1;p<end;p++)
    {
        *cell_at(g,p->x,p->y)='o';
    }
}
static void draw(const Game* g){
    printf("\033[2J\033[H");
    printf("score=%d len=%d wasd move q\n",g->score,g->snake.len);
    printf("+");
    for(int i=0;i<MAP_W;i++){
        putchar('-');

    }
    printf("\n");
    const char* row=g->cell;
    for(int y=0;y<MAP_H;y++){
        putchar('|');
        fwrite(row,1,MAP_W,stdout);
        putchar('|');
        row+=MAP_W;
    }
    //bottom
    printf('+');
    for (int i = 0; i < MAP_W; i++)
    {
        putchar('-');

    }
    printf("+\n");
    if (!g->alive)
    {
        printf("game over %d\n",g->score);
    }
    }
static void game_stick(Game* g){
    if(!g->alive){
        return;
    }
    Point next ={
        g->snake.body[0].x+g->snake.dir.x,
        g->snake.body[0].y+g->snake.dir.y,
    };
    if(!in_bound(&next)||snake_hit_self(&g->snake,&next)){
        g->alive=0;
        return;

    }


}
int main(){
    srand((unsigned)time(NULL));
    Game game;
    game_ini(&game);
    printf("inpute step");
    puts("ws");
    puts("ad");
    printf("start game");
    (void)getchar();
    while (game.alive)
    {
        /* code */
        paint(&game);
        draw(&game);
        printf(">");
        fflush(stdout);
        int ch =getchar();
        if (ch==EOF)
        {
            break;
        }
        if(ch=="\n"){
            game_tick(&game);
            continue;
        }
        int rest =getchar();
        if(rest!='\n'&&rest!=EOF){
            while (rest!='\n'&&rest!=EOF)
            {
                rest=getchar();
            }
            
        }
        //return
        if(!handle_key(&game,ch)){
            break;

        }
        
    }
    paint(&game);
    draw(&game);
    game_free(&game);
    
    return 0;
}