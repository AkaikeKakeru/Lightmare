#pragma once
#include "Struct.h"


typedef struct Object
{
	Transform transform;
	Corner corner;
	Edge edge;
	Color color;

	Object();
	Object(int x,int y, int R,int G, int B);
	~Object();

	void Draw();
}Object;