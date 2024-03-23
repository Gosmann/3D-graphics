#include "vector.hpp"
#include "display.hpp"

#include <math.h>

const float fov_factor = 800 ;

// vect3d_t function

float vect2d_t::get_modulus(){
    return std::sqrt( x*x + y*y ) ;
}

vect2d_t vect2d_t::add( vect2d_t vector2 ){
    return vect2d_t( vector2.x + x , vector2.y + y ) ;
}
vect2d_t vect2d_t::operator+( vect2d_t vector2 ){
    return add( vector2 ) ;
}

vect2d_t vect2d_t::sub( vect2d_t vector2 ){
    return vect2d_t( x - vector2.x , y - vector2.y ) ;
}
vect2d_t vect2d_t::operator-( vect2d_t vector2 ){
    return sub( vector2 ) ;
}

vect2d_t vect2d_t::mult( float factor ){
    return vect2d_t( x * factor , y * factor ) ;
}
vect2d_t vect2d_t::operator*( float factor ){
    return mult( factor ) ;
}

vect2d_t vect2d_t::div( float factor ){
    return vect2d_t( x / factor , y / factor ) ;
}
vect2d_t vect2d_t::operator/( float factor ){
    return div( factor ) ;
}

// vect3d_t function

vect2d_t vect3d_t::project( void ){
    
    vect2d_t projection_2d( 
        ( x * fov_factor ) / z ,
        ( y * fov_factor ) / z ) ; 

    projection_2d.x += window_width / 2 ;
    projection_2d.y += window_height / 2 ;

    return projection_2d ;
}

vect3d_t vect3d_t::add( vect3d_t v ){
    return vect3d_t( x + v.x, y + v.y, z + v.z ) ;
}
vect3d_t vect3d_t::operator+( vect3d_t vector ){
    return add( vector ) ;
}

vect3d_t vect3d_t::sub( vect3d_t v ){
    return vect3d_t( x - v.x , y - v.y, z - v.z ) ;
}
vect3d_t vect3d_t::operator-( vect3d_t vector ){
    return sub( vector ) ;
}

vect3d_t vect3d_t::mult( float factor ){
    return vect3d_t( x * factor , y * factor, z * factor ) ;
}
vect3d_t vect3d_t::operator*( float factor ){
    return mult( factor ) ;
}

vect3d_t vect3d_t::div( float factor ){
    return vect3d_t( x / factor , y / factor, z / factor ) ;
}
vect3d_t vect3d_t::operator/( float factor ){
    return div( factor ) ;
}

vect3d_t vect3d_t::cross( vect3d_t b ){

    vect3d_t res ;

    res.x = y * b.z - z * b.y ;
    res.y = z * b.x - x * b.z ;
    res.z = x * b.y - y * b.x ;

    return res ;
}
vect3d_t vect3d_t::operator*( vect3d_t vector ){
    return cross( vector ) ;
}

float vect3d_t::get_modulus(){
    return std::sqrt( x*x + y*y + z*z ) ;
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

