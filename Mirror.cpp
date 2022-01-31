#include "DxLib.h"
#include "Grobal.h"
#include "Struct.h"
#include "Mirror.h"

Mirror::Mirror()
{
	transform.pos.x = 0;
	transform.pos.y = 0;
	transform.radius = 32;

	alive = false;

	direction = 0;
	angle = 0;
	graph = 0;
}


Mirror::Mirror(int MirrorGraph)
{
	transform.pos.x = 0;
	transform.pos.y = 0;
	transform.radius = 32;

	alive = false;

	direction = 0;
	angle = 0;
	graph = MirrorGraph;
}

Mirror::~Mirror()
{
	DeleteGraph(graph);
}

void Mirror::Move(char* keys,char*oldkeys)
{
	if (keys[KEY_INPUT_UP] == true)
	{
		transform.pos.y-=4;
	}

	if (keys[KEY_INPUT_DOWN] == true)
	{
		transform.pos.y+=4;
	}

	if (keys[KEY_INPUT_LEFT] == true)
	{
		transform.pos.x-=4;
	}

	if (keys[KEY_INPUT_RIGHT] == true)
	{
		transform.pos.x+=4;
	}
}

void Mirror::Draw()
{
	DrawRotaGraph(transform.pos.x, transform.pos.y, 1.0, angle, graph, TRUE);
}