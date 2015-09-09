#ifndef DGAMEMAP_H
#define DGAMEMAP_H

#include "irrlicht.h"
#include "TileMesh.h"
#include "TileCornerMesh.h"
#include "TileEdgeMesh.h"
#include "MyShaderCallBack.h"
#include "CBatchingMesh.h"
#include "DRandom.h"


#define INFINITE 32536
#define NEWWORLDSEEDS 21

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

struct Coord
{
    int x;
    int y;
};

struct Gradient
{
    float x;
    float y;
};



namespace TILE_TYPES
{
const int TUNDRA = 0;
const int TAIGA = 1;
const int COLD = 2;
const int TEMPERATE = 3;
const int ARID = 4;
const int SPRUCE = 5;
const int PINE = 6;
const int BIRCH = 7;
const int HILLS_COLD = 8;
const int HILLS_WARM = 9;
const int SWAMP = 10;
const int MOUNTAINS = 11;
const int BEACH = 12;
const int SEA = 13;
const int PERMAFROST = 14;
const int POLAR = 15;
}

const int ID_IsNotPickable = 0;

float My_ATan ( int x, int y)
{
    float atan_;
    if (y!=0) atan_ = atanf(fabs((float)y)/fabs((float)x)); else atan_ = 0.0;

    if (x<0) atan_ = PI - atan_;
    if (y<0) atan_ = 2*PI-atan_;

   return atan_;
}

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
    case TILE_TYPES::TUNDRA:
        return 0;
        break;

    case TILE_TYPES::TAIGA:
        return 0;
        break;

    case TILE_TYPES::COLD:
        return 0;
        break;

    case TILE_TYPES::TEMPERATE:
        return 0;
        break;

    case TILE_TYPES::ARID:
        return 0;
        break;

    case TILE_TYPES::SPRUCE:
        return 0;
        break;

    case TILE_TYPES::PINE:
        return 0;
        break;

    case TILE_TYPES::BIRCH:
        return 0;
        break;

    case TILE_TYPES::HILLS_COLD:
        return 0;
        break;

    case TILE_TYPES::HILLS_WARM:
        return 0;
        break;

    case TILE_TYPES::SWAMP:
        return 0;
        break;

    case TILE_TYPES::MOUNTAINS:
        return 0;
        break;

    case TILE_TYPES::BEACH:
        return 0;
        break;

    case TILE_TYPES::SEA:
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
    case TILE_TYPES::TUNDRA:
        return "Tundra";
        break;

    case TILE_TYPES::TAIGA:
        return "Taiga";
        break;

    case TILE_TYPES::COLD:
        return "Cold";
        break;

    case TILE_TYPES::TEMPERATE:
        return "Temperate";
        break;

    case TILE_TYPES::ARID:
        return "Arid";
        break;

    case TILE_TYPES::SPRUCE:
        return "Spruce";
        break;

    case TILE_TYPES::PINE:
        return "Pine";
        break;

    case TILE_TYPES::BIRCH:
        return "Birch";
        break;

    case TILE_TYPES::HILLS_COLD:
        return "Hills";
        break;

    case TILE_TYPES::HILLS_WARM:
        return "Hills";
        break;

    case TILE_TYPES::SWAMP:
        return "Swamp";
        break;

    case TILE_TYPES::MOUNTAINS:
        return "Mountains";
        break;

    case TILE_TYPES::BEACH:
        return "Shore";
        break;

    case TILE_TYPES::SEA:
        return "Sea";
        break;

    case TILE_TYPES::PERMAFROST:
        return "Permafrost";
        break;

    case TILE_TYPES::POLAR:
        return "Polar";
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
    case TILE_TYPES::TUNDRA:
        return 1;
        break;

    case TILE_TYPES::TAIGA:
        return 2;
        break;

    case TILE_TYPES::COLD:
        return 10;
        break;

    case TILE_TYPES::TEMPERATE:
        return 5;
        break;

    case TILE_TYPES::ARID:
        return 2;
        break;

    case TILE_TYPES::SPRUCE:
        return 4;
        break;

    case TILE_TYPES::PINE:
        return 3;
        break;

    case TILE_TYPES::BIRCH:
        return 1;
        break;

    case TILE_TYPES::HILLS_COLD:
        return 2;
        break;

    case TILE_TYPES::HILLS_WARM:
        return 1;
        break;

    case TILE_TYPES::SWAMP:
        return 2;
        break;

    case TILE_TYPES::MOUNTAINS:
        return 3;
        break;

    case TILE_TYPES::BEACH:
        return 4;
        break;

    case TILE_TYPES::SEA:
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


float interpolate( float x, float y)
{
    return (3*(1-x)*(1-x)-2*(1-x)*(1-x)*(1-x))*(3*(1-y)*(1-y)-2*(1-y)*(1-y)*(1-y));
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
    float** Noise;

void FloodFill(Coord start)
{

// Sorry, but I will not check for array limits, 'cause we have margins and so on...

    if (TileMap[start.x][start.y].Height!=2)
    {
            TileMap[start.x][start.y].Height=2;
            Coord temp;

            temp.x = UNbrI(start.x,start.y);
            temp.y = UNbrJ(start.x,start.y);
            FloodFill (temp);

            temp.x = URNbrI(start.x,start.y);
            temp.y = URNbrJ(start.x,start.y);
            FloodFill (temp);


            temp.x = LRNbrI(start.x,start.y);
            temp.y = LRNbrJ(start.x,start.y);
            FloodFill (temp);


            temp.x = LNbrI(start.x,start.y);
            temp.y = LNbrJ(start.x,start.y);
            FloodFill (temp);


            temp.x = LLNbrI(start.x,start.y);
            temp.y = LLNbrJ(start.x,start.y);
            FloodFill (temp);


            temp.x = ULNbrI(start.x,start.y);
            temp.y = ULNbrJ(start.x,start.y);
            FloodFill (temp);
    }
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

/******************************* MAP GENERATION ********************************************************/


        DRandom *mapRandom = new DRandom(8154413541);

        int OCTAVES = 4;

        int period = 16*2;
        float persistency = 0.65;
        float amplitude = 2.0;

         Noise = new float*[I_SIZE];
        for (int i=0;i<I_SIZE;i++)
            Noise[i]= new float[J_SIZE];

        for (int i=0;i<I_SIZE;i++)
         for (int j=0;j<J_SIZE;j++)
             Noise[i][j] = 0.0;

        for (int octave=0;octave<OCTAVES;octave++)
        {//for each octave

         period = period/2;
         amplitude = amplitude*persistency;

        //let's calculate the number of grad points
         int NUM_GRAD_POINTS_X = I_SIZE/period + 1;
         int NUM_GRAD_POINTS_Y = J_SIZE/period + 1;


        //let's allocate the memory
         Gradient** Gradients = new Gradient*[NUM_GRAD_POINTS_X];
         for (int i=0;i<NUM_GRAD_POINTS_X;i++)
             Gradients[i] = new Gradient[NUM_GRAD_POINTS_Y];


         //let's set up the gradients
            for (int i=0;i<NUM_GRAD_POINTS_X;i++)
            for (int j=0;j<NUM_GRAD_POINTS_Y;j++)
            {
                Gradients[i][j].x = 2*(mapRandom->Get()-0.5);
                Gradients[i][j].y = 2*(mapRandom->Get()-0.5);
            }

         //so as long as we have gradients, let's make some noise! :)

           for (int i=0;i<I_SIZE;i++)
           for (int j=0;j<J_SIZE;j++)
           {//for each tile, let's calculate, assuming
               // 3 4
               // 1 2

            //so, as long as our tile's coords are ints, so dx and dy are basically i%period and j%period for 1 and 3; for 2 and 4 that would be period- i%period and period - j%period
               //then, we should normalize them by dividing by period
               float noise1 = Gradients[i/period][j/period].x*(-i%period)/period  + Gradients[i/period][j/period].y*(-j%period)/period;
               float noise2 = Gradients[(i/period+1)!=NUM_GRAD_POINTS_X-1?(i/period+1):0][j/period].x*(period - i%period)/period  + Gradients[(i/period+1)!=NUM_GRAD_POINTS_X-1?(i/period+1):0][j/period].y*(-j%period)/period;
               float noise3 = Gradients[i/period][j/period+1].x*(-i%period)/period  + Gradients[i/period][j/period+1].y*(period- j%period)/period;
               float noise4 = Gradients[(i/period+1)!=NUM_GRAD_POINTS_X-1?(i/period+1):0][j/period+1].x*(period- i%period)/period  + Gradients[(i/period+1)!=NUM_GRAD_POINTS_X-1?(i/period+1):0][j/period+1].y*(period - j%period)/period;


               float noisevalue =  noise1* interpolate((float)(i%period)/period,(float)(j%period)/period)
                       +noise2*interpolate((float)(period-i%period)/period,(float)(j%period)/period)
                       +noise3*interpolate((float)(i%period)/period,(float)(period-j%period)/period)
                       +noise4*interpolate((float)(period-i%period)/period,(float)(period-j%period)/period) ;

                noisevalue *= amplitude;

                Noise[i][j] +=noisevalue;


           }

         for (int i=0;i<I_SIZE;i++)
             for (int j=0;j<J_SIZE;j++)
             {
                 if (Noise[i][j]<0.21) { TileMap[i][j].Height=0;  TileMap[i][j].TerrainType=TILE_TYPES::SEA;}else
                     if (Noise[i][j]<0.29) { TileMap[i][j].Height=0; TileMap[i][j].TerrainType=TILE_TYPES::BEACH; } else
                     if (Noise[i][j]<0.43) { TileMap[i][j].Height=2; TileMap[i][j].TerrainType=TILE_TYPES::TEMPERATE; } else
                     if (Noise[i][j]<0.65) { TileMap[i][j].Height=2; TileMap[i][j].TerrainType=TILE_TYPES::PINE; } else
                      { TileMap[i][j].Height=2; TileMap[i][j].TerrainType=TILE_TYPES::MOUNTAINS; }
             }



         //let's free the memory
         delete [] *Gradients;
         delete [] Gradients;


        }
        int MAX_POLAR_CAPS = 5;
        int MIN_POLAR_CAPS = 1;

        for (int i=0;i<I_SIZE;i++)
          {
            int CAPS_NORTH =(int)trunc(MIN_POLAR_CAPS+mapRandom->Get()*(MAX_POLAR_CAPS-MIN_POLAR_CAPS));
            int CAPS_SOUTH =(int)trunc(MIN_POLAR_CAPS+mapRandom->Get()*(MAX_POLAR_CAPS-MIN_POLAR_CAPS));
            for (int j=0;j<CAPS_NORTH ;j++)
            {
                TileMap[i][J_SIZE-1-j].Height=2;
                TileMap[i][J_SIZE-1-j].TerrainType=TILE_TYPES::POLAR;
            }

            for (int j=0;j<CAPS_SOUTH ;j++)
            {
                TileMap[i][j].Height=2;
        
