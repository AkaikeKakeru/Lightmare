#include "Light.h"

//コンスト
Light::Light()
{
		transform.pos.x = BLOCK_SIZE *2;
		transform.pos.y = BLOCK_SIZE + BLOCK_SIZE /2 ;
		transform.radius = BLOCK_SIZE / 2;

		width.length = WIN_WIDTH;
		width.side = BLOCK_SIZE / 2;
	
		speed.direction.x = 0;
		speed.direction.y = 0;
		speed.config = 4;

		IsSideways = true;
	
		color.R = 230;
		color.G = 230;
		color.B = 230;
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
};
//デスト
Light::~Light()
{
};

//座標取得
void Light::GetCoordinate()
{
	edge.top = transform.pos.y - width.side;
	edge.bottom = transform.pos.y + width.side;
	edge.left = transform.pos.x - width.length;
	edge.right = transform.pos.x + width.length;

	corner.leftTop.x = edge.left;
	corner.leftTop.y = edge.top;
	
	corner.leftBottom.x = edge.left;
	corner.leftBottom.y = edge.bottom;
	
	corner.rightTop.x = edge.right;
	corner.rightTop.y = edge.top;
	
	corner.rightBottom.x = edge.right;
	corner.rightBottom.y = edge.bottom;
};
//描画
void Light::Draw()
{
	int top = transform.pos.y - width.side;
	int bottom = transform.pos.y + width.side;
	int left = transform.pos.x - width.length;
	int right = transform.pos.x + width.length;

	DrawBox(left,top,right,bottom,color.RGB,true);
};

//更新
void Light::UpDate()
{
};