#pragma once
#include "Struct.h"
typedef struct Mirror
{
	Transform transform;
	//Corner corner;
	//Edge edge;
	//Color color;
	bool alive;

	int direction;
	int angle;

	int graph;

	Mirror();
	Mirror(int graph);
	~Mirror();

	void Move(char*keys,char*oldkeys);
	void Draw();
}Mirror;

////鏡
//
//	//鏡の最大値
//	
//const int MIRROR_MAX = 5;
//	int mirrorMax = 0;//ステージごとに変える用
	//int mirrorPosX[MIRROR_MAX] = {};
	//int mirrorPosY[MIRROR_MAX] = {};

	//int mirrorRadiusX = 32;//鏡半径
	//int mirrorRadiusY = 32;

	//int mirrorDirection[MIRROR_MAX] = {};//0↗ 1↘ 2↙ 3↖
	//float mirrorAngle[MIRROR_MAX] = {};//鏡角度