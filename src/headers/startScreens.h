#include "raylib.h"

#include <iostream>
#include <cstring>

using std::string;

#include "screens.h"
#include "logic.h"

// ---------------------Prototype--------------------- //
// Inicio de sesion

// MENU
SCREENS DrawMenu(int screenWidth, int screenHeight, char UserName[]);

// Dibujar cargado
string DrawCharge(int screenWidth, int screenHeight);

// Dibujar fallo al cargar
SCREENS DrawFailToLoad(int screenWidth, int screenHeight);

// Ultima pantalla
void DrawExit(int screenWidht, int screenHeight);
// ---------------------Functions--------------------- // 

// MENU
SCREENS DrawMenu(int screenWidth, int screenHeight, char UserName[]){
    
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
    
    bool finish = false;
    Vector2 mouse;
    Vector2 click;

    SCREENS nextScreen;

    while (finish != true)
    {
        BeginDrawing();
            ClearBackground(BlackBackgdround);

            mouse = GetMousePosition();
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                click = mouse;
            }
            
            // Fondo
            // DrawTriangle3D({float(screenWidth*0.7),0},{0,0},{0,720},WHITE);
            
            // Bienvenido
            DrawTextEx(fuente,archiveCh[0],archiveChV,fontSize,1.0f,WHITE);
            DrawTextEx(fuente,archiveCh[1],nameChV,fontSize,1.0f,WHITE);

            // Cargar achivo
            DrawTextEx(fuente,archiveLd,arch_ld_pos,fontSizeOptions,1.0f,WHITE);
            
            if(CheckCollisionPointRec(mouse,arch_ld_box)){
                DrawTextEx(fuente,archiveLd,arch_ld_pos,fontSizeOptions,1.0f,Orange);
            }
            
            if(CheckCollisionPointRec(click,arch_ld_box)){
                nextScreen = LOAD;
                finish = true;
            }
            

            // Salir
            DrawTextEx(fuente,exit,exit_pos,fontSizeOptions,1.0f,WHITE);
            
            if(CheckCollisionPointRec(mouse,exit_box)){
                DrawTextEx(fuente,exit,exit_pos,fontSizeOptions,1.0f,Orange);
                
                if(CheckCollisionPointRec(click,exit_box)){
                    nextScreen = EXIT;
                    finish = true;
                }
            }
            

        EndDrawing();
    }
    return nextScreen;
}

// Fallo al cargar
SCREENS DrawFailToLoad(int screenWidth, int screenHeight){
    // ---------- Recursos ----------
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    // ---------- texto ----------
    const char *fail_ch = {"Archivo no encontrado"};
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

// Cargar archivo
string DrawCharge(int screenWidth, int screenHeight){
    // -----------------Recursos-----------------

    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

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
            
            // ------------- instruccion -------------//
            DrawTextEx(fuente,ins_ch,ins_pos,64,1,WHITE);

            // -------------Boton siguiente -------------
            DrawRectangleRec(next_rec,Color{41,41,41,255});

            DrawTextEx(fuente,next_ch,next_pos,54,1.0f,WHITE);

            if(CheckCollisionPointRec(click,next_rec)){
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
            
            DrawRectangleRec(arch_rec,Color{41,41,41,255});
            
            DrawTextEx(fuente,arch_ch,arch_pos,34,1.0f,WHITE);

            if(CheckCollisionPointRec(click,arch_rec)){
                int key = GetCharPressed();
                
                std::cout<<arch_ch<<std::endl;
                
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

// Salida
void DrawExit(int screenWidht, int screenHeight){
    //-------------- Recursos --------------//
    Font fuente = LoadFont("../assets/Fuentes/TangoSans.ttf");

    // --------------Adios --------------//
    char bye[10] = {"Adios"};
    Vector2 ByeSize = MeasureTextEx(fuente,bye,64,1);
    Vector2 ByeV = {(screenWidht/2) - (ByeSize.x /2), (screenHeight / 2) - (ByeSize.y / 2)};
    
    // Tiempo
    float timetolive=1.5f;
    float actualtime=0.0f;

    while(actualtime <=timetolive){
        BeginDrawing();
            actualtime+=GetFrameTime();
            ClearBackground(BlackBackgdround);
            DrawTextEx(fuente,bye,ByeV,64,1.0f,WHITE);
        EndDrawing();
    }
   
}

void DrawShow(int screenWidth, int screenHeight, string arch_name){
    
    // --------- Archivos Backend ---------//
    Tdata temp; // base donde se almacenara los campos
    const char *arch = arch_name.c_str(); // Nombre del archivo
    FILE *doc = fopen(arch,"rb"); // abrir el archivo

    // --------- Archivos Fronted ---------//
    

    // ---------Generales ---------- //
    bool finish = false;
    while(finish == false){
        BeginDrawing();

        EndDrawing();
    }
}
