#include "mesh.hpp"

face_t::face_t( std::vector<int> indexes_ ){
    indexes = indexes_ ;
}

cube_t::cube_t( vect3d_t origin_ , float length_ ){
    
    origin = origin_ ;
    length = length_ ;

    int i;

    // creates all vertices
    for( i = 0 ; i < 8 ; i++ ){
        
        vect3d_t vertice = origin ;

        switch(i){
            case 0 :    // vertice is equal o the origin
                break ;
            case 1 :
                vertice.x += length ;
                break ;
            case 2 :
                vertice.y += length ;
                break ;
            case 3 : 
                vertice.x += length ;
                vertice.y += length ;
                break ;
            case 4 :
                vertice.z += length ;
                break ;
            case 5 :
                vertice.x += length ;
                vertice.z += length ;
                break ;
            case 6 :
                vertice.y += length ;
                vertice.z += length ;
                break ;
            case 7 : 
                vertice.x += length ;
                vertice.y += length ;
                vertice.z += length ;
                break;

            default:
                break;
        }

        mesh.vertices.push_back( vertice ) ;

        vect2d_t projected_point = vertice.project() ;
        
        proj_vertices.push_back( projected_point ) ;
    }

    // creates all faces
    for( i = 0 ; i < 6 ; i++){

        std::vector<int> indexes ; 

        switch ( i ) {
            
            case 0:     // indexes for the first face
                indexes.push_back(0); indexes.push_back(1); indexes.push_back(3); indexes.push_back(2);
                break;
            case 1: 
                indexes.push_back(0); indexes.push_back(1); indexes.push_back(5); indexes.push_back(4);
                break;
            case 2: 
                indexes.push_back(0); indexes.push_back(2); indexes.push_back(6); indexes.push_back(4);
                break;
            case 3: 
                indexes.push_back(1); indexes.push_back(3); indexes.push_back(7); indexes.push_back(5);
                break;
            case 4: 
                indexes.push_back(2); indexes.push_back(3); indexes.push_back(7); indexes.push_back(6);
                break;
            case 5: 
                indexes.push_back(4); indexes.push_back(5); indexes.push_back(7); indexes.push_back(6);
                break;

            default:
                break;
        }

        face_t face ( indexes ) ;
        mesh.faces.push_back( face ) ;

        indexes.clear() ;  

    }


    

}


