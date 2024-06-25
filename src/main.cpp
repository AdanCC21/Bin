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

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            arch_name = DrawCharge(screenWidth,screenHeight,"Adan");
            std::cout<<arch_name<<"\n"<<std::endl;
            
        EndDrawing();
    }
    CloseWindow();
}
