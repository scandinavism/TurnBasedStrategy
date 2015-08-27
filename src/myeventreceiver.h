#include <irrlicht.h>
using namespace irr;

class MyEventReceiver :public IEventReceiver
{
public:

    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        if ((event.EventType == irr::EET_MOUSE_INPUT_EVENT))
        {
            switch (event.MouseInput.Event)

            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                if (!event.MouseInput.isMiddlePressed() && !event.MouseInput.isRightPressed())
                    MouseEvents[0]=true;
                break;

            case EMIE_RMOUSE_PRESSED_DOWN:
                if (!event.MouseInput.isMiddlePressed() && !event.MouseInput.isLeftPressed())
                    MouseEvents[1]=true;
                break;
                break;

            case EMIE_MMOUSE_PRESSED_DOWN:
                break;

            case EMIE_LMOUSE_LEFT_UP:
                break;

            case EMIE_RMOUSE_LEFT_UP:
                break;

            case EMIE_MMOUSE_LEFT_UP:
                break;

            case EMIE_MOUSE_MOVED:
                break;

            case EMIE_MOUSE_WHEEL:
                MouseEvents[10]=true;
                wheel = event.MouseInput.Wheel;

                break;

            case EMIE_LMOUSE_DOUBLE_CLICK:
                break;

            case EMIE_RMOUSE_DOUBLE_CLICK:
                break;

            case EMIE_MMOUSE_DOUBLE_CLICK:
                break;

            default:

                break;
            }
        }


        return false;
    }
    virtual bool IsKeyDown(EKEY_CODE keyCode)
    {
        return KeyIsDown[keyCode];
    }

    explicit MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;

        for (u32 i=0; i<11; ++i)
            MouseEvents[i] = false;


    }

    bool IsLeftButtonClick()
    {
        if (MouseEvents[0])
        {
            MouseEvents[0] = false;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool IsRightButtonClick()
    {
        if (MouseEvents[1])
        {
            MouseEvents[1] = false;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool IsWheel()
    {
        if (MouseEvents[10])
        {
            MouseEvents[10]=false;
            return true;
        }
        else
        {
            return false;
        }
    }

    f32 getWheel()
    {
        return wheel;
    }

private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    bool MouseEvents[11];
    f32 wheel;
};

