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
                vertice.z -= length ;
                break ;
            case 2 :
                vertice.x += length ;
                break ;
            case 3 : 
                vertice.x += length ;
                vertice.z -= length ;
                break ;
            case 4 :
                vertice.y += length ;
                break ;
            case 5 :
                vertice.z -= length ;
                vertice.y += length ;
                break ;
            case 6 :
                vertice.x += length ;
                vertice.y += length ;
                break ;
            case 7 : 
                vertice.x += length ;
                vertice.y += length ;
                vertice.z -= length ;
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
                indexes.push_back(0); indexes.push_back(4); indexes.push_back(5); indexes.push_back(1);
                break;
            case 2: 
                indexes.push_back(0); indexes.push_back(2); indexes.push_back(6); indexes.push_back(4);
                break;
            case 3: 
                indexes.push_back(1); indexes.push_back(5); indexes.push_back(7); indexes.push_back(3);
                break;
            case 4: 
                indexes.push_back(2); indexes.push_back(3); indexes.push_back(7); indexes.push_back(6);
                break;
            case 5: 
                indexes.push_back(4); indexes.push_back(6); indexes.push_back(7); indexes.push_back(5);
                break;

            default:
                break;
        }
        
        faces.push_back( indexes ) ;

        indexes.clear() ;  

    }
   
}

void mesh_t::update_position( vect3d_t rotation, vect3d_t position ){
    
    int i, j, k ;

    faces_to_render.clear();

    // iterates over the faces in the mesh
    for( i = 0 ; i < faces.size() ; i++ ){
        
        std::vector< vect3d_t > transformed_vertices ;

        // iterates over the vertices in a face
        for( j = 0 ; j < faces[i].size() ; j++ ){

            // rotate point
            vect3d_t point = vertices[ faces[i][j] ] ;

            point = point.rotate_x( rotation.x );
            point = point.rotate_y( rotation.y );
            point = point.rotate_z( rotation.z ); 

            // move points away from the camera
            point.x -= position.x ;
            point.y -= position.y ;
            point.z -= position.z ;

            transformed_vertices.push_back( point ) ;        

        }

        // calculate back face culling
        vect3d_t vector_ab = transformed_vertices[1] - transformed_vertices[0] ;
        vect3d_t vector_ac = transformed_vertices[2] - transformed_vertices[0] ;
         
        vect3d_t normal = vector_ab * vector_ac ;

        vect3d_t camera_ray = position - transformed_vertices[1] ;

        float dot_normal = normal.dot( camera_ray ) ;

        float cos_angle = dot_normal / ( camera_ray.get_modulus() + normal.get_modulus() ) ;

        // if it is not alligned, dont show it
        if( cos_angle < (0.01) ){
            continue ;

        }
        else{
            // if(i == 4) std::cout << cos_angle << " \n " ;
        }
            
        // make the projection
        // iterates over the vertices in a face
        std::vector< vect2d_t > vertices_to_render ;

        for( j = 0 ; j < faces[i].size() ; j++ ){
            vertices_to_render.push_back( transformed_vertices[j].project() ) ;            
        }   

        faces_to_render.push_back( vertices_to_render ) ;

    }

}

void mesh_t::render_vertices( unsigned int color ){
    
    int i, j ;

    for( i = 0 ; i < faces_to_render.size() ; i++ ){   
            for( j = 0 ; j < faces_to_render.size() ; j++ ){   
            
                vect2d_t pt1 = faces_to_render[i][j] ;
                
                rester.rectangle( pt1.x, pt1.y, 1 , 1 , color ) ;
            
            }       
    }
}

void mesh_t::render_edges( unsigned int color ){

    int i, j ;

    for( i = 0 ; i < faces_to_render.size() ; i++ ){           

            for( j = 0 ; j < faces_to_render[i].size() ; j++ ){
                
                // vect if vertice if visible

                //if( visibility[ faces[i][j] ] ){
                if(1){

                    vect2d_t pt1 = faces_to_render[ i ][ j ] ;
                    
                    vect2d_t pt2 ; 

                    if( (j+1) >= faces_to_render[i].size() )
                        pt2 = faces_to_render[ i ][ 0 ] ;
                    else
                        pt2 = faces_to_render[ i ][ j + 1 ] ;

                    rester.line( pt1.x, pt1.y, pt2.x, pt2.y, color ) ;

                }

            }
                    
        }


}



