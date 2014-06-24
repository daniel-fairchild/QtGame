#include "ctrlcollection.h"
#include <QDebug>


QtSDLCtrlCollection::QtSDLCtrlCollection(int num_mappings){

    SDL_Init(SDL_INIT_JOYSTICK);

    for (int i = 0; i < 17; i++)
        this->gamepads[i] = NULL;

    for (int i = 0; i < this->numGamepads(); i++){
//        qDebug() << SDL_JoystickName(i) << "\n";

        this->gamepads[i] = new QtSDLGamePad(num_mappings, i);
    }
}

int QtSDLCtrlCollection::numGamepads()
{
    return SDL_NumJoysticks();
}

QtGamepad *QtSDLCtrlCollection::gamepad(int index)
{
    return this->gamepads[index];
}


void QtSDLCtrlCollection::probe_hardware()
{
    SDL_JoystickUpdate();
}
