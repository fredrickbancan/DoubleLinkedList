#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include "DoubleLinkedList.h"
#include <iostream>
#include <string>


/*Draws the provided array of ints representing a doubly linked list as nodes as gui buttons.
  Buttons are used so they can be selected for insertions.*/
void drawDLLNodes(bool* nodeButtons, const int* intList, int count);

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    //initializing DLL to have just one node
    DoubleLinkedList* theList= new DoubleLinkedList(53,1);

    bool* nodeButtons = nullptr;

    //Booleans for detecting button presses
    bool buttonAddToFrontPressed = false;
    bool buttonAddToBackPressed = false;
    bool buttonInsertAfterNodePressed = false;
    bool buttonInsertBeforeNodePressed = false;
    bool buttonSortPressed = false;
    
    //will be true if int array representing nodes needs to be rebuilt
    bool listNeedsRefresh = true;

    //int array representing nodes and node values in the dll
    int* listInts = nullptr;

    InitWindow(screenWidth, screenHeight, "Fredrick - Double Linked List (Integers)");
    //--------------------------------------------------------------------------------------

    //initialize arrays
    listInts = theList->toIntArray();
    nodeButtons = new bool[theList->getCount()]{ false };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        //Update button booleans
        buttonAddToFrontPressed = GuiButton(Rectangle{ 350, 340, 115, 20 }, "Add to Front of List");
        buttonAddToBackPressed= GuiButton(Rectangle{ 350, 360, 115, 20 }, "Add to Back of List");
        buttonInsertAfterNodePressed = GuiButton(Rectangle{ 350, 380, 115, 20 }, "Insert after node");
        buttonInsertBeforeNodePressed = GuiButton(Rectangle{ 350, 400, 115, 20 }, "Insert before node");
        buttonSortPressed = GuiButton(Rectangle{ 372, 420, 70, 20 }, "Sort List");

        //rebuild int array if needed
        if (listNeedsRefresh)
        {
            delete[] nodeButtons;
            delete[] listInts;
            listInts = theList->toIntArray();
            nodeButtons = new bool[theList->getCount()]{ false };
            listNeedsRefresh = false;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawText("Double Linked List", 325, 10, 20, BLACK);

        drawDLLNodes(nodeButtons, listInts, theList->getCount());

        //TODO: draw list and impliment buttons
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    delete listInts;
    delete theList;
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
   //  system("PAUSE");
    return 0;
}

float clamp(float in, float max)
{
    if (in >= max)
    {
        return max;
    }
    return in;
}

void drawDLLNodes(bool* nodeButtons, const int* intList, int count)//TODO: align center
{
    static constexpr int maxNodesWide = 10;

    for (int i = 0; i < count; i++)
    {
        float nodeStartPosX = 430 - (((i % 10) * 75.0F)/ 2.0F );
        float nodeX = nodeStartPosX;// +((i % 10) * 75.0F);
        float nodeY = 50.0F + (i / 10) * 50.0F;
        nodeButtons[i] = GuiButton(Rectangle{ nodeX, nodeY, 30, 30 }, std::to_string(intList[i]).c_str());//drawing each node as a button
		//DrawLine(nodeX, 225, 0, 0, DARKGREEN);//drawing line to next node
		//DrawLine(0, 0, 0, 0, RED);//drawing line to previous node
    }
}