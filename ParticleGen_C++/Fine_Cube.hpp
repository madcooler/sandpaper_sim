//
//  Fine_Cube.hpp
//  ParticleGen_C++
//
//  Created by Administrator on 23/03/2017.
//  Copyright © 2017 Administrator. All rights reserved.
//

#ifndef Fine_Cube_hpp
#define Fine_Cube_hpp

#include <stdio.h>
#include "Object.h"


class Fine_Cube:public ShapeObject
{
    Plane            *  top;
    Plane            *  bottom;
    Plane            *  left;
    Plane            *  right;
    Plane            *  front;
    Plane            *  back;
    
    
public:
    Fine_Cube(int res)
    {
        top     = new Plane(res);
        top->MoveObject(0, 0, 1);
        
        bottom  = new Plane(res);
        
        left    = new Plane(res);
        left->Rotate(90, 0, 0);
        left->MoveObject(0, -0.5, 0.5);
        
        back    = new Plane(res);
        back->Rotate(0, -90, 0);
        back->MoveObject(-0.5, 0, 0.5);
        
        right   = new Plane(res);
        right->Rotate(-90, 0, 0);
        right->MoveObject(0, 0.5, 0.5);
        
        front   = new Plane(res);
        front->Rotate(0, 90, 0);
        front->MoveObject(0.5, 0, 0.5);
        
        
        AddShape(bottom);
        AddShape(top);
        ConnectShape(left, 0.001);
        ConnectShape(right, 0.001);
        ConnectShape(front, 0.001);
        ConnectShape(back, 0.001);
//        ConnectShape(top, 0);
        
        
//        AddShape(left);
//        AddShape(right);
//        AddShape(front);
//        AddShape(back);
//        
//        AddShape(top);
        
        
        
        
    }
    
    Fine_Cube(int res,double a,double b,double c)
    {
        top     = new Plane(res);
        top->MoveObject(0, 0, 1);
        
        bottom  = new Plane(res);
        
        left    = new Plane(res);
        left->Rotate(90, 0, 0);
        left->MoveObject(0, -0.5, 0.5);
        
        back    = new Plane(res);
        back->Rotate(0, -90, 0);
        back->MoveObject(-0.5, 0, 0.5);
        
        right   = new Plane(res);
        right->Rotate(-90, 0, 0);
        right->MoveObject(0, 0.5, 0.5);
        
        front   = new Plane(res);
        front->Rotate(0, 90, 0);
        front->MoveObject(0.5, 0, 0.5);
        
        
        
        AddShape(bottom);
        AddShape(top);
        ConnectShape(left, 0.001);
        ConnectShape(right, 0.001);
        ConnectShape(front, 0.001);
        ConnectShape(back, 0.001);


        ScaleObject(a, b, c);
    
    }


};

#endif /* Fine_Cube_hpp */
