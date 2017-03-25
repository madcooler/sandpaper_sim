//
//  Object.h
//  plytest
//
//  Created by Administrator on 26/08/16.
//  Copyright © 2016 Administrator. All rights reserved.
//

#ifndef Object_h
#define Object_h
#include <math.h>
#include <vector>

typedef int Vertex_Indices[3];
typedef int Vertex_Indices_4[4];

#define Vertex Vector
#define RAD_TO_DEG 180/M_PI
#define DEG_TO_RAD M_PI/180

class Vertex
{
public:
    double x;
    double y;
    double z;
    
    // i-th vertex of an object
    int id;
    void Move(double a,double b,double c)
    {
        x += a;
        y += b;
        z += c;
    }

    void Scale(double a,double b,double c)
    {
        x *= a;
        y *= b;
        z *= c;
    }

    void vertexAddVertex(Vertex v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    
    double distance(Vertex v)
    {
        return sqrt( (x-v.x)*(x-v.x) + (y-v.y)*(y-v.y) + (z-v.z)*(z-v.z));
    }

    
    Vertex()
    {
        x = y = z = 0;
        id = -1;
    }
    
    Vertex(double a,double b,double c)
    {
        x = a;
        y = b;
        z = c;
    }
    
    void operator = (Vertex v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    
    Vertex operator * (double t)
    {
        Scale(t, t, t);
        return *this;
    }
    
    void RotX(double theta);
    void RotY(double theta);
    void RotZ(double theta);

} ;

class Face
{
public:
  unsigned char     intensity; /* this user attaches intensity to faces */
  unsigned int      nverts;    /* number of vertex indices in list */
  
  std::vector<int>  verts;           /* vertex index list */
 

  int getIndexAt(int t)
  {
    return verts[t];
  }
  
  void setVertexNumber( int n)
  {
    nverts = n;
  }
  
  void addIndex(int i)
  {
    verts.push_back(i);
    //nverts++;
  }
  
  int getTotalIndexNum()
  {
    return nverts;
  }
  
  void printFace()
  {
    for( int i = 0 ; i < nverts ; i ++ )
    {
        int ind = verts[i];
        printf(" %d ",ind);
    }

  }
} ;


class ShapeObject
{
public:
    double length_a;
    double length_b;
    double length_c;
    
    std::vector< Vertex > vertex_list;
    std::vector< Face   > face_list;

    ShapeObject()
    {
        length_a = 1;
        length_b = 1;
        length_c = 1;

    };
    ~ShapeObject()
    {
        vertex_list.empty();
        face_list.empty();
    };
    
    void AddShape(const ShapeObject * shape);
    
    void AddVertex(
        double a,
        double b,
        double c
    )
    {
        Vertex v;
        v.x = a;
        v.y = b;
        v.z = c;
        v.id = vertex_list.size();
        vertex_list.push_back(v);
    }
    void AddVertex(Vertex *v)
    {
        v->id = vertex_list.size();
        vertex_list.push_back(*v);
    }
    void AddFace(
        unsigned char inten,
        unsigned int nv,
        int *v
    )
    {
        Face f;
        //f.intensity = inten;
        f.setVertexNumber(nv);
        for(int i = 0;i < nv; i++)
            f.addIndex(v[i]);
        
        face_list.push_back(f);
    }
    
    void setNewVertexWithID (Vertex *v)
    {
        v->id = vertex_list.size();
    }
    void deleteFace (int faceIndex);
    void MoveObject (double a,double b,double c);
    void ScaleObject(double a,double b,double c);
    void RandomlyRotate();
    
    virtual void RandomlyRotate(
        double angleX,
        double angleY,
        double angleZ
        );
    
    virtual void Rotate(
        double angleX,
        double angleY,
        double angleZ
        );
    
    void SlightlyRotateAlongXY(double angle);
    
    virtual void Distortion (double movement);
    
    void DivideFace (double movement);
    
    void DivideOneFace(
        Face * chosenFace,
        int chosenFaceIndex,
        double movement
        );
    
    void DivideAllFace(double movement);
    
    void RandomlyStretch();
    
    void PrintAllFace();
    
    virtual void ConnectShape(
        const ShapeObject * obj,
        double threshold);
    
    virtual void ConnectShape(
        const ShapeObject *obj,
        double minDis,
        double maxDis);
    
    virtual void AddTails(
        double minDis,
        double maxDis);
};

class Cube : public ShapeObject
{

public:
    Cube()
    {
    }
    Cube( double size ): ShapeObject()
    {
        AddVertex( 0, 0, 0 );
        AddVertex( size, 0, 0 );
        AddVertex( size, size, 0 );
        AddVertex( 0, size, 0 );
        AddVertex( 0, 0, size );
        AddVertex( size, 0, size );
        AddVertex( size, size, size );
        AddVertex( 0, size, size );
        
        MoveObject(-size/2, -size/2, -size/2);
        
        Vertex_Indices vert_ptrs[] = {
            { 0, 2, 1 },
            { 7, 5, 6 },
            { 0, 5, 4 },
            { 1, 6, 5 },
            { 2, 7, 6 },
            { 3, 4, 7 },
            { 0, 3, 2 },
            { 7, 4, 5 },
            { 0, 1, 5 },
            { 1, 2, 6 },
            { 2, 3, 7 },
            { 3, 0, 4 },
        };
        
        AddFace('0', 3 , vert_ptrs[0]);
        AddFace('0', 3 , vert_ptrs[1]);
        AddFace('0', 3 , vert_ptrs[2]);
        AddFace('0', 3 , vert_ptrs[3]);
        AddFace('0', 3 , vert_ptrs[4]);
        AddFace('0', 3 , vert_ptrs[5]);
        AddFace('0', 3 , vert_ptrs[6]);
        AddFace('0', 3 , vert_ptrs[7]);
        AddFace('0', 3 , vert_ptrs[8]);
        AddFace('0', 3 , vert_ptrs[9]);
        AddFace('0', 3 , vert_ptrs[10]);
        AddFace('0', 3 , vert_ptrs[11]);
    }
    
    Cube( double length, double width,double height ): ShapeObject()
    {
        AddVertex( 0, 0, 0 );
        AddVertex( length, 0, 0 );
        AddVertex( length, width, 0 );
        AddVertex( 0, width, 0 );
        AddVertex( 0, 0, height );
        AddVertex( length, 0, height );
        AddVertex( length, width, height );
        AddVertex( 0, width, height );
        
        MoveObject(-length/2, -width/2, -height/2);
        
        Vertex_Indices vert_ptrs[] = {
            { 0, 2, 1 },
            { 7, 5, 6 },
            { 0, 5, 4 },
            { 1, 6, 5 },
            { 2, 7, 6 },
            { 3, 4, 7 },
            { 0, 3, 2 },
            { 7, 4, 5 },
            { 0, 1, 5 },
            { 1, 2, 6 },
            { 2, 3, 7 },
            { 3, 0, 4 },
        };
        
        AddFace('0', 3 , vert_ptrs[0]);
        AddFace('0', 3 , vert_ptrs[1]);
        AddFace('0', 3 , vert_ptrs[2]);
        AddFace('0', 3 , vert_ptrs[3]);
        AddFace('0', 3 , vert_ptrs[4]);
        AddFace('0', 3 , vert_ptrs[5]);
        AddFace('0', 3 , vert_ptrs[6]);
        AddFace('0', 3 , vert_ptrs[7]);
        AddFace('0', 3 , vert_ptrs[8]);
        AddFace('0', 3 , vert_ptrs[9]);
        AddFace('0', 3 , vert_ptrs[10]);
        AddFace('0', 3 , vert_ptrs[11]);
    }
    
    Cube( double length, double width,double height, int faceNum )
    {
        AddVertex( 0, 0, 0 );
        AddVertex( length, 0, 0 );
        AddVertex( length, width, 0 );
        AddVertex( 0, width, 0 );
        AddVertex( 0, 0, height );
        AddVertex( length, 0, height );
        AddVertex( length, width, height );
        AddVertex( 0, width, height );
        
        MoveObject(-length/2, -width/2, -height/2);
        
        Vertex_Indices_4 vert_ptrs[] = {
            { 0, 3, 2, 1 },
            { 4, 5, 6 ,7 },
            { 0, 1, 5, 4 },
            { 1, 2, 6, 5 },
            { 2, 3, 7, 6 },
            { 3, 0, 4, 7 },
        };
        
        AddFace('0', 4 , vert_ptrs[0]);
        AddFace('0', 4 , vert_ptrs[1]);
        AddFace('0', 4 , vert_ptrs[2]);
        AddFace('0', 4 , vert_ptrs[3]);
        AddFace('0', 4 , vert_ptrs[4]);
        AddFace('0', 4 , vert_ptrs[5]);
    }


};


class Tetrahedron : public ShapeObject
{

public:
    Tetrahedron()
    {
    }
    Tetrahedron( double size ): ShapeObject()
    {
        AddVertex( 0, 0, 0);
        AddVertex( size, size, 0);
        AddVertex( size, 0, size);
        AddVertex( 0, size, size);
        
        Vertex_Indices vert_ptrs[] = {
            { 0, 1, 2 },
            { 0, 1, 3 },
            { 0, 2, 3 },
            { 1, 3, 2 },
        };
        
        AddFace('0', 3 , vert_ptrs[0]);
        AddFace('0', 3 , vert_ptrs[1]);
        AddFace('0', 3 , vert_ptrs[2]);
        AddFace('0', 3 , vert_ptrs[3]);
        
    }
    
    
};


class Circle : public ShapeObject
{

public:
    Circle()
    {
    }
    Circle( double R ): ShapeObject()
    {
        size_t circle_num = 10;
    
        for(double phi = 0; phi < 2 * 3.1415; phi += 2 *3.1415/circle_num)
        {
            Vertex v;
            v.x = R*cos(phi);
            v.y = R*sin(phi);
            v.z = 0;
            AddVertex(&v);
        }
    
        
        Vertex_Indices vert_ptrs[] = {
            { 0, 1, 2 },
            { 1, 2, 3 },
            { 2, 3, 4 },
            { 3, 4, 5 },
            { 4, 5, 6 },
            { 5, 6, 7 },
            { 6, 7, 8 },
            { 7, 8, 9 },
            { 8, 9, 0 },
        };
//
        AddFace('0', 3 , vert_ptrs[0]);
        AddFace('0', 3 , vert_ptrs[1]);
        AddFace('0', 3 , vert_ptrs[2]);
        AddFace('0', 3 , vert_ptrs[3]);
        AddFace('0', 3 , vert_ptrs[4]);
        AddFace('0', 3 , vert_ptrs[5]);
        AddFace('0', 3 , vert_ptrs[6]);
        AddFace('0', 3 , vert_ptrs[7]);
        AddFace('0', 3 , vert_ptrs[8]);

        
    }
    
    
};


class Plane : public ShapeObject
{
    size_t plane_ver_num;
    size_t plane_face_num;
public:
    Plane(): ShapeObject()
    {
        AddVertex( -0.5, -0.5, 0);
        AddVertex(  0.5, -0.5, 0);
        AddVertex(  0.5,  0.5, 0);
        AddVertex( -0.5,  0.5, 0);
        
        Vertex_Indices vert_ptrs[] = {
            { 0, 1, 2 },
            { 2, 3, 0 },
        };
        
        AddFace('0', 3 , vert_ptrs[0]);
        AddFace('0', 3 , vert_ptrs[1]);
    }
    
    Plane(double width, double height): ShapeObject()
    {
        AddVertex( -(width)/2, -(height/2), 0);
        AddVertex(  (width)/2, -(height/2), 0);
        AddVertex(  (width)/2,  (height/2), 0);
        AddVertex( -(width)/2,  (height/2), 0);
        
        Vertex_Indices vert_ptrs[] = {
            { 0, 1, 2 },
            { 2, 3, 0 },
        };
        
        AddFace('0', 3 , vert_ptrs[0]);
        AddFace('0', 3 , vert_ptrs[1]);
        
        length_a = width;
        length_b = height;
    }
    
    Plane(int res,double width, double height): ShapeObject()
    {
        double x;
        double y;
        double z = 0;
        
        for(int i = 0; i < res; i++)
        {
            for(int j = 0; j < res; j++)
            {
                x = ( (double)(i - res/2 )/(res-1)) * width;
                y = ( (double)(j - res/2 )/(res-1)) * height;
                AddVertex(x, y, z);
            }
        }
    
    
        for(int i = 0; i < res - 1; i++)
            for(int j = 0; j < res - 1; j++)
            {
                Vertex_Indices vert_ptrs[] = {
                        {   i * res + j,
                            (i+1) * res + j,
                            i * res + j+1
                            
                        },
                    
                        {   i*res+j+1,
                            (i+1) * res + j,
                            (i+1) * res + j+1
                        },
                    };
                
                AddFace('0', 3 , vert_ptrs[0]);
                AddFace('0', 3 , vert_ptrs[1]);
            }
        
        plane_ver_num = res * res;
        plane_face_num = 2 * (res-1) * (res-1);
        
        length_a = width;
        length_b = height;
    }
    
    Plane(int res): ShapeObject()
    {
        double x;
        double y;
        double z = 0;
        
        for(int i = 0; i < res; i++)
        {
            for(int j = 0; j < res; j++)
            {
                x = ( (double)(i - res/2 )/(res-1));
                y = ( (double)(j - res/2 )/(res-1));
                AddVertex(x, y, z);
            }
        }
    
    
        for(int i = 0; i < res - 1; i++)
            for(int j = 0; j < res - 1; j++)
            {
                Vertex_Indices vert_ptrs[] = {
                        {   i * res + j,
                            (i+1) * res + j,
                            i * res + j+1
                            
                        },
                    
                        {   i*res+j+1,
                            (i+1) * res + j,
                            (i+1) * res + j+1
                        },
                    };
                
                AddFace('0', 3 , vert_ptrs[0]);
                AddFace('0', 3 , vert_ptrs[1]);
            }
            
        plane_ver_num = res * res;
        plane_face_num = 2 * (res-1) * (res-1);
    }
    
    void ConnectShape(
        const ShapeObject * obj,
        double threshold);
        
//    void ConnectShape(
//        const ShapeObject *obj,
//        double minDis,
//        double maxDis);
    
};

class GaussianSurface : public ShapeObject
{
    double **       height;
    int             res;
public:
    GaussianSurface(): ShapeObject()
    {
        res = 20;
        gaussian_2d_surface(1,2,2,1,1);
    }
    
    GaussianSurface(double scale): ShapeObject()
    {
        res = 20;
        gaussian_2d_surface(scale, 2,2,1,1);
    }
    
    void allocate(int resolution)
    {
        if(! (resolution > 0))
            res = 20;
        else
            res = resolution;
        
        height = new double*[res];
        
        for(int i = 0; i < res; i++)
            height[i] = new double[res];
        
        for(int i = 0; i < res; i++)
            for(int j = 0; j < res; j++)
                height[i][j] = 0;
    }
    
    double gaussian_2d_surface(
        double scale,
        double var_x,
        double var_y,
        double mean_x,
        double mean_y)
    {
        
        double x;
        double y;
        double z;
        
        double lowest = 0.0;
        
        for(int i = 0; i < res; i++)
            for(int j = 0; j < res; j++)
            {
                
                x = ( (double)(i - res/2 )/res);
                y = ( (double)(j - res/2 )/res);
                
                if( i ==0 && j == 0)
                {
                    lowest =  - x * x / 2 * var_x * var_x - y * y / 2 * var_y * var_y ;
                    lowest = scale * exp(lowest)/ 1;
                }
                
                
                z = x * x / 2 * var_x * var_x + y * y / 2 * var_y * var_y ;
                
                z = - z ;
                
                z = scale * exp(z)/ 1;//(2 * M_PI * var_x * var_y);
                
                z = z - lowest;
                
//                height[i][j] = exp(z);
                
                AddVertex(x, y, z);
                
                
            }
        
        for(int i = 0; i < res - 1; i++)
            for(int j = 0; j < res - 1; j++)
            {
                Vertex_Indices vert_ptrs[] = {
                        {   i * res + j,
                            (i+1) * res + j,
                            i * res + j+1
                            
                        },
                    
                        {   i*res+j+1,
                            (i+1) * res + j,
                            (i+1) * res + j+1
                        },
                    };
        
                AddFace('0', 3 , vert_ptrs[0]);
                AddFace('0', 3 , vert_ptrs[1]);
            }
        
        return 0;
        
    }
    
};

class Mushroom : public ShapeObject
{
    int                 res;

    bool *             is_cube;
    
public:
    Mushroom(): ShapeObject()
    {
        res = 20;
        generate_mushroom(1,0.12,0.12,1,1);
    }
    
    Mushroom(double scale): ShapeObject()
    {
        res = 30;
        allocate(res);
        generate_mushroom(scale, 0.12,0.12,1,1);
    }
    
    void allocate(int resolution)
    {
        if(! (resolution > 0))
            res = 20;
        else
            res = resolution;
        
        is_cube = new bool[res*res];
        
        for(int i = 0; i < res * res; i++)
            is_cube[i] = false;
    }
    
    double generate_mushroom(
        double scale,
        double var_x,
        double var_y,
        double mean_x,
        double mean_y)
    {
        
        double x;
        double y;
        double z;
        
        double lowest = 0.0;
        
        int count = 0;
        
        for(int i = 0; i < res; i++)
        {
            
            for(int j = 0; j < res; j++)
            {
                
                x = ( (double)(i - res/2 )/res);
                y = ( (double)(j - res/2 )/res);
                
                if( i ==0 && j == 0)
                {
                    lowest =  - x * x / (2 * var_x * var_x) - y * y / (2 * var_y * var_y) ;
                    lowest = scale * exp(lowest)/ 1;
                }
                
                z = - x * x / (2 * var_x * var_x) - y * y / (2 * var_y * var_y) ;
                
                z = scale * exp(z)/ 1;//(2 * M_PI * var_x * var_y);
                
                z = z - lowest;

                
                if( z > 0.1 && z < 0.12 )
                {
                    z = 0.12;
                }

                
                if( z > 0.13 )
                {
                    z = 0.2;
                    is_cube[i*res+j]=true;
                }
                
                AddVertex(x, y, z);
                
                count ++;
            }
        }
    
    
    
        for(int i = 0; i < res - 1; i++)
            for(int j = 0; j < res - 1; j++)
            {
                Vertex_Indices vert_ptrs[] = {
                        {   i * res + j,
                            (i+1) * res + j,
                            i * res + j+1
                            
                        },
                    
                        {   i*res+j+1,
                            (i+1) * res + j,
                            (i+1) * res + j+1
                        },
                    };
                
                if( vertex_list[i * res + j].z > 0.01
                    && vertex_list[(i+1) * res + j].z > 0.01
                    && vertex_list[i * res + j+1].z > 0.01
                    )
                    AddFace('0', 3 , vert_ptrs[0]);
                
                if( vertex_list[i*res+j+1].z > 0.01
                    && vertex_list[(i+1) * res + j].z > 0.01
                    && vertex_list[(i+1) * res + j+1].z > 0.01
                    )
                    AddFace('0', 3 , vert_ptrs[1]);
            }
        
        return 0;
        
    }
    
    void Distortion(double movement);
    void RandomlyRotate(
        double angleX,
        double angleY,
        double angleZ
        );
};


class Wall_With_Tail : public ShapeObject
{
    int                 res;

    bool *             is_cube;
    
public:
    Wall_With_Tail(): ShapeObject()
    {
        res = 20;
        generate_wall(1,2,2);
    }
    
    Wall_With_Tail(double scale): ShapeObject()
    {
        res = 15;
        allocate(res);
        generate_wall(scale, 0.1,0.1);
    }
    
    void allocate(int resolution)
    {
        if(! (resolution > 0))
            res = 20;
        else
            res = resolution;
        
        is_cube = new bool[res*res];
        
        for(int i = 0; i < res * res; i++)
            is_cube[i] = false;
    }
    
    double generate_wall(
        double scale,
        double var_x,
        double var_y
        )
    {
        
        double x;
        double y;
        double z;
        
//        double lowest = 0.0;
        
        int count = 0;
        double y_pos;
        
        for(int i = 0; i < res; i++)
        {
            x = ( (double)( i - res )/res);
            z = - x * x / (2 * var_x * var_x);
            z =  exp(z) ;
            
        
            
            for(int j = 0; j < res; j++)
            {
                
                y = ( (double)(j - res/2 )/res);
                
                AddVertex(x - 0.3, y, z);
                
                count ++;
            }
        }
    
    
    
        for(int i = 0; i < res - 1; i++)
            for(int j = 0; j < res - 1; j++)
            {
                Vertex_Indices vert_ptrs[] = {
                        {   i * res + j,
                            (i+1) * res + j,
                            i * res + j+1
                            
                        },
                    
                        {   i*res+j+1,
                            (i+1) * res + j,
                            (i+1) * res + j+1
                        },
                    };
                
                if( vertex_list[i * res + j].z > 0.01
                    && vertex_list[(i+1) * res + j].z > 0.01
                    && vertex_list[i * res + j+1].z > 0.01
                    )
                    AddFace('0', 3 , vert_ptrs[0]);
                
                if( vertex_list[i*res+j+1].z > 0.01
                    && vertex_list[(i+1) * res + j].z > 0.01
                    && vertex_list[(i+1) * res + j+1].z > 0.01
                    )
                    AddFace('0', 3 , vert_ptrs[1]);
            }
        
        return 0;
        
    }
    
    void Distortion(double movement);
    void RandomlyRotate(
        double angleX,
        double angleY,
        double angleZ
        );
};

class Cube_With_Tail : public ShapeObject
{
    Wall_With_Tail   *  left;
    Wall_With_Tail   *  right;
    Wall_With_Tail   *  front;
    Wall_With_Tail   *  back;

    Plane            *  top;
    Plane            *  bottom;
public:
    Cube_With_Tail(): ShapeObject()
    {
        
    }
    
    Cube_With_Tail(double scale): ShapeObject()
    {
        left = new Wall_With_Tail(scale);
        
        right = new Wall_With_Tail(scale);
        
        right->Rotate(0, 0, 180);
        
        front = new Wall_With_Tail(scale);
        
        front->Rotate(0, 0, 270);
        
        back = new Wall_With_Tail(scale);
        back->Rotate(0, 0, 90);

        
        AddShape(left);
        AddShape(right);
        AddShape(front);
        AddShape(back);
        
        
        top     = new Plane();
        top->MoveObject(0, 0, 0.8);
        bottom  = new Plane();
        AddShape(top);
        AddShape(bottom);
        
    }
    
    
};


inline Vector Cross(const Vector &v1, const Vector &v2) {
	
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
	double v2x = v2.x, v2y = v2.y, v2z = v2.z;
	return Vector((v1y * v2z) - (v1z * v2y),
		(v1z * v2x) - (v1x * v2z),
		(v1x * v2y) - (v1y * v2x));
}





#endif /* Object_h */
