
// main.cpp

#include "myeventreceiver.h"
#include "TileMesh.h"
#include "WaterTileMesh.h"
#include "MyShaderCallBack.h"
#include "TileEdgeMesh.h"
#include "TileCornerMesh.h"
#include "DGameMap.h"
#include "PathFinding.h"
#include "GameManager.h"
#include "DRandom.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;



int IRRCALLCONV main(int argc, char* argv[])
{
       /* Заранее прошу прощения за то, что иногда комментарии прыгают
        * с английского языка на русский и обратно. Я билингвален и иногда
        * удобнее думать на английском языке.
        *
        * К тому же, привычнее оставлять англоязычные комментарии,
        * так как во многих Open-Source проектах используется, всё же
        *  английский.
        *
        * Комментарии, описывающие вызовы, идут непосредственно ПОСЛЕ вызова.
        * Однако, иногда встречаются комменатарии, описывающие набор предстоящих действий.
        * Такие вызовы идут перед группой описываемых вызовов и определений.
        *
        *  Данила.
        */

    u32 ticker = 0;  //каждый шаг вычислений увеличивает значение этой переменной на единицу. Таким образом, каждый периодический процесс может взять остаток от деления на свой период и получить текущее значение "фазы".
    const u32 tickermax = 3628800;  // = 10! (так что делится на все числа от одного до десяти без остатка. Более того, делится и на произведения, такие как 90=10*9, 21 = 7*3 и т.д. )

    MyEventReceiver receiver; // класс обработчика событий, описан в своём h-файле.

    device =  createDevice( video::EDT_OPENGL, dimension2d<u32>(SCREEN_WIDTH, SCREEN_HEIGHT), 32,  true, true, false, &receiver);
    if (!device) return 1;
    /* Создали контекст и окно OpenGL средствами Irrlicht.
     * 32 бита.
     * Полный экран
     * Стенсил-Буффер
     * НЕТ Вертикальной синхронизации.
     *
     * Ширина и высота пока что задаются через #define, в последствии будут переменными.
     *
     * Если не удалось создать, то выходим из программы.
     *
     * TODO: добавить сообщение об ошибке
    */

    device->setWindowCaption(L"Terra Normanorum v0.021");//меняем заголовок окна. Название временное и кодирует стадию разработки
    IVideoDriver* driver = device->getVideoDriver();//
    ISceneManager* smgr = device->getSceneManager();//
    IGUIEnvironment* guienv = device->getGUIEnvironment();//эти три переменные для упрощения вызова в дальнейшем.


    scene::ICameraSceneNode* camera = smgr->addCameraSceneNode(0,core::vector3df(30,25,-15),core::vector3df(30,30,0),ID_IsNotPickable,true);
    /* Задали камеру, через которую мы будем видеть игровой мир.
     * Как дочерний нод главному ноду сцены
     * В определённой точке пространства
     * Смотрим на другую точку пространства
     * Задаём ID
     * Делаем её активной камерой
     */

    scene::ISceneNode* highlightedSceneNode = 0;

    scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();//класс для определения столкновений. В частности, определения куда мы указываем мышкой.

    scene::ITriangleSelector* selector = 0; // эта переменная будет содержать селекторы, которые отвечают в ноде за детекцию столкновений, и которые мы будем создавать непосредственно под каждый нод, используя только одну переменную - указатель.

    video::SMaterial material;//служебная переменная для хранения свойств материалов.

    core::vector3df cameranodePosition = camera->getPosition(); // позиция камеры
    core::vector3df targetPosition = camera->getTarget(); // позиция направления обзора

    core::vector3df cameranodePositionTarget = cameranodePosition; //
    core::vector3df targetPositionTarget = targetPosition; // эти две переменные хранят позиции точек, куда должны сдвинуться камера и точка обзора

    s32 VisibleX = trunc(targetPosition.X/3*2)/I_CHUNKSIZE;
    s32 VisibleY = trunc(targetPosition.Y/sqrt(3))/J_CHUNKSIZE;
    /* Всё игровое поле сразу не рисуется. Оно делится на подразделения, чанки.
     * В каждый момент времени видно девять чанков -
     *
     *      ***
     *      ***
     *      ***
     *
     * В центральном чанке находится точка, в которую смотрит камера.
     * Эти две переменные хранят номера центрального чанка.
     * TODO: на рефакторинге заменить непосредственное вычисление функцией
     */

    material.setTexture(0, 0);
    material.Lighting = false;

    device->getCursorControl()->setVisible(true);
    // switching cursor on


    ILightSceneNode *lightnode = smgr->addLightSceneNode(0, vector3df(0,100,0), SColorf(1.0f, 1.0f, 1.0f, 1.0f), 10.0f);
    /* создаём основной источник света.
     * как дочерний нод для головного узла
     * в такой-то точке пространства (не важно, в какой)
     * задаём цвет
     * и радиус
     */


        lightnode->setLightType(video::ELT_DIRECTIONAL);
        // Меняем тип нашего источника света на бесконечно удалённый (параллельно идут лучи, важно только направление)
        //lightnode->setPosition(core::vector3df(-sqrt(1/3),-sqrt(1/3),-sqrt(1/3)));
        //lightnode->setRotation(vector3df(0,0,180));
        lightnode->setRotation(vector3df(32,22,12));
        // Поворот у такого типа источников меняет направление распространения.
        // Значения в градусах

    lightnode->setVisible(true);
    //нет необходимости, но делаем наш свет видимым, "включаем его"



    driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY,true);
    //даём указания драйверу оптимизироваться на качество. Альтернативно можно использовать
    //driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED,true);

    driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL ,false);
    //разрешаем использовать альфа-канал в текстурах
    driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS,true);
    //и создавать мип-мэпы.


        scene::ILightSceneNode* lightnode2 = 0;
        lightnode2 = smgr->addLightSceneNode(0, core::vector3df(0,0,-10),

                                             video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 10.0f);
        //временно для экспериментов и демонстрации создадим точечный источник света.
        //TODO: удалить

        scene::ISceneNode* node = 0;
        //создадим пустой нод. Эта переменная нам понадобится позже, возможно.
        //тем более, это просто указатель...

        node = smgr->addBillboardSceneNode(lightnode2, core::dimension2d<f32>(0.2, 0.2));
        //а пока что прилепим билборд на наш источник света

        node->setMaterialFlag(video::EMF_LIGHTING, false);
        //сам он не будет подсвечиваться
        node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
        //а в качестве слоя прозрачности пусть будет цвет в точке (0;0) текстуры. Типичный колор-мэппинг
        node->setMaterialTexture(0, driver->getTexture("notexture"));
        //здесь я принципиально добавляю не совсем корректное имя файла.
        //для временных целей меня устраивает просто белый квадрат непрогрузившейся текстуры

        smgr->setShadowColor(video::SColor(150,0,0,0));
        //первоначально этот источник с билбордом был добавлен для тестирования теней.
        //этот вызов остался с тех времён, но всё равно полезен

    ShaderWrapper *MyShaders = new ShaderWrapper;
    //здесь я инициализирую класс, загружающий и поддерживающий шейдеры.
    //информация в своём h-файле

    u32* a = &ticker;
    //создаю указатель, указывающий на тикер.

    s32 rendermode = 0;
    MyShaders->LoadShaders(driver,lightnode,&ticker,&rendermode,deepness);
    /* Загружаю шейдеры.
     * Rendermode - переменная, необходимая для отображения воды и передаётся в шейдер поверхности.
     * Меняется по нескольку раз за кадр, так что, как и в случае с тикером, передаём указатель
     *
     * Что касается deepness - это "глубина" расположения морского дна. Вода находится на половине этого уровня.
     * Величина эта не меняется, это глобальный параметр. Однако, по соображениям масштабируемости, передаём её как параметр,
     * не определяя константу внутри класса шейдеров.
     */

    VisibleMap *VisMa = new VisibleMap(smgr,driver,lightnode,a,MyShaders);
    /* Класс, который содержит всю карту.
     * Описан в своём h-файле.
     *
     * a - неиспользуемый параметр, который уйдёт при рефакторинге.
     *
     */

    for (int a=0; a<I_SIZE/I_CHUNKSIZE; a++)
        for (int b=0; b<J_SIZE/J_CHUNKSIZE; b++) //для всех чанков
        {
            selector = smgr->createTriangleSelector(VisMa->nodes[a][b]->getMesh(),VisMa->nodes[a][b]);
            //создаём селектор с таким-то мешем для такого-то нода. Логично, что в качестве меша используем меш самого нода.
            VisMa->nodes[a][b]->setTriangleSelector(selector);
            //вешаем селектор на нод чанка
            selector->drop();
            // избавляемся от селектора
        }


    scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();

    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
    bill->setMaterialTexture(0, driver->getTexture("media/particle.bmp"));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialFlag(video::EMF_ZBUFFER, false);
    bill->setSize(core::dimension2d<f32>(0.2f, 0.2f));
    bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it
    bill->setVisible(false);
    //этот биллборд отображался на поверхности, в точке, на которую показывает курсор
    //сейчас он выключен.
    //TODO: избавиться


    IGUIStaticText* statex = guienv->addStaticText(L"tempchar", rect<s32>(10,40,460,52), true);
    statex->setBackgroundColor(video::SColor(255,255,255,255));
    statex->setVisible(false);
    //верхняя служебная полоска отображения служебной информации
    //сейчас она выключена.
    //TODO: избавиться


    IGUIStaticText* tileinfopanel = guienv->addStaticText(L"",rect<s32>(10,SCREEN_HEIGHT-140,260,SCREEN_HEIGHT-10),false);
    tileinfopanel->setBackgroundColor(SColor(127,50,50,50));
    tileinfopanel->setOverrideColor(SColor(255,255,255,255));
    // Создаём нижне-левую панель информации
    // магические числа, формально задают положение на экране.
    // TODO: заменить магические числа на функции, возвращающие значения в зависимости от alignmenta, ширины и высоты
    // TODO: вместо жёсткого задания цвета текста изменить общий скин интерфейса


    const int MINIMAPX = SCREEN_WIDTH-I_SIZE*2;
    const int MINIMAPY = SCREEN_HEIGHT;


    IGUIImage* minimap = guienv->addImage(core::rect<s32>(MINIMAPX,MINIMAPY-J_SIZE*2-2,SCREEN_WIDTH,SCREEN_HEIGHT),0,-1,L"Minimap",true);

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
    //Всё то же: создаём интерфейс
    //TODO: перейти на использование скина.


    SMesh* HoverMesh = new SMesh();
    createHexHoverMesh(HoverMesh );
    IMeshSceneNode* HoverNode = smgr->addMeshSceneNode((IMesh*)HoverMesh);
    //создаём простой шестиугольник, который будет отображатсья на том тайле, на который указывает курсор

    HoverNode->setMaterialTexture(0,driver->getTexture("assets/gui/hexhover.png"));
    HoverNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    HoverNode->setMaterialFlag(video::EMF_BACK_FACE_CULLING,false);
    HoverNode->setMaterialFlag(video::EMF_LIGHTING,false);
    HoverNode->setMaterialFlag(EMF_ZBUFFER,false);
    HoverNode->setVisible(true);
    //параметры нода

    scene::IVolumeLightSceneNode * n = smgr->addVolumeLightScene
