#pragma once
#include "Grobal.h"
#include "Struct.h"

typedef struct Light
{
//関数
	Light();
	~Light();

	//座標取得
	void SetCoordinate(int posX,int posY,bool sideway);
	//描画
	void Draw(bool sideway);

	void Move(char*keys,char *oldkeys);

	//更新
	void UpDate(char *keys,char*oldkeys);

//変数
	//位置座標 & 半径
	Transform transform;

	Width width;

	//速度
	Speed speed;

	//辺の座標
	Edge edge;

	//角の座標
	Corner corner;

	//色
	Color color;

	bool IsSideways;
}Light;