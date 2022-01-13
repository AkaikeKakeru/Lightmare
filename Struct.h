#pragma once
#include "DxLib.h"

/*構造体*/

//座標
typedef struct Coordinate
{
	int x;
	int y;
}Coordinate;

//位置 & 半径
typedef struct Transform
{
	Coordinate pos;
	int radius;
}Transform;

//幅
typedef struct Width
{
	int length;
	int side;
}Width;

//速度
typedef struct Speed
{
	Coordinate direction;
	int config;
}Speed;

//角
typedef struct Corner
{
	Coordinate leftTop;
	Coordinate leftBottom;
	Coordinate rightTop;
	Coordinate rightBottom;
}Corner;

//辺
typedef struct Edge
{
	int top;
	int bottom;
	int left;
	int right;
}Edge;

//色
typedef struct Color
{
	int R;
	int G;
	int B;
	int RGB;
}Color;