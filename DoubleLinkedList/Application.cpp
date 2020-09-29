#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

#include "DoubleLinkedList.h"
#include <iostream>
#include <string>


/*Draws the provided array of ints representing a doubly linked list as nodes as gui buttons.
  Buttons are used so they can be selected for insertions.*/
void drawDLLNodes(bool* nodeButtons, const int* intList, int count);//TODO: demonstrate count, first, last and isEmpty graphically.

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    //initializing DLL to have just one node
    DoubleLinkedList* theList= new DoubleLinkedList();

    bool* nodeButtons = nullptr;

    //Booleans for detecting button presses
    bool buttonAddToFrontPressed = false;
    bool buttonAddToBackPressed = false;
    bool buttonInsertAfterNodePressed = false;
    bool buttonInsertBeforeNodePressed = false;
    bool buttonSortPressed = false;
    
    //will be true if int array representing nodes needs to be rebuilt
    bool listNeedsRefresh = false;

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

        DrawText((std::string("List Is Empty: ") + (theList->getIsEmpty() ? "True" : "False")).c_str(), 5, 380, 15, BLACK);//showing if list is empty
        DrawText((std::string("First node value: ") + std::to_string(theList->getFront())).c_str(), 5, 400, 15, BLACK);//showing first value
        DrawText((std::string("Last node value: ") + std::to_string(theList->getBack())).c_str(), 5, 420, 15, BLACK);//showing last value

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

void drawDLLNodes(bool* nodeButtons, const int* intList, int count)//TODO: replace int array with itterator to properly demonstrate use of dll
{
    static constexpr int maxNodesWide = 10;
    static constexpr int nodeSize = 30;
    static constexpr float nodeSpacing = 75.0F;
    static constexpr float rowHeight = 50.0F;
    static constexpr float center = 430.0F;

    static constexpr float rowLeftStartingPos = center - (maxNodesWide * nodeSpacing) / 2; //float value of where to start placing nodes at each row from left.

    float remainingNodesStartingPos = center - ((count % maxNodesWide) * nodeSpacing) / 2; //float value of where to start placing the last remaining nodes that are less than a row.
    int filledRowNodes = (count / maxNodesWide) * maxNodesWide;//using int truncation we can get the number of nodes that fit into full rows
    
    float prevNodeX;
    float prevNodeY;
    
    for (int i = 0; i < count; i++)//draw next and previous lines
    {
        float nodeStartPosX = i < filledRowNodes ? rowLeftStartingPos : remainingNodesStartingPos;
        float nodeX = nodeStartPosX + ((i % maxNodesWide) * nodeSpacing);
        float nodeY = ((i / maxNodesWide) + 1) * rowHeight;

        float nextNodeStartPosX = (i + 1) < filledRowNodes ? rowLeftStartingPos : remainingNodesStartingPos;
        float nextNodeX = nextNodeStartPosX + (((i + 1) % maxNodesWide) * nodeSpacing);
        float nextNodeY = (((i + 1) / maxNodesWide) + 1) * rowHeight;

        if (i < count - 1)
            DrawLine(nodeX + nodeSize, nodeY + nodeSize / 4, nextNodeX, nextNodeY + nodeSize / 4, DARKGREEN);//line to next node

        if (i > 0)
            DrawLine(nodeX , nodeY + (nodeSize - nodeSize / 4), prevNodeX + nodeSize, prevNodeY + (nodeSize - nodeSize / 4), RED);//line to previous node

        prevNodeX = nodeX;
        prevNodeY = nodeY;
    }

    for (int i = 0; i < count; i++)//draw nodes
    {
        float nodeStartPosX = i < filledRowNodes ? rowLeftStartingPos : remainingNodesStartingPos;
        float nodeX = nodeStartPosX + ((i % maxNodesWide) * nodeSpacing);
        float nodeY = ((i / maxNodesWide) + 1) * rowHeight;
        nodeButtons[i] = GuiButton(Rectangle{ nodeX, nodeY, nodeSize, nodeSize }, std::to_string(intList[i]).c_str());//drawing each node as a button
    }
}