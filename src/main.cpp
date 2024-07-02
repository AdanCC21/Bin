#include "raylib.h"

// El rayGui se queda en screens.h por un problema de redefinicion

#include "./headers/startScreens.h"

int main(){
    // Screen size
    int screenWidth = 1280;
    int screenHeight = 720;

    // Inits
    InitWindow(1280,720,"BIN");
    InitAudioDevice();

    char *arch_name;

    
    SCREENS currentScreen = MENU;
    bool finish = false;

    while (!WindowShouldClose() && finish == false)
    {
        switch (currentScreen)
        {
        case MENU:
        {
            currentScreen = DrawCharge(screenWidth,screenHeight,"Adan");
            break;
        }
        case CHARGE:
        {
            
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
