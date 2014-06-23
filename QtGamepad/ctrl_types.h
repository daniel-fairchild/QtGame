#ifndef CTRL_TYPES_H
#define CTRL_TYPES_H

typedef enum {
    WIIMOTE = 1,
    SIXAXIS,
    X360,
    KEYBOARD,
    DUMMY_INP,
    UNKNOWN_INP
} e_input;

typedef struct {
    e_input type;
    int device_id;
    int numaxis;
    int numbtns;
} gamepad_t;

typedef enum {
    CMAP_NONE = 0,
    CMAP_BUTTON = 1,
    CMAP_AXIS = 2,
    CMAP_TRIGGER = 4,
    CMAP_BTN2NEGAXIS = 8,
    CMAP_BTN2PLUSAXIS = 16,
} CMAP_E;

typedef struct {
  CMAP_E from_type;
  CMAP_E to_type;
  unsigned char src;
//  unsigned char to;
  int value;
} gp_mapping_t;


typedef struct {
    int length;
    gp_mapping_t* bindings;
} gp_map_col_t;

#endif // CTRL_TYPES_H
