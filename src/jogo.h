#ifndef JOGO_H
#define JOGO_H

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define STD_SIZE_X 38
#define STD_SIZE_Y 38
#define STD_SIZE_BOMB_X 30
#define STD_SIZE_BOMB_Y 30
#define SCREEN_BORDER 27
#define HNUMBOMB 2
#define H1NUMBOMB 2

Texture2D chaves;
Texture2D kiko;
Texture2D madruga;
Texture2D barriga;
Texture2D barril;
Texture2D bola;
Texture2D chapeu;
Texture2D maleta;
Texture2D bomba;
Texture2D explosion_right;
Texture2D bombaExtra;
Texture2D velocidade;
Texture2D raio;
Texture2D abertura;
Texture2D campeao;
Texture2D borda_sup_inf;
Texture2D bordaLateral;
Texture2D fundo;
int vencedor;
int vencedor1;

Music musicaPlay;
Music musicaInit;
Music musicaEnd;
Music bomb;

typedef struct Bomb{
    Rectangle pos;
    Rectangle explosion_right;
    Rectangle explosion_left;
    Rectangle explosion_up;
    Rectangle explosion_down;
    int isActive;
    float distance;
    int time;
    int collision;
}Bomb;

typedef struct Hero {
    Rectangle pos;
    Color color;
    float speed;
    int special;
    int draw_bomb;
    int put_bomb;
    int num_bombs;
    Bomb bombs[10];
    Texture2D boneco;
    char name[100];
} Hero;

typedef struct Powerup {
   Rectangle rec;
   int exist;
   int type;
} Powerup;

typedef struct{
    Rectangle left;
    Rectangle right;
    Rectangle up;
    Rectangle down;
}Border;

typedef struct{
    Rectangle barrier1;
    int exist;
}Barrier;

typedef struct Map {
    Rectangle barriers[36];
    Barrier barriers1[25];
    int num_barriers;
    int num_barriers1;
    Color color;
    int next_map;
    int prev_map;
    Powerup powerups[25];
} Map;


typedef struct Game { 
    Map maps[10];
    int num_maps;
    int curr_map;
    Hero hero;
    Hero hero1;
    int screenWidth;
    int screenHeight;
    int gameover;
    Border bord;
    double startTime;
    double gameDuration;
    int partidaIniciada;

} Game;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
void InitGame(Game *g);         // Initialize game
void UpdateGame(Game *g);       // Update game (one frame)
void DrawGame(Game *g);         // Draw game (one frame)
void UpdateDrawFrame(Game *g);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Auxiliar Functions Declaration
//------------------------------------------------------------------------------------
void salvarPlacar(Game *g);
void DrawTimer(Game *g);
void IniciarPartida(Game *g);
void makeHero(Game *g);    
void initialScreen(Game *g);
void drawMapScreen(Game *g);
void drawDeathScreen(Game *g, Hero *h);
void drawDrawScreen(Game *g);
void nameScreen(Game *g, Hero *h, int n);
void draw_borders(Game *g);
void draw_map(Game *g);
void draw_map1(Game *g);
void draw_bomb(Game *g);
void draw_hero(Game *g);
void drawPowerUps(Game *g);
void update_hero_pos(Game *g);
void update_bomb(Game *g);
void updatePowerUp(Game *g, Hero *h);
int barrier_collision(Map *m, Rectangle t);
int barrier1_collision(Map *m, Rectangle t);
int border_collision(Game *g, Rectangle t);
int bomb_collision(Game *g, Rectangle target);
int bomb1_collision(Game *g, Rectangle target);
int bombBarrierCollison(Game *g);
void checkBombChainReaction(Hero *h, Hero *h1, int index);
void map0_setup(Game *g);
void map1_setup(Game *g);
int deathHero(Bomb b, Hero *target, Game *g);


#endif