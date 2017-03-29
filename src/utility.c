#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include "chip8.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '#' : ' '), \
  (byte & 0x40 ? '#' : ' '), \
  (byte & 0x20 ? '#' : ' '), \
  (byte & 0x10 ? '#' : ' '), \
  (byte & 0x08 ? '#' : ' '), \
  (byte & 0x04 ? '#' : ' '), \
  (byte & 0x02 ? '#' : ' '), \
  (byte & 0x01 ? '#' : ' ') 

void test_font(unsigned char* font)
{
int i;

	for(i=0;i<(CHARACTER_DIMENSION * NUMBER_OF_CHARACTERS);i++)
	{
		printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(font[i]));
		if((i+1)%5==0)
			printf("\n");
		printf("\n");
	}
}

void print_state(chip8* chip)
{
int i,j;
	
	system("clear");
	printf("CHIP STATE\n");
	printf("I: %x\n",chip->I);
	printf("PC: %04x\n",chip->pc);
	printf("SP: %x\n",chip->sp);
	printf("key: %x\n",chip->key);
	printf("current opcode: %x\n",chip->opcode);
	printf("delay timer: %x\n",chip->delay_timer);
	printf("sound timer: %x\n",chip->sound_timer);
	printf("\nV registers:\n");
	printf(" [0]:%02x\t [1]:%02x\t[2]:%02x\t[3]:%02x\t[4]:%02x\t[5]:%02x\t[6]:%02x\t[7]:%02x\n",chip->V[0],chip->V[1],chip->V[2],chip->V[3],chip->V[4],chip->V[5],chip->V[6],chip->V[7]);
	printf(" [8]:%02x\t [9]:%02x\t[A]:%02x\t[B]:%02x\t[C]:%02x\t[D]:%02x\t[E]:%02x\t[F]:%02x\n",chip->V[8],chip->V[9],chip->V[10],chip->V[11],chip->V[12],chip->V[13],chip->V[14],chip->V[15]);
	
	printf("\t\t--------Video Memory--------\n\n");
	
	for(i = 0; i < HEIGHT; i++)
	{
		for(j = 0; j< WIDTH; j++)
		{
			printf("%d",chip->gfx[i+j*HEIGHT]);
		}
		printf("\n");
	}
	
	printf("\n ----------------");
	
	
	printf("\nMEMORY\nAddr\tValue\n");
	printf("0%x:",chip->pc-2);
		printf("\t%02x%02x\n",chip->memory[chip->pc-2],chip->memory[chip->pc-1]);
	for(i = 0; i < 16; i+=2)
	{
		printf("0%x:",chip->pc+i);
		printf("\t%02x%02x\n",chip->memory[chip->pc+i],chip->memory[chip->pc+i+1]);
	}
	
}


