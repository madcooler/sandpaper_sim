//
//  Scene.cpp
//  ParticleGen_C++
//
//  Created by Administrator on 26/08/16.
//  Copyright © 2016 Administrator. All rights reserved.
//

#include "Scene.hpp"

void Scene::writeSceneToPLYFiles()
{
    
}


void Scene::DeleteInvalidFace()
{
    for (size_t i = 0; i < scene.size() ; i++)
    {
        // loop over all faces
        for(size_t j = 0; j < scene[i]->face_list.size(); j++)
        {
            Face *f = &scene[i]->face_list[j];
            if( f->verts[0] == f->verts[1] || f->verts[2] == f->verts[1] || f->verts[0] == f->verts[2] )
            {
                scene[i]->deleteFace(j);
            }
        
        }
    
    }
}


void Scene::writeScene(char * filename)
{
    
//    DeleteInvalidFace();
    
    
    int nverts = 0;
    int nfaces = 0;
    
    for (int i = 0; i < scene.size() ; i++)
    {
        nverts += scene[i]->vertex_list.size();
        nfaces += scene[i]->face_list.size();
    }

    //char filename[50] = "";
    //strcat(filename, "crystal_0.ply");
    
    FILE * ply_file;
    ply_file = fopen(filename, "w");
    
    fprintf(ply_file,"ply \nformat ascii 1.0 \ncomment author: Chi Wang \n");
    
    fprintf(ply_file, "element vertex %d \nproperty float x \nproperty float y \nproperty float z \n",nverts);
    
    fprintf(ply_file, "element face %d \nproperty list uchar int vertex_indices\n",nfaces);
    
    fprintf(ply_file, "end_header\n");
    
    for (int i = 0; i < scene.size() ; i++)
    {
        ShapeObject * obj = scene[i];
        
        for (int k = 0; k < obj->vertex_list.size(); k++)
        {
            
            fprintf(ply_file, "%f %f %f \n" ,
                obj->vertex_list[k].x,
                obj->vertex_list[k].y,
                obj->vertex_list[k].z
                );
        }
        
    }
    

    int indexBase = 0;
    
    /* set up and write the face elements */
    
    for (int i = 0; i < scene.size() ; i++)
    {
        ShapeObject * obj = scene[i];
        
        for (int k = 0; k < obj->face_list.size(); k++)
        {
                    
            fprintf(ply_file, "%d " , obj->face_list[k].getTotalIndexNum());
            
            for (int j = 0; j < obj->face_list[k].getTotalIndexNum(); j++)
            {
                int index = indexBase + obj->face_list[k].getIndexAt(j);
                fprintf(ply_file, "%d " , index);
            }
            fprintf(ply_file, "\n");
        }
        indexBase += obj->vertex_list.size();
        
    }

    fclose(ply_file);

}








