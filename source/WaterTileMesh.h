#ifndef WATERTILEMESH_H
#define WATERTILEMESH_H


#include "irrlicht.h"

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

class WaterTileMesh
{
private:
    u16 Width;
    u16 Height;
    f32 Scale;
public:
    SMesh* Mesh;

    WaterTileMesh() : Mesh(0), Width(0), Height(0), Scale(1.f)
    {
        Mesh = new SMesh();
    }

    ~WaterTileMesh()
    {
        Mesh->drop();
    }

    // Unless the heightmap is small, it won't all fit into a single
    // SMeshBuffer. This function chops it into pieces and generates a
    // buffer from each one.

//    void init(const HeightMap &hm, f32 scale, colour_func cf, IVideoDriver *driver)
    void init (f32 scale, IVideoDriver *driver)
    {
        Scale = scale;



        SMeshBuffer *buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);

            buf->Vertices.set_used(61);


        float stepx = 0.25;
        float stepy_x = -0.125;
        float stepy_y = 0.125*sqrt(3);

        float curx = 0.5-1;
        float cury = 0-sqrt(3)/2;
        float intcurx = curx;

        for (int i = 0;i<5;i++)
        {
            intcurx = curx;
            for (int j=((i-1)*(i-1)+11*(i-1))/2+5; j<(i*i+11*i)/2+5; j++)
            {
                S3DVertex& v = buf->Vertices[j];
                v.Pos.set(curx,cury,0);
                v.Normal.set(0,0,-1);
                v.Color = SColor(255,255,255,255);
                v.TCoords.set(0.5+0.5*curx,0.5+0.5*cury);

                curx+=stepx;
            }
            curx=intcurx;
            curx+=stepy_x;
            cury+=stepy_y;
        }

        stepy_x = +0.125;

        curx = -1+stepy_x;
        cury = 0+stepy_y;// sqrt(3)/2-sqrt(3)/2;

        for (int i = 3;i>=0;i--)
        {
            intcurx = curx;
            for (int j=(-(i+1)*(i+1)-9*(i+1))/2+61; j<(-i*i-9*i)/2+61; j++)
            {
                S3DVertex& v = buf->Vertices[j];
                v.Pos.set(curx,cury,0);
                v.Normal.set(0,0,-1);
                v.Color = SColor(255,255,255,255);
                v.TCoords.set(0.5+0.5*curx,0.5+0.5*cury);

                curx+=stepx;
            }
            curx=intcurx;
            curx+=stepy_x;
            cury+=stepy_y;
        }



        buf->Indices.set_used(0);


        for (int i = 0;i<4;i++)
        {

            for (int j=((i-1)*(i-1)+11*(i-1))/2+5; j<(i*i+11*i)/2+5; j++)
            {

                    buf->Indices.push_back(j);
                    buf->Indices.push_back(j-((i-1)*(i-1)+11*(i-1))/2-5+(i*i+11*i)/2+5);
                    buf->Indices.push_back(j-((i-1)*(i-1)+11*(i-1))/2-5+(i*i+11*i)/2+6);

                    if (j<(i*i+11*i)/2+4)
                    {
                        buf->Indices.push_back(j);
                        buf->Indices.push_back(j+1);
                        buf->Indices.push_back(j-((i-1)*(i-1)+11*(i-1))/2-5+(i*i+11*i)/2+6);
                    }

            }
       }


        for (int i = 3;i>=0;i--)
        {

            for (int j=(-(i+1)*(i+1)-9*(i+1))/2+61; j<(-i*i-9*i)/2+61; j++)
            {
                buf->Indices.push_back(j);
                buf->Indices.push_back(
                            -(-i*i-9*i)/2+
                            (-(i+1)*(i+1)-9*(i+1))/2
                            +j-1
                            );
                buf->Indices.push_back(-(-i*i-9*i)/2+
                                       (-(i+1)*(i+1)-9*(i+1))/2
                                       +j);


                if (j<(-i*i-9*i)/2+60) {
                    buf->Indices.push_back(j);
                    buf->Indices.push_back(-(-i*i-9*i)/2+
                                           (-(i+1)*(i+1)-9*(i+1))/2
                                           +j);
                    buf->Indices.push_back(j+1);

                }


            }

        }






        buf->recalculateBoundingBox();
        buf->drop();

        Mesh->setDirty();
        Mesh->recalculateBoundingBox();


    }



};



#endif // WATERTILEMESH_H
