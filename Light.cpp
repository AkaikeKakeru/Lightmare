#include "DxLib.h"
#include "Light.h"

//コンスト
Light::Light()
{
		transform.pos.x = BLOCK_SIZE + BLOCK_SIZE /2;
		transform.pos.y = BLOCK_SIZE + BLOCK_SIZE /2 ;
		transform.radius = BLOCK_SIZE / 2;

		width.length = WIN_WIDTH;
		width.side = BLOCK_SIZE / 2;
	
		speed.direction.x = 0;
		speed.direction.y = 0;
		speed.config = 4;

		alive = false;

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
void Light::SetCoordinate(int posX,int posY,bool sideway)
{
	transform.pos.x = posX;
	transform.pos.y = posY;

	if(sideway == true)
	{
	edge.top = transform.pos.y - width.side;
	edge.bottom = transform.pos.y + width.side;
	edge.left = transform.pos.x - width.length;
	edge.right = transform.pos.x + width.length;
	}
	else
	{
	edge.top = transform.pos.y - width.length;
	edge.bottom = transform.pos.y + width.length;
	edge.left = transform.pos.x - width.side;
	edge.right = transform.pos.x + width.side;
	}

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
void Light::Draw(bool sideway)
{
	int top = transform.pos.y - width.side;
	int bottom = transform.pos.y + width.side;
	int left = transform.pos.x - width.length;
	int right = transform.pos.x + width.length;

	if(sideway == true)
	{
	top = transform.pos.y - width.side;
	bottom = transform.pos.y + width.side;
	left = transform.pos.x - width.length;
	right = transform.pos.x + width.length;
	}
	else
	{
	top = transform.pos.y - width.length;
	bottom = transform.pos.y + width.length;
	left = transform.pos.x - width.side;
	right = transform.pos.x + width.side;
	}

	DrawBox(left,top,right,bottom,color.RGB,true);
};

void Light::Move(char*keys,char *oldkeys)
{
	if(keys[KEY_INPUT_W] == false
	&& oldkeys[KEY_INPUT_W] == true)
	{
		transform.pos.y -= BLOCK_SIZE;
	}

	if(keys[KEY_INPUT_S] == false
	&& oldkeys[KEY_INPUT_S] == true)
	{
		transform.pos.y += BLOCK_SIZE;
	}

	if(keys[KEY_INPUT_A] == false
	&& oldkeys[KEY_INPUT_A] == true)
	{
		transform.pos.x -= BLOCK_SIZE;
	}

	if(keys[KEY_INPUT_D] == false
	&& oldkeys[KEY_INPUT_D] == true)
	{
		transform.pos.x += BLOCK_SIZE;
	}

	if(keys[KEY_INPUT_C] == false
	&& oldkeys[KEY_INPUT_C] == true)
	{
		IsSideways = !IsSideways;
	}
}

//更新
void Light::UpDate(char *keys,char *oldkeys)
{
	SetCoordinate(transform.pos.x,transform.pos.y,IsSideways);
	//Move(keys,oldkeys);
};