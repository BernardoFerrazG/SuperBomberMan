#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "jogo.h"

//configs_gerais herois
    void makeHero(Game *g){
        g->hero.pos = (Rectangle) { 55, 30 , STD_SIZE_X, STD_SIZE_Y};
        g->hero.speed = 3;
        g->hero.special = 0;
        g->hero.num_bombs = 1;
        g->hero.put_bomb = 0;
        g->hero.draw_bomb = 0;
        
        
        g->hero1.pos = (Rectangle) { 700, 532, STD_SIZE_X, STD_SIZE_Y};
        g->hero1.speed = 3;
        g->hero1.special = 0;
        g->hero1.num_bombs = 1;
        g->hero1.put_bomb = 0;
        g->hero1.draw_bomb = 0;
        
        
    }

void draw_hero(Game *g){
    if(g->curr_map == 0){
        //DrawRectangleRec(g->hero.pos, BLACK);
        DrawTexture(chaves, g->hero.pos.x,g->hero.pos.y , WHITE);
        //DrawRectangleRec(g->hero1.pos, PINK);
        DrawTexture(kiko, g->hero1.pos.x,g->hero1.pos.y , WHITE);
        bombBarrierCollison(g);
    }
    if(g->curr_map == 1){
        //DrawRectangleRec(g->hero.pos, BLACK);
        DrawTexture(madruga, g->hero.pos.x,g->hero.pos.y , WHITE);
        //DrawRectangleRec(g->hero1.pos, PINK);
        DrawTexture(barriga, g->hero1.pos.x,g->hero1.pos.y , WHITE);
        bombBarrierCollison(g);
    }
}


void update_hero_pos(Game *g){
    // config_move hero

    Hero *h = &g->hero;
    Hero *h1 = &g->hero1;
    Map *m = &g->maps[g->curr_map];
    

    if(IsKeyDown(KEY_A)) {
        if(!border_collision(g, h->pos) && !(bomb_collision(g, h->pos)) && !(bomb1_collision(g, h->pos)))
            h->pos.x -= h->speed;
        if(barrier_collision(m, h->pos) || (bomb_collision(g, h->pos)) || (bomb1_collision(g, h->pos)) || barrier1_collision(m, h->pos) || border_collision(g, h->pos)) 
            h->pos.x += h->speed;

    } else if(IsKeyDown(KEY_D)) {
        if(!border_collision(g, h->pos) && !(bomb_collision(g, h->pos)) && !(bomb1_collision(g, h->pos)))
            h->pos.x += h->speed;
        if(barrier_collision(m, h->pos) || (bomb_collision(g, h->pos)) || (bomb1_collision(g, h->pos)) || barrier1_collision(m, h->pos) || border_collision(g, h->pos)) 
            h->pos.x -= h->speed;

    } else if(IsKeyDown(KEY_W)) {
        if(!border_collision(g, h->pos) && !(bomb_collision(g, h->pos)) && !(bomb1_collision(g, h->pos)))
            h->pos.y -= h->speed;
        if(barrier_collision(m, h->pos) || (bomb_collision(g, h->pos)) || (bomb1_collision(g, h->pos)) || barrier1_collision(m, h->pos) || border_collision(g, h->pos)) 
            h->pos.y += h->speed;

    } else if(IsKeyDown(KEY_S)) {
        if(!border_collision(g, h->pos) && !(bomb_collision(g, h->pos)) && !(bomb1_collision(g, h->pos)))
            h->pos.y += h->speed;
        if(barrier_collision(m, h->pos) || (bomb_collision(g, h->pos)) || (bomb1_collision(g, h->pos)) || barrier1_collision(m, h->pos) || border_collision(g, h->pos)) 
            h->pos.y -= h->speed;
    }
    //config_move hero1


    if(IsKeyDown(KEY_LEFT)) {
        if(!border_collision(g, h->pos) && !(bomb1_collision(g, h1->pos)) && !(bomb_collision(g, h1->pos)))
            h1->pos.x -= h1->speed;
        if(barrier_collision(m, h1->pos) || (bomb1_collision(g, h1->pos)) || (bomb_collision(g, h1->pos)) || barrier1_collision(m, h1->pos) || border_collision(g, h1->pos)) 
            h1->pos.x += h1->speed;

    } else if(IsKeyDown(KEY_RIGHT)) {
        if(!border_collision(g, h->pos) && !(bomb1_collision(g, h1->pos)) && !(bomb_collision(g, h1->pos)))
            h1->pos.x += h1->speed;
        if(barrier_collision(m, h1->pos) || (bomb1_collision(g, h1->pos)) || (bomb_collision(g, h1->pos)) || barrier1_collision(m, h1->pos) || border_collision(g, h1->pos)) 
            h1->pos.x -= h1->speed;

    } else if(IsKeyDown(KEY_UP)) {
        if(!border_collision(g, h->pos) && !(bomb1_collision(g, h1->pos)) && !(bomb_collision(g, h1->pos)))
            h1->pos.y -= h1->speed;
        if(barrier_collision(m, h1->pos) || (bomb1_collision(g, h1->pos)) || (bomb_collision(g, h1->pos)) || barrier1_collision(m, h1->pos) || border_collision(g, h1->pos)) 
            h1->pos.y += h1->speed;

    } else if(IsKeyDown(KEY_DOWN)) {
        if(!border_collision(g, h->pos) && !(bomb1_collision(g, h1->pos)) && !(bomb_collision(g, h1->pos)))
            h1->pos.y += h1->speed;
        if(barrier_collision(m, h1->pos) || (bomb1_collision(g, h1->pos)) || (bomb_collision(g, h1->pos)) || barrier1_collision(m, h1->pos) || border_collision(g, h1->pos)) 
            h1->pos.y -= h1->speed;
    }
}

int deathHero(Bomb b, Hero *target, Game *g){
        if(CheckCollisionRecs(target->pos, b.explosion_down) ||
            CheckCollisionRecs(target->pos, b.explosion_left) ||
            CheckCollisionRecs(target->pos, b.explosion_up) ||
            CheckCollisionRecs(target->pos, b.explosion_right)){
                return 1;   
        }
}


