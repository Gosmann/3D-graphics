#include "rester.hpp"

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