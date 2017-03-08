#include "Chip8.h"

#include <cstdio>
#include <iostream>

Chip8 myChip8;

void setupGraphics()
{
    std::cout << "TODO: setupGraphics()\n";
}

void setupInput()
{
    std::cout << "TODO: setupInput()\n";
}

int main(int argc, char** argv)
{
    // Set up render system (window size, display mode, etc.)
    setupGraphics();

    // Register input callbacks (bind callbacks).
    setupInput();

    // Initialize the Chip8 system: clear the memory, registers and screen.
    myChip8.initialize();

    // Load the game into the memory.
    myChip8.loadGame("pong");

    // Emulation loop
    for(;;)
    {
        // Emulate one cycle.
        myChip8.emulateCycle();

        // Because the system does not draw every cycle, we should set a draw flag
        // when we need to update our screen.  Only two opcodes should set this flag:
        //   * 0x00E0 - Clears the screen
        //   * 0xDXYN - Draws a sprite on the screen
        if (myChip8.drawFlag)
        {
            myChip8.drawGraphics();
        }

        // If we press or release a key, we should store this state in the part that
        // emulates the keypad.
        myChip8.setKeys();
    }

    return 0;
}
