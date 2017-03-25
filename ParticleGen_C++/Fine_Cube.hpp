//
//  Fine_Cube.hpp
//  ParticleGen_C++
//
//  Created by Administrator on 23/03/2017.
//  Copyright © 2017 Administrator. All rights reserved.
//
#pragma once

#ifndef Fine_Cube_hpp
#define Fine_Cube_hpp

#include <stdio.h>
#include "Object.h"


class Fine_Cube:public ShapeObject
{
    
//    std::vector<size_t> corner_ver_num;
    
public:
    Fine_Cube(int res)
    {
        CreateUnityCube(res);
    }
    
    Fine_Cube(int res,double a,double b,double c)
    {
        CreateUnityCube(res);
        
        ScaleObject(a, b, c);
    }

    void CreateUnityCube(int res);
    
    void Unity_Cube_5(
        double * x,
        double * y,
        double * z,
        Vertex_Indices * vert,
        size_t * ver_num,
        size_t * face_num
        );
        
    void ConnectCircle();
};



#endif /* Fine_Cube_hpp */
