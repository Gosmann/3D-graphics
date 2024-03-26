#ifndef VECTOR_HPP
#define VECTOR_HPP

class vect2d_t {
    
    public:
        float x ;
        float y ;
        
        vect2d_t( float x, float y ) : x(x), y(y) {} ;
        vect2d_t( void ) : x(0), y(0) {} ;

        vect2d_t add( vect2d_t ) ;
        vect2d_t operator+( vect2d_t ) ;
        
        vect2d_t sub( vect2d_t ) ;
        vect2d_t operator-( vect2d_t ) ;

        vect2d_t mult( float ) ;
        vect2d_t operator*( float ) ;
        
        vect2d_t div( float ) ;
        vect2d_t operator/( float ) ;

        float dot( vect2d_t ) ;

        float get_modulus( ) ;
        

} ; 

class vect3d_t {

    public:
        float x ;
        float y ;
        float z ; 

        vect3d_t( float x, float y, float z ) : x(x), y(y), z(z) {} ;
        vect3d_t( void ) : x(0), y(0), z(0) {} ;

        vect2d_t project( void ) ;

        vect3d_t add( vect3d_t ) ;
        vect3d_t operator+( vect3d_t ) ;
        
        vect3d_t sub( vect3d_t ) ;
        vect3d_t operator-( vect3d_t ) ;
        
        vect3d_t mult( float ) ;
        vect3d_t operator*( float ) ;
        
        vect3d_t div( float ) ;
        vect3d_t operator/( float ) ;

        vect3d_t cross( vect3d_t ) ;
        vect3d_t operator*( vect3d_t ) ;

        float dot( vect3d_t ) ;

        float get_modulus( ) ;

        vect3d_t rotate_x( float ) ;
        vect3d_t rotate_y( float ) ;
        vect3d_t rotate_z( float ) ;

};

class camera_t {

    public:

        vect3d_t position ;
        vect3d_t rotation ;
        float fov_angle ;

} ;

#endif