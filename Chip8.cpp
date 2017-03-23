#include "Chip8.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

void Chip8::initialize()
{
    // Initialize registers and memory once.

    pc = 0x200;  // Program counter starts at 0x200
    opcode = 0;  // Reset current opcode
    I = 0;       // Reset index register
    sp = 0;      // Reset stack pointer

    // Clear display
    drawFlag = false;  // TODO: check this.

    // Clear stack
    // Clear registers V0-VF
    // Clear memory

    // Load fontset
    for (int i = 0; i < 80; ++i)
    {
        memory[i] = chip8_fontset[i];
    }

    // Reset timers

    // Clear screen once
    drawFlag = true;
}

void Chip8::loadGame(const std::string& filename)
{    
    FILE* space = fopen("PONG", "rb");
    if (space == nullptr)
    {
        printf("Failed to open PONG!");
        exit(0);
    }
    fseek(space, 0, SEEK_END);
    long bufferSize = ftell(space);
    rewind(space);
    unsigned char* buffer = (unsigned char *)malloc(sizeof(char) * bufferSize);
    size_t result = fread(buffer, 1, bufferSize, space);
    for (int i = 0; i < bufferSize; ++i){ //Load ROM at 0x200
        memory[i + 512] = buffer[i];
    }
    fclose(space);
    free(buffer);
}

void Chip8::emulateCycle()
{
    // Fetch Opcode
    opcode = memory[pc] << 8 | memory[pc + 1];

    // Decode Opcode
    switch (opcode & 0xF000)
    {
        // Some opcodes //

        // In some cases, we can not rely solely on the first four
        // bits to see what the opcode means.  For example, 0x00E0 and
        // 0x00EE both start with 0x0.  In this case we add an additional
        // switch and compare the last four bits.
        case 0x0000:
            switch (opcode & 0x000F)
            {
                case 0x0000:  // 0x00E0: Clears the screen
                    // TODO: Execute opcode
                    break;

                case 0x000E:  // 0x00EE: Return from subroutine
                    // TODO: Execute opcode
                    break;

                default:
                    std::printf("Unknown opcode [0x0000]: 0x%X\n", opcode);
            }
            break;

        case 0x2000:
            stack[sp] = pc;
            ++sp;
            pc = opcode & 0x0FFF;
            break;

        case 0x8000:
            switch (opcode & 0x000F)
            {
                case 0x0004:
                    if (V[(opcode & 0x00F0) >> 4] > (0xFF - V[opcode & 0x0F00]))
                    {
                        V[0xF] = 1;  // carry
                    }
                    else
                    {
                        V[0xF] = 0;
                    }
                    V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
                    pc += 2;
                    break;
            }
            break;

        case 0xA000:  // ANNN: Sets I to the address NNN
            // Execute opcode
            I = opcode & 0x0FFF;
            pc += 2;
            break;

        case 0xD000:
            {
                unsigned short x = V[(opcode & 0x0F00) >> 8];
                unsigned short y = V[(opcode & 0x00F0) >> 4];
                unsigned short height = opcode & 0x000F;
                unsigned short pixel;

                V[0xF] = 0;
                for (int yline = 0; yline < height; yline++)
                {
                    pixel = memory[I + yline];
                    for (int xline = 0; xline < 8; xline++) 
                    {
                        if ((pixel & (0x80 >> xline)) != 0)
                        {
                            if (gfx[(x + xline + ((y + yline) * 64))] == 1)
                            {
                                V[0xF] = 1;
                            }
                            gfx[x + xline + ((y + yline) * 64)] ^= 1;
                        }
                    }
                }
                drawFlag = true;
                pc += 2;
            }
            break;

        case 0xE000:
            switch (opcode & 0x00FF)
            {
                // EX9E: Skips the next instruction
                // if the key stored in VX is pressed
                case 0x009E:
                    if (key[V[(opcode & 0x0F00) >> 8]] != 0)
                    {
                        pc += 4;
                    }
                    else
                    {
                        pc += 2;
                    }
                    break;
            }
            break;

        case 0xF000:  // Stores the Binary-coded decimal representation of VX at the addresses I, I + 1 and I + 2.
            switch (opcode & 0x00FF)
            {
                case 0x0033:
                    memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
                    memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
                    memory[I + 2] = (V[(opcode & 0X0F00) >> 8] % 100) % 10;
                    pc += 2;
                    break;
            }
            break;

        // More opcodes //

        default:
            std::printf("Unknown opcode: 0x%X\n", opcode);
    }

    // Update timers
    if (delay_timer > 0)
    {
        --delay_timer;
    }
    if (sound_timer > 0)
    {
        if (sound_timer == 1)
        {
            std::printf("BEEP!\n");
        }
        --sound_timer;
    }
}

void Chip8::drawGraphics()
{
    for (int y = 0; y < 32; ++y)
    {
        for (int x = 0; x < 64; ++x)
        {
            if (gfx[(y*64) + x] == 0)
            {
                std::printf("0");
            }
            else
            {
                std::printf(" ");
            }
        }
        std::printf("\n");
    }
    std::printf("\n");
}

void Chip8::setKeys()
{
}
