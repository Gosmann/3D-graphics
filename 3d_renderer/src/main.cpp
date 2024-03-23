#include <iostream>
#include <SDL2/SDL.h>   // include SDL 

#include "rester.hpp"
#include "display.hpp"
#include "vector.hpp"
#include "mesh.hpp"

const int FPS_TARGET = 30 ;
const int FRAME_TARGET_TIME = (1000 / FPS_TARGET) ;


vect3d_t camera_position ( 0, 1, 30.0 ) ;

const float ROTATION_STEP = 0.05 ;
const float POS_STEP = 0.50 ;

vect3d_t cube_rotation = { ROTATION_STEP * 7 ,  0, 0 } ;

int previous_frame_time = 0 ;


cube_t cube1( {1, 1, 0}, 3.0 ); 


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
    
    create_cube_grid(  ) ;
    
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
                        camera_position.z -= POS_STEP ;
                        break ;
                    
                    case SDLK_a:
                        camera_position.x -= POS_STEP ;
                        break ;

                    case SDLK_s:
                        camera_position.z += POS_STEP ;
                        break ;

                    case SDLK_d:
                        camera_position.x += POS_STEP ;
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
                camera_position.y += event.wheel.y * 0.25 ;
                break;

        }

    }
    
}

void update ( void ){
    
    // project elements on the screen
    int i, j ;
    
    // update ground elements
    for(i = 0 ; i < gnd_cubes.size() ; i++){

        for(j = 0 ; j < gnd_cubes[i].vertices.size() ; j++ ){
            
            // rotate point
            vect3d_t point = gnd_cubes[i].vertices[j] ;

            point = point.rotate_x( cube_rotation.x );
            point = point.rotate_y( cube_rotation.y );
            point = point.rotate_z( cube_rotation.z ); 

            // move points away from the camera
            point.x -= camera_position.x ;
            point.y -= camera_position.y ;
            point.z -= camera_position.z ;

            gnd_cubes[i].proj_vertices[j] = point.project() ;
            
            gnd_cubes[i].visibility[j] = ( point.z < -5.0 ) ? true : false ;

        }

    }

    // update ground elements
    for(j = 0 ; j < cube1.vertices.size() ; j++ ){
        
        // rotate point
        vect3d_t point = cube1.vertices[j] ;

        point = point.rotate_x( cube_rotation.x );
        point = point.rotate_y( cube_rotation.y );
        point = point.rotate_z( cube_rotation.z ); 

        // move points away from the camera
        point.x -= camera_position.x ;
        point.y -= camera_position.y ;
        point.z -= camera_position.z ;

        cube1.proj_vertices[j] = point.project() ;
        
        cube1.visibility[j] = ( point.z < -5.0 ) ? true : false ;
        
    }




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
    
    std::cout << "FPS: " << 1.0 / ((SDL_GetTicks() - previous_frame_time )/1000.0) << "\n";
    previous_frame_time = SDL_GetTicks() ;
    
}

void render ( void ){
    int i, j, k;

    rester.clear( BLACK ); 

    // iterates over the elements
    for( i = 0 ; i < gnd_cubes.size() ; i++){

        // render cubes vertices
        gnd_cubes[i].render_vertices( PINK_1 ) ;

        // render cubes faces
        gnd_cubes[i].render_edges( PINK_1 ) ;
      
    }

    cube1.render_edges( BLUE_2 ) ;
    
    render_color_buffer();
    
    SDL_RenderPresent(renderer);
}

int main( void ){
    
    // create an SDL window
    is_running = init_window() ;
    
    setup() ;

    vect3d_t a(1, 0, 0 );
    vect3d_t b(0, 1, 0 );

    vect3d_t c = a * b ;

    std::cout << c.x << " " << c.y << " " << c.z << " \n" ;

    is_running = false ;

    while( is_running ){    

        process_input();

        update();

        render();

    }

    destroy_window() ;

    return 0;

}


