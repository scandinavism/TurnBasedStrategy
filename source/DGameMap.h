#ifndef DGAMEMAP_H
#define DGAMEMAP_H

#include "irrlicht.h"
#include "TileMesh.h"
#include "TileCornerMesh.h"
#include "TileEdgeMesh.h"
#include "MyShaderCallBack.h"
#include "CBatchingMesh.h"

#define INFINITE 32536;

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;



namespace TILE_TYPES
{
const int CRATER1 = 0;
const int CRATER2 = 1;
const int ROCKS = 2;
const int SEDIMENT1 = 3;
const int SEDIMENT2 = 4;
const int MOUNTAINS = 5;
const int HILLS = 6;
const int BARREN = 7;
const int BASALT_ROCKS = 8;
const int BASALT = 9;
const int CHANNELS = 10;
const int LAVA = 11;
const int RIFT = 12;
const int VOLCANO = 13;
const int PERMAFROST = 14;
const int POLAR = 15;
}

const int ID_IsNotPickable = 0;

bool BoundaryCheck (int x, int y, int left, int right, int top, int bottom)
{
    return (x<right) && (x>=left) && (y>=bottom) && (y<top);

}

bool JCheck (int y)
{
    return (y>=0)&&(y<J_SIZE/J_CHUNKSIZE);
}

int IWrap (int i)
{
    return i<0?i+I_SIZE/I_CHUNKSIZE:i%(I_SIZE/I_CHUNKSIZE);
}

int DUMMYFUNCTION(int tiletype)//template func
{
    switch (tiletype)
    {
    case TILE_TYPES::CRATER1:
        return 0;
        break;

    case TILE_TYPES::CRATER2:
        return 0;
        break;

    case TILE_TYPES::ROCKS:
        return 0;
        break;

    case TILE_TYPES::SEDIMENT1:
        return 0;
        break;

    case TILE_TYPES::SEDIMENT2:
        return 0;
        break;

    case TILE_TYPES::MOUNTAINS:
        return 0;
        break;

    case TILE_TYPES::HILLS:
        return 0;
        break;

    case TILE_TYPES::BARREN:
        return 0;
        break;

    case TILE_TYPES::BASALT_ROCKS:
        return 0;
        break;

    case TILE_TYPES::BASALT:
        return 0;
        break;

    case TILE_TYPES::CHANNELS:
        return 0;
        break;

    case TILE_TYPES::LAVA:
        return 0;
        break;

    case TILE_TYPES::RIFT:
        return 0;
        break;

    case TILE_TYPES::VOLCANO:
        return 0;
        break;

    case TILE_TYPES::PERMAFROST:
        return 0;
        break;

    case TILE_TYPES::POLAR:
        return 0;
        break;

    default:
        return 0;
        break;

    }

}


core::string<char> TileName(int tiletype)
{
    switch (tiletype)
    {
    case TILE_TYPES::CRATER1:
        return "Crater 1";
        break;

    case TILE_TYPES::CRATER2:
        return "Crater 2";
        break;

    case TILE_TYPES::ROCKS:
        return "Rocks";
        break;

    case TILE_TYPES::SEDIMENT1:
        return "Sedimentary (sand)";
        break;

    case TILE_TYPES::SEDIMENT2:
        return "Sedimentary (lime)";
        break;

    case TILE_TYPES::MOUNTAINS:
        return "Mountains";
        break;

    case TILE_TYPES::HILLS:
        return "Old Mountains";
        break;

    case TILE_TYPES::BARREN:
        return "Barren land";
        break;


    default:
        return "";
        break;

    }

}

int getBaseMovementCost(int tiletype)//template func
{
    switch (tiletype)
    {
    case TILE_TYPES::CRATER1:
        return 1;
        break;

    case TILE_TYPES::CRATER2:
        return 2;
        break;

    case TILE_TYPES::ROCKS:
        return 10;
        break;

    case TILE_TYPES::SEDIMENT1:
        return 5;
        break;

    case TILE_TYPES::SEDIMENT2:
        return 2;
        break;

    case TILE_TYPES::MOUNTAINS:
        return 4;
        break;

    case TILE_TYPES::HILLS:
        return 3;
        break;

    case TILE_TYPES::BARREN:
        return 1;
        break;

    case TILE_TYPES::BASALT_ROCKS:
        return 2;
        break;

    case TILE_TYPES::BASALT:
        return 1;
        break;

    case TILE_TYPES::CHANNELS:
        return 2;
        break;

    case TILE_TYPES::LAVA:
        return 3;
        break;

    case TILE_TYPES::RIFT:
        return 4;
        break;

    case TILE_TYPES::VOLCANO:
        return 5;
        break;

    case TILE_TYPES::PERMAFROST:
        return 2;
        break;

    case TILE_TYPES::POLAR:
        return 2;
        break;

    default:
        return INFINITE;
        break;

    }

}



void FreeDynamicArray(int** dArray)
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
}




struct TileInfo
{
    int TerrainType;
    int Height;
};


int getMovementCost(TileInfo tileinfo)
{
    int mcost = getBaseMovementCost(tileinfo.TerrainType);
    //do something
    return mcost;

}


class VisibleMap
{
public:

    // TileCornerMesh cornermesh;
    TileEdgeMesh edgemesh;

    ISceneManager* smgr;
    IVideoDriver* driver;
    ILightSceneNode *lightNode;
    u32 *ticker;
    ShaderWrapper *MyShaders;
    IMeshSceneNode* b0;

    IMeshSceneNode* **nodes;
    IMeshSceneNode* **trees;
    TileInfo** TileMap;


    void setIMeshTexture (IMesh* mesh, int textureLayer, int tiletype)
    {

        ITexture* texture;

        switch (tiletype)
        {
        case TILE_TYPES::CRATER1:
            texture = driver->getTexture("assets/textures/crater1/1.jpg");
            break;

        case TILE_TYPES::CRATER2:
            texture = driver->getTexture("assets/textures/crater2/1.jpg");
            break;

        case TILE_TYPES::ROCKS:
            texture = driver->getTexture("assets/textures/rocks/1.jpg");
            break;

        case TILE_TYPES::SEDIMENT1:
            texture = driver->getTexture("assets/textures/sediment1/1.jpg");
            break;

        case TILE_TYPES::SEDIMENT2:
            texture = driver->getTexture("assets/textures/sediment2/1.jpg");
            break;

        case TILE_TYPES::MOUNTAINS:
            texture = driver->getTexture("assets/textures/mountains/1.jpg");
            break;

        case TILE_TYPES::HILLS:
            texture = driver->getTexture("assets/textures/hills/1.jpg");
            break;

        case TILE_TYPES::BARREN:
            texture = driver->getTexture("assets/textures/barren/1.jpg");
            break;

        case TILE_TYPES::BASALT_ROCKS:
            texture = driver->getTexture("assets/textures/basalt_rocks/1.jpg");
            break;

        case TILE_TYPES::BASALT:
            texture = driver->getTexture("assets/textures/basalt/1.jpg");
            break;

        case TILE_TYPES::CHANNELS:
            texture = driver->getTexture("assets/textures/channels/1.jpg");
            break;

        case TILE_TYPES::LAVA:
            texture = driver->getTexture("assets/textures/lava/1.jpg");
            break;

        case TILE_TYPES::RIFT:
            texture = driver->getTexture("assets/textures/rift/1.jpg");
            break;

        case TILE_TYPES::VOLCANO:
            texture = driver->getTexture("assets/textures/volcano/1.jpg");
            break;

        case TILE_TYPES::PERMAFROST:
            texture = driver->getTexture("assets/textures/permafrost/1.jpg");
            break;

        case TILE_TYPES::POLAR:
            texture = driver->getTexture("assets/textures/polar/1.jpg");
            break;

        default:
            texture = driver->getTexture("assets/shared/exclusion.png");
            break;
        }


        mesh->getMeshBuffer(0)->getMaterial().setTexture(textureLayer, texture);

    }


    VisibleMap(ISceneManager* _smgr,IVideoDriver* _driver,ILightSceneNode *_lightNode, u32 *_ticker, ShaderWrapper *_MyShaders)
    {
        smgr = _smgr;
        driver = _driver;
        lightNode = _lightNode;
        ticker = _ticker;

        MyShaders = _MyShaders;


        edgemesh.init();
        // cornermesh.init();

        srand(244422);

        TileMap = new TileInfo*[I_SIZE];
        for( int i = 0 ; i < I_SIZE ; i++ )
            TileMap[i] = new TileInfo [J_SIZE];

        nodes = new IMeshSceneNode**[I_SIZE/I_CHUNKSIZE];
        for( int i = 0 ; i < I_SIZE/I_CHUNKSIZE ; i++ )
            nodes[i] = new IMeshSceneNode* [J_SIZE/J_CHUNKSIZE];

        trees = new IMeshSceneNode**[I_SIZE/I_CHUNKSIZE];
        for( int i = 0 ; i < I_SIZE/I_CHUNKSIZE ; i++ )
            trees[i] = new IMeshSceneNode* [J_SIZE/J_CHUNKSIZE];


        for (int i=0; i<I_SIZE; i++)
            for (int j=0; j<J_SIZE; j++)
            {

                TileMap[i][j].Height= (rand()%24>=17)?2:0;
            }

        for (int i=0; i<I_SIZE; i++)
            for (int j=0; j<J_SIZE; j++)
            {
                if ( TileMap[i][j].Height==0 &&
                        (
                            TileMap[UNbrI(i,j)][UNbrJ(i,j)].Height==2 ||
                            TileMap[URNbrI(i,j)][URNbrJ(i,j)].Height==2 ||
                            TileMap[ULNbrI(i,j)][ULNbrJ(i,j)].Height==2 ||
                            TileMap[LNbrI(i,j)][LNbrJ(i,j)].Height==2 ||
                            TileMap[LLNbrI(i,j)][LLNbrJ(i,j)].Height==2 ||
                            TileMap[LRNbrI(i,j)][LRNbrJ(i,j)].Height==2
                        )
                   )

                {
                    TileMap[i][j].Height=1;

                }

            }

        for (int i=0; i<I_SIZE; i++)
            for (int j=0; j<J_SIZE; j++)
                switch (TileMap[i][j].Height)
            {
                case 0:   TileMap[i][j].TerrainType = 2; break;
                case 1:   TileMap[i][j].TerrainType = 3; break;
                case 2:   TileMap[i][j].TerrainType = 0; break;
            }

        for (int a=0; a<I_SIZE/I_CHUNKSIZE; a++)
            for (int b=0; b<J_SIZE/J_CHUNKSIZE; b++)
            {

                CBatchingMesh* BatMesh = new CBatchingMesh();

                for (int I=0+a*I_CHUNKSIZE; I<I_CHUNKSIZE+a*I_CHUNKSIZE; I++)
                    for (int J=0+b*J_CHUNKSIZE; J<J_CHUNKSIZE+b*J_CHUNKSIZE; J++)
                    {

                        int i = I; //for consistency
                        int j = J; //for consistency

                        //let's add nodes

                        SMesh* stempmesh = new SMesh();

                        switch (TileMap[i][j].Height)
                        {
                        case 0:
                            doLowMesh(stempmesh,TileMap[i][j].TerrainType);
                            break;
                        case 1:
                            doShoreMesh(stempmesh,TileMap,i,j,TileMap[i][j].TerrainType);
                            break;
                        case 2:
                            doNormalMesh(stempmesh,TileMap[i][j].TerrainType);
                            break;
                        default:
                            doBasicMesh(stempmesh,TileMap[i][j].TerrainType);
                            break;

                        }

                        IMesh* tempmesh = (IMesh*)stempmesh;

                        tempmesh->getMeshBuffer(0)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)MyShaders->TerrainMaterial;

                        tempmesh->getMeshBuffer(0)->getMaterial().setTexture(0,driver->getTexture("assets/textures/atlas.png"));
                        //setIMeshTexture(tempmesh,0,TileMap[i][j].TerrainType);



                        BatMesh->addMesh(tempmesh,core::vector3df(i*(1.5),j*2*(sqrt(3)/2) + 2*0.5*(sqrt(3)/2)*(i%2),0),core::vector3df(0.0,0.0,0.0),core::vector3df(1.0,1.0,1.0));
                        delete stempmesh;

                        float height;
                        //time for smooth transitions

                        if (j!=J_SIZE-1)
                        {

                            stempmesh = new SMesh();
                            edgemesh.createMesh(stempmesh,0,TileMap[i][j].TerrainType,TileMap[i][j+1].TerrainType);
                            tempmesh = (IMesh*)stempmesh;
                            tempmesh->getMeshBuffer(0)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)MyShaders->TerrainMaterial;
                            tempmesh->getMeshBuffer(0)->getMaterial().setTexture(0,driver->getTexture("assets/textures/atlas.png"));




                        height=TileMap[UNbrI(i,j)][UNbrJ(i,j)].Height==2||TileMap[i][j].Height==2?0:deepness;
                        BatMesh->addMesh(tempmesh,core::vector3df(i*(1.5),j*2*(sqrt(3)/2) + 2*0.5*(sqrt(3)/2)*(i%2)+(sqrt(3)/2),height),core::vector3df(0.0,0.0,0.0),core::vector3df(1.0,1.0,1.0));

                        delete stempmesh;
                         }

                        //another edge
                        stempmesh = new SMesh();

                        edgemesh.createMesh(stempmesh,1,TileMap[i][j].TerrainType,TileMap[URNbrI(i,j)][URNbrJ(i,j)].TerrainType);
                        tempmesh = (IMesh*)stempmesh;
                        tempmesh->getMeshBuffer(0)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)MyShaders->TerrainMaterial;
                        tempmesh->getMeshBuffer(0)->getMaterial().setTexture(0,driver->getTexture("assets/textures/atlas.png"));




                        height=TileMap[URNbrI(i,j)][URNbrJ(i,j)].Height==2||TileMap[i][j].Height==2?0:deepness;
                        BatMesh->addMesh(tempmesh,core::vector3df(i*(1.5)+0.75,j*2*(sqrt(3)/2) + 2*0.5*(sqrt(3)/2)*(i%2)+(sqrt(3)/4),height),core::vector3df(0.0,0.0,-60.0),core::vector3df(1.0,1.0,1.0));
                        delete stempmesh;
                        //and, finally


                        stempmesh = new SMesh();
                        edgemesh.createMesh(stempmesh,2,TileMap[i][j].TerrainType,TileMap[LRNbrI(i,j)][LRNbrJ(i,j)].TerrainType);
                        tempmesh = (IMesh*)stempmesh;
                        tempmesh->getMeshBuffer(0)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)MyShaders->TerrainMaterial;
                        tempmesh->getMeshBuffer(0)->getMaterial().setTexture(0,driver->getTexture("assets/textures/atlas.png"));
                        height=TileMap[LRNbrI(i,j)][LRNbrJ(i,j)].Height==2||TileMap[i][j].Height==2?0:deepness;
                        BatMesh->addMesh(tempmesh,core::vector3df(i*(1.5)+0.75,j*2*(sqrt(3)/2) + 2*0.5*(sqrt(3)/2)*(i%2)-(sqrt(3)/4),height),core::vector3df(0.0,0.0,-120.0),core::vector3df(1.0,1.0,1.0));
                        delete stempmesh;

                        //now, corners...

                        stempmesh = new SMesh();
                        doCornerMesh(stempmesh,TileMap,I,J,TileMap[i][j].TerrainType,TileMap[URNbrI(i,j)][URNbrJ(i,j)].TerrainType,TileMap[UNbrI(i,j)][UNbrJ(i,j)].TerrainType);
                        tempmesh=(IMesh*)stempmesh;

                        tempmesh->getMeshBuffer(0)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)MyShaders->TerrainMaterial;
                        tempmesh->getMeshBuffer(0)->getMaterial().setTexture(0,driver->getTexture("assets/textures/atlas.png"));
                        height=((TileMap[URNbrI(i,j)][URNbrJ(i,j)].Height==2)||(TileMap[i][j].Height==2)||(TileMap[UNbrI(i,j)][UNbrJ(i,j)].Height==2))?0:deepness;
                        BatMesh->addMesh(tempmesh,core::vector3df(i*(1.5)+0.5,j*2*(sqrt(3)/2) + 2*0.5*(sqrt(3)/2)*(i%2)+(sqrt(3)/2),height),core::vector3df(0.0,0.0,0.0),core::vector3df(1.0,1.0,1.0));


                        delete stempmesh;

                        stempmesh = new SMesh();
                        do2CornerMesh(stempmesh,TileMap,I,J,TileMap[i][j].TerrainType,TileMap[LRNbrI(i,j)][LRNbrJ(i,j)].TerrainType,TileMap[URNbrI(i,j)][URNbrJ(i,j)].TerrainType);
                        tempmesh=(IMesh*)stempmesh;

                        tempmesh->getMeshBuffer(0)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)MyShaders->TerrainMaterial;
                        tempmesh->getMeshBuffer(0)->getMaterial().setTexture(0,driver->getTexture("assets/textures/atlas.png"));

                        //setIMeshTexture(tempmesh,0,TileMap[i][j].TerrainType);
                        //setIMeshTexture(tempmesh,2,TileMap[URNbrI(i,j)][URNbrJ(i,j)].TerrainType);
                        //setIMeshTexture(tempmesh,1,TileMap[LRNbrI(i,j)][LRNbrJ(i,j)].TerrainType);

                        //tempmesh->getMeshBuffer(0)->getMaterial().setTexture(3, driver->getTexture("assets/textures/shared/corner.png"));
                        height=((TileMap[URNbrI(i,j)][URNbrJ(i,j)].Height==2)||(TileMap[i][j].Height==2)||(TileMap[LRNbrI(i,j)][LRNbrJ(i,j)].Height==2))?0:deepness;
                        BatMesh->addMesh(tempmesh,core::vector3df(i*(1.5)+1,j*2*(sqrt(3)/2) + 2*0.5*(sqrt(3)/2)*(i%2),height),core::vector3df(0.0,0.0,-60.0),core::vector3df(1.0,1.0,1.0));
                        delete stempmesh;

                    }

                //BatMesh->setHardwareMappingHint(scene::EHM_STATIC,scene::EBT_VERTEX_AND_INDEX);
                BatMesh->finalize();

                nodes[a][b] = smgr->addMeshSceneNode(BatMesh);
                nodes[a][b]->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
                nodes[a][b]->setMaterialFlag(video::EMF_FRONT_FACE_CULLING,false);
                //nodes[a][b]->setMaterialFlag(EMF_WIREFRAME,true);
                nodes[a][b]->setVisible(false);
                //nodes[a][b]->setAutomaticCulling(true);
                BatMesh->drop();


            }



       // waterloo->setPosition (core::vector3df(-7.0,5.0,0.0));
        //waterloo->setScale(core::vector3df(5,5,5));





    }


    ~VisibleMap()
    {
        delete [] *TileMap;
        delete [] TileMap;
    }

    void doLowMesh (SMesh* Mesh, int tertype)
    {

        SColor color;
        color = SColor(0,tertype,0,0);

        SMeshBuffer *buf;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


        buf->Vertices.set_used(61);

        float stepx = 0.25;
        float stepy_x = -0.125;
        float stepy_y = 0.125*sqrt(3);

        float curx = 0.5-1;
        float cury = 0-sqrt(3)/2;
        float intcurx = curx;

        f32 bumps[61];

        for (int i=0; i<5; i++)
            for (int j=((i-1)*(i-1)+11*(i-1))/2+5; j<(i*i+11*i)/2+5; j++)
            {
                bumps[j]=0;
            }

        for (int i = 3; i>=0; i--)
        {
            for (int j=(-(i+1)*(i+1)-9*(i+1))/2+61; j<(-i*i-9*i)/2+61; j++)
            {
                bumps[j]=0;
            }
        }




        for (int i = 0; i<5; i++)
        {
            intcurx = curx;
            for (int j=((i-1)*(i-1)+11*(i-1))/2+5; j<(i*i+11*i)/2+5; j++)
            {
                S3DVertex& v = buf->Vertices[j];

                if ((i!=0)&&(j!=((i-1)*(i-1)+11*(i-1))/2+5)&&(j!=(i*i+11*i)/2+4))
                    v.Pos.set(curx,cury,deepness+bumps[j]);
                else
                    v.Pos.set(curx,cury,deepness+0.1);

                if (j>0)
                {
                    vector3df A1 = vector3df(stepx,0,bumps[j]-bumps[j-1]);
                    A1 = A1.crossProduct(vector3df(stepy_x,stepy_y,bumps[j]-bumps[j-((i-1)*(i-1)+11*(i-1))/2-5+(i*i+11*i)/2+5]));
                    if (A1.Z>0) A1= A1.invert();
                    A1 = A1.normalize();
                    v.Normal = A1;

                }

                else
                {
                    v.Normal.set(0,0,-1);
                }

                v.Color = color;
                v.TCoords.set(0.5+0.5*TEXTUREFACTOR*curx,0.5+0.5*TEXTUREFACTOR*cury);

                curx+=stepx;
            }
            curx=intcurx;
            curx+=stepy_x;
            cury+=stepy_y;
        }

        stepy_x = +0.125;

        curx = -1+stepy_x;
        cury = 0+stepy_y;// sqrt(3)/2-sqrt(3)/2;

        for (int i = 3; i>=0; i--)
        {
            intcurx = curx;
            for (int j=(-(i+1)*(i+1)-9*(i+1))/2+61; j<(-i*i-9*i)/2+61; j++)
            {
                S3DVertex& v = buf->Vertices[j];



                if ((i!=0)&&(j!=(-(i+1)*(i+1)-9*(i+1))/2+61)&&(j!=(-i*i-9*i)/2+60))
                    v.Pos.set(curx,cury,deepness+bumps[j]);
                else
                    v.Pos.set(curx,cury,deepness+0.1);

                if (j!=0)
                {
                    vector3df A1 = vector3df(stepx,0,bumps[j]-bumps[j-1]);
                    A1 = A1.crossProduct(vector3df(stepy_x,stepy_y,bumps[j]-bumps[-(-i*i-9*i)/2+(-(i+1)*(i+1)-9*(i+1))/2+j]));
                    if (A1.Z>0) A1= A1.invert();
                    A1 = A1.normalize();
                    v.Normal = A1;

                }

                else
                {
                    v.Normal.set(0,0,-1);
                }

                v.Color = color;
                v.TCoords.set(0.5+0.5*TEXTUREFACTOR*curx,0.5+0.5*TEXTUREFACTOR*cury);

                curx+=stepx;
            }
            curx=intcurx;
            curx+=stepy_x;
            cury+=stepy_y;
        }

        buf->Indices.set_used(0);


        for (int i = 0; i<4; i++)
        {

            for (int j=((i-1)*(i-1)+11*(i-1))/2+5; j<(i*i+11*i)/2+5; j++)
            {

                buf->Indices.push_back(j);
                buf->Indices.push_back(j-((i-1)*(i-1)+11*(i-1))/2-5+(i*i+11*i)/2+5);
                buf->Indices.push_back(j-((i-1)*(i-1)+11*(i-1))/2-5+(i*i+11*i)/2+6);

                if (j<(i*i+11*i)/2+4)
                {
                    buf->Indices.push_back(j);
                    buf->Indices.push_back(j-((i-1)*(i-1)+11*(i-1))/2-5+(i*i+11*i)/2+6);
                    buf->Indices.push_back(j+1);
                }

            }
        }


        for (int i = 3; i>=0; i--)
        {

            for (int j=(-(i+1)*(i+1)-9*(i+1))/2+61; j<(-i*i-9*i)/2+61; j++)
            {
                buf->Indices.push_back(j);
                buf->Indices.push_back(-(-i*i-9*i)/2+
                                       (-(i+1)*(i+1)-9*(i+1))/2
                                       +j);
                buf->Indices.push_back(
                    -(-i*i-9*i)/2+
                    (-(i+1)*(i+1)-9*(i+1))/2
                    +j-1
                );



                if (j<(-i*i-9*i)/2+60)
                {
                    buf->Indices.push_back(j);
                    buf->Indices.push_back(j+1);
                    buf->Indices.push_back(-(-i*i-9*i)/2+
                                           (-(i+1)*(i+1)-9*(i+1))/2
                                           +j);


                }
            }
        }
        buf->recalculateBoundingBox();
        //  buf->drop();

        Mesh->setDirty();
        Mesh->recalculateBoundingBox();


    }

    void doShoreMesh (SMesh* Mesh,TileInfo** HeightMap,int I,int J, int tertype)
    {
        //   Mesh->clear();
        SColor color = SColor (0,tertype,0,0);

        SMeshBuffer *buf;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }

        buf->Vertices.set_used(61);

        float stepx = 0.25;
        float stepy_x = -0.125;
        float stepy_y = 0.125*sqrt(3);

        float curx = -0.25;
        float cury = 0-sqrt(3)/4;
        float intcurx = curx;

        int num=0;

        for (int j=0; j<=2; j++)
        {
            intcurx = curx;
            for (int i=0; i<3+j; i++)
            {
                S3DVertex& v=buf->Vertices[num];
                v.Pos.set(curx,cury,deepness);
                v.Normal.set(0,0,-1);
                v.Color = color;
                v.TCoords.set(0.5+0.5*TEXTUREFACTOR*curx,0.5+0.5*TEXTUREFACTOR*cury);

                num++;
                curx+=stepx;
            }
            curx=intcurx;
            curx+=stepy_x;
            cury+=stepy_y;
        }

        stepy_x = -stepy_x;

        curx = -0.125-0.25;
        cury = sqrt(3)/8;

        for (int j=1; j>=0; j--)
        {
            intcurx = curx;
            for (int i=0; i<3+j; i++)
            {
                S3DVertex& v=buf->Vertices[num];
                v.Pos.set(curx,cury,deepness);
                v.Normal.set(0,0,-1);
                v.Color =color;
                v.TCoords.set(0.5+0.5*TEXTUREFACTOR*curx,0.5+0.5*TEXTUREFACTOR*cury);

                num++;
                curx+=stepx;
            }
            curx=intcurx;
            curx+=stepy_x;
            cury+=stepy_y;
        }


        float height = 0;

        height = HeightMap[LNbrI(I,J)][LNbrJ(I,J)].Height==2?0.0:deepness;

        for (int i=19; i<23; i++)
        {
            S3DVertex& v=buf->Vertices[i];
            v.Pos.set(-0.25-0.125+0.25*(i-19),-sqrt(3)/8*3,height);
            v.Normal.set(0,(HeightMap[LNbrI(I,J)][LNbrJ(I,J)].Height!=2)?0:deepness,(HeightMap[LNbrI(I,J)][LNbrJ(I,J)].Height!=2)?-1:-sqrt(3)/8);

            if (v.Normal.Z>0) v.Normal.invert();
            v.Normal = v.Normal.normalize();

            v.Color=color;
            v.TCoords.set(0.5*TEXTUREFACTOR*(-0.25-0.125+0.25*(i-19))+0.5,0.5+0.5*TEXTUREFACTOR*(-sqrt(3)/8*3));
        }


        height = HeightMap[LRNbrI(I,J)][LRNbrJ(I,J)].Height==2?0.0:deepness;

        for (int i=23; i<27; i++)
        {
            S3DVertex& v=buf->Vertices[i];
            v.Pos.set(0.25+0.125+0.125*(i-23),-sqrt(3)/8*3+sqrt(3)/8*(i-23),height);
            v.Normal.set(0.125,-sqrt(3)/8,height-deepness);
            v.Normal = v.Normal.crossProduct(vector3df(0.25,0,height-deepness));
            if (v.Normal.Z>0) v.Normal.invert();
            v.Normal = v.Normal.normalize();
            v.Color=color;
            v.TCoords.set(0.5+0.5*TEXTUREFACTOR*(0.25+0.125+0.125*(i-23)),0.5+0.5*TEXTUREFACTOR*(-sqrt(3)/8*3+sqrt(3)/8*(i-23)));
        }

        height = HeightMap[URNbrI(I,J)][URNbrJ(I,J)].Height==2?0.0:deepness;

        for (int i=27; i<31; i++)
        {
            S3DVertex& v=buf->Vertices[i];
            v.Pos.set(0.75-0.125*(i-27),0+sqrt(3)/8*(i-27),height);

            v.Normal.set(0.125,sqrt(3)/8,height-deepness);
            v.Normal = v.Normal.crossProduct(vector3df(0.25,0,height-deepness));
            if (v.Normal.Z>0) v.Normal.invert();
            v.Normal = v.Normal.normalize();


            v.Color=color;
            v.TCoords.set(0.5+0.5*TEXTUREFACTOR*(0.75-0.125*(i-27)),0.5+0.5*TEXTUREFACTOR*(0+sqrt(3)/8*(i-27)));
        }

        height = HeightMap[UNbrI(I,J)][UNbrJ(I,J)].Height==2?0.0:deepness;

        for (int i=31; i<35; i++)
        {
            S3DVertex& v=buf->Vertices[i];
            v.Pos.set(0.25+0.125-0.25*(i-31),+sqrt(3)/8*3,height);


            v.Normal.set(0,(HeightMap[UNbrI(I,J)][UNbrJ(I,J)].Height!=2)?0:-deepness,(HeightMap[UNbrI(I,J)][UNbrJ(I,J)].Height!=2)?-1:-sqrt(3)/8);
            if (v.Normal.Z>0) v.Normal.invert();
            v.Normal = v.Normal.normalize();


            v.Color=color;
            v.TCoords.set(0.5+0.5*TEXTUREFACTOR*(0.25+0.125-0.25*(i-31)),0.5+0.5*TEXTUREFACTOR*(+sqrt(3)/8*3));
        }


        height = HeightMap[ULNbrI(I,J)][ULNbrJ(I,J)].Height==2?0.0:deepness;

        for (int i=35; i<39; i++)
        {
            S3DVertex& v=buf->Vertices[i];
            v.Pos.set(-0.25-0.125-0.125*(i-35),+sqrt(3)/8*3-sqrt(3)/8*(i-35),height);

            v.Normal.set(-0.125,sqrt(3)/8,height-deepness);
            v.Normal = v.Normal.crossProduct(vector3df(-0.25,0,height-deepness));
            if (v.Normal.Z>0) v.Normal.invert();
            v.Normal = v.Normal.normalize();

            v.Color=color;
            v.TCoords.set(0.5+0.5*TEXTUREFACTOR*(-0.25-0.125-0.125*(i-35)),0.5+0.5*TEXTUREFACTOR*(+sqrt(3)/8*3-sqrt(3)/8*(i-35)));
        }


        height = HeightMap[LLNbrI(I,J)][LLNbrJ(I,J)].Height==2?0.0:deepness;

        for (int i=39; i<43; i++)
        {
            S3DVertex& v=buf->Vertices[i];
            v.Pos.set(-0.75+0.125*(i-39),0-sqrt(3)/8*(i-39),height);

            v.Normal.set(-0.125,-sqrt(3)/8,height-deepness);
            v.Normal = v.Normal.crossProduct(vector3df(-0.25,0,height-deepness));
            if (v.Normal.Z>0) v.Normal.invert();
            v.Normal = v.Normal.normalize();

            v.Color=color;
            v.TCoords.set(0.5+0.5*TEXTUREFACTOR*(-0.75+0.125*(i-39)),0.5+0.5*TEXTUREFACTOR*(0-sqrt(3)/8*(i-39)));
        }



        buf->Indices.set_used(0);

        buf->Indices.push_back(0);
        buf->Indices.push_back(7);
        buf->Indices.push_back(9);
        buf->Indices.push_back(0);
        buf->Indices.push_back(9);
        buf->Indices.push_back(2);
        buf->Indices.push_back(2);
        buf->Indices.push_back(9);
        buf->Indices.push_back(11);
        buf->Indices.push_back(7);
        buf->Indices.push_back(16);
        buf->Indices.push_back(9);
        buf->Indices.push_back(9);
        buf->Indices.push_back(16);
        buf->Indices.push_back(18);
        buf->Indices.push_back(9);
        buf->Indices.push_back(18);
        buf->Indices.push_back(11);

        buf->Indices.push_back(19);
        buf->Indices.push_back(0);
        buf->Indices.push_back(20);
        buf->Indices.push_back(20);
        buf->Indices.push_back(1);
        buf->Indices.push_back(21);
        buf->Indices.push_back(21);
        buf->Indices.push_back(2);
        buf->Indices.push_back(22);

        buf->Indices.push_back(20);
        buf->Indices.push_back(0);
        buf->Indices.push_back(1);
        buf->Indices.push_back(21);
        buf->Indices.push_back(1);
        buf->Indices.push_back(2);

        buf->Indices.push_back(23);
        buf->Indices.push_back(2);
        buf->Indices.push_back(24);
        buf->Indices.push_back(24);
        buf->Indices.push_back(6);
        buf->Indices.push_back(25);
        buf->Indices.push_back(25);
        buf->Indices.push_back(11);
        buf->Indices.push_back(26);

        buf->Indices.push_back(24);
        buf->Indices.push_back(2);
        buf->Indices.push_back(6);
        buf->Indices.push_back(25);
        buf->Indices.push_back(6);
        buf->Indices.push_back(11);

        buf->Indices.push_back(27);
        buf->Indices.push_back(11);
        buf->Indices.push_back(28);
        buf->Indices.push_back(28);
        buf->Indices.push_back(15);
        buf->Indices.push_back(29);
        buf->Indices.push_back(29);
        buf->Indices.push_back(18);
        buf->Indices.push_back(30);

        buf->Indices.push_back(28);
        buf->Indices.push_back(11);
        buf->Indices.push_back(15);
        buf->Indices.push_back(29);
        buf->Indices.push_back(15);
        buf->Indices.push_back(18);

        buf->Indices.push_back(31);
        buf->Indices.push_back(18);
        buf->Indices.push_back(32);
        buf->Indices.push_back(32);
        buf->Indices.push_back(17);
        buf->Indices.push_back(33);
        buf->Indices.push_back(33);
        buf->Indices.push_back(16);
        buf->Indices.push_back(34);

        buf->Indices.push_back(32);
        buf->Indices.push_back(18);
        buf->Indices.push_back(17);
        buf->Indices.push_back(33);
        buf->Indices.push_back(17);
        buf->Indices.push_back(16);


        buf->Indices.push_back(35);
        buf->Indices.push_back(16);
        buf->Indices.push_back(36);
        buf->Indices.push_back(36);
        buf->Indices.push_back(12);
        buf->Indices.push_back(37);
        buf->Indices.push_back(37);
        buf->Indices.push_back(7);
        buf->Indices.push_back(38);

        buf->Indices.push_back(36);
        buf->Indices.push_back(16);
        buf->Indices.push_back(12);
        buf->Indices.push_back(37);
        buf->Indices.push_back(12);
        buf->Indices.push_back(7);

        buf->Indices.push_back(39);
        buf->Indices.push_back(7);
        buf->Indices.push_back(40);
        buf->Indices.push_back(40);
        buf->Indices.push_back(3);
        buf->Indices.push_back(41);
        buf->Indices.push_back(41);
        buf->Indices.push_back(0);
        buf->Indices.push_back(42);

        buf->Indices.push_back(40);
        buf->Indices.push_back(7);
        buf->Indices.push_back(3);
        buf->Indices.push_back(41);
        buf->Indices.push_back(3);
        buf->Indices.push_back(0);

        buf->recalculateBoundingBox();
//        buf->drop();

        Mesh->setDirty();
        Mesh->recalculateBoundingBox();





    }

    void doNormalMesh (SMesh* Mesh, int tertype)
    {
        SColor color = SColor (0,tertype,0,0);
        SMeshBuffer *buf;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


        buf->Vertices.set_used(7);


        //srand (1488);


        for (int i = 0; i<6; i++)
        {
               S3DVertex& v = buf->Vertices[i];

                    v.Pos.set(0.75*cosf(i*PI/3.0),0.75*sinf(i*PI/3.0),0.0);

                   v.Normal.set(0.0,0.0,-1.0);

                v.Color = color;
                v.TCoords.set(0.5+0.375*TEXTUREFACTOR*cosf(i*PI/3),0.5+0.375*TEXTUREFACTOR*sinf(i*PI/3));


            }

        S3DVertex& v0 = buf->Vertices[6];
        v0.Pos.set(0.0,0.0,0.0);
        v0.Normal.set(0.0,0.0,-1.0);
        v0.Color = color;
        v0.TCoords.set(0.5,0.5);



        buf->Indices.set_used(0);


        for (int i = 0; i<6; i++)
        {
            buf->Indices.push_back(i);
            buf->Indices.push_back(6);
            buf->Indices.push_back((i+1)%6);
        }




        buf->recalculateBoundingBox();
        //  buf->drop();

        Mesh->setDirty();
        Mesh->recalculateBoundingBox();

    }

    void doBasicMesh (SMesh* Mesh, int tertype)
    {

        SMeshBuffer *buf;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


        buf->Vertices.set_used(3);


        for (int i=0; i<3; i++)
        {

            S3DVertex& v = buf->Vertices[i];
            v.Pos.set(0.125*cosf(PI/3*i),0.125*sinf(PI/3*i),deepness);
            v.Normal.set(0,0,-1);
            v.Color = SColor(0,tertype,255,255);
            v.TCoords.set(0.5+0.5*TEXTUREFACTOR*0.125*cosf(PI/3*i),0.5+0.5*TEXTUREFACTOR*0.125*sinf(PI/3*i));


        }




        buf->Indices.set_used(0);
        buf->Indices.push_back(2);
        buf->Indices.push_back(1);
        buf->Indices.push_back(0);



        buf->recalculateBoundingBox();
        //  buf->drop();

        Mesh->setDirty();
        Mesh->recalculateBoundingBox();
        Mesh->setHardwareMappingHint(scene::EHM_STATIC);

    }


    void doWaterQuadMesh (SMesh* Mesh)
    {

        SMeshBuffer *buf;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


        buf->Vertices.set_used(4);


            S3DVertex& v = buf->Vertices[0];
            v.Pos.set(0.0,0.0,0.0);
            v.Normal.set(0,0,-1);
            v.Color = SColor(230,255,255,255);
            v.TCoords.set(0.0,0.0);

            S3DVertex& v1=buf->Vertices[1];
            v1.Pos.set(5.0,0.0,0.0);
            v1.Normal.set(0,0,-1);
            v1.Color = SColor(230,255,255,255);
            v1.TCoords.set(1.0,0.0);

            S3DVertex& v2=buf->Vertices[2];
            v2.Pos.set(5.0,5.0,0.0);
            v2.Normal.set(0,0,-1);
            v2.Color = SColor(230,255,255,255);
            v2.TCoords.set(1.0,1.0);


            S3DVertex& v3=buf->Vertices[3];
            v3.Pos.set(0.0,5.0,0.0);
            v3.Normal.set(0,0,-1);
            v3.Color = SColor(230,255,255,255);
            v3.TCoords.set(0.0,1.0);


        buf->Indices.set_used(0);
        buf->Indices.push_back(0);
        buf->Indices.push_back(2);
        buf->Indices.push_back(1);

        buf->Indices.push_back(2);
        buf->Indices.push_back(0);
        buf->Indices.push_back(3);



        buf->recalculateBoundingBox();
        //  buf->drop();

        Mesh->setDirty();
        Mesh->recalculateBoundingBox();
        Mesh->setHardwareMappingHint(scene::EHM_STATIC);

    }


    void doCornerMesh(SMesh* Mesh, TileInfo** TileMap, int I,int J,int tertype1, int tertype2, int tertype3)
    {
        //Mesh->setHardwareMappingHint(scene::EHM_STATIC);

        SColor color  = SColor(32*4,tertype1,tertype2,tertype3);

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
        v0.Color = color;
        v0.TCoords.set(0.5 ,0.5);


        for (int i = 1; i<7; i++)
        {

            S3DVertex& v = buf->Vertices[i];//for regular cap;
            v.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
            v.Normal.set(0,0,-1);
            v.Color =  color;
            v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*TEXTUREFACTOR*0.25*sinf(PI/3*(i-1)));

            S3DVertex& vv = buf->Vertices[i+18];//for one of the cliffs
            vv.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
            vv.Normal.set(0,0,-1);
            vv.Color =  color;
            vv.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*TEXTUREFACTOR*0.25*sinf(PI/3*(i-1)));

            vector3df face1;
            face1.set(0.25*cosf(PI/3*(i+1)),0.25*sinf(PI/3*(i+1)),0);
            face1 = face1.crossProduct(vector3df(-0.25*cosf(PI/3*(i-1)),-0.25*sinf(PI/3*(i-1)),-deepness));
            if (face1.Z>0) face1.invert();
            vv.Normal = face1.normalize();

            //clone of this same vertex for next cliff
            S3DVertex& vv2 = buf->Vertices[i+24];
            vv2.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
            vv2.Normal.set(0,0,-1);
            vv2.Color =  color;
            vv2.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*TEXTUREFACTOR*0.25*sinf(PI/3*(i-1)));

            face1.set(0.25*cosf(PI/3*(i)),0.25*sinf(PI/3*(i)),0);
            face1 = face1.crossProduct(vector3df(-0.25*cosf(PI/3*(i-2)),-0.25*sinf(PI/3*(i-2)),-deepness));
            if (face1.Z>0) face1.invert();
            vv2.Normal = face1.normalize();

            S3DVertex& v2 = buf->Vertices[5+2*i];//lower of the cliff
            v2.Pos.set(0.5*cosf(PI/3*(i-1)),0.5*sinf(PI/3*(i-1)),deepness);
            v2.Normal.set(0,0,-1);
            v2.Color =  color;
            v2.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.5*cosf(PI/3*(i-1))),0.5 +0.5*0.5*TEXTUREFACTOR*sinf(PI/3*(i-1)));

            S3DVertex& v3 = buf->Vertices[5+2*i+1]; //middle of the cliff
            v3.Pos.set(0.5*cosf(PI/3*(i-1))+0.25*cosf(PI/3*(i+1)),0.5*sinf(PI/3*(i-1))+0.25*sinf(PI/3*(i+1)),deepness);
            v3.Normal.set(0,0,-1);
            v3.Color = color;
            v3.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.5*cosf(PI/3*(i-1))+0.25*TEXTUREFACTOR*cosf(PI/3*(i+1))),0.5 +0.5*TEXTUREFACTOR*(0.5*sinf(PI/3*(i-1))+0.25*sinf(PI/3*(i+1))));

        }






        buf->Indices.set_used(0);

        bool allow[6];

        allow[0] = (TileMap[UNbrI(I,J)][UNbrJ(I,J)].Height==TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height)&&(TileMap[UNbrI(I,J)][UNbrJ(I,J)].Height<TileMap[I][J].Height);
        allow[1] = allow[0];

        allow[2] = (TileMap[UNbrI(I,J)][UNbrJ(I,J)].Height==TileMap[I][J].Height)&&(TileMap[I][J].Height<TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height);
        allow[3] = allow[2];

        allow[4] = (TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height==TileMap[I][J].Height)&&(TileMap[UNbrI(I,J)][UNbrJ(I,J)].Height>TileMap[I][J].Height);
        allow[5] = allow[4];

        for (int i = 1; i<7; i++)
        {

            buf->Indices.push_back(i);
            buf->Indices.push_back(0);
            buf->Indices.push_back((i+1-1)%6+1);//cap


            if (allow[i-1])
            {
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


    void do2CornerMesh(SMesh* Mesh, TileInfo** TileMap, int I,int J,int tertype1, int tertype2, int tertype3)
    {
        //Mesh->setHardwareMappingHint(scene::EHM_STATIC);

        SColor color = SColor (32*5+16,tertype1,tertype2,tertype3);

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
        v0.Color =  color;
        v0.TCoords.set(0.5 ,0.5);


        for (int i = 1; i<7; i++)
        {

            S3DVertex& v = buf->Vertices[i];//for regular cap;
            v.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
            v.Normal.set(0,0,-1);
            v.Color =  color;
            v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*TEXTUREFACTOR*0.25*sinf(PI/3*(i-1)));

            S3DVertex& vv = buf->Vertices[i+18];//for one of the cliffs
            vv.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
            vv.Normal.set(0,0,-1);
            vv.Color =  color;
            vv.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*TEXTUREFACTOR*0.25*sinf(PI/3*(i-1)));

            vector3df face1;
            face1.set(0.25*cosf(PI/3*(i+1)),0.25*sinf(PI/3*(i+1)),0);
            face1 = face1.crossProduct(vector3df(-0.25*cosf(PI/3*(i-1)),-0.25*sinf(PI/3*(i-1)),-deepness));
            if (face1.Z>0) face1.invert();
            vv.Normal = face1.normalize();

            //clone of this same vertex for next cliff
            S3DVertex& vv2 = buf->Vertices[i+24];
            vv2.Pos.set(0.25*cosf(PI/3*(i-1)),0.25*sinf(PI/3*(i-1)),0);
            vv2.Normal.set(0,0,-1);
            vv2.Color =  color;
            vv2.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.25*cosf(PI/3*(i-1))),0.5 +0.5*TEXTUREFACTOR*0.25*sinf(PI/3*(i-1)));

            face1.set(0.25*cosf(PI/3*(i)),0.25*sinf(PI/3*(i)),0);
            face1 = face1.crossProduct(vector3df(-0.25*cosf(PI/3*(i-2)),-0.25*sinf(PI/3*(i-2)),-deepness));
            if (face1.Z>0) face1.invert();
            vv2.Normal = face1.normalize();

            S3DVertex& v2 = buf->Vertices[5+2*i];//lower of the cliff
            v2.Pos.set(0.5*cosf(PI/3*(i-1)),0.5*sinf(PI/3*(i-1)),deepness);
            v2.Normal.set(0,0,-1);
            v2.Color =  color;
            v2.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.5*cosf(PI/3*(i-1))),0.5 +0.5*TEXTUREFACTOR*0.5*sinf(PI/3*(i-1)));

            S3DVertex& v3 = buf->Vertices[5+2*i+1]; //middle of the cliff
            v3.Pos.set(0.5*cosf(PI/3*(i-1))+0.25*cosf(PI/3*(i+1)),0.5*sinf(PI/3*(i-1))+0.25*sinf(PI/3*(i+1)),deepness);
            v3.Normal.set(0,0,-1);
            v3.Color = color;
            v3.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(0.5*cosf(PI/3*(i-1))+0.25*cosf(PI/3*(i+1))),0.5 +0.5*TEXTUREFACTOR*(0.5*sinf(PI/3*(i-1))+0.25*sinf(PI/3*(i+1))));

        }






        buf->Indices.set_used(0);

        bool allow[6];

        allow[4] = (TileMap[LRNbrI(I,J)][LRNbrJ(I,J)].Height==TileMap[I][J].Height)&&(TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height>TileMap[I][J].Height);
        allow[5] = allow[4];

        allow[0] = (TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height==TileMap[LRNbrI(I,J)][LRNbrJ(I,J)].Height)&&(TileMap[I][J].Height>TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height);
        allow[1] = allow[0];

        allow[2] = (TileMap[URNbrI(I,J)][URNbrJ(I,J)].Height==TileMap[I][J].Height)&&(TileMap[LRNbrI(I,J)][LRNbrJ(I,J)].Height>TileMap[I][J].Height);
        allow[3] = allow[2];

        for (int i = 1; i<7; i++)
        {

            buf->Indices.push_back(i);
            buf->Indices.push_back(0);
            buf->Indices.push_back((i+1-1)%6+1);//cap


            if (allow[i-1])
            {

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

    static void doTreeMesh (SMesh* Mesh)
    {

        SColor color = SColor (255,255,255,255);
        SMeshBuffer *buf = 0;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


        buf->Vertices.set_used(399);


        float width;
        float height;

        float basewidth = 0.02;
        float maxheight = 0.4*(1+0.3*(rand()%64/64.0-0.5));

        for (int j = 0; j<4; j++)
        {
         width =  basewidth - (j/5.0)*basewidth;
         height = 0 /*baseheight*/ - (j/3.0)*maxheight;
        for (int i = 0; i<4; i++)
        {

            S3DVertex& v = buf->Vertices[i+4*j];//for regular cap;
            v.Pos.set(width*cosf(PI/2*i),width*sinf(PI/2*i),height);
            //v.Normal.set(width*cosf(PI/2*i),width*sinf(PI/2*i),-1);
            v.Normal.set(0,0,-1);
            v.Color =  color;
            v.TCoords.set(0.5,0.5);
        }

        }

        int NUM_SEGMENTS = 6;
        int NUM_STAGES = 5;


        float FOLIAGE_START_HEIGHT = 0.3*maxheight;
        float FOLIAGE_FALL = -0.1;
        float STAGE_OFFSET = 0.0;
        float BASE_STAGE_WIDTH=0.25;

        for (int j=0;j<NUM_STAGES;j++)
        {



            S3DVertex& v0 = buf->Vertices[16+0+(NUM_SEGMENTS+1)*j];
            v0.Pos.set(0,0,-(FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j ));
            v0.Normal.set(0,0,-1);
            v0.Color =  color;
            v0.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(v0.Pos.X),0.5 +0.5*TEXTUREFACTOR*v0.Pos.Y);

            STAGE_OFFSET = 2*PI*(rand()%64)/64.0;


            float STAGE_WIDTH;


            for (int i=1;i<=NUM_SEGMENTS;i++)
            {
                STAGE_WIDTH = BASE_STAGE_WIDTH*(1.0-0.25*abs(j-3)/3.0)*(1.0+0.1*((rand()%64)/64.0 - 0.5));

                FOLIAGE_FALL = -0.17+0.13*(rand()%64)/64;
                 if (j>=NUM_STAGES-2) FOLIAGE_FALL = 0.07;

                S3DVertex& v = buf->Vertices[16+i+(NUM_SEGMENTS+1)*j];
                v.Pos.set(STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*(i-1)+STAGE_OFFSET),STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*(i-1)+STAGE_OFFSET),-(FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL ));

                // to compute normal we should take a crossproduct of two vectors:
                // one is going from current vertex to a base vertex V0.
                // Second can go to prev vertex or next vertex;
                // to get a kinda smooth lighting we should take average of them;

                core::vector3df ToPrev;
                core::vector3df ToNext;
                core::vector3df ToBase;

                ToBase.X = v.Pos.X - v0.Pos.X;
                ToBase.Y = v.Pos.Y - v0.Pos.Y;
                ToBase.Z = v.Pos.Z - v0.Pos.Z;

                ToNext.X = v.Pos.X - STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*(i%NUM_SEGMENTS)+STAGE_OFFSET);
                ToNext.Y = v.Pos.Y - STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*(i%NUM_SEGMENTS)+STAGE_OFFSET);
                ToNext.Z = v.Pos.Z - (FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL );

                ToPrev.X = v.Pos.X - STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*((i-2)<0?NUM_SEGMENTS:i-2)+STAGE_OFFSET);
                ToPrev.Y = v.Pos.Y - STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*((i-2)<0?NUM_SEGMENTS:i-2)+STAGE_OFFSET);
                ToPrev.Z = v.Pos.Z - (FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL );

                core::vector3df NormalPrev = ToBase.crossProduct(ToNext);
                core::vector3df NormalNext = ToBase.crossProduct(ToPrev);

                if (NormalPrev.Z>0) NormalPrev.invert();
                if (NormalNext.Z>0) NormalNext.invert();

                core::vector3df Normal = (NormalPrev.normalize()+NormalNext.normalize());

                v.Normal = Normal.normalize();


                v.Color =  color;
                v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(cosf(2*PI/NUM_SEGMENTS*(i-1))),0.5 +0.5*TEXTUREFACTOR*sinf(2*PI/NUM_SEGMENTS*(i-1)));

            }
        }

        S3DVertex& vCenter = buf->Vertices[16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+1];
        vCenter.Pos.set(0,0,-(maxheight+FOLIAGE_START_HEIGHT)*0.5);
        vCenter.Normal.set(0,0,-1);
        vCenter.TCoords.set(0.5,0.5);


        for (int i=0;i<6;i++)
        {
            S3DVertex& v = buf->Vertices[16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+2+i];

            v.Pos.set(0,sinf(PI/3.0*i)*BASE_STAGE_WIDTH,(maxheight+FOLIAGE_START_HEIGHT)*0.5+cosf(PI/3.0*i)*(maxheight-FOLIAGE_START_HEIGHT)*0.5);
            v.Pos.Z*=-1.0;
            v.Normal.set(0,0,-1);
            v.TCoords.set((0.5+0.5*sinf(PI/3*i))*TEXTUREFACTOR,(0.5+0.5*cosf(PI/3*i))*TEXTUREFACTOR);
            v.Color = SColor (255,255,255,255);
        }

        for (int i=0;i<6;i++)
        {
            S3DVertex& v = buf->Vertices[16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+8+i];

            v.Pos.set(sinf(PI/3.0*i)*BASE_STAGE_WIDTH,0,(maxheight+FOLIAGE_START_HEIGHT)*0.5+cosf(PI/3.0*i)*(maxheight-FOLIAGE_START_HEIGHT)*0.5);
            v.Pos.Z*=-1.0;
            v.Normal.set(0,0,-1);
            v.Color = SColor (255,255,255,255);
            v.TCoords.set((0.5+0.5*sinf(PI/3*i))*TEXTUREFACTOR,(0.5+0.5*cosf(PI/3*i))*TEXTUREFACTOR);
        }


        buf->Indices.set_used(0);


        for (int j=0; j<4-1;j++)
            for (int i=0;i<4;i++)
            {
                buf->Indices.push_back(4*j+i);buf->Indices.push_back(4*j+(i+1)%4);buf->Indices.push_back(4*(j+1)+(i+1)%4);
                buf->Indices.push_back(4*(j+1)+(i+1)%4);buf->Indices.push_back(4*(j+1)+(i));buf->Indices.push_back(4*j+i);
            }


       for (int j=0;j<NUM_STAGES;j++)
        {

            for (int i=1;i<=NUM_SEGMENTS;i++)
            {
                 buf->Indices.push_back(16+i+(NUM_SEGMENTS+1)*j);
                 buf->Indices.push_back(16+0+(NUM_SEGMENTS+1)*j);
                 buf->Indices.push_back(16+(i)%(NUM_SEGMENTS)+1 + (NUM_SEGMENTS+1)*j);

            }
        }

        for (int i=0;i<6;i++)
        {

           buf->Indices.push_back(16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+2+i);
           buf->Indices.push_back(16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+1);
           buf->Indices.push_back(16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+2+(i+1)%6);

            buf->Indices.push_back(16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+8+i);
            buf->Indices.push_back(16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+1);
            buf->Indices.push_back(16+NUM_SEGMENTS+(NUM_SEGMENTS+1)*(NUM_STAGES-1)+8+(i+1)%6);
        }

        buf->recalculateBoundingBox();
        // buf->drop();


        Mesh->setDirty();
        Mesh->recalculateBoundingBox();

        }


    static void doPineMesh (SMesh* Mesh)
    {

        SColor color = SColor (255,255,255,255);
        SMeshBuffer *buf = 0;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


        buf->Vertices.set_used(99);


        float width;
        float height;

        float basewidth = 0.03;
        float maxheight = 0.4*(1+0.7*(rand()%64/64.0-0.5));

        for (int j = 0; j<4; j++)
        {
         width =  basewidth - (j/5.0)*basewidth;
         height = 0 /*baseheight*/ - (j/3.0)*maxheight;
        for (int i = 0; i<4; i++)
        {

            S3DVertex& v = buf->Vertices[i+4*j];//for regular cap;
            v.Pos.set(width*cosf(PI/2*i),width*sinf(PI/2*i),height);
            //v.Normal.set(width*cosf(PI/2*i),width*sinf(PI/2*i),-1);
            v.Normal.set(0,0,-1);
            v.Color =  color;
            v.TCoords.set(0.5,0.5);
        }

        }

        int NUM_SEGMENTS = 6;
        int NUM_STAGES = 2;


        float FOLIAGE_START_HEIGHT = 0.9*maxheight;
        float FOLIAGE_FALL = 0;
        float STAGE_OFFSET = 0.0;
        float BASE_STAGE_WIDTH=0.35;

        for (int j=0;j<NUM_STAGES;j++)
        {


            S3DVertex& v0 = buf->Vertices[16+0+(NUM_SEGMENTS+1)*j];
            v0.Pos.set(0,0,-(FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j ));
            v0.Normal.set(0,0,-1);
            v0.Color =  color;
            v0.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(v0.Pos.X),0.5 +0.5*TEXTUREFACTOR*v0.Pos.Y);

            STAGE_OFFSET = 2*PI*(rand()%64)/64.0;




            float STAGE_WIDTH;


            for (int i=1;i<=NUM_SEGMENTS;i++)
            {
                STAGE_WIDTH = (BASE_STAGE_WIDTH + 0.4*j*BASE_STAGE_WIDTH)*(1.0+0.3*((rand()%64)/64.0 - 0.5));

                FOLIAGE_FALL = -0.05+0.13*(rand()%64)/64;
                S3DVertex& v = buf->Vertices[16+i+(NUM_SEGMENTS+1)*j];
                v.Pos.set(STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*(i-1)+STAGE_OFFSET),STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*(i-1)+STAGE_OFFSET),-(FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL ));

                // to compute normal we should take a crossproduct of two vectors:
                // one is going from current vertex to a base vertex V0.
                // Second can go to prev vertex or next vertex;
                // to get a kinda smooth lighting we should take average of them;

                core::vector3df ToPrev;
                core::vector3df ToNext;
                core::vector3df ToBase;

                ToBase.X = v.Pos.X - v0.Pos.X;
                ToBase.Y = v.Pos.Y - v0.Pos.Y;
                ToBase.Z = v.Pos.Z - v0.Pos.Z;

                ToNext.X = v.Pos.X - STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*(i%NUM_SEGMENTS)+STAGE_OFFSET);
                ToNext.Y = v.Pos.Y - STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*(i%NUM_SEGMENTS)+STAGE_OFFSET);
                ToNext.Z = v.Pos.Z - (FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL );

                ToPrev.X = v.Pos.X - STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*((i-2)<0?NUM_SEGMENTS:i-2)+STAGE_OFFSET);
                ToPrev.Y = v.Pos.Y - STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*((i-2)<0?NUM_SEGMENTS:i-2)+STAGE_OFFSET);
                ToPrev.Z = v.Pos.Z - (FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL );

                core::vector3df NormalPrev = ToBase.crossProduct(ToNext);
                core::vector3df NormalNext = ToBase.crossProduct(ToPrev);

                if (NormalPrev.Z>0) NormalPrev.invert();
                if (NormalNext.Z>0) NormalNext.invert();

                core::vector3df Normal = (NormalPrev.normalize()+NormalNext.normalize());

                v.Normal = Normal.normalize();


                v.Color =  color;
                v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(cosf(2*PI/NUM_SEGMENTS*(i-1))),0.5 +0.5*TEXTUREFACTOR*sinf(2*PI/NUM_SEGMENTS*(i-1)));

            }
        }





        buf->Indices.set_used(0);


        for (int j=0; j<4-1;j++)
            for (int i=0;i<4;i++)
            {
                buf->Indices.push_back(4*j+i);buf->Indices.push_back(4*j+(i+1)%4);buf->Indices.push_back(4*(j+1)+(i+1)%4);
                buf->Indices.push_back(4*(j+1)+(i+1)%4);buf->Indices.push_back(4*(j+1)+(i));buf->Indices.push_back(4*j+i);
            }


        for (int j=0;j<NUM_STAGES;j++)
        {

            for (int i=1;i<=NUM_SEGMENTS;i++)
            {
                 buf->Indices.push_back(16+i+(NUM_SEGMENTS+1)*j);
                 buf->Indices.push_back(16+0+(NUM_SEGMENTS+1)*j);
                 buf->Indices.push_back(16+(i/*+1-1*/)%(NUM_SEGMENTS)+1 + (NUM_SEGMENTS+1)*j);

            }
        }

        buf->recalculateBoundingBox();
        // buf->drop();


        Mesh->setDirty();
        Mesh->recalculateBoundingBox();

        }


    static void doSpruceMesh (SMesh* Mesh)
    {

        SColor color = SColor (255,255,255,255);
        SMeshBuffer *buf = 0;
        if (Mesh->getMeshBufferCount()>0)
            buf = (SMeshBuffer*)Mesh->getMeshBuffer(0);
        else
        {

            buf = new SMeshBuffer();
            Mesh->addMeshBuffer(buf);
        }


        buf->Vertices.set_used(99);


        float width;
        float height;

        float basewidth = 0.05;
        float maxheight = 0.5;

        for (int j = 0; j<3; j++)
        {
         width =  basewidth - (j/5.0)*basewidth;
         height = 0 /*baseheight*/ - (j/3.0)*maxheight;
        for (int i = 0; i<4; i++)
        {

            S3DVertex& v = buf->Vertices[i+4*j];//for regular cap;
            v.Pos.set(width*cosf(PI/2*i),width*sinf(PI/2*i),height);
            v.Normal.set(width*cosf(PI/2*i),width*sinf(PI/2*i),0);
            v.Color =  color;
            v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(v.Pos.X),0.5 +0.5*TEXTUREFACTOR*v.Pos.Y);
        }

        }

        int NUM_SEGMENTS = 7;
        int NUM_STAGES = 4;


        float FOLIAGE_START_HEIGHT = 0.3;
        float FOLIAGE_FALL = 0.2;
        float STAGE_OFFSET = 0.0;
        float BASE_STAGE_WIDTH=0.4;

        for (int j=0;j<NUM_STAGES;j++)
        {

            S3DVertex& v0 = buf->Vertices[16+0+(NUM_SEGMENTS+1)*j];
            v0.Pos.set(0,0,-(FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j ));
            v0.Normal.set(0,0,-1);
            v0.Color =  color;
            v0.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(v0.Pos.X),0.5 +0.5*TEXTUREFACTOR*v0.Pos.Y);

            STAGE_OFFSET = 2*PI*(rand()%64)/64.0;




            float STAGE_WIDTH = BASE_STAGE_WIDTH - exp((j*1.0/NUM_STAGES))*0.15;


            for (int i=1;i<=NUM_SEGMENTS;i++)
            {

                S3DVertex& v = buf->Vertices[16+i+(NUM_SEGMENTS+1)*j];
                v.Pos.set(STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*(i-1)+STAGE_OFFSET),STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*(i-1)+STAGE_OFFSET),-(FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL ));

                // to compute normal we should take a crossproduct of two vectors:
                // one is going from current vertex to a base vertex V0.
                // Second can go to prev vertex or next vertex;
                // to get a kinda smooth lighting we should take average of them;

                core::vector3df ToPrev;
                core::vector3df ToNext;
                core::vector3df ToBase;

                ToBase.X = v.Pos.X - v0.Pos.X;
                ToBase.Y = v.Pos.Y - v0.Pos.Y;
                ToBase.Z = v.Pos.Z - v0.Pos.Z;

                ToNext.X = v.Pos.X - STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*(i%NUM_SEGMENTS)+STAGE_OFFSET);
                ToNext.Y = v.Pos.Y - STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*(i%NUM_SEGMENTS)+STAGE_OFFSET);
                ToNext.Z = v.Pos.Z - (FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL );

                ToPrev.X = v.Pos.X - STAGE_WIDTH*cosf(2*PI/NUM_SEGMENTS*((i-2)<0?NUM_SEGMENTS:i-2)+STAGE_OFFSET);
                ToPrev.Y = v.Pos.Y - STAGE_WIDTH*sinf(2*PI/NUM_SEGMENTS*((i-2)<0?NUM_SEGMENTS:i-2)+STAGE_OFFSET);
                ToPrev.Z = v.Pos.Z - (FOLIAGE_START_HEIGHT + (maxheight-FOLIAGE_START_HEIGHT)/(NUM_STAGES-1)*j - FOLIAGE_FALL );

                core::vector3df NormalPrev = ToBase.crossProduct(ToNext);
                core::vector3df NormalNext = ToBase.crossProduct(ToPrev);

                if (NormalPrev.Z>0) NormalPrev.invert();
                if (NormalNext.Z>0) NormalNext.invert();

                core::vector3df Normal = (NormalPrev.normalize()+NormalNext.normalize());

                v.Normal = Normal.normalize();


                v.Color =  color;
                v.TCoords.set(0.5 +0.5*TEXTUREFACTOR*(cosf(2*PI/NUM_SEGMENTS*(i-1))),0.5 +0.5*TEXTUREFACTOR*sinf(2*PI/NUM_SEGMENTS*(i-1)));

            }
        }





        buf->Indices.set_used(0);


        for (int j=0; j<3-1;j++)
            for (int i=0;i<4;i++)
            {
                buf->Indices.push_back(4*j+i);buf->Indices.push_back(4*j+(i+1)%4);buf->Indices.push_back(4*(j+1)+(i+1)%4);
                buf->Indices.push_back(4*(j+1)+(i+1)%4);buf->Indices.push_back(4*(j+1)+(i));buf->Indices.push_back(4*j+i);
            }


        for (int j=0;j<NUM_STAGES;j++)
        {

            for (int i=1;i<=NUM_SEGMENTS;i++)
            {
                 buf->Indices.push_back(16+i+(NUM_SEGMENTS+1)*j);
                 buf->Indices.push_back(16+0+(NUM_SEGMENTS+1)*j);
                 buf->Indices.push_back(16+(i/*+1-1*/)%(NUM_SEGMENTS)+1 + (NUM_SEGMENTS+1)*j);

            }
        }

        buf->recalculateBoundingBox();
        // buf->drop();


        Mesh->setDirty();
        Mesh->recalculateBoundingBox();

        }


};



#endif // DGAMEMAP_H
