#include "raylib.h"

#include <iostream>
#include <cstring>

using std::string;

// ----------------- Prototipos ------------------- //
string DrawCharge(int screenWidth, int screenHeight);

string DrawNew(int screenWidth, int screenHeight, int *p);

SCREENS DrawFailToLoad(int screenWidth, int screenHeight);

// ----------------- Funciones ------------------- //

// Cargar archivo
string DrawCharge(int screenWidth, int screenHeight){
    // -----------------Recursos-----------------

    Font fuente = LoadFont("../assets/Fuentes/arialroundedmtbold.ttf");

    // salida
    char *exit_ch = {"X"};
    Vector2 exit_pos = {screenWidth *0.01, screenHeight *0.01};
    Vector2 exit_size = MeasureTextEx(fuente,exit_ch,EXITSIZE,1.0f);
    Rectangle exit_rec = {exit_pos.x,exit_pos.y,
                        exit_size.x,exit_size.y};

    // -----------------Cuadro de Texto-----------------
    const int MaxChar = 30;
    char arch_ch[MaxChar] = {""};
    int arch_cd = 0;
    bool arch_full = false;

    Rectangle arch_rec;
    arch_rec.width = screenWidth * 0.50;
    arch_rec.height = screenHeight *0.10;
    arch_rec.x = (screenWidth / 2) - (arch_rec.width / 2);
    arch_rec.y = (screenHeight / 2) - (arch_rec.height / 2);

    Vector2 arch_pos;
    arch_pos.x = arch_rec.x + 5;
    arch_pos.y = arch_rec.y + 5;

    // -----------------Boton siguiente-----------------
    char next_ch[10] = {"Siguiente"};
    Vector2 next_size = MeasureTextEx(fuente,next_ch,54,1);
    
    Rectangle next_rec;
    next_rec.width = screenWidth *0.4;
    next_rec.height = screenHeight *0.1;
    next_rec.x = (screenWidth / 2)  -  (next_rec.width / 2);
    next_rec.y = (screenHeight / 2)  - (next_rec.height /2) + (arch_rec.height + (arch_rec.height/2));
    
    Vector2 next_pos;
    next_pos.x = (screenWidth /2 ) - (next_size.x /2);
    next_pos.y = (next_rec.y) + (next_size.y * 0.15);

    // -----------------Texto de instruccion-----------------
    const char * ins_ch = {"Escriba el nombre de su archivo"};
    
    Vector2 ins_size = MeasureTextEx(fuente,ins_ch,64,1);

    Vector2 ins_pos;
    ins_pos.x= (screenWidth / 2) - (ins_size.x /2);
    ins_pos.y = (screenHeight /2 )- (ins_size.y / 2) - (arch_rec.height + (arch_rec.height / 2));

    // -----------------Generales-----------------
    bool finish=false;
    
    Vector2 mouse;
    Vector2 click;

    while(finish == false){
        BeginDrawing();
            ClearBackground(Color{36,36,36,255});

            mouse = GetMousePosition();

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                click = mouse;
            }

            // Salida
            DrawTextEx(fuente,exit_ch,exit_pos,EXITSIZE,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,exit_rec)){
                DrawTextEx(fuente,exit_ch,exit_pos,EXITSIZE,1.0f,Orange);
                if(CheckCollisionPointRec(click,exit_rec)){
                    return "invalid";
                }
            }
            
            // ------------- instruccion -------------//
            DrawTextEx(fuente,ins_ch,ins_pos,64,1,WHITE);

            // -------------Boton siguiente -------------
            DrawRectangleRec(next_rec,BlackItem);

            DrawTextEx(fuente,next_ch,next_pos,54,1.0f,WHITE);

            if(CheckCollisionPointRec(click,next_rec) || IsKeyPressed(KEY_ENTER)){
                if(arch_full == true){
                    finish = true;
                }
                else
                {
                    click = {0,0};
                    // Dibujar una pantalla de favor de ingresar todos los datos
                }
            }
            

            // ------------- Cuadro de texto -----------------s
            
            DrawRectangleRec(arch_rec,BlackItem);
            
            DrawTextEx(fuente,arch_ch,arch_pos,34,1.0f,WHITE);

            if(CheckCollisionPointRec(click,arch_rec)){
            
                DrawRectangleRec(arch_rec,BlackItemBright);
                DrawTextEx(fuente,arch_ch,arch_pos,34,1.0f,WHITE);
                int key = GetCharPressed();
                
                while (key > 0)
                {
                    if ((key >= 48) && (key <= 125) && (arch_cd <MaxChar)) 
                    {
                        arch_ch[arch_cd] = (char)key; 
                        arch_ch[arch_cd+1] = '\0'; 
                        arch_cd++; 
                        arch_full = true;
                    }
                    key = GetCharPressed();  
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if(arch_cd <=1){
                        arch_full=false;
                    }
                    if (arch_cd <= 0){
                    } else{
                        arch_cd--;   
                        arch_ch[arch_cd] = '\0'; 
                    }
                }
            }
            
            // --------------------------------

        EndDrawing();
    }
    strcat(arch_ch,".dll");
    string archive = arch_ch;

    UnloadFont(fuente);
    return archive;
}

// Nuevo archivo
string DrawNew(int screenWidth, int screenHeight, int *p){
    // -----------------Recursos-----------------

    Font fuente = LoadFont("../assets/Fuentes/arialroundedmtbold.ttf");

    // salida
    char *exit_ch = {"X"};
    Vector2 exit_pos = {screenWidth *0.01, screenHeight *0.01};
    Vector2 exit_size = MeasureTextEx(fuente,exit_ch,EXITSIZE,1.0f);
    Rectangle exit_rec = {exit_pos.x,exit_pos.y,
                        exit_size.x,exit_size.y};

    // -----------------Cuadro de Texto-----------------
    const int MaxChar = 30;
    char arch_ch[MaxChar] = {""};
    int arch_cd = 0;
    bool arch_full = false;

    Rectangle arch_rec;
    arch_rec.width = screenWidth * 0.50;
    arch_rec.height = screenHeight *0.10;
    arch_rec.x = (screenWidth / 2) - (arch_rec.width / 2);
    arch_rec.y = (screenHeight / 2) - (arch_rec.height / 2);

    Vector2 arch_pos;
    arch_pos.x = arch_rec.x + 5;
    arch_pos.y = arch_rec.y + 5;

    // -----------------Boton siguiente-----------------
    char next_ch[10] = {"Siguiente"};
    Vector2 next_size = MeasureTextEx(fuente,next_ch,54,1);
    
    Rectangle next_rec;
    next_rec.width = screenWidth *0.4;
    next_rec.height = screenHeight *0.1;
    next_rec.x = (screenWidth / 2)  -  (next_rec.width / 2);
    next_rec.y = (screenHeight / 2)  - (next_rec.height /2) + (arch_rec.height + (arch_rec.height/2));
    
    Vector2 next_pos;
    next_pos.x = (screenWidth /2 ) - (next_size.x /2);
    next_pos.y = (next_rec.y) + (next_size.y * 0.15);

    // -----------------Texto de instruccion-----------------
    const char * ins_ch = {"Escriba el nombre de su nuevo archivo"};
    
    Vector2 ins_size = MeasureTextEx(fuente,ins_ch,64,1);

    Vector2 ins_pos;
    ins_pos.x= (screenWidth / 2) - (ins_size.x /2);
    ins_pos.y = (screenHeight /2 )- (ins_size.y / 2) - (arch_rec.height + (arch_rec.height / 2));

    // -----------------Generales-----------------
    bool finish=false;
    
    Vector2 mouse;
    Vector2 click;

    while(finish == false){
        BeginDrawing();
            ClearBackground(Color{36,36,36,255});

            mouse = GetMousePosition();

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                click = mouse;
            }
            
            // Salida
            DrawTextEx(fuente,exit_ch,exit_pos,EXITSIZE,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,exit_rec)){
                DrawTextEx(fuente,exit_ch,exit_pos,EXITSIZE,1.0f,Orange);
                if(CheckCollisionPointRec(click,exit_rec)){
                    return "invalid";
                }
            }

            // ------------- instruccion -------------//
            DrawTextEx(fuente,ins_ch,ins_pos,64,1,WHITE);

            // -------------Boton siguiente -------------
            DrawRectangleRec(next_rec,BlackItem);

            DrawTextEx(fuente,next_ch,next_pos,54,1.0f,WHITE);

            if(CheckCollisionPointRec(click,next_rec) || IsKeyPressed(KEY_ENTER)){
                if(arch_full == true){
                    finish = true;
                }
                else
                {
                    click = {0,0};
                    // Dibujar una pantalla de favor de ingresar todos los datos
                }
            }
            

            // ------------- Cuadro de texto -----------------s
            
            DrawRectangleRec(arch_rec,BlackItem);
            
            DrawTextEx(fuente,arch_ch,arch_pos,34,1.0f,WHITE);

            if(CheckCollisionPointRec(click,arch_rec)){
            
                DrawRectangleRec(arch_rec,BlackItemBright);
                DrawTextEx(fuente,arch_ch,arch_pos,34,1.0f,WHITE);
                int key = GetCharPressed();
                
                while (key > 0)
                {
                    if ((key >= 48) && (key <= 125) && (arch_cd <MaxChar)) 
                    {
                        arch_ch[arch_cd] = (char)key; 
                        arch_ch[arch_cd+1] = '\0'; 
                        arch_cd++; 
                        arch_full = true;
                    }
                    key = GetCharPressed();  
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if(arch_cd <=1){
                        arch_full=false;
                    }
                    if (arch_cd <= 0){
                    } else{
                        arch_cd--;   
                        arch_ch[arch_cd] = '\0'; 
                    }
                }
            }
            
            // --------------------------------

        EndDrawing();
    }
    strcat(arch_ch,".dll");
    string archive = arch_ch;
    bin_create(p, arch_ch);
    
    UnloadFont(fuente);
    return archive;
}

// Fallo al cargar
SCREENS DrawFailToLoad(int screenWidth, int screenHeight){
    // ---------- Recursos ----------
    Font fuente = LoadFont("../assets/Fuentes/arialroundedmtbold.ttf");

    // ---------- texto ----------
    const char *fail_ch = {"Archivo no encontrado o nombre invalido"};
    Vector2 fail_size = MeasureTextEx(fuente,fail_ch,64,1);
    Vector2 fail_pos = {(screenWidth /2) - (fail_size.x /2), (screenHeight / 2) - (fail_size.y / 2)};

    // ---------- Generales ----------
    // Tiempo
    float timetolive=1.5f;
    float actualtime=0.0f;

    while(actualtime <=timetolive){
        BeginDrawing();
            actualtime +=GetFrameTime();
            ClearBackground(BlackBackgdround);
            DrawTextEx(fuente,fail_ch,fail_pos,64,1,WHITE);
        EndDrawing();
    }
    return MENU;
}
