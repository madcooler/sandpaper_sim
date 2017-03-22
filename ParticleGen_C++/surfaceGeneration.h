//
//  surfaceGeneration.h
//  ParticleGen_C++
//
//  Created by Administrator on 28/08/16.
//  Copyright © 2016 Administrator. All rights reserved.
//

#ifndef surfaceGeneration_h
#define surfaceGeneration_h
#include "RandomNumber.h"
#include "Scene.hpp"

#define WIDTH   1
#define HEIGHT  1

// denstity of particle per unit grid
#define DENSITY 1

#define HasPlane false

inline void generateSurface()
{
    Scene myscene;
    
    Plane p1( WIDTH ,HEIGHT);
    
    // parameters used in siggraph mesh
//    int     disNum                  =  1;
//    double  distortionParameter     = 0.2;
//    double  divideParameter         = 0.2;
////    double  cubeSize                = 0.5;
//    int     Rot_X                   = 45;
    
    int     disNum                  =  2;
    double  distortionParameter     = 0.01;
    double  divideParameter         = 0.2;
//    double  cubeSize                = 0.5;
    int     Rot_X                   = 0;
    
    if(HasPlane)
    {
        myscene.AddObject( & p1 );
    }
    
    
    ShapeObject * objPointer;
    
//    objPointer = new Mushroom(0.5);
//    myscene.AddObject( objPointer );
    
    for(int i = 0; i < WIDTH; i++)
        for( int j = 0; j< HEIGHT;j++)
            for( int l = 0; l < DENSITY; l++ )
            {
                
                //int chooseObj = getUniformRandomNumber(0.0,2.0);
//                double a = getUniformRandomNumber(0.0,1.0);
//                double b = getUniformRandomNumber(0.0,1.0);
//                double c = getUniformRandomNumber(0.5,1.0);

                double a = getUniformRandomNumber(0.0,1.0);
                double b = getUniformRandomNumber(0.0,1.0);
                double c = getUniformRandomNumber(0.5,1.0);
                
                objPointer  = new Cube(1);
                
    //            if ( chooseObj < 1.0)
    //                objSet[i][j][l]  = Cube(0.8);
    //            else
    //                objSet[i][j][l]  = Tetrahedron(0.8);
                
                
                
                objPointer->Distortion( distortionParameter );
                
                for ( int k = 0 ; k < disNum; k++)
                {
                    objPointer->DivideFace(divideParameter/(k+1));
                }
                
                
//                objPointer->RandomlyRotate( Rot_X, Rot_X, 180 );
                
                // move obj to corresponding grid with a little random shift
                a = getUniformRandomNumber( - 0.2, 0.2 );
                b = getUniformRandomNumber( - 0.2, 0.2 );
                c = getUniformRandomNumber(   0.0, 0.5 );
                
//                objPointer->MoveObject(
//                    ( i - WIDTH /2 + a  ),
//                    ( j - HEIGHT/2 + b ),
//                                   + c
//                    );
                
//                myscene.AddObject( objPointer );
//                
//                objPointer = new GaussianSurface(0.5);
//                
//                objPointer->MoveObject(
//                    ( i - WIDTH /2  ),
//                    ( j - HEIGHT/2  ),
//                      0
//                    );
                
                myscene.AddObject( objPointer );
            }
    
    char filename[50];
//    sprintf(filename, "c_%d_%d_%d_%d_%d_%d.ply",
//            WIDTH,
//            DENSITY,
//            disNum,
//            (int)(divideParameter * 10),
//            (int)(distortionParameter * 10),
//            Rot_X
//            );
    sprintf(filename, "c_%d_line.ply",
            HEIGHT
            );
    sprintf(filename, "c_%d_%d_%d_%d_%d_%d.ply",
            WIDTH,
            DENSITY,
            disNum,
            (int)(divideParameter * 10),
            (int)(distortionParameter * 10),
            Rot_X
            );

    
    myscene.writeScene(filename);
}


inline void generateSurface_old()
{
    Scene myscene;
    
    Plane p1( WIDTH ,HEIGHT);
    
    // parameters used in siggraph mesh
    int     disNum                  =  1;
    double  distortionParameter     = 0.2;
    double  divideParameter         = 0.2;
//    double  cubeSize                = 0.5;
    int     Rot_X                   = 45;
    
    
    if(HasPlane)
    {
        myscene.AddObject( & p1 );
    }
    
    
    ShapeObject * objPointer;
    
    for(int i = 0; i < WIDTH; i++)
        for( int j = 0; j< HEIGHT;j++)
            for( int l = 0; l < DENSITY; l++ )
            {
                
                //int chooseObj = getUniformRandomNumber(0.0,2.0);
//                double a = getUniformRandomNumber(0.0,1.0);
//                double b = getUniformRandomNumber(0.0,1.0);
//                double c = getUniformRandomNumber(0.5,1.0);

                double a = getUniformRandomNumber(0.0,1.0);
                double b = getUniformRandomNumber(0.0,1.0);
                double c = getUniformRandomNumber(0.5,1.0);
                
                objPointer  = new Cube(a,b,c);
                
    //            if ( chooseObj < 1.0)
    //                objSet[i][j][l]  = Cube(0.8);
    //            else
    //                objSet[i][j][l]  = Tetrahedron(0.8);
                
                
                
                objPointer->Distortion( distortionParameter );
                
                for ( int k = 0 ; k < disNum; k++)
                {
                    objPointer->DivideFace(divideParameter/(k+1));
                }
                
                
                objPointer->RandomlyRotate( Rot_X, Rot_X, 180 );
                
                // move obj to corresponding grid with a little random shift
                a = getUniformRandomNumber( - 0.2, 0.2 );
                b = getUniformRandomNumber( - 0.2, 0.2 );
                c = getUniformRandomNumber(   0.0, 0.5 );
                
                objPointer->MoveObject(
                    ( i - WIDTH /2 + a  ),
                    ( j - HEIGHT/2 + b ),
                                   + c
                    );
                
                myscene.AddObject( objPointer );
            }
    
    char filename[50];
//    sprintf(filename, "c_%d_%d_%d_%d_%d_%d.ply",
//            WIDTH,
//            DENSITY,
//            disNum,
//            (int)(divideParameter * 10),
//            (int)(distortionParameter * 10),
//            Rot_X
//            );
    sprintf(filename, "c_%d_line.ply",
            HEIGHT
            );
    sprintf(filename, "c_%d_%d_%d_%d_%d_%d.ply",
            WIDTH,
            DENSITY,
            disNum,
            (int)(divideParameter * 10),
            (int)(distortionParameter * 10),
            Rot_X
            );

    
    myscene.writeScene(filename);
}



#endif /* surfaceGeneration_h */
