#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>   // include SDL 

#include "rester.hpp"

extern SDL_Window * window ;
extern SDL_Renderer * renderer ;
extern SDL_Texture * color_buffer_texture ;

extern int window_width ;
extern int window_height ;

extern color_buffer rester;

bool init_window( void ) ;

void destroy_window( void ) ;

void render_color_buffer( void ) ;

#endif

