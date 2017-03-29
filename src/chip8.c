#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chip8.h"

void create_font(unsigned char* font)
{
int i;

	// 0
	font[0] = 0xF0;
	font[1] = 0x90;
	font[2] = 0x90;
	font[3] = 0x90;
	font[4] = 0xF0;
	
	// 1
	font[5] = 0x20;
	font[6] = 0x60;
	font[7] = 0x20;
	font[8] = 0x20;
	font[9] = 0x70;
	
	// 2
	font[10] = 0xF0;
	font[11] = 0x10;
	font[12] = 0xF0;
	font[13] = 0x80;
	font[14] = 0xF0;
	
	// 3
	font[15] = 0xF0;
	font[16] = 0x10;
	font[17] = 0xF0;
	font[18] = 0x10;
	font[19] = 0xF0;
	
	// 4
	font[20] = 0x90;
	font[21] = 0x90;
	font[22] = 0xF0;
	font[23] = 0x10;
	font[24] = 0x10;
	
	// 5
	font[25] = 0xF0;
	font[26] = 0x80;
	font[27] = 0xF0;
	font[28] = 0x10;
	font[29] = 0xF0;
	
	// 6
	font[30] = 0xF0;
	font[31] = 0x80;
	font[32] = 0xF0;
	font[33] = 0x90;
	font[34] = 0xF0;
	
	// 7
	font[35] = 0xF0;
	font[36] = 0x10;
	font[37] = 0x20;
	font[38] = 0x40;
	font[39] = 0x40;
	
	// 8
	font[40] = 0xF0;
	font[41] = 0x90;
	font[42] = 0xF0;
	font[43] = 0x90;
	font[44] = 0xF0;
	
	// 9
	font[45] = 0xF0;
	font[46] = 0x90;
	font[47] = 0xF0;
	font[48] = 0x10;
	font[49] = 0xF0;
	
	// A
	font[50] = 0xF0;
	font[51] = 0x90;
	font[52] = 0xF0;
	font[53] = 0x90;
	font[54] = 0x90;
	
	// B
	font[55] = 0xE0;
	font[56] = 0x90;
	font[57] = 0xE0;
	font[58] = 0x90;
	font[59] = 0xE0;
	
	// C
	font[60] = 0xF0;
	font[61] = 0x80;
	font[62] = 0x80;
	font[63] = 0x80;
	font[64] = 0xF0;
	
	// D
	font[65] = 0xE0;
	font[66] = 0x90;
	font[67] = 0x90;
	font[68] = 0x90;
	font[69] = 0xE0;
	
	// E
	font[70] = 0xF0;
	font[71] = 0x80;
	font[72] = 0xF0;
	font[73] = 0x80;
	font[74] = 0xF0;
	
	// F
	font[75] = 0xF0;
	font[76] = 0x80;
	font[77] = 0xF0;
	font[78] = 0x80;
	font[79] = 0x80;

}


void initialize(chip8* chip)
{
int i;

	chip->opcode = 0;
	
	for(i=0 ; i < DIM_MEMORY ; i++)
		chip->memory[i] = 0;
		
	for(i=0 ; i < NUMBER_REGISTERS ; i++)
		chip->V[i] = 0;
	
	for(i=0; i< WIDTH*HEIGHT; i++)
		chip->gfx[i] = 0;
	
	chip->gfx_refresh = 0;
		
	chip->I = 0;
	
	chip->pc = PROGRAM_STARTING_ADDRESS;		//program starts at 0x0200
	
	chip->delay_timer = 0;
	
	chip->sound_timer = 0;
	
	for(i=0 ; i < STACK_LEVELS ; i++)
		chip->stack[i] = 0;
		
	chip->sp = 0;
}

void load_rom(chip8* chip)
{
FILE *fp;
unsigned char *buffer;
int i;
int size;

	//open file, get size and change file pointer position
	fp = fopen("games/BLINKY", "r+");
	if(fp==NULL) {
		perror("error in opening file");
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	size=ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	buffer = (unsigned char *) malloc(sizeof(unsigned char) * size);
	
	fread(buffer, 1, size, fp);
	
	// enable to check what you get in memory
	/*
	printf("\n");
	for(i = 0; i < size ; i++)
		printf("%04x: %02x\n",i,buffer[i]);
	*/
	for(i=0;i<size;i++)
		chip->memory[PROGRAM_STARTING_ADDRESS + i] = buffer[i];
	printf("%d byte loaded\n",size);
	
	free(buffer);
}

void fetch(chip8* chip)
{
	unsigned short instruction;
	
	instruction = chip->memory[chip->pc];
	instruction = instruction << 8;
	chip->opcode = instruction;
	chip->pc++;
	instruction = chip->memory[chip->pc];
	chip->pc++;
	chip->opcode += instruction;
	
}

//*****************************************************************
//								OPCODE
//*****************************************************************

void execute(chip8* chip)
{
unsigned short opcode;
unsigned short op1, op2, op3;
unsigned char x, y;
	opcode = chip->opcode;

	switch(opcode & 0xF000)
	{
		case 0x0000:
		{
			if(opcode == 0x0000)
				for(int i = 0; i< WIDTH*HEIGHT; i++)
					chip->gfx[i] = 0;	
			
			if(opcode == 0x00E0)
			{
				chip->pc = chip->stack[chip->sp];
				chip->sp--;
			}
		}
		break;
		
		case 0x1000:
		{
			unsigned short jump;
			
			jump = chip->opcode & 0x0FFF;		//get new pc address
			chip->pc = jump;					//update pc
		}
		break;
		
		case 0x2000:
		{
			unsigned short jump;
			
			chip->sp++;							//increment sp
			chip->stack[chip->sp] = chip->pc;	//save the pc value in the stack
			jump = chip->opcode & 0x0FFF;		//get new pc address
			chip->pc = jump;					//update pc
			
		}
		break;
		
		case 0x3000:
		{
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00FF;
			if(chip->V[op1] == op2)
				chip->pc += 2;
		}
		break;
		
		case 0x4000:
		{
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00FF;
			if(chip->V[op1] != op2)
				chip->pc += 2;;
		}
		break;
		
		case 0x5000:
		{
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00F0;
			op2 = op2 >> 4;
			if(chip->V[op1] == chip->V[op2])
				chip->pc += 2;
		}
		break;
		
		case 0x6000:
		{
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00FF;
			chip->V[op1] = op2;
		}
		break;
		
		case 0x7000:
		{
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00FF;
			chip->V[op1] += op2;
		}
		break;
	
		case 0x8000:
		{
			switch(opcode & 0x000F)
			{
				case 0x0000:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					op2 = opcode & 0x00F0;
					op2 = op2 >> 4;
					chip->V[op1] = chip->V[op2];
				}
				break;
				
				case 0x0001:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					op2 = opcode & 0x00F0;
					op2 = op2 >> 4;
					chip->V[op1] = chip->V[op1] | chip->V[op2];
				}
				break;
				
				case 0x0002:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					op2 = opcode & 0x00F0;
					op2 = op2 >> 4;
					chip->V[op1] = chip->V[op1] & chip->V[op2];
				}
				break;
				
				case 0x0003:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					op2 = opcode & 0x00F0;
					op2 = op2 >> 4;
					chip->V[op1] = chip->V[op1] ^ chip->V[op2];
				}
				break;
				
				case 0x0004:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					op2 = opcode & 0x00F0;
					op2 = op2 >> 4;
					unsigned char res = chip->V[op1]+chip->V[op2];
					unsigned short carry = (chip->V[op1]+chip->V[op2])/0x100;
					chip->V[op1] = res;
					chip->V[15] = (1 == carry) ? 1 : 0;
				}
				break;
				
				case 0x0005:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					op2 = opcode & 0x00F0;
					op2 = op2 >> 4;
					unsigned char res = chip->V[op1]-chip->V[op2];
					chip->V[op1] = res;
					chip->V[15] = (chip->V[op1] > chip->V[op2]) ? 1 : 0;
				}
				break;
				
				case 0x0006:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					if(chip->V[op1]&0x0001)
						chip->V[15] = 1;
					else
						chip->V[15] = 0;
					chip->V[op1] = chip->V[op1] >> 1;					
				}
				break;
				
				case 0x0007:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					op2 = opcode & 0x00F0;
					op2 = op2 >> 4;
					unsigned char res = chip->V[op2]-chip->V[op1];
					chip->V[op1] = res;
					chip->V[15] = (chip->V[op1] < chip->V[op2]) ? 1 : 0;
				}
				break;
				
				case 0x000E:
				{
					op1 = opcode & 0x0F00;
					op1 = op1 >> 8;
					if(chip->V[op1]&0x0001)
						chip->V[15] = 1;
					else
						chip->V[15] = 0;
					chip->V[op1] = chip->V[op1] << 1;
				}
				break;
			}
		}
		break;
		
		case 0x9000:
		{
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00F0;
			op2 = op1 >> 4;
			if(chip->V[op1] != chip->V[op2])
				chip->pc += 2;
		}
		break;
		
		case 0xA000:
		{
			op1 = chip->opcode & 0x0FFF;
			chip->I = op1;
		}
		break;
		
		case 0xB000:
		{
			op1 = chip->opcode & 0x0FFF;
			chip->pc = chip->V[0] + op1;
		}
		break;
		
		case 0xC000:
		{
			unsigned char tmp;
			srand(time(NULL));
			
			tmp = rand()%256;
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00FF;
			chip->V[op1] = tmp & op2;
		}
		break;
		
		case 0xD000:
		{
			op1 = chip->opcode & 0x0F00;
			op1 = op1 >> 8;
			op2 = chip->opcode & 0x00F0;
			op2 = op1 >> 4;
			op3 = chip->opcode & 0x000F;
			
			x = chip->V[op1] % WIDTH;
			y = chip->V[op2] % HEIGHT;
			unsigned char collision = 0;
			
			for(int i = 0; i < op3; i++)
			{
					if( chip->gfx[x + y*HEIGHT] ^ chip->memory[chip->I+i] == 0 && chip->gfx[x+y*HEIGHT] ==1)
						collision = 1;
					chip->gfx[x + y*HEIGHT] ^= chip->memory[chip->I+i];
			}
			chip->V[15] = collision;
		}
		break;
		
		case 0xE000:
		{

			if(opcode & 0x009E)
			{
				op1 = chip->opcode & 0x0F00;
				op1 = op1 >> 8;
				if(chip->key == chip->V[op1])
					chip->pc += 2;
			}
			
			if(opcode & 0x00A1)
			{
				op1 = chip->opcode & 0x0F00;
				op1 = op1 >> 8;
				if(chip->key != chip->V[op1])
					chip->pc += 2;
			}	
		}
		break;
		
		case 0xF000:
		{
			switch(opcode & 0x00FF)
			{
				case 0x0007:
				{
					op1 = chip->opcode & 0x0F00;
					op1 = op1 >> 8;
					chip->V[op1] = chip->delay_timer;
				}
				break;
				
				case 0x000A:
				{
					op1 = chip->opcode & 0x0F00;
					op1 = op1 >> 8;
					/* STAY ON THIS INSTRUCTION UNTIL A KEY IS PRESSED */
					if (chip->key == 0x10)
						chip->pc -=2;
					else
						chip->V[op1] = chip->key;
				}
				break;
				
				case 0x0015:
				{
					op1 = chip->opcode & 0x0F00;
					op1 = op1 >> 8;
					chip->delay_timer = chip->V[op1];
				}
				break;
				
				case 0x0018:
				{
					op1 = chip->opcode & 0x0F00;
					op1 = op1 >> 8;
					chip->sound_timer = chip->V[op1];
				}
				break;
				
				case 0x001E:
				{
					op1 = chip->opcode & 0x0F00;
					op1 = op1 >> 8;
					chip->I = chip->I + chip->V[op1];
				}
				break;
				
				case 0x0029:
				{
					chip->gfx[1 + 1*HEIGHT] = 1;
				}
				break;
				
				case 0x0033:
				{
					chip->gfx[2 + 2*HEIGHT] = 1;
				}
				break;
				
				case 0x0055:
				{
					int i;
					op1 = chip->opcode & 0x0F00;
					op1 = op1 >> 8;
					for(i = 0; i <= op1 ; i++)
						chip->memory[chip->I+i] = chip->V[i];
				}
				break;
				
				case 0x0065:
				{
					int i;
					op1 = chip->opcode & 0x0F00;
					op1 = op1 >> 8;
					for(i = 0; i <= op1 ; i++)
						 chip->V[i] = chip->memory[chip->I+i];
				}
				break;
			}
		}
		break;
		
	
		default:
		  printf ("Unknown opcode: 0x%X\n", chip->opcode);
		break;
	}

}



