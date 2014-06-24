#ifndef QTSDLGAMEPAD_H
#define QTSDLGAMEPAD_H

#include "../qtgamepad.h"

#include <SDL/SDL_joystick.h>


class QtSDLGamePad : public QtGamepad
{

public:
    QtSDLGamePad(size_t num_mappings, int device_index);



private:
    int device_index;
    SDL_Joystick* device;

    // QtGamepad interface
protected:
    int readButton(int btnindex);
    int readAxis(int axisindex);

    // QtGamepad interface
public:
    int numButtons();
    int numAxes();
};

#endif // QTSDLGAMEPAD_H
