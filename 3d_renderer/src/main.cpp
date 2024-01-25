#include <iostream>
#include <SDL2/SDL.h>   // include SDL 

#include "rester.hpp"
#include "display.hpp"
#include "vector.hpp"

const int FPS_TARGET = 30 ;
const int FRAME_TARGET_TIME = (1000 / FPS_TARGET) ;

const int N_POINTS = 9 * 9 * 9 ;

vect3d_t points[ N_POINTS ] ;
vect2d_t projected_points[ N_POINTS ] ;

vect3d_t camera_position = { .x = 0 , .y = 0, .z = -4.0 } ;

vect3d_t cube_rotation = { 0 ,  0, 0 } ;

const float ROTATION_STEP = 0.05 ;

int previous_frame_time = 0 ;

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
     
    // populates the cloud points
    float i, j, k; 
    int point_count = 0;

    for( i = -1.0 ; i <= 1.0 ; i += 0.25 ){
        for( j = -1.0 ; j <= 1.0 ; j += 0.25 ){
            for( k = -1.0 ; k <= 1.0 ; k += 0.25 ){
                vect3d_t new_point = {.x = i, .y = j, .z = k} ;
                
                points[point_count] = new_point ;
                point_count++;
            }
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
    
    // project elements on the screen
    int i;
    for(i = 0 ; i < N_POINTS ; i++){

        // rotate point
        vect3d_t point = points[i] ;

        point = points[i].rotate_x( cube_rotation.x );
        point = point.rotate_y( cube_rotation.y );
        point = point.rotate_z( cube_rotation.z ); 

        // move points away from the camera
        point.x -= camera_position.x ;
        point.y -= camera_position.y ;
        point.z -= camera_position.z ;

        vect2d_t projected_point = point.project() ;
        
        projected_points[i] = projected_point ;
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
    
    previous_frame_time = SDL_GetTicks() ;
    


}


void render ( void ){
    
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255 ) ;     // paint it red!
    //SDL_RenderClear(renderer);

    rester.clear( BLACK ); 

    int i;
    for( i = 0 ; i < N_POINTS ; i++){
                
        rester.rectangle(
            projected_points[i].x + window_width / 2,
            projected_points[i].y + window_height / 2,
            2  ,
            2  ,
            BLUE_2 ) ;       
    }
    
    //rester.grid( 20, 20, PINK_1 ) ;

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


