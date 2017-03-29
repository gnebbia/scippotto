#include <stdio.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../src/display.h"



int main(int argc, char* args[])
{
	SDL_Event event;
	SDL_Surface* screen = NULL; 
	SDL_Surface* raw_pixel  = NULL;	
	SDL_Surface* pixel = NULL;
	int quit = 0;	

//
//
//	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) { 
//		return -1; 
//	} 
//	
//	//Set up the screen 
//	screen = SDL_SetVideoMode( WIDTH*MULTIPLIER, HEIGHT*MULTIPLIER, VIDEO_DEPTH, SDL_SWSURFACE ); 
//	SDL_WM_SetCaption( "Chip-8 Emulator", NULL ); 
//
//	//If there was an error in setting up the screen 
//	if( screen == NULL ) { 
//		return -2; 
//	} 
//	

	printf("QUi arrivo prima\n");

	screen = init_display(screen);
	//Set the window caption 


	raw_pixel = SDL_LoadBMP( "img/pixel.bmp" );	

	pixel = SDL_DisplayFormat( raw_pixel );	

	int rows = 32;
	int cols = 64;
	int *matrix = malloc(sizeof(int) * rows * cols); 

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			matrix[i + j*rows] = 0;
		}
	}

//	matrix[0 + 0*rows] = 1;
//	matrix[31 + 63*rows] = 1;
//
//	matrix[2 + 4*rows] = 1;
//
//	matrix[1 + 10*rows] = 1;	

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			printf("%d",matrix[i + j*rows]);
		}
		printf("\n");
	}
	
	
	apply_matrix_on_display(matrix, rows, cols, pixel, screen);

	//Update the screen
	SDL_Flip( screen );


	while( !quit ) {
		while( SDL_PollEvent( &event ) != 0 ) { 
			if( event.type == SDL_QUIT ) { 
				quit = 1; 
			} 
			else if( event.type == SDL_KEYDOWN ) {
				printf( "Key press detected\n" );
				keydown_case(event);
			}
		}
	}
	

	SDL_FreeSurface( pixel );

	SDL_Quit();

	return 0;
}
