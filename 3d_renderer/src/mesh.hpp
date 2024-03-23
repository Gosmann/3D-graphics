#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <vector>
#include "display.hpp"

#include "vector.hpp"

class mesh_t {

    public :
        std::vector < vect3d_t > vertices ;                  // holds the vertices of the mesh
        std::vector < std::vector<int> > faces ;             // holds the faces of the mesh 

        std::vector <vect2d_t> proj_vertices ;               // holds the projected vertices of the cube
        std::vector <bool> visibility ;                      // holds the visibility of the projected vertices

        vect3d_t position ;                                   
        
        void render_edges( unsigned int color = PINK_1 ) ;
        
        void render_vertices( unsigned int color = PINK_1 ) ;
        // mesh_t() ;

} ;

class cube_t : public mesh_t {

    public:
        
        float length ;

        cube_t ( vect3d_t , float ) ; 
} ;


#endif