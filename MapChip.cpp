#pragma once
#include "Grobal.h"
#include "Struct.h"
#include "MapChip.h"

MapChip::MapChip()
{
	transform.pos.x = 0;
	transform.pos.y = 0;
	transform.radius = BLOCK_SIZE /2;

	edge.top = transform.pos.y - transform.radius;
	edge.bottom = transform.pos.y + transform.radius;
	edge.left = transform.pos.x - transform.radius;
	edge.right = transform.pos.x + transform.radius;

	corner.leftTop.x = edge.left;
	corner.leftTop.y = edge.top;
	corner.leftBottom.x = edge.left;
	corner.leftBottom.y = edge.bottom;
	corner.rightTop.x = edge.right;
	corner.rightTop.y = edge.top;
	corner.rightBottom.x = edge.right;
	corner.rightBottom.y = edge.bottom;

	color.R = 130;
	color.G = 130;
	color.B = 130;
	color.RGB = GetColor(color.R,color.G,color.B);
}

MapChip::~MapChip()
{
}

void::MapChip::GetPosion()
{

}

void MapChip::Draw()
{
	int top = transform.pos.y - transform.radius;
	int bottom = transform.pos.y + transform.radius;
	int left = transform.pos.x - transform.radius;
	int right = transform.pos.x + transform.radius;

	DrawBox(left,top,right,bottom,color.RGB,true);

	DrawBox(edge.left,edge.top,edge.right,edge.bottom,GetColor(50,50,50),false);
}