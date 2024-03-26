#include <iostream>
#include <SDL2/SDL.h>   // include SDL 

#include "rester.hpp"
#include "display.hpp"
#include "vector.hpp"
#include "mesh.hpp"

const int FPS_TARGET = 30 ;
const int FRAME_TARGET_TIME = (1000 / FPS_TARGET) ;


vect3d_t camera_position ( 0, 0, -10 ) ;

const float ROTATION_STEP = 0.05 ;
const float POS_STEP = 0.50 ;

vect3d_t cube_rotation = { ROTATION_STEP * 0 ,  0, 0 } ;

int previous_frame_time = 0 ;

cube_t cube1( {0, 0, 0}, 1.0 ); 


std::vector<cube_t> gnd_cubes ;
//std::vector<cube_t> gnd_cubes ;

std::vector<mesh_t> testing ;

void create_cube_grid( ){
    int i, j ;
    
    cube_t cube_base( {0, 0, 0}, 1.0 ); 

    for( i = -5 ; i < 5 ; i++ ){
        for( j = -5 ; j < 5 ; j++){

            cube_t cube_mod ( { i, 0, j }, 1.0 ) ;
            
            gnd_cubes.push_back( cube_mod ) ;
                    
        }
    }

}

bool is_running ;

int mouse_count = 0 ;
int mouse_wheel = 0 ;

void setup( void ){
    
    //create_cube_grid(  ) ;
    
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
                    
                    case SDLK_LEFT:
                        cube_rotation.y += ROTATION_STEP ;
                        break ;
                    
                    case SDLK_RIGHT:
                        cube_rotation.y -= ROTATION_STEP ;
                        break ;

                    case SDLK_UP:
                        cube_rotation.x += ROTATION_STEP ;
                        break ;

                    case SDLK_DOWN:
                        cube_rotation.x -= ROTATION_STEP ;
                        break ;


                    case SDLK_w:
                        camera_position.y += POS_STEP ;
                        break ;
                    
                    case SDLK_a:
                        camera_position.x += POS_STEP ;
                        break ;

                    case SDLK_s:
                        camera_position.y -= POS_STEP ;
                        break ;

                    case SDLK_d:
                        camera_position.x -= POS_STEP ;
                        break ;
                    
                }

                break ;

            case SDL_MOUSEMOTION:
                std::cout << "mouse_motion " << mouse_count << " \n" ;
                mouse_count++;
                break;

            case SDL_MOUSEWHEEL:
                if(event.wheel.y > 0){          // scroll up
                    mouse_wheel++;        
                }
                else if(event.wheel.y < 0){     // scroll down
                    mouse_wheel--;
                }
                //std::cout << "mouse_wheel " << mouse_wheel << " \n" ;
                camera_position.z += event.wheel.y * 0.25 ;
                break;

        }

    }
    
}

void update ( void ){
    
    // project elements on the screen
    int i, j, k;
    
    // update ground elements

    // update gnd_cubes
    for(i = 0 ; i < gnd_cubes.size() ; i++){

        // update position ( cube_rotation, camera_position )
        //gnd_cubes[i].update_position( cube_rotation, camera_position );

    }

    // update big cube
    cube1.update_position( cube_rotation, camera_position );    
    

    // check backface culling


    SDL_UpdateTexture(
        color_buffer_texture, 
        NULL, 
        rester.p,
        (int)(window_width * sizeof( uint32_t ) )
    );

    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time );

    if( time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME ){
        SDL_Delay(time_to_wait) ;
    }
    
    //std::cout << "FPS: " << 1.0 / ((SDL_GetTicks() - previous_frame_time )/1000.0) << "\n";
    //std::cout << camera_position.z << " \n " ;
    
    previous_frame_time = SDL_GetTicks() ;
    
}

void render ( void ){
    int i, j, k;

    rester.clear( BLACK ); 

    // iterates over the elements
    for( i = 0 ; i < gnd_cubes.size() ; i++){

        // render cubes faces
        gnd_cubes[i].render_edges( PINK_1 ) ;

        gnd_cubes[i].render_vertices( PINK_1 ) ;
      
    }

    // renders the big cube
    cube1.render_edges( BLUE_2 ) ;
    
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


