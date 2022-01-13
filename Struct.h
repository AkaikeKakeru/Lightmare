#pragma once
#include "DxLib.h"

/*�\����*/

//���W
typedef struct Coordinate
{
	int x;
	int y;
}Coordinate;

//�ʒu & ���a
typedef struct Transform
{
	Coordinate pos;
	int radius;
}Transform;

//��
typedef struct Width
{
	int length;
	int side;
}Width;

//���x
typedef struct Speed
{
	Coordinate direction;
	int config;
}Speed;

//�p
typedef struct Corner
{
	Coordinate leftTop;
	Coordinate leftBottom;
	Coordinate rightTop;
	Coordinate rightBottom;
}Corner;

//��
typedef struct Edge
{
	int top;
	int bottom;
	int left;
	int right;
}Edge;

//�F
typedef struct Color
{
	int R;
	int G;
	int B;
	int RGB;
}Color;