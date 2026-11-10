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