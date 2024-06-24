#include "raylib.h"

#include <iostream>
#include <cstring>

#include "screens.h"

// ---------------------Prototype--------------------- //
// Inicio de sesion

// Cargar archivo
SCREENS DrawCharge(int screenWidth, int screenHeight, char UserName[]);

// Menu del usuario


// ---------------------Functions--------------------- // 

SCREENS DrawCharge(int screenWidth, int screenHeight, char UserName[]){
    
    // Recursos
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");
    short int fontSize = 82;
    short int fontSizeOptions = 52;
    
    // Bienvenido
    char archiveCh[2][30] = {"Bienvenido"};
    strcpy(archiveCh[1],UserName);

    Vector2 archiveChSize = MeasureTextEx(fuente,archiveCh[0],fontSize,1);
    Vector2 archiveChSizeName = MeasureTextEx(fuente,archiveCh[1],fontSize,1);

    Vector2 archiveChV = {((screenWidth / 4) - (archiveChSize.x / 2)), 
                        ((screenHeight / 2) - ((archiveChSize.y + archiveChSizeName.y) / 2) ) };
                        
    Vector2 nameChV = archiveChV;
    nameChV.y += archiveChSize.y;

    // Opciones
    
    // Cargar archivo
    char archiveLd[15] = ("Cargar Archivo");
    Vector2 arch_ld_size = MeasureTextEx(fuente,archiveLd,fontSizeOptions,1.0f);
    Vector2 arch_ld_pos = {(screenWidth - arch_ld_size.x) - (screenWidth * 0.05) ,
                            ((screenHeight / 2) - (arch_ld_size.y / 2)) - arch_ld_size.y};
    Rectangle arch_ld_box = {arch_ld_pos.x,arch_ld_pos.y,
                            arch_ld_size.x,arch_ld_size.y};

    // Salir
    char * exit = ("Salir");
    Vector2 exit_size = MeasureTextEx(fuente,exit,fontSizeOptions,1.0f);
    Vector2 exit_pos = {(screenWidth - exit_size.x) - (screenWidth * 0.05) ,
                        ((screenHeight / 2) - (exit_size.y / 2 )) + exit_size.y};
    Rectangle exit_box = {exit_pos.x,exit_pos.y,
                        exit_size.x,exit_size.y};
    

    SCREENS selection;
    
    bool finish = false;
    Vector2 mouse;
    Vector2 click;

    while (!WindowShouldClose() && finish != true)
    {
        BeginDrawing();
            ClearBackground(WHITE);

            mouse = GetMousePosition();
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                click = mouse;
            }
            
            // Fondo
            // DrawTriangle3D({float(screenWidth*0.7),0},{0,0},{0,720},WHITE);
            
            // Bienvenido
            DrawTextEx(fuente,archiveCh[0],archiveChV,fontSize,1.0f,BLACK);
            DrawTextEx(fuente,archiveCh[1],nameChV,fontSize,1.0f,BLACK);

            // Cargar achivo
            DrawTextEx(fuente,archiveLd,arch_ld_pos,fontSizeOptions,1.0f,BLACK);
            
            if(CheckCollisionPointRec(mouse,arch_ld_box)){
                DrawTextEx(fuente,archiveLd,arch_ld_pos,fontSizeOptions,1.0f,YELLOW);
                if(CheckCollisionPointRec(click,arch_ld_box)){
                    selection = MENU;
                    finish = true;
                }
            }
            

            // Salir
            DrawTextEx(fuente,exit,exit_pos,fontSizeOptions,1.0f,BLACK);
            if(CheckCollisionPointRec(mouse,exit_box)){
                DrawTextEx(fuente,exit,exit_pos,fontSizeOptions,1.0f,YELLOW);
                if(CheckCollisionPointRec(click,arch_ld_box)){
                    selection = EXIT;
                    finish = true;
                }
            }
        EndDrawing();
    }
    return selection;
}

