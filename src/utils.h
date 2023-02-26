#ifndef __UTILS
#define __UTILS

#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

//chess pieces unicodes
#define bKING 	0x2654
#define bQUEEN 	0x2655
#define bROOK	0x2656
#define bBISHOP	0x2657
#define bKNIGHT	0x2658
#define bPAWN	0x2659
#define wKING	0x265A
#define wQUEEN	0x265B
#define wROOK	0x265C
#define wBISHOP	0x265D
#define wKNIGHT	0x265E
#define wPAWN	0x265F

#define bSQUARE	0x25A0
#define wSQUARE	0x25A1

#define WHITE 1
#define BLACK 0

#define INVALID -1
#define VALID	0

#define c2num(a) (a-'a'+1)

#define min(a,b)	((a<b)?a:b)
#define max(a,b)	((a>b)?a:b)

#define clear() 	printf("\x1b[H\x1b[J")

void avoidSpaces();

void toLower(char *s);

#endif