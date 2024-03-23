#include "mesh.hpp"



cube_t::cube_t( vect3d_t position_ , float length_ ){
    
    position = position_ ;
    length = length_ ;

    int i;

    // creates all vertices
    for( i = 0 ; i < 8 ; i++ ){
        
        vect3d_t vertice = position ;

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

        vertices.push_back( vertice ) ;

        visibility.push_back( true ) ;
        
        proj_vertices.push_back( vertice.project() ) ;
    
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
        
        faces.push_back( indexes ) ;

        indexes.clear() ;  

    }
   
}


void mesh_t::render_vertices( unsigned int color ){
    int i;

    for( i = 0 ; i < proj_vertices.size() ; i++ ){

            vect2d_t pt1 = proj_vertices[i] ;
            
            if( visibility[ i ] )
                rester.rectangle( pt1.x, pt1.y, 1 , 1 , color ) ;       
    }
}

void mesh_t::render_edges( unsigned int color ){

    int i, j ;

    for( i = 0 ; i < faces.size() ; i++ ){           

            for( j = 0 ; j < faces[i].size() ; j++ ){
                
                // vect if vertice if visible
                if( visibility[ faces[i][j] ] ){

                    vect2d_t pt1 = proj_vertices[ faces[i][j] ] ;
                    
                    vect2d_t pt2 ; 

                    if( (j+1) >= faces[i].size() )
                        pt2 = proj_vertices[ faces[i][0] ] ;
                    else
                        pt2 = proj_vertices[ faces[i][j+1] ] ;;

                    
                    rester.line( pt1.x, pt1.y, pt2.x, pt2.y, color ) ;

                }


            }
                    
        }


}


