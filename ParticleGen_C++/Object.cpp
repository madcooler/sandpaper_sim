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

