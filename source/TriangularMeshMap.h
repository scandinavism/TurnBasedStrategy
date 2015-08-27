#ifndef TRIANGULARMESHMAP_H
#define TRIANGULARMESHMAP_H

#include "irrlicht.h"

#define MapWidth 30
#define MapHeight 8

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

/*void FreeDynamicArray(int** dArray)
{
      delete [] *dArray;
      delete [] dArray;
}

int** AllocateDynamicArray(int nRows, int nCols)
{
      int **dynamicArray;

      dynamicArray = new int*[nRows];
      for( int i = 0 ; i < nRows ; i++ )
      dynamicArray[i] = new int [nCols];

      return dynamicArray;
}*/

f32 get(u16 i, u16 j)
{
  return j%2?0.25*sinf(PI/7*i+PI/20*2*j)+0.1*cosf(PI/13*i - PI/6*2*j):0.25*sinf(PI/7*i+PI/20*(2*j+1))+0.1*cosf(PI/13*i - PI/6*(2*j+1));

}

vector3df getnormal(u16 x, u16 y, f32 s)
    {
        const f32 zc = get(x, y);
        f32 zl, zr, zu, zd;
        f32 Width = MapWidth*9;
        f32 Height = MapHeight*5;
        if (x == 0)
        {
            zr = get(x + 1, y);
            zl = zc + zc - zr;
        }
        else if (x == Width - 1)
        {
            zl = get(x - 1, y);
            zr = zc + zc - zl;
        }
        else
        {
            zr = get(x + 1, y);
            zl = get(x - 1, y);
        }

        if (y == 0)
        {
            zd = get(x, y + 1);
            zu = zc + zc - zd;
        }
        else if (y == Height - 1)
        {
            zu = get(x, y - 1);
            zd = zc + zc - zu;
        }
        else
        {
            zd = get(x, y + 1);
            zu = get(x, y - 1);
        }

        return vector3df(s * 2 * (zl - zr), 4, s * 2 * (zd - zu)).normalize();
    }



class TriangularMeshMap
{
public:
    IMeshSceneNode* node;
    SMesh* mesh;

    TriangularMeshMap(ISceneManager* smgr,IVideoDriver* driver)
    {

        mesh = new SMesh;

        SMeshBuffer *buf = new SMeshBuffer();
        mesh->addMeshBuffer(buf);
        buf->Vertices.set_used(2 * MapWidth * 9 * MapHeight * 5);

        for (int i = 0;i<MapWidth*9;i++)
            for (int j=0;j<MapHeight*5;j++)
        {
        S3DVertex& v = buf->Vertices[i+j*MapWidth*9*2];
        v.Pos.set(0.25*i,0+j*sqrt(3)/4,0.25*sinf(PI/7*i+PI/20*2*j)+0.1*cosf(PI/13*i - PI/6*2*j));
        v.Normal = getnormal(i,j,1);

        v.Color = SColor(125,125,255,255);
        v.TCoords.set(0,0);


        S3DVertex& v2 = buf->Vertices[i+MapWidth*9+j*MapWidth*9*2];
        v2.Pos.set(0.125+0.25*i,sqrt(3)*0.125+j*sqrt(3)/4,0.25*sinf(PI/7*i+PI/20*(2*j+1))+0.1*cosf(PI/13*i - PI/6*(2*j+1)));
        v.Normal = getnormal(i,j+1,1);;
        v2.Color = SColor(125,125,255,255);
        v2.TCoords.set(0,0);
        }

        buf->Indices.set_used(0);

       for (int i=0;i<(MapWidth*9-1);i++)
           for (int j=0;j<MapHeight*5-1;j++)
       {
           buf->Indices.push_back(i+j*MapWidth*9*2);
           buf->Indices.push_back(i+1+j*MapWidth*9*2);
           buf->Indices.push_back(i+MapWidth*9+j*MapWidth*9*2);

           buf->Indices.push_back(i+1+j*MapWidth*9*2);
           buf->Indices.push_back(i+MapWidth*9+j*MapWidth*9*2);
           buf->Indices.push_back(i+MapWidth*9+1+j*MapWidth*9*2);

           buf->Indices.push_back(i+MapWidth*9+j*MapWidth*9*2);
           buf->Indices.push_back(i+MapWidth*9+1+j*MapWidth*9*2);
           buf->Indices.push_back(i+1+(j+1)*MapWidth*9*2);

           buf->Indices.push_back(i+MapWidth*9+j*MapWidth*9*2);
           buf->Indices.push_back(i+1+(j+1)*MapWidth*9*2);
           buf->Indices.push_back(i+(j+1)*MapWidth*9*2);
       }

       buf->recalculateBoundingBox();
       buf->drop();

       mesh->setDirty();
       mesh->recalculateBoundingBox();

       node = smgr->addOctreeSceneNode(mesh);
       scene::ITriangleSelector* selector =  smgr->createOctreeTriangleSelector(mesh,node);
       node->setTriangleSelector(selector);
       selector->drop();

       node->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);
       //node->setMaterialFlag(video::EMF_WIREFRAME, true);
       node->setMaterialType(video::EMT_SOLID);
       node->setMaterialFlag(video::EMF_LIGHTING, true);

    }

    ~TriangularMeshMap()
    {
        mesh->drop();
    }

};


#endif // TRIANGULARMESHMAP_H
