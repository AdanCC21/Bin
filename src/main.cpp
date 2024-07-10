#include "raylib.h"

#include "./headers/startScreens.h"

int main(){
    // Screen size
    int screenWidth = 1280;
    int screenHeight = 720;

    // Inits
    InitWindow(1280,720,"BIN");
    Image icono = LoadImage("../assets/icono/icono.png");
    SetWindowIcon(icono);
    InitAudioDevice();


    string arch_name; // Nombre del archivo cargado
    int p; // Posiciones cargadas, enviala con &
    bool charged = false;
    
    SCREENS currentScreen = MENU;
    bool finish = false;

    while (!WindowShouldClose() && finish == false)
    {
        switch (currentScreen)
        {
        case MENU:
        {
            currentScreen = DrawMenu(screenWidth,screenHeight,"Adan");
            break;
        }
        case LOAD:
        {
            arch_name = DrawCharge(screenWidth,screenHeight);
            charged = charge(arch_name,&p);
            if(charged == true){
                currentScreen = SHOW;
            }
            else
            {
                currentScreen = DrawFailToLoad(screenWidth,screenHeight);
            }
            break;
        }
        case SHOW:
        {
            DrawShow(screenWidth,screenHeight,arch_name);
            currentScreen = MENU;
            break;
        }
        case EXIT:
        {
            DrawExit(screenWidth,screenHeight);
            finish = true;
            break;
        }
        default:
            break;
        }
    }
    CloseWindow();
}
