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
#include <assert.h>
#include <time.h>

#define bSQUARE	0x25A0
#define wSQUARE	0x25A1

#define WHITE 1
#define BLACK 0

#define c2num(a) (a-'a'+1)

#define min(a,b)	((a<b)?a:b)
#define max(a,b)	((a>b)?a:b)

#define clear() 	printf("\x1b[H\x1b[J")

void avoidSpaces();

void toLower(char *s);

#endif