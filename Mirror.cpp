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
	if (keys[KEY_INPUT_I] == false
	&& oldkeys[KEY_INPUT_I] == true)
	{
		transform.pos.y-=BLOCK_SIZE;
	}
	if (keys[KEY_INPUT_K] == false
	&& oldkeys[KEY_INPUT_K] == true)
	{
		transform.pos.y+=BLOCK_SIZE;
	}

	if (keys[KEY_INPUT_J] == false
	&& oldkeys[KEY_INPUT_J] == true)
	{
		transform.pos.x-=BLOCK_SIZE;
	}
	if (keys[KEY_INPUT_L] == false
	&& oldkeys[KEY_INPUT_L] == true)
	{
		transform.pos.x+=BLOCK_SIZE;
	}
}

void Mirror::Draw()
{
	DrawRotaGraph(transform.pos.x, transform.pos.y, 1.0, angle, graph, TRUE);
}