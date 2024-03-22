#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>

#include "vector.hpp"

// holds the indexes for the vertices of a single face in a mash
class face_t {  
    
    public:
        std::vector <int> indexes ;             // it has normally 3 values (for a triangle)
                                                // but any value is possible

        face_t( std::vector <int> ) ;
} ;

class mesh_t {

    public :
        std::vector <vect3d_t> vertices ;       // holds the vertices of the mesh
        std::vector <face_t> faces ;            // holds the faces of the mesh 

} ;

class cube_t {
    public:
        mesh_t mesh ;
        
        std::vector <vect2d_t> proj_vertices ;  // holds the projected vertices of the cube

        vect3d_t origin ;
        float length ;

        cube_t ( vect3d_t, float ) ;

} ;


#endif