#include "raylib.h"

#include <iostream>
#include <cstring>

using std::string;

#include "screens.h"
#include "logic.h"

#define EXITSIZE 64



// ---------------------Prototype--------------------- //

// MENU
SCREENS DrawMenu(int screenWidth, int screenHeight, char UserName[]);

// Cargar archivo
string DrawCharge(int screenWidth, int screenHeight);

// Dibujar fallo al cargar
SCREENS DrawFailToLoad(int screenWidth, int screenHeight);

// Mostrar informacion
SCREENS DrawShow(int screenWidth, int screenHeight, string arch_name);

// Agregar registro
SCREENS DrawAdd(int screenWidth, int screenHeight, string arhc_name, int *p);

// Ultima pantalla
void DrawExit(int screenWidht, int screenHeight);
// ---------------------Functions--------------------- // 

// MENU
SCREENS DrawMenu(int screenWidth, int screenHeight, char UserName[]){
    
    // Recursos
    Font fuente = LoadFont("../assets/Fuentes/arialroundedmtbold.ttf");
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
                            screenHeight *0.3};
    Rectangle arch_ld_box = {arch_ld_pos.x,arch_ld_pos.y,
                            arch_ld_size.x,arch_ld_size.y};

    // Crear archivo
    char *create_ch = ("Nuevo archivo");
    Vector2 create_size = MeasureTextEx(fuente,create_ch,fontSizeOptions,1.0f);
    Vector2 create_pos = {(screenWidth - create_size.x) - (screenWidth * 0.05), 
                        screenHeight*0.5};

    Rectangle create_rec;
    create_rec.x = create_pos.x;
    create_rec.y = create_pos.y;
    create_rec.width = create_size.x;
    create_rec.height = create_size.y;

    // Salir
    char * exit = ("Salir");
    Vector2 exit_size = MeasureTextEx(fuente,exit,fontSizeOptions,1.0f);
    Vector2 exit_pos = {(screenWidth - exit_size.x) - (screenWidth * 0.05) ,
                        screenHeight *0.7};
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
                if(CheckCollisionPointRec(click,arch_ld_box)){
                    nextScreen = LOAD;
                    finish = true;
                }
            }
            
            
            // Crear archivo
            DrawTextEx(fuente,create_ch,create_pos,fontSizeOptions,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,create_rec)){
                
                DrawTextEx(fuente,create_ch,create_pos,fontSizeOptions,1.0f,Orange);
                
                if(CheckCollisionPointRec(click,create_rec)){
                    nextScreen = CREATE;
                    finish = true; 
                }
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

// Mostrar informacion
SCREENS DrawShow(int screenWidth, int screenHeight, string arch_name){
    //-------------- Recursos --------------//
    Font fuente = LoadFont("../assets/Fuentes/arialroundedmtbold.ttf");

    // Altura default del conteido
    int const content_size = 24;
    // Altura de la fuente
    Vector2 fuente_size = MeasureTextEx(fuente,"",content_size,1);

    // --------- Archivos Backend ---------//
    Tdata temp; // base donde se almacenara los campos
    const char *arch = arch_name.c_str(); // Nombre del archivo
    FILE *doc = fopen(arch,"rb"); // abrir el archivo

    // --------- Cabezera ---------//
    Vector2 head_pos = {0,0};

    Rectangle head_rec;
    head_rec.width = screenWidth;
    head_rec.height = screenHeight *0.05;
    head_rec.x = head_pos.x;
    head_rec.y = head_pos.y;

    // Indice
    char *indi_head = {"No."};    
    Vector2 indi_head_pos = {0,0};

    // Lugar
    char *place_head = {"Place"};
    Vector2 place_head_pos = {screenWidth *0.05,0};

    // Contraseña
    char *pass_head = {"Passwoard"};
    Vector2 pass_head_pos = {screenWidth *0.27,0 };

    // Nota
    char *note_head = {"Note"};
    Vector2 note_head_pos = {screenWidth*0.54,0};
    
    // --------- Archivos Fronted ---------//
    int indice = 0;
    char indi_ch[1];
    Vector2 indice_pos = {0,(head_rec.y + head_rec.height)};
    // Tomara 1% del screenwidth

    // Lugar de la contraseña
    char place_ch[50];
    Vector2 place_pos = {screenWidth *0.05, (head_rec.y + head_rec.height)};
    // Tomara 25% del width

    // Contraseñas
    char pass_ch[50];
    Vector2 pass_pos = {screenWidth *0.27,(head_rec.y + head_rec.height)};
    // Tomara 25% del width

    // Nota
    char note_ch[50];
    Vector2 note_pos = {screenWidth *0.54,(head_rec.y + head_rec.height)};

    // -----------------Botones-----------------
    int txbt_size = 54;
    // Agregar----------
    char add_ch[20] = {"Agregar"};

    Rectangle add_rec;
    add_rec.x=screenWidth *0.8;
    add_rec.y=screenHeight *0.1;
    add_rec.width=screenWidth*0.2;
    add_rec.height=screenHeight*0.1;

    Vector2 add_pos;
    add_pos.x = add_rec.x + 10;
    add_pos.y = add_rec.y + 10;
    
    // Eliminar ----------
    char del_ch[20] = {"Eliminar"};

    Rectangle delete_rec;
    delete_rec.x=add_rec.x;
    delete_rec.y=screenHeight *0.3;
    delete_rec.width=add_rec.width;
    delete_rec.height=screenHeight*0.1;

    Vector2 del_pos = {delete_rec.x +10, delete_rec.y+10};

    // Editar ----------
    char edit_ch[20] = {"Editar"};

    Rectangle edite_rec;
    edite_rec.x=add_rec.x;
    edite_rec.y=screenHeight *0.5;
    edite_rec.width=add_rec.width;
    edite_rec.height=screenHeight*0.1;

    Vector2 edit_pos = {edite_rec.x +10 , edite_rec.y + 10};

    // Salir ----------
    char return_ch[20] = {"Salir"};

    Rectangle return_rec;
    return_rec.x=screenWidth *0.9;
    return_rec.y=screenHeight *0.8;
    return_rec.width=screenWidth*0.1;
    return_rec.height=screenHeight*0.1;
    
    Vector2 return_pos = {return_rec.x +10, return_rec.y +10};


    // ---------Generales ---------- //
    Rectangle border;
    border.x= screenWidth * 0.75;
    border.y=0;
    border.width= screenWidth - (border.x);
    border.height = screenHeight;

    bool finish = false;

    Vector2 mouse;
    Vector2 click;

    while(finish == false){
        BeginDrawing();
            mouse= GetMousePosition();

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                click=mouse;
            }

            ClearBackground(BlackBackgdround);
            DrawRectangleRec(border,BlackItem);

            // ------------Botones------------
            // Agregar
            DrawTextEx(fuente,add_ch,add_pos,txbt_size,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,add_rec)){
                DrawTextEx(fuente,add_ch,add_pos,txbt_size,1.0f,Orange);
                if(CheckCollisionPointRec(click,add_rec)){
                    return ADD;
                }
            }

            // Eliminar
            DrawTextEx(fuente, del_ch, del_pos,txbt_size,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,delete_rec)){
                DrawTextEx(fuente, del_ch, del_pos,txbt_size,1.0f,Orange);
                if(CheckCollisionPointRec(click,delete_rec)){
                    return DELETE;
                }
            }
            
            // Editar
            // DrawRectangleRec(edite_rec,WHITE);
            DrawTextEx(fuente,edit_ch,edit_pos,txbt_size,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,edite_rec)){
                
                DrawTextEx(fuente,edit_ch,edit_pos,txbt_size,1.0f,Orange);
                if(CheckCollisionPointRec(click,edite_rec)){
                    return EDIT;
                }
            }

            // Salir
            // DrawRectangleRec(return_rec,WHITE);
            DrawTextEx(fuente,return_ch,return_pos,txbt_size,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,return_rec)){
                
                DrawTextEx(fuente,return_ch,return_pos,txbt_size,1.0f,Orange);
                if(CheckCollisionPointRec(click,return_rec)){
                    return MENU;
                }
            }
            
            // Cabezera
            {
                DrawRectangleRec(head_rec,BlackItem);
                DrawTextEx(fuente,indi_head,indi_head_pos,content_size,1,Orange);
                DrawTextEx(fuente,place_head,place_head_pos,content_size,1,Orange);
                DrawTextEx(fuente,pass_head,pass_head_pos,content_size,1,Orange);
                DrawTextEx(fuente,note_head,note_head_pos,content_size,1,Orange);
            }

            // Reiniciamos posiciones
            indice_pos = {0,(head_rec.y + head_rec.height)};
            place_pos = {float(screenWidth *0.05), (head_rec.y + head_rec.height)};
            pass_pos = {float(screenWidth *0.27),(head_rec.y + head_rec.height)};
            note_pos = {float(screenWidth *0.54),(head_rec.y + head_rec.height)};
            
            while(fread(&temp,sizeof(Tdata),1,doc))
            {
                indice = temp.ind;
                itoa(indice,indi_ch,10);

                strcpy(place_ch,temp.place);
                strcpy(pass_ch,temp.pas);
                strcpy(note_ch,temp.note);

                DrawTextEx(fuente,indi_ch,indice_pos,content_size,1,WHITE);
                DrawTextEx(fuente,place_ch,place_pos,content_size,1,WHITE);
                DrawTextEx(fuente,pass_ch,pass_pos,content_size,1,WHITE);
                DrawTextEx(fuente,note_ch,note_pos,content_size,1,WHITE);

                indice_pos.y+=fuente_size.y;
                place_pos.y += fuente_size.y;
                pass_pos.y+= fuente_size.y;
                note_pos.y+=fuente_size.y;
            }
            fseek(doc,0,SEEK_SET);// Reposicionar al inicio

        EndDrawing();
    }
}

// Agregar registro
SCREENS DrawAdd(int screenWidth, int screenHeight, string arhc_name, int *p){
    // ------------------ Recursos ------------------
    Font fuente = LoadFont("../assets/Fuentes/arialroundedmtbold.ttf");

    const int inputx = 24;
    const int inputitle = 54;

    // salida
    char *exit_ch = {"X"};
    Vector2 exit_pos = {screenWidth *0.01, screenHeight *0.01};
    Vector2 exit_size = MeasureTextEx(fuente,exit_ch,EXITSIZE,1.0f);
    Rectangle exit_rec = {exit_pos.x,exit_pos.y,
                        exit_size.x,exit_size.y};

    // ------------------ Botones ------------------

    // Lugar ------------------
    const char *place_ch = {"Lugar"};

    Vector2 place_size = MeasureTextEx(fuente,place_ch,inputitle,1.0f);

    Rectangle place_rec;
    place_rec.x = screenWidth *0.1;
    place_rec.y = screenHeight *0.2;
    place_rec.width = screenWidth *0.3;
    place_rec.height = screenHeight *0.1;

    Vector2 place_pos = {place_rec.x, place_rec.y};
    Vector2 title_place_pos = {place_rec.x, place_rec.y-place_size.y};
    
    // Contraseña ---------
    const char *pass_ch = {"Passwoard"};
    Vector2 pass_size  = MeasureTextEx(fuente,pass_ch,inputitle,1.0f);

    Rectangle pass_rec;
    pass_rec.x = screenWidth *0.6;
    pass_rec.y = screenHeight *0.2;
    pass_rec.width = screenWidth *0.3;
    pass_rec.height = screenHeight *0.1;

    Vector2 pass_pos = {pass_rec.x,pass_rec.y};
    Vector2 title_pass_pos = {pass_rec.x, pass_rec.y - pass_size.y};
    
    // Note ---------
    const char *note_ch = {"Nota"};
    Vector2 note_size = MeasureTextEx(fuente,note_ch,inputitle,1.0f);

    Rectangle note_rec;
    note_rec.x = screenWidth *0.25;
    note_rec.y = screenHeight *0.6;
    note_rec.width = screenWidth *0.50;
    note_rec.height = screenHeight *0.2;

    Vector2 note_pos = {note_rec.x,note_rec.y};
    Vector2 title_note_pos = {note_rec.x, note_rec.y - note_size.y};

    // --------- Boton siguiente -------- //
    char next_ch[20] = {"Continuar"};

    Vector2 next_size = MeasureTextEx(fuente,next_ch,64,1.0f);

    Vector2 next_pos = {(screenWidth / 2) - (next_size.x / 2), (screenHeight *0.9 - (next_size.y / 2))};
    
    Rectangle next_rec;
    next_rec.x = next_pos.x;
    next_rec.y = next_pos.y;
    next_rec.width = next_size.x;
    next_rec.height = next_size.y;

    // ------------------ Logicos ------------------
    char place[MAXCHAR] = {""};
    int placeCount = 0;
    bool placeFull = false;

    char pass[MAXCHAR] = {""};
    int passCount = 0;
    bool passFull = false;

    char note[MAXCHAR] = {""};
    int noteCount = 0;
    bool noteFull = false;

    // ------------------ Generales ------------------
    Vector2 mouse;
    Vector2 click;

    bool finish = false;
    while (finish == false)
    {
        BeginDrawing();
        mouse = GetMousePosition();
            ClearBackground(BlackBackgdround);

            // Salida
            DrawTextEx(fuente,exit_ch,exit_pos,EXITSIZE,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,exit_rec)){
                DrawTextEx(fuente,exit_ch,exit_pos,EXITSIZE,1.0f,Orange);
                if(CheckCollisionPointRec(click,exit_rec)){
                    return SHOW;
                }
            }

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                click = mouse;
            }

            // Boton de place
            DrawTextEx(fuente,place_ch,title_place_pos,inputitle,1.0f,WHITE);
            DrawRectangleRec(place_rec,BlackItem);
            
            DrawTextEx(fuente,place,place_pos,inputx,1.0f,WHITE);
            if(CheckCollisionPointRec(click,place_rec)){
                
                DrawRectangleRec(place_rec,BlackItemBright);
                DrawTextEx(fuente,place,place_pos,inputx,1.0f,WHITE);
                
                int key = GetCharPressed();
                
                while (key > 0)
                {
                    if ((key >= 48) && (key <= 125) && (placeCount <MAXCHAR)) 
                    {
                        place[placeCount] = (char)key; 
                        place[placeCount+1] = '\0'; 
                        placeCount++; 
                        placeFull = true;
                    }
                    key = GetCharPressed();  
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if(placeCount <=1){
                        placeFull=false;
                    }
                    if (placeCount <= 0){
                    } else{
                        placeCount--;   
                        place[placeCount] = '\0'; 
                    }
                }
            }
            
            // Pass
            DrawTextEx(fuente,pass_ch,title_pass_pos,inputitle,1.0f,WHITE);
            DrawRectangleRec(pass_rec,BlackItem);

            DrawTextEx(fuente,pass,pass_pos,inputx,1.0f,WHITE);
            if(CheckCollisionPointRec(click,pass_rec)){
                
                DrawRectangleRec(pass_rec,BlackItemBright);
                DrawTextEx(fuente,pass,pass_pos,inputx,1.0f,WHITE);
                
                int key = GetCharPressed();;
                
                while (key > 0)
                {
                    if ((key >= 48) && (key <= 125) && (passCount <MAXCHAR)) 
                    {
                        pass[passCount] = (char)key; 
                        pass[passCount+1] = '\0'; 
                        passCount++; 
                        passFull = true;
                    }
                    key = GetCharPressed();  
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if(passCount <=1){
                        passFull=false;
                    }
                    if (passCount <= 0){
                    } else{
                        passCount--;   
                        pass[passCount] = '\0'; 
                    }
                }
            }
            
            // Note
            DrawTextEx(fuente,note_ch,title_note_pos,inputitle,1.0f,WHITE);
            DrawRectangleRec(note_rec,BlackItem);

            DrawTextEx(fuente,note,note_pos,inputx,1.0f,WHITE);
            if(CheckCollisionPointRec(click,note_rec)){
                
                DrawRectangleRec(note_rec,BlackItemBright);
                DrawTextEx(fuente,note,note_pos,inputx,1.0f,WHITE);
                int key = GetCharPressed();;
                
                while (key > 0)
                {
                    if ((key >= 48) && (key <= 125) && (noteCount <MAXCHAR)) 
                    {
                        note[noteCount] = (char)key; 
                        note[noteCount+1] = '\0'; 
                        noteCount++; 
                        noteFull = true;
                    }
                    key = GetCharPressed();  
                }
                if (IsKeyPressed(KEY_BACKSPACE)) 
                {
                    if(noteCount <=1){
                        noteFull=false;
                    }
                    if (noteCount <= 0){
                    } else{
                        noteCount--;   
                        note[noteCount] = '\0'; 
                    }
                }
            }

            // Continuar
            DrawTextEx(fuente,next_ch,next_pos,64,1.0f,WHITE);
            if(CheckCollisionPointRec(mouse,next_rec)){
                DrawTextEx(fuente,next_ch,next_pos,64,1.0f,Orange);

                if(CheckCollisionPointRec(click,next_rec)){
                    
                    if(placeFull== true && passFull == true){
                        const char *arch = arhc_name.c_str();
                        load(p,arch,place,pass,note);
                        return SHOW;
                    }
                    else
                    {
                        float timetolive = 1.5f;
                        float actualTime =0.0f;
                        
                        char *please_ch = {"Porfavor llena los campos necesarios"};
                        Vector2 please_size = MeasureTextEx(fuente,please_ch, 64,1.0f);

                        Vector2 please_pos = {(screenWidth /2) - (please_size.x/2), (screenHeight /2) - (please_size.y / 2)};
                        while(actualTime < timetolive){
                            BeginDrawing();
                                ClearBackground(BlackBackgdround);
                                actualTime+= GetFrameTime();
                                
                                DrawTextEx(fuente,please_ch,please_pos,64,1.0f,WHITE);
                                click = {0,0};
                            EndDrawing();
                        }
                    }
                }
            }

        EndDrawing();
    }
    
}

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

// Salida
void DrawExit(int screenWidht, int screenHeight){
    //-------------- Recursos --------------//
    Font fuente = LoadFont("../assets/Fuentes/arialroundedmtbold.ttf");

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
