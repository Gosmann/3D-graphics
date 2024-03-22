#include "rester.hpp"
#include <math.h>

void color_buffer::init( int x, int y ){
    rester_width = x ;
    rester_height = y ;

    p = new uint32_t[ rester_width * rester_height ] ;
}

void color_buffer::clear( uint32_t color ){
    int i, j ;

    for( i = 0 ; i < rester_width ; i++ ){
        for( j = 0 ; j < rester_height ; j++ ){
            pixel( i, j, color ) ;
        }
    }        
    
}

// x sets the horizontal spacing of the grid
// y sets the vertical spacing of the grid
void color_buffer::grid( int h_spacing, int v_spacing, uint32_t color ){
    int i, j ;
    
    // print horizontal lines
    for( i = v_spacing ; i < rester_height ; i+= v_spacing ){
        for( j = 0 ; j < rester_width ; j++ ){
            pixel( j, i, color ) ;
        }
    }

    // print horizontal lines
    for( i = 0 ; i < rester_height ; i++ ){
        for( j = h_spacing ; j < rester_width ; j += h_spacing ){
            pixel( j, i, color ) ;
        }
    }
}


// draws a rectangle on the screen
void color_buffer::rectangle( int x0, int y0, int width, int height, uint32_t color){
    int i, j;

    for( i = x0 ; i < ( x0 + height ) ; i++ ){
        for( j = y0 ; j < ( y0 + width ) ; j++ ){
            pixel( i, j, color ) ;
        }
    }

}

// draws a pixel on the screen
void color_buffer::pixel( int x, int y, uint32_t color ){
    
    if( x >= 0 && x < rester_width && y >=0 && y < rester_height)
        p[ x + y * rester_width ] = color ;
}

int color_buffer::line( int x0, int y0, int x1, int y1, uint32_t color ){

    /*
    std::cout << "pt1.x : " << x0 << " \n" ;
    std::cout << "pt1.y : " << y0 << " \n" ;
    std::cout << "pt2.x : " << x1 << " \n" ;
    std::cout << "pt2.y : " << y1 << " \n\n" ;
    */
   
    if( x0 >= 0 && x0 < rester_width && y0 >= 0 && y0 < rester_height ){

    }
    else{
        return -1;
        if( x0 < 0 ) x0 = 0 ;  
        if( x0 >= rester_width ) x0 = rester_width ; 
        if( y0 < 0 ) y0 = 0 ;  
        if( y0 >= rester_width ) y0 = rester_width ; 
    }

    int delta_x = (x1 - x0) ;
    int delta_y = (y1 - y0) ;

    int longest_side_length;
    if( abs(delta_x ) >= abs(delta_y) ){
        longest_side_length = abs(delta_x) ;
    }
    else{
        longest_side_length = abs(delta_y) ;
    }

    float x_inc = delta_x / (float)longest_side_length ;
    float y_inc = delta_y / (float)longest_side_length ;

    float current_x = x0 ;
    float current_y = y0 ;

    int i;
    for( i = 0 ; i < longest_side_length ; i++ ){

        if( round(current_x) >= 0 && round(current_x) < rester_width &&
            round(current_y) >= 0 && round(current_y) < rester_height ){
            
            pixel( round(current_x), round(current_y), color ) ;
            //std::cout << "pixel \n" ;
        }
            
        current_x += x_inc ;
        current_y += y_inc ;
    }
    
    
    return 0;

}