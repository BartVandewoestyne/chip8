#ifndef CHIP8_H
#define CHIP8_H

#include <string>

// Chip 8 font set.  Each number or character is 4 pixels wide and 5 pixels high.
static unsigned char chip8_fontset[80] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8
{
public:
    void initialize();
    void loadGame(const std::string& title);
    void emulateCycle();
    void drawGraphics();
    void setKeys();
    bool drawFlag;

private:

    // TODO: use data type that allows us to store two bytes.
    unsigned short opcode;

    // 4K memory in total
    unsigned char memory[4096];

    // The Chip 8 has 15 8-bit general purpose registers named V0, V1 up to VE.
    // The 16th register is used for the 'carry flag'.
    unsigned char V[16];

    // There is an Index register I and a program counter (pc) which can have
    // a value from 0x000 to 0xFFF.
    unsigned short I;
    unsigned short pc;

    // Systems memory map:
    // 0x000 - 0x1FF - Chip 8 interpreter (contains font set in emu).
    // 0x050 - 0x0A0 - Used for the built in 4x5 pixel font set (0-F).
    // 0x200 - 0xFFF - Program ROM and work RAM

    // Graphics system: the Chip 8 has one instruction that draws sprite to the screen.
    // Drawing is done in XOR mode and if a pixel is turned off as a result of drawing,
    // the VF register is set.  This is used for collision detection.

    // The graphics of the Chip 8 are black and white and the screen has a total of 2048
    // pixels (64x32).  This can easily be implemented using an aray that hold the pixel
    // state (1 or 0).
    unsigned char gfx[64*32];

    // Interrupts and hardware registers.  The Chip 8 has none, but there are two timer
    // registers that count at 60 Hz.  When set above zero, they will count down to zero.
    unsigned char delay_timer;
    unsigned char sound_timer;

    // The system buzzer sounds when the sound timer reaches zero.

    // Stack.
    unsigned short stack[16];
    unsigned short sp;

    // HEX-based keypad (0x0-0xF).  We use an array to store the current state of the key.
    unsigned char key[16];


};

#endif  // CHIP8_H
