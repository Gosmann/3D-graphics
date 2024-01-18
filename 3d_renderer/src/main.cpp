#include <iostream>
#include <SDL2/SDL.h>   // include SDL 

#include "rester.hpp"
#include "display.hpp"

class box{

    public:
        int width ;
        int height ;

        int x ;
        int y ;
        
        box( int, int, int, int ) ;

} ;

box::box( int box_width, int box_height, int box_x_pos, int box_y_pos ){
    
    width = box_width ;
    height = box_height ;
    x = box_x_pos ;
    y = box_y_pos ;
}

bool is_running ;
int mouse_count = 0 ;
box b1( 20, 20, 0, 0 ); 

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

    rester.clear( BLACK ); 

}

void process_input( void ){
    
    SDL_Event event ;

    while( SDL_PollEvent( &event ) ){

        switch( event.type ){
            case SDL_QUIT:              // 'x' button pressed on the window
                is_running = false ;
                break ;

            case SDL_KEYDOWN:           // a key was pressed on the keyboard
                
                switch( event.key.keysym.sym ){    
                    case SDLK_ESCAPE : case SDLK_q :
                        is_running = false ;
                        break;
                    
                    case SDLK_w:
                        b1.x -= 20 ;
                        break ;
                    
                    case SDLK_a:
                        b1.y -= 20 ;
                        break ;

                    case SDLK_s:
                        b1.x += 20 ;
                        break ;

                    case SDLK_d:
                        b1.y += 20 ;
                        break ;
                }

                break ;

            case SDL_MOUSEMOTION:
                std::cout << "mouse_motion " << mouse_count << " \n" ;
                mouse_count++;
                break;
        }

    }
    
}

void update ( void ){
    
    SDL_UpdateTexture(
        color_buffer_texture, 
        NULL, 
        rester.p,
        (int)(window_width * sizeof( uint32_t ) )
    );

}


void render ( void ){
    
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 ) ;     // paint it red!
    //SDL_RenderClear(renderer);

    rester.clear( BLACK ); 

    rester.rectangle( b1.x, b1.y, b1.width , b1.height, BLUE_2 ) ;
    
    rester.grid( 20, 20, PINK_1 ) ;

    render_color_buffer();
    
    SDL_RenderPresent(renderer);
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


