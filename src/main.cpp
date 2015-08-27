
// main.cpp

#include "myeventreceiver.h"
#include "TileMesh.h"
#include "WaterTileMesh.h"
#include <QString>
#include "MyShaderCallBack.h"
#include "MyWaterShaderCallBack.h"
#include "TileEdgeMesh.h"
#include "TileCornerMesh.h"
#include "DGameMap.h"
#include "PathFinding.h"
#include "GameManager.h"
#include "DRandom.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



int IRRCALLCONV main(int argc, char* argv[])
{

    u32 ticker = 0;
    const u32 tickermax = 3628800;

    MyEventReceiver receiver;

    device =  createDevice( video::EDT_OPENGL, dimension2d<u32>(SCREEN_WIDTH, SCREEN_HEIGHT), 32,  true, true, false, &receiver);
    if (!device) return 1;

    device->setWindowCaption(L"Crash Col Viking Punk");
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    s32 VisibleX = 0;
    s32 VisibleY = 0;
   // guienv->addStaticText(L"Hello World! This is the Irrlicht OpenGL renderer!", rect<s32>(10,10,260,22), true);

    scene::ICameraSceneNode* camera = smgr->addCameraSceneNode(0,core::vector3df(0,-5,-15),core::vector3df(0,0,0),ID_IsNotPickable,true);
    scene::ISceneNode* highlightedSceneNode = 0;
    scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
    scene::ITriangleSelector* selector = 0;
    video::SMaterial material;

    core::vector3df cameranodePosition = camera->getPosition();
    core::vector3df targetPosition = camera->getTarget();

    core::vector3df cameranodePositionTarget = cameranodePosition;
    core::vector3df targetPositionTarget = targetPosition;

    VisibleX = trunc(targetPosition.X/3*2)/I_CHUNKSIZE;
    VisibleY = trunc(targetPosition.Y/sqrt(3))/J_CHUNKSIZE;

    material.setTexture(0, 0);
    material.Lighting = false;
    device->getCursorControl()->setVisible(true);



    ILightSceneNode *lightnode = smgr->addLightSceneNode(0, vector3df(0,100,0), SColorf(1.0f, 1.0f, 1.0f, 1.0f), 10.0f);


        //  lightnode->getLightData().Attenuation.set(0.f, 1.f/5.f, 0.f);
        lightnode->setLightType(video::ELT_DIRECTIONAL);

        lightnode->setPosition(core::vector3df(-sqrt(1/3),-sqrt(1/3),-sqrt(1/3)));
        lightnode->setRotation(vector3df(0,0,180));
        lightnode->setRotation(vector3df(22,22,0));

    lightnode->setVisible(true);



    driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY,true);
    //driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED,true);
    driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL ,false);
    driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS,true);


        scene::ILightSceneNode* lightnode2 = 0;
        lightnode2 = smgr->addLightSceneNode(0, core::vector3df(0,0,-10),
                                             video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 10.0f);

        // attach billboard to light

        scene::ISceneNode* node = 0;
        node = smgr->addBillboardSceneNode(lightnode2, core::dimension2d<f32>(0.2, 0.2));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
        node->setMaterialTexture(0, driver->getTexture("media/particlewhite.bmp"));

      //   IMeshSceneNode* qqq =(IMeshSceneNode*)smgr->addCubeSceneNode(1,0,-1,vector3df(5,5,-1));
       //  qqq->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
       //  qqq->setMaterialTexture(0,driver->getTexture("assets/gui/hexhover.png"));
      //  qqq->addShadowVolumeSceneNode();

        smgr->setShadowColor(video::SColor(150,0,0,0));

    ShaderWrapper *MyShaders = new ShaderWrapper;

    u32* a = &ticker;
    s32 rendermode = 0;
    MyShaders->LoadShaders(driver,lightnode,&ticker,&rendermode,deepness);

    VisibleMap *VisMa = new VisibleMap(smgr,driver,lightnode,a,MyShaders);

    for (int a=0; a<I_SIZE/I_CHUNKSIZE; a++)
        for (int b=0; b<J_SIZE/J_CHUNKSIZE; b++)
        {
            selector = smgr->createTriangleSelector(VisMa->nodes[a][b]->getMesh(),VisMa->nodes[a][b]);
            VisMa->nodes[a][b]->setTriangleSelector(selector);
            selector->drop();
        }



    u32 then = device->getTimer()->getTime();

    const f32 MOVEMENT_SPEED = 0.5f;
    const f32 ACTUAL_MOVEMENT_SPEED = 0.1f;

    scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("media/particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d<f32>(0.2f, 0.2f));
    bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

    IGUIStaticText* statex = guienv->addStaticText(L"tempchar", rect<s32>(10,40,460,52), true);
    statex->setVisible(false);

    IGUIStaticText* tileinfopanel = guienv->addStaticText(L"",rect<s32>(10,SCREEN_HEIGHT-140,260,SCREEN_HEIGHT-10),false);
    tileinfopanel->setBackgroundColor(SColor(127,50,50,50));
    tileinfopanel->setOverrideColor(SColor(255,255,255,255));

    IGUIImage* minimap = guienv->addImage(core::rect<s32>(SCREEN_WIDTH-360,SCREEN_HEIGHT-140,SCREEN_WIDTH,SCREEN_HEIGHT),0,-1,L"Minimap",true);
    IGUIImage* topbar = guienv->addImage(core::rect<s32>(SCREEN_WIDTH-512,0,SCREEN_WIDTH,32),0,-1,L"topbar",true);
    IGUIImage* topbarcorner = guienv->addImage(core::rect<s32>(SCREEN_WIDTH-512-32,0,SCREEN_WIDTH-512,32),0,-1,L"topbarcorner",true);

    IGUIButton* endturn = guienv->addButton(core::rect<s32>(SCREEN_WIDTH-400,SCREEN_HEIGHT-125,SCREEN_WIDTH-350,SCREEN_HEIGHT-75),0,12,L"END TURN",L"END CURRENT TURN");

    minimap->setImage(driver->getTexture("assets/gui/minimap.png"));
    minimap->setScaleImage(true);

    topbar->setImage(driver->getTexture("assets/gui/topbar.png"));
    topbar->setScaleImage(true);

    topbarcorner->setImage(driver->getTexture("assets/gui/topbarcorner.png"));
    topbarcorner->setScaleImage(false);

    endturn->setImage(driver->getTexture("assets/gui/endturn.png"));
    endturn->setScaleImage(true);
    endturn->setPressedImage(driver->getTexture("assets/gui/endturnpressed.png"));

    statex->setBackgroundColor(video::SColor(255,255,255,255));

    SMesh* HoverMesh = new SMesh();
    createHexHoverMesh(HoverMesh );
   IMeshSceneNode* HoverNode = smgr->addMeshSceneNode((IMesh*)HoverMesh);
  //IMeshSceneNode* HoverNode = smgr->addCubeSceneNode(1,0,-1,core::vector3df(0,0,0),core::vector3df(0,0,0),core::vector3df(1,1,1));
    HoverNode->setMaterialTexture(0,driver->getTexture("assets/gui/hexhover.png"));
    HoverNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
     // HoverNode->setMaterialType(video::EMT_SOLID);
    HoverNode->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
    HoverNode->setMaterialFlag(video::EMF_LIGHTING,false);
   // HoverNode->setMaterialFlag(video::EMF_WIREFRAME,true);
    HoverNode->setMaterialFlag(EMF_ZBUFFER,false);
    HoverNode->setVisible(true);

    PathNode start;
    PathNode finish;

    start.x=3;
    start.y=5;

    finish.x=5;
    finish.y=9;


    core::array<vector2d<s32> > path;
    int length = path.size();
    ISceneNode* *pathnode = new ISceneNode*[length];
    DRandom* TreeRandom = new DRandom(34912);

   for (int i=0;i<I_SIZE/I_CHUNKSIZE;i++)
   for (int j=0;j<J_SIZE/J_CHUNKSIZE;j++)
       {

         CBatchingMesh* MetaBatch = new CBatchingMesh();
     //for each chunk we make foliage MetaBatch

         for (int x=0;x<I_CHUNKSIZE;x++)
         for (int y=0;y<J_CHUNKSIZE;y++ )
         if (VisMa->TileMap[i*I_CHUNKSIZE+x][j*J_CHUNKSIZE+y].Height==2) //&& TreeRandom->Get()>0.25)
            {

                CBatchingMesh* Batch = new CBatchingMesh();

                int NUM_TREES = TreeRandom->Get()<0.25?2:(TreeRandom->Get()>0.75?4:3);
                for (int a=0;a<NUM_TREES;a++)
                for (int b=0; b<NUM_TREES+a;b++)
                     {
                      SMesh* stempmesh = new SMesh();
                      VisibleMap::doSpruceMesh(stempmesh);
                      IMesh* tempmesh = (IMesh*)stempmesh;

                        float JITTER_X = 0.2;
                      float JITTER_Y = 0.25;

                          float TreeX = (-0.5+ 1.0/(NUM_TREES-1)*b - 0.5/(NUM_TREES-1)*a)*0.9;
                        float TreeY = (-sqrt(3)/2+sqrt(3)/2/(NUM_TREES-1)*a)*0.9;
                        Batch->addMesh(tempmesh,core::vector3df(TreeX+(TreeRandom->Get()-0.5)*2*1.0/(NUM_TREES-1)*JITTER_X,TreeY+sqrt(3)/2/(NUM_TREES-1)*JITTER_Y*2*(TreeRandom->Get()-0.5),0),core::vector3df(0,0,0),core::vector3df(0.9,0.9,0.9));
                        if (a!=NUM_TREES-1) Batch->addMesh(tempmesh,core::vector3df(TreeX+(TreeRandom->Get()-0.5)*2*1.0/(NUM_TREES-1)*JITTER_X,-TreeY+sqrt(3)/2/(NUM_TREES-1)*JITTER_Y*2*(TreeRandom->Get()-0.5),0),core::vector3df(0,0,0),core::vector3df(0.9,0.9,0.9));
                        delete tempmesh;
                      }

             Batch->finalize();

             IMeshSceneNode* treeno = smgr->addMeshSceneNode(Batch);


              //  treeno->setPosition(core::vector3df(Hex2PixelX(18,14),Hex2PixelY(18,14),0));//TileMap[5][5].Height==2?0:deepness));


            Batch->drop();

            MetaBatch->addMesh(treeno->getMesh(),core::vector3df(Hex2PixelX(i*I_CHUNKSIZE+x,j*J_CHUNKSIZE+y),Hex2PixelY(i*I_CHUNKSIZE+x,j*J_CHUNKSIZE+y),0),core::vector3df(0,0,0),core::vector3df(1,1,1));
            treeno->setVisible(false);
            treeno->remove();
            }
            MetaBatch->finalize();
            VisMa->trees[i][j] = smgr->addMeshSceneNode(MetaBatch);
            VisMa->trees[i][j]->setVisible(false);
            VisMa->trees[i][j]->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
            VisMa->trees[i][j]->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
            VisMa->trees[i][j]->setMaterialTexture(0,driver->getTexture("assets/textures/spruce.png"));
            MetaBatch->drop();
       }


   for (int i=-1;i<2;i++)
       for (int j=-1;j<2;j++)
           if (JCheck(VisibleY+j))
           {
               VisMa->nodes[IWrap(VisibleX+i)][VisibleY+j]->setVisible(true);
               VisMa->trees[IWrap(VisibleX+i)][VisibleY+j]->setVisible(true);
}

   SMesh* stempmesh = new SMesh();
    VisMa->doWaterQuadMesh(stempmesh);
    IMesh* tempmesh=(IMesh*)stempmesh;

    // create render target
      video::ITexture* reflection = 0;
      reflection = driver->addRenderTargetTexture(core::dimension2d<u32>(SCREEN_WIDTH,SCREEN_HEIGHT), "RTT1");

      video::ITexture* refraction = 0;
      refraction = driver->addRenderTargetTexture(core::dimension2d<u32>(SCREEN_WIDTH,SCREEN_HEIGHT), "RTT2");



    tempmesh->getMeshBuffer(0)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)MyShaders->newMaterialType2;
    tempmesh->getMeshBuffer(0)->getMaterial().setTexture(0,reflection);//driver->getTexture("assets/textures/water/reflection.jpg"));
    tempmesh->getMeshBuffer(0)->getMaterial().setTexture(1,refraction);//driver->getTexture("assets/textures/water/refraction.jpg"));
    tempmesh->getMeshBuffer(0)->getMaterial().setTexture(2,driver->getTexture("assets/textures/water/normal.jpg"));
    tempmesh->getMeshBuffer(0)->getMaterial().setTexture(3,driver->getTexture("assets/textures/water/dudv.jpg"));


    CBatchingMesh* bbb = new CBatchingMesh();

         for (int x=0;x<80;x++)
       for (int y=0;y<25;y++)
       bbb->addMesh(tempmesh,core::vector3df(-10+5.0*x,-10+5.0*y,deepness*0.5),core::vector3df(0,0,0),core::vector3df(1,1,1));

    bbb->finalize();

   IMeshSceneNode* waterloo =smgr->addMeshSceneNode(bbb);
    waterloo->setScale(core::vector3df(1,1,1));
    bbb->drop();
    delete tempmesh;

    driver->enableClipPlane(0,false);
    driver->enableClipPlane(1,false);
    driver->enableClipPlane(2,false);
    driver->enableClipPlane(3,false);
    driver->enableClipPlane(4,false);
    driver->enableClipPlane(5,false);



    scene::IVolumeLightSceneNode * n = smgr->addVolumeLightSceneNode(0, -1,
                  64,                              // Subdivisions on U axis
                  64,                              // Subdivisions on V axis
                  video::SColor(0, 255, 255, 255), // foot color
                  video::SColor(0, 0, 0, 0));      // tail color

      if (n)
      {
          n->setScale(core::vector3df(2.0f, 2.0f, 2.0f));
          n->setPosition(HoverNode->getPosition());
          n->setRotation(core::vector3df(-90,0,0));

          // load textures for animation
          core::array<video::ITexture*> textures;
          for (s32 g=7; g > 0; --g)
          {
              core::stringc tmp;
              tmp = "assets/gui/hexglow.png";
             // tmp += g;
              //tmp += ".bmp";
              video::ITexture* t = driver->getTexture( tmp.c_str() );
              textures.push_back(t);
          }

          // create texture animator
          scene::ISceneNodeAnimator* glow = smgr->createTextureAnimator(textures, 150);

          // add the animator
          n->addAnimator(glow);
    }

    /* MAIN LOOOOOOOOP */

    u32 t = 0;
    u32 dt = 40;
    u32 currentTime = device->getTimer()->getTime();
    u32 accumulator = 0;

    f32 previousState = 0.0;
    f32 currentState = 1.0;

    bool exitflag= false;


    smgr->setActiveCamera(camera);

    while(device->run()&&!exitflag)
    {

        const u32 now = device->getTimer()->getTime();
        // Time in seconds
        then = now;

        u32 newTime = device->getTimer()->getTime();
        u32 frameTime = newTime - currentTime;

        if ( frameTime > 250 ) frameTime = 250;
        currentTime = newTime;
        accumulator += frameTime;

        while ( accumulator >= dt )
        { /* **************************  INTEGRATE ***************************** */



            previousState = currentState;

            if (ticker<tickermax-1)
            {
                ticker++;
            }
            else ticker = 0;


            t += dt;
            accumulator -= dt;

            if (highlightedSceneNode)
            {
                highlightedSceneNode = 0;
            }


            n->setScale(core::vector3df(2.0+0.05*sin(2*PI*(ticker%120)/120),2.0+0.05*sin(2*PI*(ticker%120)/120),2.0+0.05*sin(2*PI*(ticker%120)/120)));
           n->setRotation(core::vector3df(-90,0,7.5*sin(2*PI*(ticker%480)/480)));
           core::line3d<f32> ray = collMan->getRayFromScreenCoordinates(device->getCursorControl()->getPosition(),0);
            core::vector3df intersection;
            core::triangle3df hitTriangle;

            scene::ISceneNode * selectedSceneNode = 0;

            selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(
                ray,
                intersection, // This will be the position of the collision
                hitTriangle, // This will be the triangle hit in the collision
                0, // This ensures that only nodes that we have
                // set up to be pickable are considered
                0); // Check the entire scene (this is actually the implicit default)


            if(selectedSceneNode)
            {
                bill->setPosition(intersection);
                bill->setVisible(false);

                                /*    driver->setTransform(video::ETS_WORLD, core::matrix4());
                                    driver->setMaterial(material);
                                    driver->draw3DTriangle(hitTriangle, video::SColor(0,255,0,0));*/


                HoverNode->setPosition(core::vector3df(Hex2PixelX(Pixel2HexX(intersection.X,intersection.Y),Pixel2HexY(intersection.X,intersection.Y)),Hex2PixelY(Pixel2HexX(intersection.X,intersection.Y),Pixel2HexY(intersection.X,intersection.Y)),0));



                QString tempstring = QString("HIGHLIGHTED X: %1 Y: %2 FPS: %3 tick %4 referencecount: %5 POLYS: %6").arg(Pixel2HexX(intersection.X,intersection.Y)).arg(Pixel2HexY(intersection.X,intersection.Y)).arg(driver->getFPS()).arg(ticker).arg(driver->getMaxTextureSize().Width).arg(driver->getMaxTextureSize().Height);
                wchar_t *tempchar = new wchar_t[tempstring.length()+1];
                tempchar[tempstring.length()]='\0';
                tempstring.toWCharArray(tempchar);
                statex->setText(tempchar);

                delete [] tempchar;
               tempstring= QString("\n   %1\n    Movement cost:%2    \n\n    PLACEHOLDER%3\n%4\n   No units").arg(TileName(VisMa->TileMap[Pixel2HexX(intersection.X,intersection.Y)%I_SIZE][Pixel2HexY(intersection.X,intersection.Y)].TerrainType)).arg(getMovementCost(VisMa->TileMap[Pixel2HexX(intersection.X,intersection.Y)%I_SIZE][Pixel2HexY(intersection.X,intersection.Y)])).arg(Hex2PixelX(I_SIZE,0)).arg(Hex2PixelY(0,J_SIZE));

                tempchar = new wchar_t[tempstring.length()+1];
                tempchar[tempstring.length()]='\0';
                tempstring.toWCharArray(tempchar);

                tileinfopanel->setText(tempchar);
                delete [] tempchar;

            }
            else
            {
                QString tempstring = QString("NOT HIGHLIGHTED CAMERA_Y:%1 CAMERA_Z:%2 FPS: %3 textures %4 POLYS: %5").arg(camera->getTarget().Y-camera->getPosition().Y).arg(camera->getPosition().Z).arg(driver->getFPS()).arg(driver->getTextureCount()).arg(driver->getPrimitiveCountDrawn());

                wchar_t *tempchar = new wchar_t[tempstring.length()+1];
                tempchar[tempstring.length()]='\0';
                tempstring.toWCharArray(tempchar);
                statex->setText(tempchar);
                delete [] tempchar;

            }

            /*INPUT*/


            if(receiver.IsKeyDown(irr::KEY_KEY_W))
            {

                if (Pixel2HexY(0,cameranodePositionTarget.Y + MOVEMENT_SPEED)<J_SIZE-11 )
                {
                cameranodePositionTarget.Y += MOVEMENT_SPEED ;
                targetPositionTarget.Y += MOVEMENT_SPEED ;
                }
            }
            if(receiver.IsKeyDown(irr::KEY_KEY_S))
            {
                if (cameranodePositionTarget.Y - MOVEMENT_SPEED > 4.5)
                {
                cameranodePositionTarget.Y -= MOVEMENT_SPEED ;
                targetPositionTarget.Y -= MOVEMENT_SPEED ;
                }
            }
            if(receiver.IsKeyDown(irr::KEY_KEY_A))
            {
                cameranodePositionTarget.X -= MOVEMENT_SPEED ;
                targetPositionTarget.X -= MOVEMENT_SPEED ;
            }
            if(receiver.IsKeyDown(irr::KEY_KEY_D))
            {
                cameranodePositionTarget.X += MOVEMENT_SPEED ;
                targetPositionTarget.X += MOVEMENT_SPEED ;
            }

            if(receiver.IsKeyDown(irr::KEY_KEY_Z))
            {
                cameranodePositionTarget.Z -= MOVEMENT_SPEED ;

            }
            if(receiver.IsKeyDown(irr::KEY_KEY_X))
            {
                cameranodePositionTarget.Z += MOVEMENT_SPEED ;

            }

            if(receiver.IsKeyDown(irr::KEY_KEY_O)&&false)
            {
                start.x = Pixel2HexX(intersection.X,intersection.Y);
                start.y = Pixel2HexY(intersection.X,intersection.Y);

                if (pathnode!=0)

                {
                    for (int i=0; i<length; i++)
                    {
                        pathnode[i]->setVisible(false);
                        pathnode[i]->remove();
                    }
                    delete [] pathnode;

                    path.clear();
                    path.set_used(0);

                    path = A_Star(start,finish,VisMa->TileMap);

                    length = path.size();

                    pathnode = new ISceneNode*[length];

                    for (int a=length-1; a>=0; a--)
                    {

                        pathnode[a] = smgr->addCubeSceneNode((float)(length-a)/length,0,0,core::vector3df(Hex2PixelX(path[a].X,path[a].Y),Hex2PixelY(path[a].X,path[a].Y),-0.2));

                    }


                }


                //anode->setPosition(core::vector3df(Hex2PixelX(start.x,start.y),Hex2PixelY(start.x,start.y),0));
            }

            if(receiver.IsKeyDown(irr::KEY_KEY_P)&&false)
            {

                finish.x = Pixel2HexX(intersection.X,intersection.Y);
                finish.y = Pixel2HexY(intersection.X,intersection.Y) ;

                if (pathnode!=0)

                {
                    for (int i=0; i<length; i++)
                    {
                        pathnode[i]->setVisible(false);
                        pathnode[i]->remove();
                    }
                    delete [] pathnode;

                    path.clear();
                    path.set_used(0);

                    path = A_Star(start,finish,VisMa->TileMap);
                    length = path.size();

                    pathnode = new ISceneNode*[length];

                    for (int a=length-1; a>=0; a--)
                    {

                        pathnode[a] = smgr->addCubeSceneNode((float)(length-a)/length,0,0,core::vector3df(Hex2PixelX(path[a].X,path[a].Y),Hex2PixelY(path[a].X,path[a].Y),-0.2));

                    }


                }
            }


            if(receiver.IsKeyDown(irr::KEY_KEY_T))
            {

                vector3df rototo = lightnode->getRotation();
                rototo.X-=1;
                lightnode->setRotation(rototo);
            }
            if(receiver.IsKeyDown(irr::KEY_KEY_G))
            {

                vector3df rototo = lightnode->getRotation();
                rototo.X+=1;
                lightnode->setRotation(rototo);

            }

            if(receiver.IsKeyDown(irr::KEY_KEY_P))
            {

                    IImage* screenshot = driver->createScreenShot();
                    driver->writeImageToFile(screenshot,"screenshot.jpg",0);

            }

            if(receiver.IsKeyDown(irr::KEY_ESCAPE))
            {

                exitflag = true;
                break;
            }


            if (receiver.IsWheel())
            {
                if (cameranodePositionTarget.Z+MOVEMENT_SPEED*0.75*receiver.getWheel()>=-15 && cameranodePositionTarget.Z+MOVEMENT_SPEED*0.75*receiver.getWheel()<=-4)

                {
                    cameranodePositionTarget.Z += MOVEMENT_SPEED*0.75*receiver.getWheel();
                    cameranodePositionTarget.Y += MOVEMENT_SPEED*0.25*receiver.getWheel() ;
                }

                else
                    if (cameranodePositionTarget.Z+MOVEMENT_SPEED*0.75*receiver.getWheel()>=-4 && cameranodePositionTarget.Z+MOVEMENT_SPEED*0.75*receiver.getWheel()<=-1.5)
                    {

                        cameranodePositionTarget.Z += MOVEMENT_SPEED*0.75*receiver.getWheel();
                    }

            }


            if (receiver.IsLeftButtonClick())
            {

            }

            if (receiver.IsRightButtonClick())
            {

            }

            cameranodePosition = camera->getPosition();
            targetPosition =camera->getTarget();

            if (cameranodePosition.getDistanceFrom(cameranodePositionTarget)>ACTUAL_MOVEMENT_SPEED*0.1)
            {
                cameranodePosition = cameranodePosition + (cameranodePositionTarget-cameranodePosition)*ACTUAL_MOVEMENT_SPEED;
            }

            if (targetPosition.getDistanceFrom(targetPositionTarget)>ACTUAL_MOVEMENT_SPEED*0.1)
            {
                targetPosition = targetPosition + (targetPositionTarget-targetPosition)*ACTUAL_MOVEMENT_SPEED;
            }




            float WORLD_WRAP_RIGHT_BOUNDARY = Hex2PixelX(I_SIZE,0);
            float WORLD_WRAP_LEFT_BOUNDARY = Hex2PixelX(-1,0);

            if (cameranodePosition.X > WORLD_WRAP_RIGHT_BOUNDARY)
            {

                targetPositionTarget.X = targetPositionTarget.X-targetPosition.X;
                targetPosition.X = 0;//(targetPosition.X-cameranodePosition.X);

                cameranodePositionTarget.X=cameranodePositionTarget.X-cameranodePosition.X;
                cameranodePosition.X = 0;


            }

            if (cameranodePosition.X < WORLD_WRAP_LEFT_BOUNDARY)
            {
                cameranodePositionTarget.X = cameranodePositionTarget.X-cameranodePosition.X;
                cameranodePosition.X = Hex2PixelX(I_SIZE-1,0);
                cameranodePositionTarget.X += Hex2PixelX(I_SIZE-1,0);

                targetPositionTarget.X = targetPositionTarget.X-targetPosition.X;
                targetPosition.X = Hex2PixelX(I_SIZE-1,0);
                 targetPositionTarget.X += Hex2PixelX(I_SIZE-1,0);



            }

            camera->setPosition(cameranodePosition);
            camera->setTarget(targetPosition);
        }


            if ( ((VisibleX!=Pixel2HexX(targetPosition.X,targetPosition.Y)/I_CHUNKSIZE)||(VisibleY!=Pixel2HexY(targetPosition.X,targetPosition.Y)/J_CHUNKSIZE)))
            {

                int NewX = Pixel2HexX(targetPosition.X,targetPosition.Y)/I_CHUNKSIZE;
                int NewY = Pixel2HexY(targetPosition.X,targetPosition.Y)/J_CHUNKSIZE;



                for (s32 i=-1;i<2;i++)
                    for (s32 j=-1;j<2;j++)
                       if (JCheck(VisibleY+j)){ VisMa->nodes[IWrap(VisibleX+i)][VisibleY+j]->setVisible(false);
                                                VisMa->trees[IWrap(VisibleX+i)][VisibleY+j]->setVisible(false);

                                                }

                for (s32 i=-1;i<2;i++)
                    for (s32 j=-1;j<2;j++)

                        if (JCheck(NewY+j)) { VisMa->nodes[IWrap(NewX+i)][NewY+j]->setVisible(true);
                            VisMa->trees[IWrap(NewX+i)][NewY+j]->setVisible(true);

                    }
                VisibleX = IWrap(NewX);
                VisibleY = NewY;


            }

        //  const double alpha = accumulator / dt;
        //  f32 state = currentState * alpha +  previousState * ( 1.0 - alpha );

        n->setPosition(core::vector3df(HoverNode->getPosition().X,HoverNode->getPosition().Y,HoverNode->getPosition().Z-0.1));
        /*RENDER*/



        driver->beginScene(true, true, SColor(255,255,0,0));
       // core::matrix4 affector;
        if (reflection && refraction)
        {
            // set render target texture

                       driver->setRenderTarget(refraction, true, true, video::SColor(255,188,188,55));
                       waterloo->setVisible(false);
                       // HoverNode->setVisible(false);
                       rendermode = 1;
                       smgr->drawAll();



                         driver->setRenderTarget(reflection, true, true, video::SColor(255,128,166,255));
                       core::vector3df oldpos = camera->getPosition();
                       core::vector3df oldtarget = camera->getTarget();


                       ICameraSceneNode* reflectionCamera = smgr->addCameraSceneNode();

                       // affector.makeIdentity();
                       // float a[16]={1,0,0,0,
                       //              0,1,0,0,
                        //             0,0,-1,0,
                        //             0,0,0,1};
                     //  affector.setM(a);

                       // affector.setScale(core::vector3df(1.0,1.0,-1.0));
                     //  reflectionCamera->setViewMatrixAffector(affector);

                        reflectionCamera->setPosition(core::vector3df(oldpos.X,oldpos.Y,2*deepness-oldpos.Z));
                        reflectionCamera->setTarget(core::vector3df(oldtarget.X,oldtarget.Y,2*deepness-oldtarget.Z));

                        reflectionCamera->setUpVector(core::vector3df(0,0,-1));


                         rendermode = 2;
                         smgr->setActiveCamera(reflectionCamera);
                         smgr->drawAll();



                       driver->setRenderTarget(0, true, true, SColor (255,0,0,0));

                      camera->setUpVector(core::vector3df(0,0,-1));
                        HoverNode->setVisible(true);
                       waterloo->setVisible(true);
                        rendermode =3;
                       camera->setPosition(core::vector3df(oldpos.X,oldpos.Y,oldpos.Z));
                       camera->setTarget(core::vector3df(oldtarget.X,oldtarget.Y,oldtarget.Z));
                        smgr->setActiveCamera(camera);





        }
        smgr->drawAll();

        guienv->drawAll();

        driver->draw2DLine(core::vector2di(10+4,SCREEN_HEIGHT-140+4),core::vector2di(260-4,SCREEN_HEIGHT-140+4),SColor(255,255,255,255));
        driver->draw2DLine(core::vector2di(10+4+2,SCREEN_HEIGHT-140+4+2),core::vector2di(260-4+2,SCREEN_HEIGHT-140+4+2),SColor(255,0,0,0));
        driver->draw2DLine(core::vector2di(10+4+2,SCREEN_HEIGHT-140+4+3),core::vector2di(260-4+2,SCREEN_HEIGHT-140+4+3),SColor(255,0,0,0));
        driver->endScene();
    }
    device->drop();

    delete VisMa;
    delete MyShaders;
    return 0;
}
