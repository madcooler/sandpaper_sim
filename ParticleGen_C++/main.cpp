//
//  main.cpp
//  ParticleGen_C++
//
//  Created by Administrator on 26/08/16.
//  Copyright © 2016 Administrator. All rights reserved.
//

#include <iostream>
#include "Scene.hpp"
#include "surfaceGeneration.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
//    Cube cube1(0.5);
//    cube1.Distortion( 0.2 );
//    
//    cube1.RandomlyRotate();
    
//    int disNum = 10;
//    double divideParameter = 0.2;
//    
//    Tetrahedron tetra1(0.5);
//    tetra1.Distortion(0.2);
//    tetra1.MoveObject(1, 0, 0);
//    
//    for ( int i = 0 ; i < disNum;i++)
//    {
//        tetra1.DivideFace(divideParameter/(i+1));
//        cube1.DivideFace (divideParameter/(i+1));
//    }
    
    //Scene myscene;
    //myscene.AddObject(& cube1);
    //myscene.AddObject(& tetra1);
    //myscene.writeScene();
    
    generateSurface();
    
    return 0;
}
