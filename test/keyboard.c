#include <stdio.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../src/display.h"



int main(int argc, char* args[])
{
	SDL_Surface* screen = NULL; 
	SDL_Event event;
	int quit = 0;	

	screen = init_display(screen);
	//Set the window caption 




	//Update the screen
	SDL_Flip( screen );


//	while( !quit ) {
//		while( SDL_PollEvent( &event ) != 0 ) { 
//			if( event.type == SDL_QUIT ) { 
//				quit = 1; 
//			} 
//			else if( event.type == SDL_KEYDOWN ) {
//				printf( "Key press detected\n" );
//				keydown_case(event);
//			}
//		}
//	}

	unsigned char key = 16;
	while(key!=17)
	{
		key = read_key(event);
		if (key !=16)
			printf("%x", key);
		sleep(1);
	}


	SDL_Quit();

	return 0;
}
