#include "display.hpp"

SDL_Window * window = NULL ;
SDL_Renderer * renderer = NULL ;
SDL_Texture * color_buffer_texture = NULL ;

int window_width = 800 ;
int window_height = 600 ;

color_buffer rester;


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

void destroy_window( void ){

    delete rester.p ;

    SDL_DestroyRenderer( renderer ) ;
    SDL_DestroyWindow( window ) ;
    SDL_Quit() ;

}

void render_color_buffer(){
    
    SDL_RenderCopy( renderer, color_buffer_texture, NULL, NULL ) ;
    
}
