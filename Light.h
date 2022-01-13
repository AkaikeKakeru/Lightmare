#pragma once
#include "Grobal.h"
#include "Struct.h"

typedef struct Light
{
//関数
	Light();
	~Light();

	//座標取得
	void GetCoordinate();
	//描画
	void Draw();

	//更新
	void UpDate();

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