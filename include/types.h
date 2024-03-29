#ifndef __TYPES
#define __TYPES

#include <stdint.h>
#include <stdbool.h>

#define getBit(var,pos,type)     (((var)&(((type)1)<<(pos)))!=0?1:0)
#define setBit(var,pos,type)     ((var)|=(((type)1)<<(pos)))
#define resetBit(var,pos,type)   ((var)&=~(((type)1)<<(pos)))
#define switchBit(var,pos,type)  ((var)^=(((type)1)<<(pos)))

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
    wPAWN,
}pieceType;

typedef struct{
    int px,py,x,y,computerMove;
}mov;

typedef struct{
    mov *m;
    int dim;
}moves;

typedef struct{
    int board[9][9];
    bool toMove;
    uint64_t coverage[2];
    bool kingCastle[2];
    struct{
        int x,y;
    }kingPosition[2];
}position;

typedef struct{
    position *current;
    position *past;
    int no,dim;
    char mode,color;
    int difficulty;
}match;

#endif