#include "raylib.h"
#include "raygui.h"

#include "./headers/startScreens.h"

int main(){
    // Screen size
    int screenWidth = 1280;
    int screenHeight = 720;

    // Inits
    InitWindow(1280,720,"BIN");
    InitAudioDevice();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawCharge(screenWidth,screenHeight,"Adan");
            
        EndDrawing();
    }
    CloseWindow();
}
