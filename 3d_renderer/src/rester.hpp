#ifndef RESTER_H
#define RESTER_H

#include <iostream>

#define BLUE_1      0xFF00fff9
#define BLACK       0xFF000000
#define BLUE_2      0xFF00b8FF
#define BLUE_3      0xFF4900FF
#define PINK_1      0xFFFF00C1
#define PURPLE_1    0xFF9600FF


// defines color buffer class
class color_buffer{

    public:
        uint32_t * p ;
        int rester_width ;
        int rester_height ; 

        void init( int, int ) ;
        void clear( uint32_t ) ;
        void grid( int, int, uint32_t ) ; 
        void rectangle( int, int, int, int, uint32_t ) ;
        void pixel( int, int, uint32_t ) ;
} ;

#endif
