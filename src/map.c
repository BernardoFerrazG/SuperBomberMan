#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "jogo.h"

void draw_map(Game *g){
    Map *map = &g->maps[0];
    
    for(int i = 0; i< 30; i++){
        DrawTexture(barril, map->barriers[i].x,map->barriers[i].y, WHITE);    
    }

    

    for(int i = 0; i< 25; i++){
        if(map[0].barriers1[i].exist == 1){
            DrawTexture(bola, map->barriers1[i].barrier1.x,map->barriers1[i].barrier1.y, WHITE);   
        }
    }
}

void draw_map1(Game *g){
    Map *map1 = &g->maps[1];
    
    for(int i = 0; i< 30; i++){
        DrawTexture(maleta, map1->barriers[i].x,map1->barriers[i].y, WHITE);    
    }

    

    for(int i = 0; i< 25; i++){
        if(map1[0].barriers1[i].exist == 1){
            DrawTexture(chapeu, map1->barriers1[i].barrier1.x,map1->barriers1[i].barrier1.y, WHITE);   
        }
    }
}

// Maps Setup
void map0_setup(Game *g){
    g->maps[0].num_barriers = 36;
    g->maps[0].num_barriers1 = 25;
    g->maps[0].color = GRAY;
    g->maps[0].prev_map = -1;
    g->maps[0].next_map = 1;



    for(int i = 0; i < 10; i++){
        g->hero.bombs[i].isActive = 0;
        g->hero.bombs[i].distance = 3;
    }
    for(int i = 0; i < 10; i++){
        g->hero1.bombs[i].isActive = 0;
        g->hero1.bombs[i].distance = 3;
    }
    for(int i = 0; i < g->maps[0].num_barriers1; i++){
        g->maps[0].barriers1[i].exist = 1;
    }
    for(int i = 0; i < 25; i++){
        g->maps[0].powerups[i].exist = 1;
    }
    
    double pos_l = 15;
    int pos_a = 72;
    for(int i = 0; i< 30; i++){
        g->maps[g->curr_map].barriers[i] = (Rectangle) {pos_l += 102, pos_a , 45, 45};       
       
       
        if(i == 5){
            pos_a +=103;
            pos_l = 15;
        }
        else if(i == 11){
            pos_a +=103;
            pos_l = 15;
        }
        else if(i == 17){
            pos_a +=103;
             pos_l = 15;
        }
        else if(i == 23){
            pos_a +=103;
             pos_l = 15;
        }
        else if(i == 29){
            pos_a +=103;
             pos_l = 15;
        }
        
    }

    double pos_l1 = 166;
    int pos_a1 = 72;
    for(int i = 0; i< 25; i++){
        if(g->maps[0].barriers1[i].exist == 1){
            g->maps[0].barriers1[i].barrier1 = (Rectangle) {pos_l1, pos_a1, 51, 45};
            g->maps[0].powerups[i].rec = (Rectangle) {pos_l1, pos_a1, 51, 45};
            g->maps[0].powerups[i].type = rand() % 5;
            if(i == 4){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            else if(i == 9){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            else if(i == 14){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            else if(i == 19){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            pos_l1 += 102;
        }
    }
    
}

void map1_setup(Game *g){

    
    g->maps[1].num_barriers = 36;
    g->maps[1].num_barriers1 = 25;
    g->maps[1].color = GRAY;
    g->maps[1].prev_map = -1;
    g->maps[1].next_map = 1;

    for(int i = 0; i < 10; i++){
        g->hero.bombs[i].isActive = 0;
        g->hero.bombs[i].distance = 3;
    }
    for(int i = 0; i < 10; i++){
        g->hero1.bombs[i].isActive = 0;
        g->hero1.bombs[i].distance = 3;
    }
    for(int i = 0; i < 25; i++){
        g->maps[1].barriers1[i].exist = 1;
    }
    for(int i = 0; i < 25; i++){
        g->maps[1].powerups[i].exist = 1;
    }

    double pos_l = 15;
        int pos_a = 72;
        for(int i = 0; i< 30; i++){
            g->maps[1].barriers[i] = (Rectangle) {pos_l += 102, pos_a , 45, 45};       
        
            if(i == 5){
                pos_a +=103;
                pos_l = 15;
            }
            else if(i == 11){
                pos_a +=103;
                pos_l = 15;
            }
            else if(i == 17){
                pos_a +=103;
                pos_l = 15;
            }
            else if(i == 23){
                pos_a +=103;
                pos_l = 15;
            }
            else if(i == 29){
                pos_a +=103;
                pos_l = 15;
            }
            
        }

    double pos_l1 = 166;
    double pos_a1 = 72;
    for(int i = 0; i< 25; i++){
        if(g->maps[1].barriers1[i].exist == 1){
            g->maps[1].barriers1[i].barrier1 = (Rectangle) {pos_l1, pos_a1, 51, 45};
            g->maps[1].powerups[i].rec = (Rectangle) {pos_l1, pos_a1, 51, 45};
            g->maps[1].powerups[i].type = rand() % 5;
            if(i == 4){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            else if(i == 9){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            else if(i == 14){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            else if(i == 19){
                pos_a1 +=103;
                pos_l1 = 63;
            }
            pos_l1 += 102;
        }
    }
}
