/*
Docuemtnazione chip8 
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#0.0
http://omokute.blogspot.it/2012/06/emulation-basics-write-your-own-chip-8.html
http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
*/

#include <stdio.h>
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */
#include <time.h>
#include <unistd.h>
#include "chip8.h"
#include "utility.h"
#include "display.h"

int main(int argc, char* argv[])
{
	chip8 chip;
	
	SDL_Event event;
	SDL_Surface* screen = NULL; 
	SDL_Surface* pixel = NULL;
	int quit = 0;
	
	unsigned char font[CHARACTER_DIMENSION * NUMBER_OF_CHARACTERS];
	
	//INIZIALIZZAZIONE SCHERMO
	printf("INIT DISPLAY\n");
	screen = init_display(screen);

	//CARICO IMMAGINE PIXEL
	printf("PRIMA DI CARICARE BMP\n");
	pixel = SDL_LoadBMP( "../res/img/pixel.bmp" );


	printf("PRIMA DI OTTIMIZZARE IMMAGINE\n");

	printf("ottimizzato\n");
	create_font(chip.memory);
	test_font(chip.memory);
		
	initialize(&chip);
	print_state(&chip);
	
	load_rom(&chip);

	//Update the screen
	
	printf("PRIMA DI FLIPPARE\n");
	SDL_Flip( screen );

	printf("DOPO DI FLIPPARE\n");

	//while( !quit ) {
		
	//}

	while(!quit)
	{
		fetch(&chip);
		print_state(&chip);
		//getchar();
		execute(&chip);
		//print_state(&chip);
		/* Blocco da sostituire */
		
		
		while( SDL_PollEvent( &event ) != 0 ) { 
			if( event.type == SDL_QUIT ) { 
				quit = 1; 
			} 
			else if( event.type == SDL_KEYDOWN ) {	
				printf( "Key press detected\n" );
				chip.key=keydown_case(event);
			}
			else if( event.type != SDL_KEYDOWN ) {
				chip.key = 16;
			}
		}
		
		/* fino a qui */

		/*DA IMPLEMENTARE READ_KEY CON TEST 
		 * chip.key = read_key(event);
		 * */
		
		getchar();
		//usleep(800);
		
	}
	SDL_FreeSurface( pixel );
	SDL_Quit();
	return 0;
}
