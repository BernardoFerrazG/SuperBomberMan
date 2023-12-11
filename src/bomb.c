#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "jogo.h"


void draw_bomb(Game *g){
    //bomb_hero
    bombBarrierCollison(g);
    for(int i = 0; i < g->hero.num_bombs; i++){
        if(g->hero.bombs[i].isActive == 1){
            if(fabs(g->hero.bombs[i].time - GetTime()) > 3){
                DrawRectangleRec(g->hero.bombs[i].explosion_right, RED);
                DrawRectangleRec(g->hero.bombs[i].explosion_left, RED);
                DrawRectangleRec(g->hero.bombs[i].explosion_up, RED);
                DrawRectangleRec(g->hero.bombs[i].explosion_down, RED);
                UpdateMusicStream(bomb);

            }else{
                DrawTexture(bomba,g->hero.bombs[i].pos.x,g->hero.bombs[i].pos.y, WHITE);
            }
        }
    }
    //bomb_hero1
    for(int i = 0; i < g->hero1.num_bombs; i++){
        if(g->hero1.bombs[i].isActive == 1){
            if(fabs(g->hero1.bombs[i].time - GetTime()) > 3){
                DrawRectangleRec(g->hero1.bombs[i].explosion_right, RED);
                DrawRectangleRec(g->hero1.bombs[i].explosion_left, RED);
                DrawRectangleRec(g->hero1.bombs[i].explosion_up, RED);
                DrawRectangleRec(g->hero1.bombs[i].explosion_down, RED);
                UpdateMusicStream(bomb);
            }else{
                DrawTexture(bomba,g->hero1.bombs[i].pos.x,g->hero1.bombs[i].pos.y, WHITE);
            }
        }
    }
}

 void drawPowerUps(Game *g){
    
     for(int i = 0; i < g->maps->num_barriers1; i++){
         if(g->maps[g->curr_map].barriers1[i].exist == 0 && g->maps[g->curr_map].powerups[i].exist == 1){
             if(g->maps[g->curr_map].powerups[i].type == 0){
                 DrawTexture(velocidade, g->maps[g->curr_map].powerups[i].rec.x,g->maps[g->curr_map].powerups[i].rec.y, WHITE);
             }
             if(g->maps[g->curr_map].powerups[i].type == 1){
                 DrawTexture(bombaExtra, g->maps[g->curr_map].powerups[i].rec.x,g->maps[g->curr_map].powerups[i].rec.y, WHITE);
             }
             if(g->maps[g->curr_map].powerups[i].type == 2){
                 DrawTexture(raio, g->maps[g->curr_map].powerups[i].rec.x,g->maps[g->curr_map].powerups[i].rec.y, WHITE);
             }
             if(g->maps[g->curr_map].powerups[i].type > 2 && g->maps[g->curr_map].powerups[i].type < 5){
                 DrawRectangleRec(g->maps[g->curr_map].powerups[i].rec, BLANK);
             }
         }
     }
 }


    //config bomb





void update_bomb(Game *g){
    
    Hero *h = &g->hero;
    Hero *h1 = &g->hero1;
    Map *actual_map = &g->maps[g->curr_map];
    //hero

    if(IsKeyPressed(KEY_SPACE)){
        g->hero.put_bomb = 1;
    }

    if(g->hero.put_bomb == 1){
        for(int i = 0; i < g->hero.num_bombs; i++){
            if(g->hero.bombs[i].isActive == 0){
                g->hero.bombs[i].collision = 0;
                g->hero.bombs[i].isActive = 1;
                g->hero.bombs[i].pos = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_right = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_left = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_down = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].explosion_up = (Rectangle) {g->hero.pos.x, g->hero.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero.bombs[i].time = GetTime();
                
                break;
            }
        }
    }
    
    for(int i = 0; i < g->hero.num_bombs; i++){
        if(g->hero.bombs[i].isActive == 1){
            if(fabs(g->hero.bombs[i].time - GetTime()) > 3 && fabs(g->hero.bombs[i].time - GetTime()) < 5){
                Rectangle verify_bomb;
                Rectangle rectangle_bomb;
                int grow_tax = g->hero.bombs[i].distance;
                
                if(g->hero.bombs[i].explosion_right.width < g->hero.bombs[i].distance * STD_SIZE_X){
                    rectangle_bomb = g->hero.bombs[i].explosion_right;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y, rectangle_bomb.width + grow_tax,  rectangle_bomb.height};
                    if(!barrier_collision(actual_map, verify_bomb) && !border_collision(g, rectangle_bomb)){
                        g->hero.bombs[i].explosion_right.width += grow_tax;
                    }
                }


                if(g->hero.bombs[i].explosion_left.width < g->hero.bombs[i].distance * STD_SIZE_X){
                    rectangle_bomb = g->hero.bombs[i].explosion_left;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x - grow_tax, rectangle_bomb.y, rectangle_bomb.width + grow_tax,  rectangle_bomb.height};
                    if(!barrier_collision(actual_map, verify_bomb) && !border_collision(g, rectangle_bomb)){
                        g->hero.bombs[i].explosion_left.width += grow_tax;
                        g->hero.bombs[i].explosion_left.x -= grow_tax;
                    }
                }

                if(g->hero.bombs[i].explosion_up.height < g->hero.bombs[i].distance * STD_SIZE_Y){
                    rectangle_bomb = g->hero.bombs[i].explosion_up;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y, rectangle_bomb.width, rectangle_bomb.height + grow_tax};
                    if (!barrier_collision(actual_map, verify_bomb) && !border_collision(g, rectangle_bomb)){
                        g->hero.bombs[i].explosion_up.height += grow_tax;
                    }
                }

                if(g->hero.bombs[i].explosion_down.height < g->hero.bombs[i].distance * STD_SIZE_Y){
                    rectangle_bomb = g->hero.bombs[i].explosion_down;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y - grow_tax, rectangle_bomb.width, rectangle_bomb.height + grow_tax};
                    if(!barrier_collision(actual_map, verify_bomb) && !border_collision(g, rectangle_bomb)){
                        g->hero.bombs[i].explosion_down.height += grow_tax;
                        g->hero.bombs[i].explosion_down.y -= grow_tax;
                    }
                }
                checkBombChainReaction(h,h, i);
                checkBombChainReaction(h,h1, i);
                if(deathHero(h->bombs[i], h, g)){
                    drawDeathScreen(g, h1);
                }
                if(deathHero(h->bombs[i], h1, g)){
                    drawDeathScreen(g, h);
                }
            }else if(fabs(g->hero.bombs[i].time - GetTime()) > 3){
                g->hero.bombs[i].isActive = 0;
            }
        }
    }

    g->hero.put_bomb = 0;

    //hero1

    if(IsKeyPressed(KEY_KP_ENTER)){
        g->hero1.put_bomb = 1;
    }

    if(g->hero1.put_bomb == 1){
        for(int i = 0; i < g->hero1.num_bombs; i++){
            if(g->hero1.bombs[i].isActive == 0){
                g->hero1.bombs[i].collision = 0;
                g->hero1.bombs[i].isActive = 1;
                g->hero1.bombs[i].pos = (Rectangle) {g->hero1.pos.x, g->hero1.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero1.bombs[i].explosion_right = (Rectangle) {g->hero1.pos.x, g->hero1.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero1.bombs[i].explosion_left = (Rectangle) {g->hero1.pos.x, g->hero1.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero1.bombs[i].explosion_down = (Rectangle) {g->hero1.pos.x, g->hero1.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};
                g->hero1.bombs[i].explosion_up = (Rectangle) {g->hero1.pos.x, g->hero1.pos.y, STD_SIZE_BOMB_X, STD_SIZE_BOMB_Y};

                g->hero1.bombs[i].time = GetTime();
                break;
            }
        }
    }
    for(int i = 0; i < g->hero1.num_bombs; i++){
        if(g->hero1.bombs[i].isActive == 1){
            if(fabs(g->hero1.bombs[i].time - GetTime()) > 3 && fabs(g->hero1.bombs[i].time - GetTime()) < 5){
                Rectangle verify_bomb;
                Rectangle rectangle_bomb;
                int grow_tax = g->hero1.bombs[i].distance;
                if(g->hero1.bombs[i].explosion_right.width < g->hero1.bombs[i].distance * STD_SIZE_X){
                    rectangle_bomb = g->hero1.bombs[i].explosion_right;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y, rectangle_bomb.width + grow_tax,  rectangle_bomb.height};
                    if(!barrier_collision(actual_map, verify_bomb) && !border_collision(g, verify_bomb)){
                        g->hero1.bombs[i].explosion_right.width += grow_tax;
                    }
                }

                if(g->hero1.bombs[i].explosion_left.width < g->hero1.bombs[i].distance * STD_SIZE_X){
                    rectangle_bomb = g->hero1.bombs[i].explosion_left;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x - grow_tax, rectangle_bomb.y, rectangle_bomb.width + grow_tax,  rectangle_bomb.height};
                    if(!barrier_collision(actual_map, verify_bomb) && !border_collision(g, verify_bomb)){
                        g->hero1.bombs[i].explosion_left.width += grow_tax;
                        g->hero1.bombs[i].explosion_left.x -= grow_tax;
                    }
                }

                if(g->hero1.bombs[i].explosion_up.height < g->hero1.bombs[i].distance * STD_SIZE_Y){
                    rectangle_bomb = g->hero1.bombs[i].explosion_up;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y, rectangle_bomb.width, rectangle_bomb.height + grow_tax};
                    if(!barrier_collision(actual_map, verify_bomb) && !border_collision(g, verify_bomb)){
                        g->hero1.bombs[i].explosion_up.height += grow_tax;
                    }
                }

                if(g->hero1.bombs[i].explosion_down.height < g->hero1.bombs[i].distance * STD_SIZE_Y){
                    rectangle_bomb = g->hero1.bombs[i].explosion_down;
                    Rectangle verify_bomb = (Rectangle){ rectangle_bomb.x, rectangle_bomb.y - grow_tax, rectangle_bomb.width, rectangle_bomb.height + grow_tax};
                    if(!barrier_collision(actual_map, verify_bomb) && !border_collision(g, verify_bomb)){
                        g->hero1.bombs[i].explosion_down.height += grow_tax;
                        g->hero1.bombs[i].explosion_down.y -= grow_tax;
                    }
                }
                checkBombChainReaction(h1,h1, i);
                checkBombChainReaction(h1,h, i);
                
                if(deathHero(h1->bombs[i], h1, g)){
                    drawDeathScreen(g, h);
                }
                if(deathHero(h1->bombs[i], h, g)){
                    drawDeathScreen(g, h1);
                }
                
            }
            else if(fabs(g->hero1.bombs[i].time - GetTime()) > 3){
                g->hero1.bombs[i].isActive = 0;
            }
        }
    }

    g->hero1.put_bomb = 0;
}

    //end config bomb

void updatePowerUp(Game *g, Hero *h){
    for(int i = 0; i < 25; i++){
        if((CheckCollisionRecs(h->pos, g->maps[g->curr_map].powerups[i].rec)) && g->maps[g->curr_map].powerups[i].exist == 1){
            if(g->maps[g->curr_map].powerups[i].type == 0){
                h->speed += 0.5;
                g->maps[g->curr_map].powerups[i].exist = 0;
            }
            if(g->maps[g->curr_map].powerups[i].type == 1){
                h->num_bombs += 1;
                g->maps[g->curr_map].powerups[i].exist = 0;
            }
            if(g->maps[g->curr_map].powerups[i].type == 2){
                h->bombs->distance += 0.5;
                g->maps[g->curr_map].powerups[i].exist = 0;
            }
            if(g->maps[g->curr_map].powerups[i].type > 2 && g->maps[g->curr_map].powerups[i].type < 5){
                g->maps[g->curr_map].powerups[i].exist = 0;
            }
        }
    }
}


int bomb_collision(Game *g, Rectangle target){
    for (int i = 0; i < 10; i++){
       if (!CheckCollisionRecs(g->hero.pos, g->hero.bombs[i].pos) && !CheckCollisionRecs(g->hero1.pos, g->hero1.bombs[i].pos))
           g->hero.bombs[i].collision = 1;
    }
    for (int i = 0; i < 10; i++){
        if(CheckCollisionRecs(target, g->hero.bombs[i].pos) && g->hero.bombs[i].isActive && g->hero.bombs[i].collision && (!bomb1_collision(g,g->hero.pos))){
            return 1;
        }
    }
    return 0;

}
int bomb1_collision(Game *g, Rectangle target){
    for (int i = 0; i < 10; i++){
       if (!CheckCollisionRecs(g->hero1.pos, g->hero1.bombs[i].pos) && !CheckCollisionRecs(g->hero.pos, g->hero.bombs[i].pos))
           g->hero1.bombs[i].collision = 1;
    }
    for (int i = 0; i < 10; i++){
        if(CheckCollisionRecs(target, g->hero1.bombs[i].pos) && g->hero1.bombs[i].isActive && g->hero1.bombs[i].collision && (!bomb_collision(g,g->hero1.pos))){
            return 1;
        }
    }
    return 0;

}


int bombBarrierCollison(Game *g){
    for(int j = 0; j < g->hero.num_bombs; j++){
        if(g->hero.bombs[j].isActive){
            for(int i = 0; i < 25; i++){
                if(g->maps[g->curr_map].barriers1[i].exist){
                    if (CheckCollisionRecs(g->maps[g->curr_map].barriers1[i].barrier1, g->hero.bombs[j].explosion_up)){
                        g->maps[g->curr_map].barriers1[i].exist = 0;
                        //g->hero.bombs[j].explosion_up -= (30 * g->hero.bombs[j].distance);
                    }
                    if (CheckCollisionRecs(g->maps[g->curr_map].barriers1[i].barrier1, g->hero.bombs[j].explosion_down)){
                        g->maps[g->curr_map].barriers1[i].exist = 0;
                        //g->hero.bombs[j].explosion_down.height += (10 * g->hero.bombs[j].distance);
                    }

                }
            }
        }
    }

    for(int j = 0; j < g->hero1.num_bombs; j++){
        if(g->hero1.bombs[j].isActive){
            for(int i = 0; i < 25; i++){
                if(g->maps[g->curr_map].barriers1[i].exist){
                    if (CheckCollisionRecs(g->maps[g->curr_map].barriers1[i].barrier1, g->hero1.bombs[j].explosion_up) ||
                        CheckCollisionRecs(g->maps[g->curr_map].barriers1[i].barrier1, g->hero1.bombs[j].explosion_down) ||
                        CheckCollisionRecs(g->maps[g->curr_map].barriers1[i].barrier1, g->hero1.bombs[j].explosion_left) ||
                        CheckCollisionRecs(g->maps[g->curr_map].barriers1[i].barrier1, g->hero1.bombs[j].explosion_right)){                 
                        g->maps[g->curr_map].barriers1[i].exist = 0;
                    }
                }
            }
        }
    }
} 


void checkBombChainReaction(Hero *h, Hero *h1, int i) {
    for (int index = 0; index < h1->num_bombs; index++) {
        if (h1->bombs[i].isActive == 1) {
            // Verifique se a explosão da bomba 'i' atinge a bomba 'index'
            if(i != index && h->bombs[index].isActive){
                if (CheckCollisionRecs(h1->bombs[i].explosion_right, h->bombs[index].pos) ||
                    CheckCollisionRecs(h1->bombs[i].explosion_left, h->bombs[index].pos) ||
                    CheckCollisionRecs(h1->bombs[i].explosion_up, h->bombs[index].pos) ||
                    CheckCollisionRecs(h1->bombs[i].explosion_down, h->bombs[index].pos)) {
                    // Ative a bomba index caso ela não esteja ativa
                    if(fabs(h->bombs[index].time - GetTime()) < 3){
                        h->bombs[index].time = GetTime() - 3;
                    }
                    // Adicione qualquer lógica h->bombs[index].timeadicional necessária aqui
                }
            }
        }
    }
}

