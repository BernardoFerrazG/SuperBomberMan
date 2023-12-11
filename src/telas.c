#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "jogo.h"


void salvarPlacar(Game *g) {
    FILE *file = fopen("placar.txt", "a"); // Abre o arquivo para escrita

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Escreve o placar no arquivo
    fprintf(file, "Placar Final\n");
    fprintf(file, "Jogador 1: %s - Pontos: %d\n", g->hero.name, vencedor);
    fprintf(file, "Jogador 2: %s - Pontos: %d\n", g->hero1.name, vencedor1);

    fclose(file); // Fecha o arquivo
}


void DrawTimer(Game *g) {
    if (g->partidaIniciada) {
        int timeLeft = (int)(g->gameDuration - (GetTime() - g->startTime));
        int minutes = timeLeft / 60;
        int seconds = timeLeft % 60;

        char timeStr[6];
        sprintf(timeStr, "%02d:%02d", minutes, seconds);
        DrawText(timeStr, g->screenWidth / 2 - MeasureText("00:00", 30) / 2, 0, 30, BLACK);
    }
}


void IniciarPartida(Game *g) {
    // Inicialize outras configurações da partida aqui
    g->partidaIniciada = 1;
    g->startTime = GetTime();
    g->gameDuration = 120.0; // 120 segundos = 2 minutos
}

// Initialize game variables
void InitGame(Game *g){
    
    
    g->num_maps = 10;
    makeHero(g);
    draw_hero(g);
    g->gameover = 0;

}

// Update game (one frame)
void UpdateGame(Game *g)
{
    if (g->curr_map == 0) {
        update_hero_pos(g);
        updatePowerUp(g, &g->hero);
        updatePowerUp(g, &g->hero1);
        update_bomb(g);
    } else if (g->curr_map == 1) {
        update_hero_pos(g);
        updatePowerUp(g, &g->hero);
        updatePowerUp(g, &g->hero1);
        update_bomb(g);
    }
    if (g->partidaIniciada) {
        if (GetTime() - g->startTime > g->gameDuration) {
            g->gameover = 1;
        }
    }
}


void initialScreen(Game *g){
    int select = 0;

    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        PlayMusicStream(musicaInit);
        UpdateMusicStream(musicaInit);
        DrawTexture(abertura, 0,0, WHITE);
        
        DrawText("Super BomberMan",
                 (g->screenWidth / 2 - MeasureText("Super BomberMan", 62) / 2) + 110, 15, 62, DARKBLUE);
        DrawText("COMEÇAR",
                 g->screenWidth / 2 - MeasureText("COMEÇAR", 55) / 2, 210, 55, (select == 0) ? GREEN : WHITE);
        DrawText("Quit Game",
                 g->screenWidth / 2 - MeasureText("Quit Game", 55) / 2, 280, 55, (select == 1) ? GREEN : WHITE); 

        EndDrawing();

        if(IsKeyPressed(KEY_UP) && select > 0){
            select--;
        }
        if(IsKeyPressed(KEY_DOWN) && select < 1){
            select++;
        }

        if(WindowShouldClose()){
            salvarPlacar(g);
            CloseWindow();
        } 
    }

    
    if(select == 0){
        drawMapScreen(g);
    }

    if(select == 1){
        salvarPlacar(g);
        CloseWindow();
    } 
}

void nameScreen(Game *g,Hero *h, int n){
    char text[50];
    sprintf(text, "Enter Player %d Name:", n);
    char playerName[100] = {0};
    int cursor = 0;

    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        PlayMusicStream(musicaInit);
        UpdateMusicStream(musicaInit);
        DrawTexture(abertura, 0,0, WHITE);
        DrawText(text, (GetScreenWidth() / 2 - MeasureText(text, 50) / 2) + 10, 200, 50, WHITE);

        DrawText(TextSubtext(playerName, 0, cursor), GetScreenWidth() / 2 - MeasureText(playerName, 20) / 2, 255, 30, WHITE);

        EndDrawing();

        //get input
        int key = GetKeyPressed();
        if(key != 0){
            if(key == KEY_BACKSPACE && cursor > 0){
                playerName[--cursor] = '\0';
            }else if(key >= 32 && key <= 125 && cursor < 100 - 1){
                playerName[cursor++] = (char)key;
            }
        }
        if(WindowShouldClose()){
            salvarPlacar(g);
            CloseWindow();
        } 
    }
    strcpy(h->name, playerName);
    for(int i = 0; i < 100; i++){
        playerName[i] = '\0';
    }
    if(IsKeyPressed(KEY_ENTER))
        drawMapScreen(g);
    
}

void drawMapScreen(Game *g){
    int select = 0;

    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        PlayMusicStream(musicaInit);
        UpdateMusicStream(musicaInit);
        DrawTexture(abertura, 0,0, WHITE);
        DrawText("Super BomberMan",
                 (g->screenWidth / 2 - MeasureText("Super BomberMan", 62) / 2) + 110, 15, 62, DARKBLUE);

        DrawText("Selecione o mapa:",
                 g->screenWidth / 2 - MeasureText("Selecione o mapa:", 50) / 2, 180, 50, WHITE);

        //opção de mapa
        DrawText("Mapa 1",
                 g->screenWidth / 2 - MeasureText("Mapa 1", 35) / 2, 250, 35, (select == 0) ? GREEN : WHITE);
        DrawText("Mapa 2",
                 g->screenWidth / 2 - MeasureText("Mapa 2", 35) / 2, 300, 35, (select == 1) ? GREEN : WHITE);


        EndDrawing();


        if(IsKeyPressed(KEY_UP) && select > 0){
            select--;
        }
        if(IsKeyPressed(KEY_DOWN) && select < 1){
            select++;
        }
        if(WindowShouldClose()){
            salvarPlacar(g);
            CloseWindow();
        } 
    }
    //mapa 1
    if(select == 0){
        g->curr_map = 0;
        DrawGame(g);
        map0_setup(g);
        IniciarPartida(g);
    }
    //mapa 2
    if(select == 1){
        g->curr_map = 1;
        DrawGame(g);
        map1_setup(g);
        IniciarPartida(g);
    } 
}

void drawDeathScreen(Game *g, Hero *h){
        int select = 0;
        
        if(strcmp(h->name, g->hero.name)){
            vencedor+=1;
        }if(strcmp(h->name, g->hero1.name)){
            vencedor1+=1;
        }
    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        PlayMusicStream(musicaEnd);
        UpdateMusicStream(musicaEnd);
        DrawTexture(campeao, 0,0, WHITE);
        DrawText(h->name,
                 g->screenWidth / 2 - MeasureText(h->name, 55) / 2, 30, 55, DARKPURPLE);

        DrawText("venceu",
                 (g->screenWidth / 2 - MeasureText("venceu", 55) / 2), 75, 55, DARKPURPLE);

        DrawText("Placar",
                 (g->screenWidth / 2 - MeasureText("Placar", 55) / 2), 190, 55, BLACK);
        
        DrawText(TextFormat("%d x %d", vencedor1, vencedor), (g->screenWidth / 2 - MeasureText("0 x 0", 45) / 2), 240, 45, BLACK);
        
        
        DrawText("Revanche",
                 g->screenWidth / 2 - MeasureText("Revanche", 40) / 2, 310, 40, (select == 0) ? GREEN : WHITE);
        DrawText("Seleção de Mapas",
                 g->screenWidth / 2 - MeasureText("Seleção de Mapas", 40) / 2, 380, 40, (select == 1) ? GREEN : WHITE);
        DrawText("Menu Principal",
                 g->screenWidth / 2 - MeasureText("Menu Principal", 40) / 2, 450, 40, (select == 2) ? GREEN : WHITE);


        EndDrawing();


        if(IsKeyPressed(KEY_UP) && select > 0){
            select--;
        }
        if(IsKeyPressed(KEY_DOWN) && select < 2){
            select++;
        }
        if(WindowShouldClose()){
            salvarPlacar(g);
            CloseWindow();
        } 
    }
    if(select == 0){
        if(IsKeyPressed(KEY_ENTER)){
            if(g->curr_map == 0){
                InitGame(g);
                draw_map(g);
                map0_setup(g);
                IniciarPartida(g);
            }
            if(g->curr_map == 1){
                InitGame(g);
                draw_map1(g);
                map1_setup(g);
                IniciarPartida(g);
            }
            
        }
    }
    if(select == 1){
        if(IsKeyPressed(KEY_ENTER)){
            InitGame(g);
            initialScreen(g);
            drawMapScreen(g);
        }
    }
    if(select == 2){
        if(IsKeyPressed(KEY_ENTER)){
            InitGame(g);
            initialScreen(g);
            initialScreen(g);
            nameScreen(g,&g->hero, 1);
            nameScreen(g,&g->hero1, 2);
            drawMapScreen(g);
            vencedor = 0;
            vencedor1 = 0;
        }
    }
}

void drawDrawScreen(Game *g){
            int select = 0;
        
    while(!IsKeyPressed(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        PlayMusicStream(musicaEnd);
        UpdateMusicStream(musicaEnd);
        DrawTexture(abertura, 0,0, WHITE);
        DrawText("EMPATE",
                 (g->screenWidth / 2 - MeasureText("EMPATE", 65) / 2), 50, 65, GOLD);

        DrawText("Placar",
                 (g->screenWidth / 2 - MeasureText("Placar", 55) / 2), 190, 55, BLACK);
        
        DrawText(TextFormat("%d x %d", vencedor1, vencedor), (g->screenWidth / 2 - MeasureText("0 x 0", 45) / 2), 240, 45, BLACK);
        
        

        DrawText("Revanche",
                 g->screenWidth / 2 - MeasureText("Revanche", 40) / 2, 310, 40, (select == 0) ? GREEN : WHITE);
        DrawText("Seleção de Mapas",
                 g->screenWidth / 2 - MeasureText("Seleção de Mapas", 40) / 2, 380, 40, (select == 1) ? GREEN : WHITE);
        DrawText("Menu Principal",
                 g->screenWidth / 2 - MeasureText("Menu Principal", 40) / 2, 450, 40, (select == 2) ? GREEN : WHITE);


        EndDrawing();


        if(IsKeyPressed(KEY_UP) && select > 0){
            select--;
        }
        if(IsKeyPressed(KEY_DOWN) && select < 2){
            select++;
        }
        if(WindowShouldClose()){
            salvarPlacar(g);
            CloseWindow();
        } 
    }
    if(select == 0){
        if(IsKeyPressed(KEY_ENTER)){
            if(g->curr_map == 0){
                InitGame(g);
                draw_map(g);
                map0_setup(g);
                IniciarPartida(g);
            }
            if(g->curr_map == 1){
                InitGame(g);
                draw_map1(g);
                map1_setup(g);
                IniciarPartida(g);
            }
            
        }
    }
    if(select == 1){
        if(IsKeyPressed(KEY_ENTER)){
            InitGame(g);
            initialScreen(g);
            drawMapScreen(g);
        }
    }
    if(select == 2){
        if(IsKeyPressed(KEY_ENTER)){
            InitGame(g);
            initialScreen(g);
            initialScreen(g);
            nameScreen(g,&g->hero, 1);
            nameScreen(g,&g->hero1, 2);
            drawMapScreen(g);
            vencedor = 0;
            vencedor1 = 0;
        }
    }
}


// Draw game (one frame)
void DrawGame(Game *g)
{
    
    if (g->curr_map == 0) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
     
    DrawTexture(fundo, 50,20, WHITE); 
    drawPowerUps(g);
    draw_borders(g);
    draw_map(g);
    draw_bomb(g);
    draw_hero(g);
    DrawTimer(g);
    EndDrawing();
    } else if (g->curr_map == 1) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
     
    DrawTexture(fundo, 50,20, WHITE); 
    drawPowerUps(g);
    draw_borders(g);
    draw_map1(g);
    draw_bomb(g);
    draw_hero(g);
    DrawTimer(g);
    EndDrawing();
    }
    
}

// Update and Draw (one frame)
void UpdateDrawFrame(Game *g)
{
    UpdateGame(g);
    DrawGame(g);
}

