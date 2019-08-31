#pragma once

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600

#define LARGE_SIZE 255

#define HERO_SPEED 5

#define GOAL 99
#define CAT 98

#define INTERFACE 102

#define MAX_COLOR 7

#define CLEAR 1
#define NOCLEAR 0
//색깔
enum
{
	RED = 0,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	NAVY,
	PURPLE,
	NONE,
};

//버튼
enum
{
	BT_RESTART = 56,
	BT_GOTOMENU,
	BT_SAVEEXIT,
	BT_PAUSENO,
};



//히어로
#define HEROMOVE_MAX 7

enum
{
	HEROMOVE_L = 0,
	HEROMOVE_R,
	HEROMOVE_U,
	HEROMOVE_D,
	HERO_CAT,
	HERO_ARR,
	HERO_STAND,
};