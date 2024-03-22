#include <iostream>
#include <SDL2/SDL.h>   // include SDL 

#include "rester.hpp"
#include "display.hpp"
#include "vector.hpp"
#include "mesh.hpp"

const int FPS_TARGET = 30 ;
const int FRAME_TARGET_TIME = (1000 / FPS_TARGET) ;

const int GROUND_POINTS = 19 * 19 ;

vect3d_t ground[ GROUND_POINTS ] ;
std::vector<vect2d_t> projected_ground ;

vect3d_t camera_position = { .x = 0 , .y = 0, .z = 30.0 } ;

const float ROTATION_STEP = 0.05 ;
const float POS_STEP = 0.50 ;

vect3d_t cube_rotation = { ROTATION_STEP * 7 ,  0, 0 } ;

int previous_frame_time = 0 ;

cube_t cube1( {0, 0, 0}, 1.5 ); 
cube_t cube2( {3, 0, 0}, 1.5 ); 
cube_t cube3( {0, 0, 1.5}, 1.5 ); 
cube_t cube4( {3, 0, 1.5}, 1.5 ); 

std::vector<cube_t> cubes { cube1, cube2, cube3, cube4} ;

std::vector<cube_t> gnd_cubes { {{0, -1.5, 0}, 1.5} , {{1.5, -1.5, 0}, 1.5}    } ;

bool is_running ;

int mouse_count = 0 ;
int mouse_wheel = 0 ;

void setup( void ){
    
    // allocates memory for rester
    rester.init( window_width, window_height ) ;    
     
    // populates the cloud points
    float i, j, k; 
    int point_count = 0;

    for( i = -10.0 ; i <= 10.0 ; i += 1.111 ){
        for( j = -10.0 ; j <= 10.0 ; j += 1.111 ){
            
            vect3d_t new_point = {.x = i, .y = 0, .z = j} ;
            
            ground[point_count] = new_point ;
            point_count++;
        
        }
    }

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
                        cube_rotation.x -= ROTATION_STEP ;
                        break ;
                    
                    case SDLK_a:
                        cube_rotation.y += ROTATION_STEP ;
                        break ;

                    case SDLK_s:
                        cube_rotation.x += ROTATION_STEP ;
                        break ;

                    case SDLK_d:
                        cube_rotation.y -= ROTATION_STEP ;
                        break ;


                    case SDLK_LEFT:
                        camera_position.x -= POS_STEP ;
                        break ;
                    
                    case SDLK_RIGHT:
                        camera_position.x += POS_STEP ;
                        break ;

                    case SDLK_UP:
                        camera_position.y += POS_STEP ;
                        break ;

                    case SDLK_DOWN:
                        camera_position.y -= POS_STEP ;
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
    int i, j ;

    projected_ground.clear() ;

    // update ground elements
    for(i = 0 ; i < GROUND_POINTS ; i++){

        // rotate point
        vect3d_t point = ground[i] ;

        point = ground[i].rotate_x( cube_rotation.x );
        point = point.rotate_y( cube_rotation.y );
        point = point.rotate_z( cube_rotation.z ); 

        // move points away from the camera
        point.x -= camera_position.x ;
        point.y -= camera_position.y ;
        point.z -= camera_position.z ;

        if( point.is_visible( -15.0 ) ){
            
            vect2d_t projected_point = point.project() ;
    
            projected_ground.push_back( projected_point ) ;

        }

        
    }

    // update cubes
    for(i = 0 ; i < cubes.size() ; i++){

        for(j = 0 ; j < 8 ; j++){

            // rotate point
            vect3d_t point = cubes[i].mesh.vertices[j] ;

            point = cubes[i].mesh.vertices[j].rotate_x( cube_rotation.x );  
            point = point.rotate_y( cube_rotation.y );
            point = point.rotate_z( cube_rotation.z ); 

            // move points away from the camera
            point.x -= camera_position.x ;
            point.y -= camera_position.y ;
            point.z -= camera_position.z ;

            vect2d_t projected_point = point.project() ;
            
            //proj_cube1[i] = projected_point ;
            cubes[i].proj_vertices[j] = projected_point ;
            
        }    
    }

    // rotate point
    vect3d_t point = ground[i] ;

    point = ground[i].rotate_x( cube_rotation.x );
    point = point.rotate_y( cube_rotation.y );
    point = point.rotate_z( cube_rotation.z ); 

    // move points away from the camera
    point.x -= camera_position.x ;
    point.y -= camera_position.y ;
    point.z -= camera_position.z ;

    vect2d_t projected_point = point.project() ;
            
    projected_ground[i] = projected_point ;


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
    
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 ) ;     // paint it red!
    //SDL_RenderClear(renderer);

    rester.clear( BLACK ); 

    int i, j;
    for( i = 0 ; i < projected_ground.size() ; i++){

        vect2d_t pt1 = projected_ground[i] ;
        pt1.x += window_width / 2;
        pt1.y += window_height / 2;
        
        rester.rectangle(
            pt1.x,
            pt1.y,
            1  ,
            1  ,
            PINK_1 ) ;       

        if( (i+1) % 19 != 0 ){
            
            vect2d_t pt2 = projected_ground[i+1] ; 
            pt2.x += window_width / 2;
            pt2.y += window_height / 2;
            
            rester.line( pt1.x, pt1.y, pt2.x, pt2.y, PINK_1 ) ;
            
        }

        if( (i+19) < GROUND_POINTS ){
            
            vect2d_t pt2 = projected_ground[ i + 19 ] ; 
            pt2.x += window_width / 2;
            pt2.y += window_height / 2;
            
            rester.line( pt1.x, pt1.y, pt2.x, pt2.y, PINK_1 ) ;
            
        }   
    }
    
    // render cubes points
    for(i = 0 ; i < cubes.size() ; i++ ){
        
        // renter rectangle lines
        for( j = 0 ; j < 8 ; j++ ){

            vect2d_t pt1 = cubes[i].proj_vertices[j] ;
            pt1.x += window_width / 2;
            pt1.y += window_height / 2;
            
            rester.rectangle(
                pt1.x,
                pt1.y,
                1  ,
                1  ,
                BLUE_2 ) ;              
        }
    }

    // rester cube's edges

    for(i = 0 ; i < cubes.size() ; i++ ){

        for( j = 0 ; j < 12 ; j++){

            vect2d_t pt1, pt2 ;

            switch( j ){
                case 0:
                    pt1 = cubes[i].proj_vertices[0] ;
                    pt2 = cubes[i].proj_vertices[1] ;
                    break;

                case 1:
                    pt1 = cubes[i].proj_vertices[0] ;
                    pt2 = cubes[i].proj_vertices[2] ;
                    break;

                case 2:
                    pt1 = cubes[i].proj_vertices[1] ;
                    pt2 = cubes[i].proj_vertices[3] ;
                    break;
                
                case 3:
                    pt1 = cubes[i].proj_vertices[2] ;
                    pt2 = cubes[i].proj_vertices[3] ;
                    break;

                case 4:
                    pt1 = cubes[i].proj_vertices[0+4] ;
                    pt2 = cubes[i].proj_vertices[1+4] ;
                    break;

                case 5:
                    pt1 = cubes[i].proj_vertices[0+4] ;
                    pt2 = cubes[i].proj_vertices[2+4] ;
                    break;

                case 6:
                    pt1 = cubes[i].proj_vertices[1+4] ;
                    pt2 = cubes[i].proj_vertices[3+4] ;
                    break;
                
                case 7:
                    pt1 = cubes[i].proj_vertices[2+4] ;
                    pt2 = cubes[i].proj_vertices[3+4] ;
                    break;

                case 8:
                    pt1 = cubes[i].proj_vertices[0] ;
                    pt2 = cubes[i].proj_vertices[0+4] ;
                    break;

                case 9:
                    pt1 = cubes[i].proj_vertices[1] ;
                    pt2 = cubes[i].proj_vertices[1+4] ;
                    break;

                case 10:
                    pt1 = cubes[i].proj_vertices[2] ;
                    pt2 = cubes[i].proj_vertices[2+4] ;
                    break;
                
                case 11:
                    pt1 = cubes[i].proj_vertices[3] ;
                    pt2 = cubes[i].proj_vertices[3+4] ;
                    break;
            
                default:
                    break;
            }

            pt1.x += window_width / 2;
            pt1.y += window_height / 2;
            
            pt2.x += window_width / 2;
            pt2.y += window_height / 2;
                
            rester.line( pt1.x, pt1.y, pt2.x, pt2.y, BLUE_2 ) ;
        }

    
    }
    

    //rester.grid( 20, 20, PINK_1 ) ;

    render_color_buffer();
    
    SDL_RenderPresent(renderer);
}

int main( void ){
    
    // create an SDL window
    is_running = init_window() ;
    
    setup() ;

/*
    int i;

    std::cout << "print_vertices : \n";
    for(i = 0 ; i < 8 ; i++ ){
        std::cout << " x: " << cube1.mesh.vertices[i].x << "| y : " << cube1.mesh.vertices[i].y << "| z : " << cube1.mesh.vertices[i].z << " \n" ;
    }

    std::cout << "print_faces : \n";
    for(i = 0 ; i < 6 ; i++ ){
        std::cout << " " << cube1.mesh.faces[i].indexes[0] << " " << cube1.mesh.faces[i].indexes[1] << 
                     " " << cube1.mesh.faces[i].indexes[2] << " " << cube1.mesh.faces[i].indexes[3] << " \n" ; 
    }
    */

   std::cout << (int)cubes.size() << " \n" ;
    
    while( is_running ){    

        process_input();

        update();

        render();

    }

    destroy_window() ;

    return 0;

}


