#ifndef QTCTRLTYPES_H
#define QTCTRLTYPES_H

typedef enum {WIIMOTE = 1, SIXAXIS, X360, KEYBOARD, DUMMY_INP, UNKNOWN_INP} e_input;

typedef struct {
    e_input type;
    int device_id;
    int numaxis;
    int numbtns;
} gamepad_t;

typedef enum  {
    BUTTON,
    AXIS,
} CMAP_SRC_E;

typedef enum {
    ANALOG,
    BINARY,
    TIMED_HOLD,
} CMAP_TRGT_E;

typedef struct {
  CMAP_E kind;
  unsigned char from;
  unsigned char to;
} gp_mapping_t;


typedef struct {
    int num_mappings;

} gp_map_col_t;

#endif // QTCTRLTYPES_H
