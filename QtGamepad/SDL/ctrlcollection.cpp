#include "ctrlcollection.h"
#include <QDebug>

char* SDL_NAMES[] = {
    "PLAYSTATION(R)3 Controller",
    "Wiimote",
    "Wireless 360 Controller"
};

e_input SDLname2enum[] ={
    SIXAXIS,
    WIIMOTE,
    X360
};

QtSDLCtrlCollection::QtSDLCtrlCollection(int num_mappings){

    SDL_Init(SDL_INIT_JOYSTICK);

    for (int i = 0; i <= 17; i++)
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
