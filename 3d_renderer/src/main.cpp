
#include <iostream>
#include <SDL2/SDL.h>   // include SDL 
#include "rester.hpp"

SDL_Window * window = NULL ;
SDL_Renderer * renderer = NULL ;
SDL_Texture * color_buffer_texture = NULL ;

color_buffer rester;

bool is_running ;

int window_width = 800 ;
int window_height = 600 ;

bool init_window( void ){

    // error in initizalization
    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0){
        std::cerr << "[ERROR] : SLD_Init() \n" ;
        return false;
    } ;    

    // create an SDL window
    window = SDL_CreateWindow( 
        NULL,
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        window_width, 
        window_height,
        SDL_WINDOW_BORDERLESS
    );

    if ( window == NULL){
        std::cerr << "[ERROR] : SDL_CreateWindow() \n" ;
        return false;
    }

    // create an SDL renderer
    renderer = SDL_CreateRenderer( window, -1, 0 );

    if( renderer == NULL ){
        std::cerr << "[ERROR] : SDL_CreateRenderer() \n" ;
        return false;
    }    

    return true;   // everything went ok
}

void setup( void ){
    
    // allocates memory for rester
    rester.init( window_width, window_height ) ;    
     
    color_buffer_texture = SDL_CreateTexture( 
        renderer, 
        SDL_PIXELFORMAT_ARGB8888,  
        SDL_TEXTUREACCESS_STREAMING, 
        window_width, 
        window_height
    ) ;

}

void process_input( void ){
    
    SDL_Event event ;
    SDL_PollEvent( &event ) ;

    switch( event.type ){
        case SDL_QUIT:              // 'x' button pressed on the window
            is_running = false ;
            break ;

        case SDL_KEYDOWN:           // a key was pressed on the keyboard
            
            switch( event.key.keysym.sym ){    
                case SDLK_ESCAPE : case SDLK_q :
                    is_running = false ;
                    break;
            }

            break ;
    }
}

void update ( void ){
    
    rester.clear( BLACK ); 

    rester.grid( 20, 20, PINK_1 ) ;

    SDL_UpdateTexture(
        color_buffer_texture, 
        NULL, 
        rester.p,
        (int)(window_width * sizeof( uint32_t ) )
    );

}

void render_color_buffer(){
    
    SDL_RenderCopy( renderer, color_buffer_texture, NULL, NULL ) ;
    
}

void render ( void ){
    
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 ) ;     // paint it red!
    //SDL_RenderClear(renderer);

    render_color_buffer();
    
    SDL_RenderPresent(renderer);
}



void destroy_window( void ){

    delete rester.p ;

    SDL_DestroyRenderer( renderer ) ;
    SDL_DestroyWindow( window ) ;
    SDL_Quit() ;

}



int main( void ){
    
    // create an SDL window
    is_running = init_window() ;

    setup() ;

    while( is_running ){    

        process_input();

        update();

        render();

    }

    destroy_window() ;

    return 0;

}


