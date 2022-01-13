#pragma once
#include "Struct.h"
#include "Grobal.h"
#include "Object.h"
#include "Light.h"

typedef struct Player
{
	Player(int x,int y, int R,int G, int B);
	~Player();

	/*void SetLight(Light light);*/
	void ReSet();
	//座標取得
	void GetCoordinate();

	//座標移動
	void Move(char *keys);

	/*bool CollisionLight(Light light);
	bool CollisionObject(Object obj);*/

	//描画
	void Draw();

	//更新
	void UpDate(char *keys);

//変数
	//位置座標 & 半径
	Transform transform;

	//速度
	Speed speed;

	//辺の座標
	Edge edge;

	//角の座標
	Corner corner;

	//色
	Color color;

	Light light;

	Object goal;
}Player;