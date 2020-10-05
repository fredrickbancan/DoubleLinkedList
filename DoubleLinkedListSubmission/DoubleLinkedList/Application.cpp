#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "DoubleLinkedList.h"
#include <iostream>
#include <string>
#include <random>

/*Draws the provided doubly linked list to the window as rows of nodes, in order.
  Also draws connecting lines in between, Green lines to the next node and red lines 
  to the previous node.*/
void drawDLLNodes(const DoubleLinkedList* dll);

/*Toggles the provided boolean reference if the provided button bool is true.*/
void toggleBooleanOnButtonPress(bool button, bool& booleanToToggle);

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    //initializing DLL to have just one node
    DoubleLinkedList* theList= new DoubleLinkedList();


    //Booleans for detecting button presses
    bool buttonAddToFrontPressed = false;
    bool buttonAddToBackPressed = false;
    bool buttonInsertAfterNodePressed = false;
    bool buttonInsertBeforeNodePressed = false;
    bool buttonSortPressed = false;
    bool buttonRemovePressed = false;
    bool buttonRandomizePressed = false;
    
    //bool for detecting value box editing
    bool valueBoxEditing0 = false;
    bool valueBoxEditing1 = false;

    //int for holding input values
    int inputValue0 = 0;
    int inputValue1 = 0;

    InitWindow(screenWidth, screenHeight, "Fredrick - Double Linked List (Integers)");
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        //Update button booleans
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 340, 115, 20 }, "Add to Front of List"), buttonAddToFrontPressed);
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 360, 115, 20 }, "Add to Back of List"), buttonAddToBackPressed);
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 380, 115, 20 }, "Insert after node"), buttonInsertAfterNodePressed);
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 350, 400, 115, 20 }, "Insert before node"), buttonInsertBeforeNodePressed);
        toggleBooleanOnButtonPress(GuiButton(Rectangle{ 465, 400, 115, 20 }, "Remove node"), buttonRemovePressed);
        buttonRandomizePressed = GuiButton(Rectangle{ 465, 380, 115, 20 }, "Randomize list");
        buttonSortPressed = GuiButton(Rectangle{ 372, 420, 70, 20 }, "Sort List");


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawText("Double Linked List", 325, 10, 20, BLACK);

        drawDLLNodes(theList);//draw nodes and lines

        //handling adding a node to front
        if (buttonAddToFrontPressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 400, 225, 115, 20 }, "Input the value for the node.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            if (GuiButton(Rectangle{ 400, 245, 95, 30 }, "Add node"))
            {
                theList->pushFront(inputValue0);
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonAddToFrontPressed = false;
            }
            if (GuiButton(Rectangle{ 400, 275, 95, 30 }, "Cancel"))
            {
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonAddToFrontPressed = false;
            }
        }

        //handling adding a node to back
        if (buttonAddToBackPressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 400, 225, 115, 20 }, "Input the value for the node.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            if (GuiButton(Rectangle{ 400, 245, 95, 30 }, "Add node"))
            {
                theList->pushBack(inputValue0);
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonAddToBackPressed = false;
            }
            if (GuiButton(Rectangle{ 400, 275, 95, 30 }, "Cancel"))
            {
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonAddToBackPressed = false;
            }
        }

        //handling inserting a node after
        if (buttonInsertAfterNodePressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 400, 205, 115, 20 }, "Input the value of the node to insert after.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 400, 225, 115, 20 }, "Input the value for the new node.", &inputValue1, 0, INT32_MAX, valueBoxEditing1), valueBoxEditing1);
            if (GuiButton(Rectangle{ 400, 245, 95, 30 }, "Add node"))
            {
                theList->insertAt(inputValue0, inputValue1, false);
                valueBoxEditing0 = false;
                valueBoxEditing1 = false;
                inputValue0 = 0;
                inputValue1 = 0;
                buttonInsertAfterNodePressed = false;
            }
            if (GuiButton(Rectangle{ 400, 275, 95, 30 }, "Cancel"))
            {
                valueBoxEditing0 = false;
                valueBoxEditing1 = false;
                inputValue0 = 0;
                inputValue1 = 0;
                buttonInsertAfterNodePressed = false;
            }
        }

        //handling inserting a node before
        if (buttonInsertBeforeNodePressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 400, 205, 115, 20 }, "Input the value of the node to insert before.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 400, 225, 115, 20 }, "Input the value for the new node.", &inputValue1, 0, INT32_MAX, valueBoxEditing1), valueBoxEditing1);
            if (GuiButton(Rectangle{ 400, 245, 95, 30 }, "Add node"))
            {
                theList->insertAt(inputValue0, inputValue1, true);
                valueBoxEditing0 = false;
                valueBoxEditing1 = false;
                inputValue0 = 0;
                inputValue1 = 0;
                buttonInsertBeforeNodePressed = false;
            }
            if (GuiButton(Rectangle{ 400, 275, 95, 30 }, "Cancel"))
            {
                valueBoxEditing0 = false;
                valueBoxEditing1 = false;
                inputValue0 = 0;
                inputValue1 = 0;
                buttonInsertBeforeNodePressed = false;
            }
        }

        //handling remove node
        if (buttonRemovePressed)
        {
            toggleBooleanOnButtonPress(GuiValueBox(Rectangle{ 400, 205, 115, 20 }, "Input the value of the node to remove.", &inputValue0, 0, INT32_MAX, valueBoxEditing0), valueBoxEditing0);
            if (GuiButton(Rectangle{ 400, 245, 95, 30 }, "Remove node"))
            {
                theList->remove(inputValue0);
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonRemovePressed = false;
            }
            if (GuiButton(Rectangle{ 400, 275, 95, 30 }, "Cancel"))
            {
                valueBoxEditing0 = false;
                inputValue0 = 0;
                buttonRemovePressed = false;
            }
        }
        //handling the sort button
        if (buttonSortPressed)
        {
            theList->sort();
        }

        //handling randomizing the list
        if (buttonRandomizePressed)
        {
            if (!theList->getIsEmpty())
            {
                delete theList;
                theList = new DoubleLinkedList();
            }

            for (int i = 0; i < 20; i++)
            {
                theList->pushBack(rand() % 1000);
            }
        }

        //drawing list info
        DrawText((std::string("List Is Empty: ") + (theList->getIsEmpty() ? "True" : "False")).c_str(), 5, 340, 20, BLACK);//showing if list is empty
        DrawText((std::string("List count: ") + std::to_string(theList->getCount())).c_str(), 5, 370, 20, BLACK);//showing count of list
        DrawText((std::string("First node value: ") + std::to_string(theList->getFront())).c_str(), 5, 400, 20, BLACK);//showing first value
        DrawText((std::string("Last node value: ") + std::to_string(theList->getBack())).c_str(), 5, 430, 20, BLACK);//showing last value

        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    delete theList;//delete list
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
   //  system("PAUSE");
    return 0;
}

void drawDLLNodes(const DoubleLinkedList* dll)
{
    static constexpr int maxNodesWide = 10;
    static constexpr int nodeSize = 30;
    static constexpr float nodeSpacing = 75.0F;
    static constexpr float rowHeight = 50.0F;
    static constexpr float center = 430.0F;

    static constexpr float rowLeftStartingPos = center - (maxNodesWide * nodeSpacing) / 2; //float value of where to start placing nodes at each row from left.

    int count = dll->getCount();
    float remainingNodesStartingPos = center - ((count % maxNodesWide) * nodeSpacing) / 2; //float value of where to start placing the last remaining nodes that are less than a row.
    int filledRowNodes = (count / maxNodesWide) * maxNodesWide;//using int truncation we can get the number of nodes that fit into full rows
    
    float prevNodeX;
    float prevNodeY;
    
    for (int i = 0; i < count; i++)//draw next and previous lines
    {
        //calculating position of current node on screen
        float nodeStartPosX = i < filledRowNodes ? rowLeftStartingPos : remainingNodesStartingPos;
        float nodeX = nodeStartPosX + ((i % maxNodesWide) * nodeSpacing);
        float nodeY = ((i / maxNodesWide) + 1) * rowHeight;
        
        //calculating position of previous node on screen
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

    Node* itterator = dll->getHead();
    for (int i = 0; i < count; i++)//draw nodes
    {
        //calculating position of current node on screen
        float nodeStartPosX = i < filledRowNodes ? rowLeftStartingPos : remainingNodesStartingPos;
        float nodeX = nodeStartPosX + ((i % maxNodesWide) * nodeSpacing);
        float nodeY = ((i / maxNodesWide) + 1) * rowHeight;

        //drawing node as a button
        GuiButton(Rectangle{ nodeX, nodeY, nodeSize, nodeSize }, std::to_string(itterator->data).c_str());//drawing each node as a button
        
        itterator = itterator->next;
    }
}

void toggleBooleanOnButtonPress(bool button, bool& booleanToToggle)
{
    if (button)
    {
        booleanToToggle = !booleanToToggle;
    }
}