#include "rester.hpp"

void color_buffer::init( int x, int y ){
    width = x ;
    height = y ;

    p = new uint32_t[ width * height ] ;
}

void color_buffer::clear( uint32_t color ){
    int i, j ;

    for( i = 0 ; i < width ; i++ ){
        for( j = 0 ; j < height ; j++ ){
            p[ i + j * width ] = color ;
        }
    }        
    
}

// x sets the horizontal spacing of the grid
// y sets the vertical spacing of the grid
void color_buffer::grid( int h_spacing, int v_spacing, uint32_t color ){
    int i, j ;
    
    // print horizontal lines
    for( i = v_spacing ; i < height ; i+= v_spacing ){
        for( j = 0 ; j < width ; j++ ){
            p[ i * width + j ] = color ;
        }
    }

    // print horizontal lines
    for( i = 0 ; i < height ; i++ ){
        for( j = h_spacing ; j < width ; j+=h_spacing ){
            p[ i * width + j ] = color ;
        }
    }
}
