#include "vector.hpp"
#include <math.h>

const float fov_factor = 800 ;

vect2d_t::vect2d_t( float component_x, float component_y ){
    x = component_x ;
    y = component_y ;
}

vect2d_t::vect2d_t( void ){
    x = 0 ;
    y = 0 ;
}

// just ignore the z component
vect2d_t vect3d_t::project( void ){

    vect2d_t projection_2d( 
        ( x * fov_factor ) / z ,
        ( y * fov_factor ) / z ) ; 

    return projection_2d ;
}

vect3d_t vect3d_t::rotate_x( float angle ){

    vect3d_t rotated ;

    rotated.x = x ; 
    rotated.y = y * cos(angle) - z * sin(angle) ;
    rotated.z = y * sin(angle) + z * cos(angle) ;

    return rotated;
}

vect3d_t vect3d_t::rotate_y( float angle ){

    vect3d_t rotated ;  

    rotated.x = x * cos(angle) + z * sin(angle) ; 
    rotated.y = y ;
    rotated.z = -x * sin(angle) + z * cos(angle) ;

    return rotated;    

}

vect3d_t vect3d_t::rotate_z( float angle ){

    vect3d_t rotated ;  

    rotated.x = x * cos(angle) - y * sin(angle) ; 
    rotated.y = x * sin(angle) + y * cos(angle) ;
    rotated.z = z ;

    return rotated;    

}

