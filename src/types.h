#ifndef __TYPES
#define __TYPES

typedef enum{
    bKING = 0x2654,
    bQUEEN,
    bROOK,
    bBISHOP,
    bKNIGHT,
    bPAWN,
    wKING,
    wQUEEN,
    wROOK,
    wBISHOP,
    wKNIGHT,
    wPAWN
}pieceType;

typedef enum{
    INACTIVE,
    ACTIVE
}status;

typedef struct{
    pieceType type;
    int x,y;
    status s;
}piece;

typedef struct{
    int x,y;
    piece *p;
}mov;

typedef struct{
    mov *m;
    int dim;
}moves;

#endif