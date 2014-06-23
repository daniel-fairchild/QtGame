#include "gamepad.h"


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
    return SDL_JoystickGetAxis(this->device, axisindex);
}
