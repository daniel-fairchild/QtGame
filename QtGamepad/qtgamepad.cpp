#include "qtgamepad.h"

#include <qdebug.h>

#include <limits.h>



/*
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
*/


#define AXIS2BTN_THRSHLD 16

QtGamepad::QtGamepad(size_t num_mappings)
{
    this->map = (gp_map_col_t*) calloc(1, sizeof(gp_map_col_t*) + sizeof(gp_mapping_t)* num_mappings);
    this->map->bindings = (gp_mapping_t*)(this->map+1);
    this->map->length = num_mappings;
}

#define INT_SIGN_DIFF(a, b) (a & 1<<(WORD_BIT-1)) != (b & 1<<(WORD_BIT-1))

static inline void _2btn(gp_mapping_t* mapping, int* output, size_t timestamp, int btnval){
    if (!btnval){
        *output = mapping->value ? timestamp - mapping->value : 0;
        mapping->value = 0;
    }
    else {
        mapping->value = mapping->value ? mapping->value : timestamp -1;
        *output = -(timestamp - mapping->value);
    }
}

static inline void _btn2axis(gp_mapping_t* mapping, int* output, size_t timestamp, uint8_t btnval){
}

static inline void _axis2btn(gp_mapping_t* mapping, int* output, size_t timestamp){
}


void QtGamepad::read_mappings(size_t timestamp, int *outvals)
{
//    for (int i= 0; i < this->numButtons(); i++){
//        int tmp = this->readButton(i);
//        if (tmp)
//            qDebug() << i << ": " << tmp;
//    }

    for (int i = 0; i < this->map->length; i++){
        switch((this->map->bindings+i)->from_type){
        {case CMAP_BUTTON:
                int btnvalue = this->readButton((this->map->bindings+i)->src);
//                btnvalue = (btnvalue<<1)-1;

                switch ((this->map->bindings+i)->to_type){
                case CMAP_BUTTON:
                    _2btn(this->map->bindings+i, outvals+i, timestamp, btnvalue);
                    break;
                case CMAP_AXIS:
                    _btn2axis(this->map->bindings+i, outvals+i, timestamp, btnvalue);
                    break;
                default:
                    break;
                }
                break;}
        case CMAP_AXIS:
            switch ((this->map->bindings+i)->to_type) {
            case CMAP_BUTTON:
                _axis2btn(this->map->bindings+i, outvals+i, timestamp);
                break;
            case CMAP_AXIS:
                *(outvals+i) = this->readAxis((this->map->bindings+i)->src);
                break;
            default:
                break;
            }
            break;
        }
    }
}

void QtGamepad::reset()
{
    for (int i = 0; i < this->map->length; i++)
        (this->map->bindings+i)->value = 0;
}

void QtGamepad::bind(CMAP_E from_type, CMAP_E to_type, unsigned char from, unsigned char to)
{
    if (to >= this->map->length){
        //TODO: error handling
        qDebug() << "HID mapping segfault!\n";
        return;
    }

    (this->map->bindings+to)->from_type = from_type;
    (this->map->bindings+to)->to_type = to_type;
    (this->map->bindings+to)->src = from;
}



void QtGamepad::unbind(unsigned char target)
{
    this->bind(CMAP_NONE, CMAP_NONE, NULL, target);
}
