#include "gamepad.h"

char* SDL_NAMES[] = {
    "PLAYSTATION(R)3 Controller",
    "Wiimote",
    "Wireless 360 Controller"
};

e_input SDLname2enum[] = {
    SIXAXIS,
    WIIMOTE,
    X360
};

QtSDLGamePad::QtSDLGamePad(size_t num_mappings, int device_index) : QtGamepad(num_mappings)
{
    this->device = SDL_JoystickOpen(device_index);
}

int QtSDLGamePad::readButton(int btnindex)
{
    return SDL_JoystickGetButton(this->device, btnindex);
}

int QtSDLGamePad::readAxis(int axisindex)
{
    int tmp = SDL_JoystickGetAxis(this->device, axisindex);
    tmp /= 256;
    return  tmp;
}


int QtSDLGamePad::numButtons()
{
    return SDL_JoystickNumButtons(this->device);
}

int QtSDLGamePad::numAxes()
{
    return SDL_JoystickNumAxes(this->device);
}
