#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <SDL/SDL_image.h>



#define	WIDTH			64
#define	HEIGHT			32
#define MULTIPLIER		10
#define VIDEO_DEPTH		 8


void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );

SDL_Surface* init_display(SDL_Surface *screen);

void apply_matrix_on_display( int *matrix, const size_t rows, const size_t cols, SDL_Surface* source, SDL_Surface* destination );

unsigned char keydown_case(SDL_Event event);

unsigned char read_key(SDL_Event event);


#endif
