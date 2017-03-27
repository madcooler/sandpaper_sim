//
//  Object.cpp
//  ParticleGen_C++
//
//  Created by Administrator on 26/08/16.
//  Copyright © 2016 Administrator. All rights reserved.
//

#include <stdio.h>
#include "RandomNumber.h"
#include "Object.h"

#include <iostream>

void ShapeObject::MoveObject(
    double a,
    double b,
    double c
    )
{
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex_list[i].Move(a,b,c);
    }
}

void ShapeObject::ScaleObject(
    double a,
    double b,
    double c
    )
{
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex_list[i].Scale(a,b,c);
    }
    
    length_a *= a;
    length_b *= b;
    length_c *= c;
}

void ShapeObject::Distortion(double movement)
{
    double a;
    double b;
    double c;
    
    for (int i = 0; i < vertex_list.size(); i++)
    {
        a = getUniformRandomNumber(-movement, movement);
        b = getUniformRandomNumber(-movement, movement);
        c = getUniformRandomNumber(-movement, movement);
        
        vertex_list[i].Move(a,b,c);
    }
}

void ShapeObject::RandomlyRotate()
{
    double a;
    double b;
    double c;
    
    a = getUniformRandomNumber(0, 2 * M_PI);
    b = getUniformRandomNumber(0, 2 * M_PI);
    c = getUniformRandomNumber(0, 2 * M_PI);

    
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex_list[i].RotX(a);
        vertex_list[i].RotY(b);
        vertex_list[i].RotZ(c);
    }
}

void ShapeObject::PrintAllFace()
{
    printf("\n Print all face \n");
    size_t all_face_num = face_list.size();
    
    for (size_t i = 0; i< all_face_num; i++)
    {
        Face * chosenFace = & face_list[i];
        
        chosenFace->printFace();
    }

}

// angleX angleY angleZ range from 0 - 180 degrees
void ShapeObject::RandomlyRotate(
        double angleX,
        double angleY,
        double angleZ
        )
{
    double a;
    double b;
    double c;
    
    double rotationX = angleX * DEG_TO_RAD;
    double rotationY = angleY * DEG_TO_RAD;
    double rotationZ = angleZ * DEG_TO_RAD;
    
    a = getUniformRandomNumber( -rotationX, rotationX);
    b = getUniformRandomNumber( -rotationY, rotationY);
    c = getUniformRandomNumber( -rotationZ, rotationZ);

    
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex_list[i].RotX(a);
        vertex_list[i].RotY(b);
        vertex_list[i].RotZ(c);
    }
}

void ShapeObject::Rotate(
        double angleX,
        double angleY,
        double angleZ
        )
{
    double rotationX = angleX * DEG_TO_RAD;
    double rotationY = angleY * DEG_TO_RAD;
    double rotationZ = angleZ * DEG_TO_RAD;
    
    
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex_list[i].RotX(rotationX);
        vertex_list[i].RotY(rotationY);
        vertex_list[i].RotZ(rotationZ);
    }
}


void ShapeObject::SlightlyRotateAlongXY(double angle)
{
    double a;
    double b;
    double c;
    
    double rotation = angle * DEG_TO_RAD;
    
    a = getUniformRandomNumber( -rotation, rotation);
    b = getUniformRandomNumber( -rotation, rotation);
    c = getUniformRandomNumber(     0    , 2 * M_PI);

    
    for (int i = 0; i < vertex_list.size(); i++)
    {
        vertex_list[i].RotX(a);
        vertex_list[i].RotY(b);
        vertex_list[i].RotZ(c);
    }
}

void ShapeObject::AddShape(const ShapeObject * shape)
{
    size_t original_size = vertex_list.size();
    
    for (size_t i = 0; i < shape->vertex_list.size(); i++)
    {
        vertex_list.push_back(shape->vertex_list[i]);
    }
    
    
    for (size_t i = 0; i < shape->face_list.size(); i++)
    {
        Face newface = shape->face_list[i];
        
        for(size_t j =0;j<newface.verts.size();j++)
        {
            newface.verts[j] += original_size;
        }
        
        face_list.push_back(newface);
    }

}

// merge near verteces
void ShapeObject::ConnectShape(const ShapeObject *obj, double threshold)
{
    size_t origin_ver_size  = vertex_list.size();
    size_t origin_face_size = face_list.size();
    
    AddShape(obj);
    
    std::vector<size_t> origin_ver;
    std::vector<size_t> obj_ver;
    
    for(size_t i = 0; i < origin_ver_size;i++)
        for(size_t j = origin_ver_size; j < vertex_list.size(); j++)
        {
            double dis = vertex_list[i].distance(vertex_list[j]);
            if(  ! (dis > threshold) )
            {
                origin_ver.push_back(i);
                obj_ver.push_back(j);

            }
        
        
        }
    
    // replace index
    // go over new added face
    for(size_t i = origin_face_size; i < face_list.size();i++)
    {
        // go over all vertices near to original obj
        for(size_t j = 0; j < obj_ver.size(); j++)
        {
            for(size_t k = 0; k < face_list[i].verts.size(); k++)
            {
                if(face_list[i].verts[k] == obj_ver[j])
                {
                    face_list[i].verts[k] = origin_ver[j];
                    continue;
                }
            }
        }
    }
    
}

void ShapeObject::ConnectShape(
    const ShapeObject *obj,
    double minDis,
    double maxDis)
{
    size_t origin_ver_size  = vertex_list.size();
    size_t origin_face_size = face_list.size();
    
    AddShape(obj);
    
//    std::vector<size_t> origin_ver;
//    std::vector<size_t> obj_ver;
//    
//    for(size_t i = 0; i < origin_ver_size;i++)
//        for(size_t j = origin_ver_size; j < vertex_list.size(); j++)
//        {
//            double dis = vertex_list[i].distance(vertex_list[j]);
//            if(  dis > minDis && dis<maxDis)
//            {
//                origin_ver.push_back(i);
//                obj_ver.push_back(j);
//
//            }
//        
//        
//        }
    double min = 0;
    int replacement_pos = -1;
    
    // nearest vertices in circle
    std::vector<size_t> origin_ver;
    
    // vertices in current object needs to be replaced
    std::vector<size_t> replaced_ver;
    
    // find nearest vertices
    for(size_t j = 0; j < origin_ver_size; j++)
    {
        min = 9999999999;
        replacement_pos = -1;
        
        for(size_t i = origin_ver_size; i < origin_ver_size + obj->vertex_list.size();i++)
        {
            double dis = vertex_list[i].distance(vertex_list[j]);
            if(  dis > minDis
                    && dis < maxDis
                    && vertex_list[j].z < (length_c/3)
                    && dis < min)
            {
                min = dis;
                replacement_pos = i;
            }
        
        
        }
        
        if(replacement_pos > 0)
        {
            origin_ver.push_back(replacement_pos);
            replaced_ver.push_back(j);
        }
        
        
    }
    
//    for(size_t j = 0; j < replaced_ver.size(); j++)
//    {
//        Face new_face;
//        
//        int x = replaced_ver[j];
//        int y = origin_ver[j];
//        
//        int z = origin_ver[j] + 1;
//        
//        if(z==vertex_list.size())
//            z = origin_ver_size;
//        
//        Vertex_Indices vert_ptrs = {
//            x, y, z
//        };
//        
//        AddFace('0', 3 , vert_ptrs);
//    }
//    PrintAllFace();
    
    for(size_t j = 0; j < replaced_ver.size(); j++)
    {
        // go over new added face from obj
        for(size_t i = 0; i < origin_face_size;i++)
        {
            for(size_t k = 0; k < face_list[i].verts.size(); k++)
            {
                if(face_list[i].verts[k] == replaced_ver[j])
                {
                    face_list[i].verts[k] = origin_ver[j];
                    continue;
                }
            }

//            if(face_list[i].verts[0] == replaced_ver[j]
//                && face_list[i].verts[1] != origin_ver[j]
//                && face_list[i].verts[2] != origin_ver[j])
//                {
//                    face_list[i].verts[0] = origin_ver[j];
//                    continue;
//                }
//            if(face_list[i].verts[0] != origin_ver[j]
//                && face_list[i].verts[1] == replaced_ver[j]
//                && face_list[i].verts[2] != origin_ver[j])
//                {
//                    face_list[i].verts[1] = origin_ver[j];
//                    continue;
//
//                }
//            if(face_list[i].verts[0] != origin_ver[j]
//                && face_list[i].verts[1] != origin_ver[j]
//                && face_list[i].verts[2] == replaced_ver[j])
//                {
//                    face_list[i].verts[2] = origin_ver[j];
//                    continue;
//
//                }

        }
    }
    
//    PrintAllFace();
//    for(size_t i = 0; i < origin_face_size;i++)
//    {
//        face_list[i].printFace();
//    
//    }

    // replace index
    // go over new added face
//    for(size_t i = origin_face_size; i < face_list.size();i++)
//    {
//        // go over all vertices near to original obj
//        for(size_t j = 0; j < obj_ver.size(); j++)
//        {
//            for(size_t k = 0; k < face_list[i].verts.size(); k++)
//            {
//                if(face_list[i].verts[k] == obj_ver[j])
//                {
//                    face_list[i].verts[k] = origin_ver[j];
//                    continue;
//                }
//            }
//        }
//    }
    
}



void ShapeObject::DivideAllFace(double movement)
{
    size_t all_face_num = face_list.size();
    
    for (size_t i = 0; i< all_face_num; i++)
    {
        Face * chosenFace = & face_list[0];
//        PrintAllFace();
        DivideOneFace(chosenFace,0,movement);
        
//        PrintAllFace();
    }
}


void ShapeObject::DivideFace(double movement)
{
    int face_num = getUniformRandomNumber( 0 , face_list.size() );
    
    //double temp = face_list.size() * getExponentialDisRandomNumber(0.2);
    
    //face_num = (int)temp;
    
    //printf("Chosen face %d \n",face_num);
    
    Face * chosenFace = & face_list[face_num];
    
    DivideOneFace(chosenFace,face_num,movement);
}


void ShapeObject::DivideOneFace(
    Face * chosenFace,
    int chosenFaceIndex,
    double movement)
{
    
    // vertex number of this face
    int numVertex = chosenFace->getTotalIndexNum();
    
    Vertex new_v;
    
    for(int i = 0; i < numVertex; i++)
        new_v.vertexAddVertex(vertex_list[chosenFace->getIndexAt(i)]);
    
    // calculate average pos of new vertex
    double average_factor = (double) 1 / numVertex;
    
    new_v.Scale(average_factor, average_factor, average_factor);
    
    // randomly move the new point
    double a;
    double b;
    double c;
    
    a = getUniformRandomNumber(-movement, movement);
    b = getUniformRandomNumber(-movement, movement);
    c = getUniformRandomNumber(-movement, movement);
    
    new_v.Move(a, b, c);
    
    // Add new vertex into vertex_list
    AddVertex( &new_v );
    
    // Add new faces
    int indexs[numVertex];
    for( int i = 0 ; i < numVertex ; i ++ )
        indexs[i] = chosenFace->getIndexAt(i);
    
    for( int i = 0 ; i < numVertex ; i ++ )
    {
        int vertexs[3];
        vertexs[0] = indexs[i];

        int next = -1;
        if( i+1 < numVertex)
            next = i+1;
        else
            next = 0;
            
        vertexs[1] = indexs[next];
        
        vertexs[2] = new_v.id;
        
        AddFace('0', 3 , vertexs);
    }
    
    // delete chosen face
    deleteFace(chosenFaceIndex);
}





void ShapeObject::deleteFace(int faceIndex)
{
    face_list.erase(face_list.begin()+faceIndex);
}




// merge near vertices ONLY to Plane
void Plane::ConnectShape(const ShapeObject *obj, double threshold)
{
    size_t origin_ver_size  = vertex_list.size();
    size_t origin_face_size = face_list.size();
    
    AddShape(obj);
    
    std::vector<size_t> origin_ver;
    std::vector<size_t> obj_ver;
    
    // find near vertices
    for(size_t i = 0; i < plane_ver_num;i++)
        for(size_t j = origin_ver_size; j < vertex_list.size(); j++)
        {
            double dis = vertex_list[i].distance(vertex_list[j]);
            if(  ! (dis > threshold) )
            {
                origin_ver.push_back(i);
                obj_ver.push_back(j);
                
            }
        
        
        }
    
    // replace index
    
    // go over new added face
    for(size_t i = origin_face_size; i < face_list.size();i++)
    {
        // go over all vertices near to original obj
        for(size_t j = 0; j < obj_ver.size(); j++)
        {
            for(size_t k = 0; k < face_list[i].verts.size(); k++)
            {
                if(face_list[i].verts[k] == obj_ver[j])
                {
                    face_list[i].verts[k] = origin_ver[j];
                    continue;
                }
            }
        }
    }
    
}

void ShapeObject::AddTails(double minDis, double maxDis)
{
//    size_t origin_ver_size  = vertex_list.size();
//    size_t origin_face_size = face_list.size();
    
    double center_x = 0;
    double center_y = 0;
    
    for(size_t j = 0; j < vertex_list.size(); j++)
    {
        center_x += vertex_list[j].x;
        center_y += vertex_list[j].y;
    }
    
    center_x /= vertex_list.size();
    center_y /= vertex_list.size();
    
        
    double R = sqrt(length_a*length_a+length_b*length_b)/2 + 0.05;
    CirclePoint cir(R);
    cir.MoveObject(center_x, center_y, 0);
    
    
    ConnectShape(&cir, minDis, maxDis);


}


//void Plane::ConnectShape(
//        const ShapeObject *obj,
//        double minDis,
//        double maxDis)
//{
//    size_t origin_ver_size  = vertex_list.size();
//    size_t origin_face_size = face_list.size();
//    
//    AddShape(obj);
//    
//    size_t with_obj_ver_size  = vertex_list.size();
//    
//    
//    // nearest vertices in circle
//    std::vector<size_t> origin_ver;
//    
//    // vertices in obj needs to be replaced
//    std::vector<size_t> obj_ver;
//    
//    
//    double center_x = 0;
//    double center_y = 0;
//    
//    for(size_t j = 0; j < obj->vertex_list.size(); j++)
//    {
//        center_x += obj->vertex_list[j].x;
//        center_y += obj->vertex_list[j].y;
//    }
//    
//    center_x /= obj->vertex_list.size();
//    center_y /= obj->vertex_list.size();
//    
//    
//    std::vector<Vertex> circle;
//    
//    double R = sqrt(obj->length_a*obj->length_a+obj->length_b*obj->length_b)/2 + 0.05;
//    
//    size_t circle_num = 10;
//    
//    for(double phi = 0; phi < 2 * 3.1415; phi += 2 *3.1415/circle_num)
//    {
//        Vertex v;
//        v.x = R*cos(phi) + center_x;
//        v.y = R*sin(phi) + center_y;
//        v.z = 0;
//        AddVertex(&v);
//    }
//    
//    double min = 0;
//    int min_entry = -1;
//    
//    // find near vertices
//    for(size_t j = origin_ver_size; j < with_obj_ver_size; j++)
//    {
//        min = 999;
//        min_entry = -1;
//        
//        for(size_t i = with_obj_ver_size; i < with_obj_ver_size + circle_num;i++)
//        {
//            double dis = vertex_list[i].distance(vertex_list[j]);
//            if(  dis > minDis
//                    && dis < maxDis
//                    && vertex_list[j].z < (obj->length_c/3)
//                    && dis < min)
//            {
//                min = dis;
//                min_entry = i;
//            }
//        
//        
//        }
//        
//        if(min_entry > 0)
//        {
//            origin_ver.push_back(min_entry);
//            obj_ver.push_back(j);
//        }
//        
//        
//    }
//    // replace index
//    
//    // go over all vertices near to original obj
//    for(size_t j = 0; j < obj_ver.size(); j++)
//    {
//        // go over new added face from obj
//        for(size_t i = origin_face_size; i < face_list.size();i++)
//        {
////            for(size_t k = 0; k < face_list[i].verts.size(); k++)
////            {
////                if(face_list[i].verts[k] == obj_ver[j])
////                {
////                    face_list[i].verts[k] = origin_ver[j];
////                    continue;
////                }
////            }
//
////            if(face_list[i].verts[0] == obj_ver[j]
////                && face_list[i].verts[1] != origin_ver[j]
////                && face_list[i].verts[2] != origin_ver[j])
////                {
////                    face_list[i].verts[0] = origin_ver[j];
////                    
////                }
////            if(face_list[i].verts[0] != origin_ver[j]
////                && face_list[i].verts[1] == obj_ver[j]
////                && face_list[i].verts[2] != origin_ver[j])
////                {
////                    face_list[i].verts[1] = origin_ver[j];
////                    
////                }
////            if(face_list[i].verts[0] != origin_ver[j]
////                && face_list[i].verts[1] != origin_ver[j]
////                && face_list[i].verts[2] == obj_ver[j])
////                {
////                    face_list[i].verts[2] = origin_ver[j];
////                    
////                }
//
//        }
//    }
//    
//    
//
//    origin_ver.empty();
//    obj_ver.empty();
//}


void Vertex::RotX(double theta)
{
    double a = x;
    double b = y;
    double c = z;
    
    x = a;
    y = cos(theta) * b - sin(theta) * c;
    z = cos(theta) * c + sin(theta) * b;
}

void Vertex::RotY(double theta)
{
    double a = x;
    double b = y;
    double c = z;
    
    x = cos(theta) * a + sin(theta) * c;
    y = b;
    z = cos(theta) * c - sin(theta) * a;;
}

void Vertex::RotZ(double theta)
{
    double a = x;
    double b = y;
    double c = z;
    
    x = cos(theta) * a - sin(theta) * b;
    y = cos(theta) * b + sin(theta) * a;
    z = c;
}

void ShapeObject::RandomlyStretch()
{
    int face_num = getUniformRandomNumber( 0 , face_list.size() );
    
    Face * chosenFace = & face_list[face_num];
    
    // vertex number of this face
    int numVertex = chosenFace->getTotalIndexNum();
    
    Vertex ver1 = vertex_list[chosenFace->getIndexAt(0)];
    Vertex ver2 = vertex_list[chosenFace->getIndexAt(1)];
    Vertex ver3 = vertex_list[chosenFace->getIndexAt(2)];
    
    Vector v1 = Vector(
        ver1.x-ver2.x,
        ver1.y-ver2.y,
        ver1.z-ver2.z
        );
    Vector v2 = Vector(
        ver3.x-ver2.x,
        ver3.y-ver2.y,
        ver3.z-ver2.z
        );
    Vector normal = Cross(v1, v2);
    
    double ran = getUniformRandomNumber(-0.5, 0.5);
    
    // randomly shift along normal direction of the chosen face
    normal = normal * ran;
    
    for( int i = 0 ; i < numVertex ; i ++ )
    {
        vertex_list[chosenFace->getIndexAt(i)].vertexAddVertex(normal);
    }

}


void Mushroom::Distortion(double movement)
{
        double a;
        double b;
        double c;
        
        for (int i = 0; i < vertex_list.size(); i++)
        {
            if( is_cube[i] == true )
            {
                a = getUniformRandomNumber(-movement, movement);
                b = getUniformRandomNumber(-movement, movement);
                c = getUniformRandomNumber(-movement, movement);
            
                vertex_list[i].Move(a,b,c);
            }
        }
    }


void Mushroom::RandomlyRotate(
        double angleX,
        double angleY,
        double angleZ
        )
{
    double a;
    double b;
    double c;
    
    double rotationX = angleX * DEG_TO_RAD;
    double rotationY = angleY * DEG_TO_RAD;
    double rotationZ = angleZ * DEG_TO_RAD;
    
    a = getUniformRandomNumber( -rotationX, rotationX);
    b = getUniformRandomNumber( -rotationY, rotationY);
    c = getUniformRandomNumber( -rotationZ, rotationZ);

    
    for (int i = 0; i < vertex_list.size(); i++)
    {
        if( is_cube[i] == true )
        {
            vertex_list[i].RotX(a);
            vertex_list[i].RotY(b);
            vertex_list[i].RotZ(c);
        }
    }
}

void Wall_With_Tail::Distortion(double movement)
{
        double a;
        double b;
        double c;
        
        for (int i = 0; i < vertex_list.size(); i++)
        {
            if( is_cube[i] == true )
            {
                a = getUniformRandomNumber(-movement, movement);
                b = getUniformRandomNumber(-movement, movement);
                c = getUniformRandomNumber(-movement, movement);
            
                vertex_list[i].Move(a,b,c);
            }
        }
    }


void Wall_With_Tail::RandomlyRotate(
        double angleX,
        double angleY,
        double angleZ
        )
{
    double a;
    double b;
    double c;
    
    double rotationX = angleX * DEG_TO_RAD;
    double rotationY = angleY * DEG_TO_RAD;
    double rotationZ = angleZ * DEG_TO_RAD;
    
    a = getUniformRandomNumber( -rotationX, rotationX);
    b = getUniformRandomNumber( -rotationY, rotationY);
    c = getUniformRandomNumber( -rotationZ, rotationZ);

    
    for (int i = 0; i < vertex_list.size(); i++)
    {
        if( is_cube[i] == true )
        {
            vertex_list[i].RotX(a);
            vertex_list[i].RotY(b);
            vertex_list[i].RotZ(c);
        }
    }
}

