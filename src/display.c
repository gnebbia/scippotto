#include <stdio.h>
#include "display.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdint.h>


void
apply_surface (int x, int y, SDL_Surface * source, SDL_Surface * destination)
{
  SDL_Rect offset;

  offset.x = x;
  offset.y = y;
  SDL_BlitSurface (source, NULL, destination, &offset);

}



void
apply_matrix_on_display (int *matrix, const size_t rows, const size_t cols,
			 SDL_Surface * source, SDL_Surface * destination)
{
  SDL_Rect offset;
  int x, y;

  for (x = 0; x < rows; x++)
    {
      for (y = 0; y < cols; y++)
	{
	  if (matrix[x + y * rows] == 1)
	    {
	      offset.x = y * 10;
	      offset.y = x * 10;
	      SDL_BlitSurface (source, NULL, destination, &offset);
	    }
	}
    }
}


SDL_Surface *
init_display (SDL_Surface * screen)
{

  SDL_Surface *fin = NULL;
  //Initialize all SDL subsystems 
  if (SDL_Init (SDL_INIT_EVERYTHING) == -1)
    {
    }

  //Set up the screen 
  screen =
    SDL_SetVideoMode (WIDTH * MULTIPLIER, HEIGHT * MULTIPLIER, VIDEO_DEPTH,
		      SDL_SWSURFACE);

  //If there was an error in setting up the screen 
  if (screen == NULL)
    {
    }

  //Set the window caption 
  SDL_WM_SetCaption ("Chip-8 Emulator", NULL);

  fin = screen;
  return fin;
}

unsigned char
keydown_case (SDL_Event event)
{
  switch (event.key.keysym.sym)
    {
    case SDLK_0:
      printf ("0 pressed\n");
      return 0;
      break;

    case SDLK_1:
      printf ("1 pressed\n");
      return 1;
      break;

    case SDLK_2:
      printf ("2 pressed\n");
      return 2;
      break;

    case SDLK_3:
      printf ("3 pressed\n");
      return 3;
      break;

    case SDLK_4:
      printf ("4 pressed\n");
      return 4;
      break;

    case SDLK_5:
      printf ("5 pressed\n");
      return 5;
      break;

    case SDLK_6:
      printf ("6 pressed\n");
      return 6;
      break;

    case SDLK_7:
      printf ("7 pressed\n");
      return 7;
      break;

    case SDLK_8:
      printf ("8 pressed\n");
      return 8;
      break;

    case SDLK_9:
      printf ("9 pressed\n");
      return 9;
      break;

    case SDLK_a:
      printf ("a pressed\n");
      return 10;
      break;

    case SDLK_b:
      printf ("b pressed\n");
      return 11;
      break;

    case SDLK_c:
      printf ("c pressed\n");
      return 12;
      break;

    case SDLK_d:
      printf ("d pressed\n");
      return 13;
      break;

    case SDLK_e:
      printf ("e pressed\n");
      return 14;
      break;

    case SDLK_f:
      printf ("f pressed\n");
      return 15;
      break;

      /* Other Keys pressed */
    default:
      return 16;
      break;

    }
}


unsigned char
read_key (SDL_Event event)
{
  while (SDL_PollEvent (&event) != 0)
    {
      if (event.type == SDL_QUIT)
	{
	  return 17;
	}
      else if (event.type == SDL_KEYDOWN)
	{
	  return keydown_case (event);
	}
      else if (event.type != SDL_KEYDOWN)
	{
	  return 16;
	}
      else
	{
	  return 16;
	}
    }
  return 18;
}
