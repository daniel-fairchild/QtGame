#include "qtctrlcollection.h"

#ifndef NO_SDL
#include <SDL/SDL.h>
#endif


#include <QDebug>

typedef enum {WIIMOTE = 1, SIXAXIS, X360, KEYBOARD, REPLAY, DUMMY_INP} e_input;

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



static inline void _SDL_setup(int i){
    const char *jn = SDL_JoystickName(i);
}

QtCtrlCollection::QtCtrlCollection()
{
    SDL_Init(SDL_INIT_JOYSTICK);

    for (int i = 0; i < this->numGamepads(); i++){
        qDebug() << SDL_JoystickName(i) << "\n";
    }
}

int QtCtrlCollection::numGamepads(){
    return SDL_NumJoysticks();
}
