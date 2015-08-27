#ifndef TILECORNERMESH_H
#define TILECORNERMESH_H
#include "irrlicht.h"
#include "DGameMap.h"

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

class TileCornerMesh
{
private:
    u16 Width;
    u16 Height;
    f32 Scale;
public:
    SMesh* Mesh;

    TileCornerMesh() : Mesh(0), Width(0), Height(0), Scale(1.f)
    {
        Mesh = new SMesh();
    }

    ~TileCornerMesh()
    {
        Mesh->drop();
    }

    // Unless the heightmap is small, it won't all fit into a single
    // SMeshBuffer. This function chops it into pieces and generates a
    // buffer from each one.

//    void init(const HeightMap &hm, f32 scale, colour_func cf, IVideoDriver *driver)
    void init (TileInfo** TileMap, int I, int J)
    {

        Mesh->setHardwareMappingHint(scene::EHM_STATIC);

        SMeshBuffer *buf = 0;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


            buf->Vertices.set_used(31);

            S3DVertex& v0 = buf->Vertices[0];
            v0.Pos.set(0.0,0.0,0);
            v0.Normal.set(0,0,-1);
            v0.Color = SColor(255,255,255,255);
            v0.TCoords.set(0.5 ,0.5);


        for (int i = 1;i<7;i++)
        {

                S3DVertex& v = buf->Vertices[i];//for regular cap;
                v.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
                v.Normal.set(0,0,-1);
                v.Color = SColor(255,255,255,255);
                v.TCoords.set(0.5 +0.5*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*0.25*sinf(PI/3*(i-1)));

                S3DVertex& vv = buf->Vertices[i+18];//for one of the cliffs
                vv.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
                vv.Normal.set(0,0,-1);
                vv.Color = SColor(255,255,255,255);
                vv.TCoords.set(0.5 +0.5*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*0.25*sinf(PI/3*(i-1)));

                vector3df face1;
                face1.set(0.25*cosf(PI/3*(i+1)),0.25*sinf(PI/3*(i+1)),0);
                face1 = face1.crossProduct(vector3df(-0.25*cosf(PI/3*(i-1)),-0.25*sinf(PI/3*(i-1)),-0.125));
                if (face1.Z>0) face1.invert();
                vv.Normal = face1.normalize();

                //clone of this same vertex for next cliff
                S3DVertex& vv2 = buf->Vertices[i+24];
                vv2.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
                vv2.Normal.set(0,0,-1);
                vv2.Color = SColor(255,255,255,255);
                vv2.TCoords.set(0.5 +0.5*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*0.25*sinf(PI/3*(i-1)));

                face1.set(0.25*cosf(PI/3*(i)),0.25*sinf(PI/3*(i)),0);
                face1 = face1.crossProduct(vector3df(-0.25*cosf(PI/3*(i-2)),-0.25*sinf(PI/3*(i-2)),-0.125));
                if (face1.Z>0) face1.invert();
                vv2.Normal = face1.normalize();

                S3DVertex& v2 = buf->Vertices[5+2*i];//lower of the cliff
                v2.Pos.set(0.5*cosf(PI/3*(i-1)),0.5*sinf(PI/3*(i-1)),0.125);
                v2.Normal.set(0,0,-1);
                v2.Color = SColor(255,255,255,255);
                v2.TCoords.set(0.5 +0.5*(0.5*cosf(PI/3*(i-1))),0.5 +0.5*0.5*sinf(PI/3*(i-1)));

                S3DVertex& v3 = buf->Vertices[5+2*i+1]; //middle of the cliff
                v3.Pos.set(0.5*cosf(PI/3*(i-1))+0.25*cosf(PI/3*(i+1)),0.5*sinf(PI/3*(i-1))+0.25*sinf(PI/3*(i+1)),0.125);
                v3.Normal.set(0,0,-1);
                v3.Color = SColor(255,255,255,255);
                v3.TCoords.set(0.5 +0.5*(0.5*cosf(PI/3*(i-1))+0.25*cosf(PI/3*(i+1))),0.5 +0.5*(0.5*sinf(PI/3*(i-1))+0.25*sinf(PI/3*(i+1))));

        }






        buf->Indices.set_used(0);

        bool allow[6];

        allow[0] = TileMap[I][J].Height!=TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height;
        allow[1] = TileMap[I][J].Height!=TileMap[UNbrI(I,J)][UNbrJ(I,J)].Height;
        allow[2] = TileMap[I][J].Height!=TileMap[ULNbrI(I,J)][ULNbrJ(I,J)].Height;
        allow[3] = TileMap[I][J].Height!=TileMap[LLNbrI(I,J)][LLNbrJ(I,J)].Height;
        allow[4] = TileMap[I][J].Height!=TileMap[UNbrI(I,J)][LLNbrJ(I,J)].Height;
        allow[5] = TileMap[I][J].Height!=TileMap[LRNbrI(I,J)][LRNbrJ(I,J)].Height;

        for (int i = 1;i<7;i++)
        {

                    buf->Indices.push_back(i);
                    buf->Indices.push_back(0);
                    buf->Indices.push_back((i+1-1)%6+1);//cap


           if (allow[i-1]){
                    buf->Indices.push_back(i+18);//19
                    buf->Indices.push_back(5+2*i);//7
                    buf->Indices.push_back(6+2*i);//8

                    buf->Indices.push_back(i+18);//19
                    buf->Indices.push_back(6+2*i);//8
                    buf->Indices.push_back((i+1-1)%6+25);//26

                    buf->Indices.push_back(6+2*i);//8
                    buf->Indices.push_back((i+1-1)%6+25);//26
                    buf->Indices.push_back(5+2*((i%6)+1));//9
                    }
       }




        buf->recalculateBoundingBox();
       // buf->drop();


        Mesh->setDirty();
        Mesh->recalculateBoundingBox();
    }



};

#endif // TILECORNERMESH_H
