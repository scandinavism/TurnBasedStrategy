#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include "irrlicht.h"
#include "PathFinding.h"


using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;


namespace GAMESTATES {

const int MAINMENU = 0;
const int LOADGAMEMENU = 1;
const int OPTIONSMENU = 2;
const int LOADING = 3;
const int MAINSCREEN = 4;
const int CITYSCREEN = 5;
const int RESEARCHSCREEN = 6;


}

typedef core::array<vector2d<s32> > CPath;

struct Pos{
    int x;
    int y;
};


class GameManager
{
public:
    GameManager()
    {
        CurrentState = GAMESTATES::MAINMENU;
    }

    ~GameManager()
    {

    }

    int GetPrevState()
    {
        return PrevState;
    }

    int GetCurrentState()
    {
        return CurrentState;
    }

    bool OpenLoadGameMenu()
    {
        if (CurrentState!=GAMESTATES::MAINMENU)
            return false;
        else
        {
           PrevState = CurrentState;
           CurrentState = GAMESTATES::LOADGAMEMENU;
        }

    }

    bool OpenOptionsMenu()
    {
        if (CurrentState!=GAMESTATES::MAINMENU)
            return false;
        else
        {
           PrevState = CurrentState;
           CurrentState = GAMESTATES::OPTIONSMENU;
        }

    }


private:
    int CurrentState;
    int PrevState;


};

class CPlayer
{

public:

    CPlayer()
    {

    }

    ~CPlayer()
    {

    }




private:

};


class CUnit
{
public:
    CUnit(int x, int y)
    {
        pos.x = x;
        pos.y = y;
    }

    ~CUnit()
    {}


    void setDestination(int x, int y)
    {

    }

    void move()
    {

    }

   CPath getPath()
    {

    }


private:
    Pos pos;
    //float health;
    float MaxMovementPoints;
    float MovementPoints;




};



#endif // GAMEMANAGER_H
