#ifndef VECTOR_HPP
#define VECTOR_HPP

class vect2d_t {
    
    public:
        float x ;
        float y ;

        vect2d_t( float, float ) ;
        vect2d_t( void ) ;
} ; 

class vect3d_t {

    public:
        float x ;
        float y ;
        float z ; 

        vect2d_t project( void ) ;

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