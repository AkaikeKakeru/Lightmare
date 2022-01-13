#pragma once
#include "Grobal.h"
#include "Struct.h"

typedef struct MapChip
{
	MapChip();
	~MapChip();
	void Draw();
	void GetPosion();

	Transform transform;
	Edge edge;
	Corner corner;
	Color color;

}MapChip;