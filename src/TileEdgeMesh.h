#ifndef TILEEDGEMESH_H
#define TILEEDGEMESH_H


#include "irrlicht.h"
#include "TileMesh.h"

#define TEXTUREFACTOR 0.75

#define deepness 0.1

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

class TileEdgeMesh
{
private:
    u16 Width;
    u16 Height;
    f32 Scale;
public:
    SMesh* Mesh;

    TileEdgeMesh() : Mesh(0), Width(0), Height(0), Scale(1.f)
    {
        Mesh = new SMesh();
    }

    ~TileEdgeMesh()
    {
        Mesh->drop();
    }

    // Unless the heightmap is small, it won't all fit into a single
    // SMeshBuffer. This function chops it into pieces and generates a
    // buffer from each one.

//    void init(const HeightMap &hm, f32 scale, colour_func cf, IVideoDriver *driver)
    void init ()
    {

        SColor color = SColor (0.0,0.0,0.0,1.0);

        Mesh->setHardwareMappingHint(scene::EHM_STATIC);
        SMeshBuffer *buf;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }

            buf->Vertices.set_used(11);


        for (int i = 0;i<4;i++)
        {

                S3DVertex& v = buf->Vertices[i];
                v.Pos.set(0.25*i-0.375,0.125*sqrt(3),0);
                v.Normal.set(0,0,-1);
                v.Color = color;
                v.TCoords.set(0.5 +0.5*(0.25*i-0.375)*TEXTUREFACTOR,0.5 +0.5*0.125*sqrt(3)*TEXTUREFACTOR);

        }

        for (int i = 0;i<3;i++)
        {

                S3DVertex& v = buf->Vertices[i+4];
                v.Pos.set(0.25*i-0.25,0,0);
                v.Normal.set(0,0,-1);
                v.Color = color;
                v.TCoords.set(0.5 +0.5*(0.25*i-0.25)*TEXTUREFACTOR,0.5 +0.5*0*TEXTUREFACTOR);
        }

        for (int i = 0;i<4;i++)
        {

                S3DVertex& v = buf->Vertices[i+7];
                v.Pos.set(0.25*i-0.375,-0.125*sqrt(3),0);
                v.Normal.set(0,0,-1);
                v.Color = color;
                v.TCoords.set(0.5 +0.5*(0.25*i-0.375)*TEXTUREFACTOR,0.5 +0.5*(-0.125)*sqrt(3)*TEXTUREFACTOR);
        }




        buf->Indices.set_used(0);


        for (int i = 0;i<3;i++)
        {

                    buf->Indices.push_back(i);
                    buf->Indices.push_back(i+1);
                    buf->Indices.push_back(i+4);

                    buf->Indices.push_back(i+7);
                    buf->Indices.push_back(i+4);
                    buf->Indices.push_back(i+8);

       }

        for (int i = 0;i<2;i++)
        {

                    buf->Indices.push_back(i+1);
                    buf->Indices.push_back(i+5);
                    buf->Indices.push_back(i+4);


                    buf->Indices.push_back(i+4);
                    buf->Indices.push_back(i+5);
                    buf->Indices.push_back(i+8);

       }

        buf->recalculateBoundingBox();
        //buf->drop();


        Mesh->setDirty();
        Mesh->recalculateBoundingBox();
    }


    void createMesh (SMesh *Mesh,int transitionnumber, int tiletype1, int tiletype2)
    {
         SColor color = SColor(32+32*transitionnumber,tiletype1,tiletype2,0);


        Mesh->setHardwareMappingHint(scene::EHM_STATIC);
        SMeshBuffer *buf;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }

            buf->Vertices.set_used(11);


        for (int i = 0;i<4;i++)
        {

                S3DVertex& v = buf->Vertices[i];
                v.Pos.set(0.25*i-0.375,0.125*sqrt(3),0);
                v.Normal.set(0,0,-1);
                v.Color = color;
                v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*i-0.375),0.5 +0.5*TEXTUREFACTOR*0.125*sqrt(3));

        }

        for (int i = 0;i<3;i++)
        {

                S3DVertex& v = buf->Vertices[i+4];
                v.Pos.set(0.25*i-0.25,0,0);
                v.Normal.set(0,0,-1);
                v.Color = color;
                v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*i-0.25),0.5 +0.5*TEXTUREFACTOR*0);
        }

        for (int i = 0;i<4;i++)
        {

                S3DVertex& v = buf->Vertices[i+7];
                v.Pos.set(0.25*i-0.375,-0.125*sqrt(3),0);
                v.Normal.set(0,0,-1);
                v.Color = color;
                v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*i-0.375),0.5 +0.5*TEXTUREFACTOR*(-0.125)*sqrt(3));
        }




        buf->Indices.set_used(0);


        for (int i = 0;i<3;i++)
        {

                    buf->Indices.push_back(i);
                    buf->Indices.push_back(i+1);
                    buf->Indices.push_back(i+4);

                    buf->Indices.push_back(i+7);
                    buf->Indices.push_back(i+4);
                    buf->Indices.push_back(i+8);

       }

        for (int i = 0;i<2;i++)
        {

                    buf->Indices.push_back(i+1);
                    buf->Indices.push_back(i+5);
                    buf->Indices.push_back(i+4);


                    buf->Indices.push_back(i+4);
                    buf->Indices.push_back(i+5);
                    buf->Indices.push_back(i+8);

       }

        buf->recalculateBoundingBox();
        //buf->drop();


        Mesh->setDirty();
        Mesh->recalculateBoundingBox();
    }
};





#endif // TILEEDGEMESH_H
