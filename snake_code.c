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
static void snake_init(Snake*s,int x,int y){
    s->body=NULL;
    s->len=0;
    s->cap=0;
    s->dir=(Point){1,0};
    if (!snake_reserve(&s->body,&s->cap,4))
    {
        fprintf(stderr,"malloc failded\n");
        exit(1);
    }
    s->body[0]=(Point){x,y};
    s->body[1]=(Point){x-1,y};
    s->body[2]=(Point){x-2,y}
    s->len=3;
    

}
static void game_init(Game* g){
    g->cell=malloc((size_t)MAP_H*MAP_W);
    if (!g->cell)
    {
        fprintf(stderr,"malloc failed");
        exit(1);
    }
    snake_init(&g->snake,MAP_W/2,MAP_H/2);
    g->score=0;
    g->alive=0;
    spawn_food(g);
    
}
static void snake_free(Snake*s){
    free(s->body);
    s->body=NULL;
    s->len=0;
    s->cap=0;
}
static void game_free(Game* g){
    snake_free(&g->snake);
    free(g->cell);
    g->cell=NULL;

}
typedef void(*Dirhandle)(Snake*s);
typedef struct{
    char key;
    Dirhandle fn;
}KeyBind;
static void go_up(Snake*s){
    if (s->dir.y!= 1)
    {
        s->dir=(Point){0,1};
    }
    

}
static void go_down(Snake*s){
    if (s->dir.y!=-1)
    {
        s->dir=(Point){0,-1};
    }
    

}
static void go_right(Snake*s){
    if (s->dir.x!=-1)
    {
        s->dir=(Point){1,0};
    }
    

}
static void go_left(Snake*s){
    if (s->dir.x!=1)
    {
        s->dir=(Point){-1,0};
    }
    
}
static const KeyBind BINDS[]={
    {'w',go_up},
    {'k',go_up},
    {'s',go_down},
    {'j',go_down},
    {'a',go_left},
    {'d',go_right},
    {'l',go_right},

}

static int handle_key(Game*g,int ch){
    ch=tolower(ch);
    if(ch=='q'){
        return 0;

    }
    const KeyBind *b=BINDS;
    const KeyBind *end =BINDS+sizeof BINDS/sizeof *BINDS;
    for ( ;b<end; b++)
    {
        if (b->key==ch)
        {
            b->fn(&g->snake);
            break;
        }
        
    }
    game_tick(g);
    retuen 1;
    

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
static int point_eq(const Point* a,const Point* b){
    return a->x==b->x&&a->y==b->y;
}
static int inbound(const Point* p){
    return p->x>=0&&p->x<MAP_W&&p->y>0&&p->y<MAP_H;
}
static int snake_hit_self(const Snake* s,const Point* head){
    const Point* p=s->body+1;
    const Point* end=s->body+s->len;
    for(;p<end;p++){
        if(point_eq(p,head)){
            return 1;

        }
        return 0;

    }
}
static int snake_reserve(Point **body,int* cap,int need){
    if(need<=*cap){
        return 1;

    }
    int cnap=*cap?*cap*2: INIT_CAP;
    while(cnap<need){
        cnap*=2;

    }
    Point* p=realloc(*body,(size_t)cnap*sizeof *p);
    if (!p)
    {
        return 0;
    }
    *body=p;
    *cap=cnap;
    return 1;
    


}
static void snake_step(Snake* s,int grow){
    Point new_head={
        s->body[0].x+s->dir.x,
        s->body[0].y+s->dir.y,
    };
    if (grow)
    {
        if(!snake_reserve(&s->body,&s->cap,s->len+1)){
            fprintf(stderr,"relloc failed\n");
            exit(1);

        }

    }
    


}
static int occupied_by_snake(const Snake *s,const Point *pt){
    const Point*p=s->body;
    const Point*end=s->body+s->len;
    for (; p<end; p++)
    {
        if (point_eq(p,pt))
        {
            return 1;
        }
        
    }
    return 0;
    

}
static void spawn_food(Game* g){
    Point cand;
    int guard=0;
    do{
        cand.x=rand()%MAP_W;
        cand.y=rand()%MAP_H;
        if(++guard>10000){
            break;
        }
    }while (occupied_by_snake(&g->snake,&cand));
    
    
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
    int grow=point_eq(&next,&g->food);
    snake_step(&g->snake,grow);
    if (grow)
    {
        g->score+=10;
        spawn_food(g);
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