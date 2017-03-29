#ifndef CHIP8_H_
#define	CHIP8_H_

#include <stdio.h>
#include <stdlib.h>

#define DIM_MEMORY 4096
#define NUMBER_REGISTERS 16
#define STACK_LEVELS 16
#define NUMBER_OF_CHARACTERS 16
#define CHARACTER_DIMENSION 5	//expressed in byte
#define WIDTH 64 
#define HEIGHT 32
#define PROGRAM_STARTING_ADDRESS 0x200

typedef struct{
	unsigned short opcode;				//code of the first instructoin 2 byte
	unsigned char memory[DIM_MEMORY];	
	unsigned char V[16];				//CPU registers
	unsigned short I;
	unsigned short pc;
	unsigned char gfx[WIDTH*HEIGHT];
	unsigned char gfx_refresh;			//1 if screen has to be refreshed
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[16];			//empty with sp = 0
	unsigned short sp;
	unsigned char key;
}chip8;

void initialize(chip8* chip);
void create_font(unsigned char* font);
void load_rom(chip8* chip);
void fetch(chip8* chip);
void execute(chip8* chip);

#endif
