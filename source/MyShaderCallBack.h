#ifndef MYSHADERCALLBACK_H
#define MYSHADERCALLBACK_H


#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

IrrlichtDevice* device = 0;




class MyTerrainShaderCallBack : public video::IShaderConstantSetCallBack
{
public:

    scene::ILightSceneNode *mylightnode;
    s32 *extmode;
    f32 waterlevel;

    virtual void OnSetConstants(video::IMaterialRendererServices* services,
            s32 userData)
    {
        video::IVideoDriver* driver = services->getVideoDriver();

        core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
        invWorld.makeInverse();
        services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);


        core::matrix4 worldViewProj;
        worldViewProj = driver->getTransform(video::ETS_PROJECTION);
        worldViewProj *= driver->getTransform(video::ETS_VIEW);
        worldViewProj *= driver->getTransform(video::ETS_WORLD);
        services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);


        core::vector3df pos2 = mylightnode->getLightData().Direction;
        services->setVertexShaderConstant("light", reinterpret_cast<f32*>(&pos2), 3);

        // set texture, for textures you can use both an int and a float setPixelShaderConstant interfaces (You need it only for an OpenGL driver).
        s32 TextureLayerID = 0;
        services->setPixelShaderConstant("atlas", &TextureLayerID, 1);

        s32 mode = *extmode ;
        services->setVertexShaderConstant("mode",&mode, 1);

        services->setVertexShaderConstant("level",&waterlevel, 1);

    }
};


class MyWaterShaderCallBack : public video::IShaderConstantSetCallBack
{
public:

    scene::ILightSceneNode *mylightnode;
    u32 *extclock;
    virtual void OnSetConstants(video::IMaterialRendererServices* services,
            s32 userData)
    {
        video::IVideoDriver* driver = services->getVideoDriver();

        // set inverted world matrix
        // if we are using highlevel shaders (the user can select this when
        // starting the program), we must set the constants by name.

        core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
        invWorld.makeInverse();

        services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);

        // set clip matrix

        core::matrix4 worldViewProj;
        worldViewProj = driver->getTransform(video::ETS_PROJECTION);
        worldViewProj *= driver->getTransform(video::ETS_VIEW);
        worldViewProj *= driver->getTransform(video::ETS_WORLD);
        services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);

        // set camera position


        core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
        services->setVertexShaderConstant("camera", reinterpret_cast<f32*>(&pos), 3);

        core::vector3df pos2 = mylightnode->getLightData().Direction;
       // pos.Y +=20;
        services->setVertexShaderConstant("light", reinterpret_cast<f32*>(&pos2), 3);

        f32 tttt = 1.0/1600.0*(*extclock % 1600);
        services->setPixelShaderConstant("shift",&tttt,1);

        // set light color

        video::SColorf col(0.4f,0.6f,0.8f,1.0f);

        services->setVertexShaderConstant("waterColor",reinterpret_cast<f32*>(&col), 4);

        // set transposed world matrix

        core::matrix4 world = driver->getTransform(video::ETS_WORLD);
        world = world.getTransposed();


            services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);
            // set texture, for textures you can use both an int and a float setPixelShaderConstant interfaces (You need it only for an OpenGL driver).
            s32 TextureLayerID = 0;
            services->setPixelShaderConstant("reflection", &TextureLayerID, 1);

            TextureLayerID = 1;
            services->setPixelShaderConstant("refraction", &TextureLayerID, 1);

            TextureLayerID = 2;
            services->setPixelShaderConstant("normalMap", &TextureLayerID, 1);

            TextureLayerID = 3;
            services->setPixelShaderConstant("dudvMap", &TextureLayerID, 1);



    }
};






struct ShaderWrapper
{

    MyWaterShaderCallBack* mwc;

    MyTerrainShaderCallBack terrainshader;

    s32 newMaterialType1 ;
    s32 newMaterialType2 ;
    s32 newMaterialType3 ;
    s32 newMaterialType4 ;
    s32 newMaterialType5 ;
    s32 newMaterialType6 ;
    s32 newMaterialType7 ;

    s32 TerrainMaterial;

    void LoadShaders(IVideoDriver* driver,ILightSceneNode *lightnode,u32 *ticker, s32* mode, f32 waterlevel)
    {
        io::path vsFileName; // filename for the vertex shader
        io::path psFileName; // filename for the pixel shader


        video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();


        psFileName = "assets/shaders/terrain.frag";
        vsFileName = "assets/shaders/terrain.vert";


        MyTerrainShaderCallBack* terrainshader = new MyTerrainShaderCallBack();
        terrainshader->mylightnode = lightnode;
        terrainshader->extmode = mode;
        terrainshader->waterlevel = waterlevel;

        TerrainMaterial = gpu->addHighLevelShaderMaterialFromFiles(
                               vsFileName, "vertexMain", video::EVST_VS_1_1,
                               psFileName, "pixelMain", video::EPST_PS_1_1,
                               terrainshader, video::EMT_SOLID, 0, video::EGSL_DEFAULT);



        psFileName = "assets/shaders/water.frag";
        vsFileName = "assets/shaders/water.vert";


        MyWaterShaderCallBack* mwc = new MyWaterShaderCallBack();
        mwc->mylightnode = lightnode;
        mwc->extclock = ticker;
        newMaterialType2 = gpu->addHighLevelShaderMaterialFromFiles(
                               vsFileName, "vertexMain", video::EVST_VS_1_1,
                               psFileName, "pixelMain", video::EPST_PS_1_1,
                               mwc, video::EMT_SOLID, 0, video::EGSL_DEFAULT);

        psFileName = "assets/shaders/transition.frag";
        vsFileName = "assets/shaders/transition.vert";



        }

    ~ShaderWrapper()
    {

    }

};

#endif // MYSHADERCALLBACK_H
