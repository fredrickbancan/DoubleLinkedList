#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include "DoubleLinkedList.h"
#include <iostream>
int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Fredrick - Double Linked List");
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawText("Double Linked List", 325, 10, 20, BLACK);
        GuiButton(Rectangle{ 350, 340, 115, 20 }, "Add to Front of List");
        GuiButton(Rectangle{ 350, 360, 115, 20 }, "Add to Back of List");
        GuiButton(Rectangle{ 350, 380, 115, 20 }, "Insert after node");
        GuiButton(Rectangle{ 350, 400, 115, 20 }, "Insert before node");
        GuiButton(Rectangle{ 372, 420, 70, 20 }, "Sort List");
        //TODO: draw list and impliment buttons
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    system("PAUSE");
    return 0;
}