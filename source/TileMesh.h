#ifndef TILEMESH_H
#define TILEMESH_H

#include "irrlicht.h"

#define I_SIZE 240
#define J_SIZE 80

#define I_CHUNKSIZE 20
#define J_CHUNKSIZE 10

//256 = 25*10
//80 = 16*5

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;


//-------Neighbour tiles' I
int UNbrI(int i, int j)
{
    return i;
}

int LNbrI(int i, int j)
{
return i;
}

int ULNbrI(int i, int j)
{
    return (i-1+I_SIZE)%I_SIZE;
}

int URNbrI(int i, int j)
{
    return (i+1)%I_SIZE;
}

int LLNbrI(int i, int j)
{
    return (i-1+I_SIZE)%I_SIZE;
}

int LRNbrI(int i, int j)
{
    return (i+1)%I_SIZE;
}

//-------Neighbour tiles' J
int UNbrJ(int i, int j)
{
    return (j+1)%J_SIZE;
}

int LNbrJ(int i, int j)
{
    return (j-1+J_SIZE)%J_SIZE;
}

int ULNbrJ(int i, int j)
{
    return i%2==0?j:(j+1)%J_SIZE;
}

int URNbrJ(int i, int j)
{
    return i%2==0?j:(j+1)%J_SIZE;
}

int LLNbrJ(int i, int j)
{
    return i%2==0?(j-1+J_SIZE)%J_SIZE:j;
}

int LRNbrJ(int i, int j)
{
    return i%2==0?(j-1+J_SIZE)%J_SIZE:j;
}



// coordinates convert

f64 Hex2PixelX(int x,int y)
{
    return x*(1.5);
}

f64 Hex2PixelY(int x,int y)
{
    return y*sqrt(3) + 0.5*sqrt(3)*(x%2);
}

int Pixel2HexX(f32 x, f32 y)
{
    int x0 = (int)floor(x/1.5);
    int x1 = x0 +1;
    int x2 = x0%2==0?x0:x1;

    int y0 =(int)floor(y/sqrt(3));
    int y1 = y0;
    int y2 = y0+1;


    if ( ( ((Hex2PixelX(x0,y0)-x)*(Hex2PixelX(x0,y0)-x)+(Hex2PixelY(x0,y0)-y)*(Hex2PixelY(x0,y0)-y))<=((Hex2PixelX(x1,y1)-x)*(Hex2PixelX(x1,y1)-x)+(Hex2PixelY(x1,y1)-y)*(Hex2PixelY(x1,y1)-y)))&&
         ( ((Hex2PixelX(x0,y0)-x)*(Hex2PixelX(x0,y0)-x)+(Hex2PixelY(x0,y0)-y)*(Hex2PixelY(x0,y0)-y))<=((Hex2PixelX(x2,y2)-x)*(Hex2PixelX(x2,y2)-x)+(Hex2PixelY(x2,y2)-y)*(Hex2PixelY(x2,y2)-y)))
       )
    {
        return x0;

    }
    else
    {
        if ( ( ((Hex2PixelX(x2,y2)-x)*(Hex2PixelX(x2,y2)-x)+(Hex2PixelY(x2,y2)-y)*(Hex2PixelY(x2,y2)-y))<((Hex2PixelX(x1,y1)-x)*(Hex2PixelX(x1,y1)-x)+(Hex2PixelY(x1,y1)-y)*(Hex2PixelY(x1,y1)-y))) )
        {
            return x2;
        }
        else
        {
            return x1;
        }
    }







}

int Pixel2HexY(f64 x, f64 y)
{
    int x0 = (int)floor(x/1.5);
    int x1 = x0 +1;
    int x2 = x0%2==0?x0:x1;

    int y0 =(int)floor(y/sqrt(3));
    int y1 = y0;
    int y2 = y0+1;




    if ( ( ((Hex2PixelX(x0,y0)-x)*(Hex2PixelX(x0,y0)-x)+(Hex2PixelY(x0,y0)-y)*(Hex2PixelY(x0,y0)-y))<=((Hex2PixelX(x1,y1)-x)*(Hex2PixelX(x1,y1)-x)+(Hex2PixelY(x1,y1)-y)*(Hex2PixelY(x1,y1)-y)))&&
         ( ((Hex2PixelX(x0,y0)-x)*(Hex2PixelX(x0,y0)-x)+(Hex2PixelY(x0,y0)-y)*(Hex2PixelY(x0,y0)-y))<=((Hex2PixelX(x2,y2)-x)*(Hex2PixelX(x2,y2)-x)+(Hex2PixelY(x2,y2)-y)*(Hex2PixelY(x2,y2)-y)))
       )
    {
        return y0;

    }
    else
    {
        if ( ( ((Hex2PixelX(x2,y2)-x)*(Hex2PixelX(x2,y2)-x)+(Hex2PixelY(x2,y2)-y)*(Hex2PixelY(x2,y2)-y))<((Hex2PixelX(x1,y1)-x)*(Hex2PixelX(x1,y1)-x)+(Hex2PixelY(x1,y1)-y)*(Hex2PixelY(x1,y1)-y))) )
        {
            return y2;
        }
        else
        {
            return y1;
        }
    }
}
void createHexHoverMesh(SMesh* mesh)
{

     SMeshBuffer *buf = 0;
     if (mesh->getMeshBufferCount()>0)
         buf = (SMeshBuffer*)mesh->getMeshBuffer(0);
     else
     {

         buf = new SMeshBuffer();
         mesh->addMeshBuffer(buf);
     }
    buf->Vertices.set_used(7);

    S3DVertex& v0 = buf->Vertices[6];
    v0.Pos.set(0.0,0.0,-0.1);
    v0.Normal.set(0,0,-1);
    v0.Color = SColor(255,255,255,255);
    v0.TCoords.set(0.5 ,0.5);


for (int i = 0;i<6;i++)
{
        S3DVertex& v = buf->Vertices[i];//for regular cap;
        v.Pos.set(cosf(PI/3*(i)),sinf(PI/3*(i)),-0.1);
        v.Normal.set(0,0,-1);
        v.Color = SColor(255,255,255,255);
        v.TCoords.set(0.5 +0.5*(cosf(PI/3*(i))),0.5 +0.5*sinf(PI/3*(i)));
}


    buf->Indices.clear();
    for (int i=0;i<6;i++)
    {
    buf->Indices.push_back(i);buf->Indices.push_back(6);buf->Indices.push_back((i+1)%6);

    }


    buf->recalculateBoundingBox();

   // buf->drop();
    mesh->setDirty();
    mesh->recalculateBoundingBox();


}


#endif // TILEMESH_H
