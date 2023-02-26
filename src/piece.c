#include "piece.h"

int getPieceValue(unsigned piece){
	switch(piece){
		case wKING:
			return 900;
			break;
		case bKING:
			return -900;
			break;
		case wQUEEN:
			return 90;
			break;
		case bQUEEN:
			return -90;
			break;
		case wROOK:
			return 50;
			break;
		case bROOK:
			return -50;
			break;
		case wKNIGHT:
			return 30;
			break;
		case bKNIGHT:
			return -30;
			break;
		case wBISHOP:
			return 30;
			break;
		case bBISHOP:
			return -30;
			break;
		case wPAWN:
			return 10;
			break;
		case bPAWN:
			return -10;
			break;
		default:
			printf("Invalid piece!\n");
			return 0;
	}
}

bool getPieceColor(unsigned piece){
	if(	piece==bKING||
		piece==bQUEEN||
		piece==bKNIGHT||
		piece==bBISHOP||
		piece==bROOK||
		piece==bPAWN){
		return BLACK;
	}

	if(	piece==wKING||
		piece==wQUEEN||
		piece==wKNIGHT||
		piece==wBISHOP||
		piece==wROOK||
		piece==wPAWN){
		return WHITE;
	}
	printf("Invalid piece code!\nThe program may not behave correctly!\n");
	return 1;
}