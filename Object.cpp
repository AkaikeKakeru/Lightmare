#include "DxLib.h"
#include "Grobal.h"
#include "Struct.h"
#include "Object.h"

Object::Object()
{
	transform.pos.x = 0;
	transform.pos.y = 0;
	transform.radius = BLOCK_SIZE /2;

	color.R = 0;
	color.G = 0;
	color.B = 0;
	color.RGB = GetColor(color.R,color.G,color.B);

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
}

Object::Object(int x,int y, int colorR,int colorG, int colorB)
{
	transform.pos.x = x;
	transform.pos.y = y;
	transform.radius = BLOCK_SIZE /2;

	color.R = colorR;
	color.G = colorG;
	color.B = colorB;
	color.RGB = GetColor(color.R,color.G,color.B);

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
}

Object::~Object()
{
}

void Object::Draw()
{
	int top = transform.pos.y - transform.radius;
	int bottom = transform.pos.y + transform.radius;
	int left = transform.pos.x - transform.radius;
	int right = transform.pos.x + transform.radius;

	color.RGB = GetColor(color.R,color.G,color.B);

	DrawBox(left,top,right,bottom,color.RGB,true);
}