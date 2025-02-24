#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "jogo.h"

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


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    Game game;
    game.screenWidth = 800;
    game.screenHeight = 600;

    vencedor = 0;
    vencedor1 = 0;

    InitWindow(game.screenWidth, game.screenHeight, "SuperBomberman 2.0F");
    chaves = LoadTexture("images/chaves.png");
    kiko = LoadTexture("images/kiko.png");
    madruga = LoadTexture("images/madruga.png");
    barriga = LoadTexture("images/barriga.png");
    barril = LoadTexture("images/barril.png");
    bola = LoadTexture("images/bola.png");
    chapeu = LoadTexture("images/chapeu.png");
    maleta = LoadTexture("images/maleta.png");
    bomba = LoadTexture("images/bomba.png");
    explosion_right = LoadTexture("images/explosion_right.png");
    bombaExtra = LoadTexture("images/bombaExtra.png");
    velocidade = LoadTexture("images/velocidade.png");
    raio = LoadTexture("images/raio.png");
    abertura = LoadTexture("images/abertura.png");
    campeao = LoadTexture("images/campeao.png");
    borda_sup_inf = LoadTexture("images/borda_sup_inf.png");
    bordaLateral = LoadTexture("images/bordaaLateral.png");
    fundo = LoadTexture("images/fundo.png");
    SetTargetFPS(120);
    
    SetTargetFPS(120);

    InitAudioDevice();
   
    musicaInit = LoadMusicStream("musics/musicInit.mp3");
    musicaPlay = LoadMusicStream("musics/musicaGame.mp3");
    musicaEnd = LoadMusicStream("musics/musicEnd.mp3");
    bomb = LoadMusicStream("musics/sound_bomb.mp3");

    
    
    PlayMusicStream(musicaPlay);
    PlayMusicStream(bomb);
    

    InitGame(&game);
    initialScreen(&game);
    nameScreen(&game,&game.hero, 1);
    nameScreen(&game,&game.hero1, 2);
    drawMapScreen(&game);
    
    
    while(!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        UpdateDrawFrame(&game);
        UpdateMusicStream(musicaPlay);
        if(game.gameover){
            drawDrawScreen(&game);
        }
        
    }

    
    

    UnloadTexture(chaves);
    UnloadTexture(kiko);
    UnloadTexture(madruga);
    UnloadTexture(barriga);
    UnloadTexture(barril);
    UnloadTexture(bola);
    UnloadTexture(chapeu);
    UnloadTexture(maleta);
    UnloadTexture(bomba);
    UnloadTexture(bombaExtra);
    UnloadTexture(velocidade);
    UnloadTexture(raio);
    UnloadTexture(abertura);
    UnloadTexture(campeao);
    UnloadTexture(borda_sup_inf);
    UnloadTexture(bordaLateral);
    UnloadTexture(fundo);


    UnloadMusicStream(musicaInit);
    UnloadMusicStream(musicaEnd);
    UnloadMusicStream(bomb);
    UnloadMusicStream(musicaPlay);
    return 0;
}


