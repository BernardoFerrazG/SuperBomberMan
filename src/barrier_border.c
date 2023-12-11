#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "jogo.h"


void draw_borders(Game *g)
{
    g->bord.right.height = g->screenHeight;
    g->bord.right.width = SCREEN_BORDER +20;
    g->bord.right.x = g->screenWidth-SCREEN_BORDER -20;
    g->bord.right.y = 0;   

    g->bord.left.height = g->screenHeight;
    g->bord.left.width = SCREEN_BORDER + 20;
    g->bord.left.x = 0;
    g->bord.left.y = 0;

    g->bord.up.height = SCREEN_BORDER;
    g->bord.up.width = g->screenWidth;
    g->bord.up.x = 0;
    g->bord.up.y = 0;

    g->bord.down.height = SCREEN_BORDER;
    g->bord.down.width = g->screenWidth; 
    g->bord.down.x = 0;
    g->bord.down.y = g->screenHeight-SCREEN_BORDER;

    DrawTexture(bordaLateral,g->bord.left.x, g->bord.left.y,WHITE); //left
    DrawTexture(borda_sup_inf,g->bord.up.x, g->bord.up.y, WHITE); //up
    DrawTexture(bordaLateral,g->bord.right.x, g->bord.right.y,WHITE); //right
    DrawTexture(borda_sup_inf,g->bord.down.x, g->bord.down.y, WHITE); //down
    
}



//ESTILO BARREIRA





int barrier_collision(Map *map, Rectangle target){
    for(int i = 0; i < map[0].num_barriers; i++){
        if(CheckCollisionRecs(target, map[0].barriers[i])){
            return 1;
        }
    }
    for(int i = 0; i < map[1].num_barriers; i++){
        if(CheckCollisionRecs(target, map[1].barriers[i])){
            return 1;
        }
    }
    
    return 0;
}

int barrier1_collision(Map *map, Rectangle target){
    for(int i = 0; i < map[0].num_barriers1; i++){
        if(CheckCollisionRecs(target, map->barriers1[i].barrier1) && map->barriers1[i].exist == 1){
            return 1;
        }
    }
    for(int i = 0; i < map[1].num_barriers1; i++){
        if(CheckCollisionRecs(target, map[1].barriers1[i].barrier1) && map[1].barriers1[i].exist == 1){
            return 1;
        }
    }
    
    return 0;
}


int border_collision(Game *g, Rectangle target){
    return (CheckCollisionRecs(target, g->bord.left) ||
            CheckCollisionRecs(target, g->bord.right) ||
            CheckCollisionRecs(target, g->bord.up) ||
            CheckCollisionRecs(target, g->bord.down));
}


