#include "qtgamepad.h"

#ifdef _WIN64
   //define something for Windows (64-bit)
#elif _WIN32
   //define something for Windows (32-bit)
#elif __APPLE__
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
        #define NO_SDL
    #elif TARGET_OS_IPHONE
        // iOS device
        #define NO_SDL
    #elif TARGET_OS_MAC
        #define NO_SDL
        // Other kinds of Mac OS
    #else
        // Unsupported platform
    #endif
#elif __linux
    // linux
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif

QtGamepad::QtGamepad()
{
}
