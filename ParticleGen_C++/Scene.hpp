//
//  Scene.hpp
//  ParticleGen_C++
//
//  Created by Administrator on 26/08/16.
//  Copyright © 2016 Administrator. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "Object.h"

class Scene
{

    std::vector< ShapeObject * > scene;

public:
    void AddObject(ShapeObject * obj)
    {
        scene.push_back(obj);
    }
    
    void writeSceneToPLYFiles();
    void writeScene(char * filename);
    void DeleteInvalidFace();
};


typedef struct RawVertex {
  float x,y,z;             /* the usual 3-space position of a vertex */
} RawVertex;

typedef struct RawFace {
  unsigned char intensity; /* this user attaches intensity to faces */
  unsigned char nverts;    /* number of vertex indices in list */
  int *verts;              /* vertex index list */
} RawFace;

#endif /* Scene_hpp */
