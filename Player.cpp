#include "DxLib.h"
#include "Player.h"
#include "Grobal.h"
#include "Struct.h"
#include "Light.h"

//�R���X�g(������)
Player::Player(int x,int y, int R,int G, int B)
{
	transform.pos.x = x;
	transform.pos.y = y;
	transform.radius = BLOCK_SIZE /2;

	speed.direction.x = 0;
	speed.direction.y = 0;
	speed.config = 4;

	color.R = R;
	color.G = G;
	color.B = B;
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

//void Player::SetLight(Light light)
//{
//	light = light;
//}

//�f�X�g
Player::~Player()
{
	
}


void Player::ReSet()
{
	transform.pos.x = 100;
	transform.pos.y = 100;
	
	speed.direction.x = 0;
	speed.direction.y = 0;
}

//���W�擾
void Player::GetCoordinate()
{
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

//���W�ړ�
void Player::Move(char *keys)
{
	speed.direction.x = 0;
	speed.direction.y = 0;

	if(keys[KEY_INPUT_UP] == true
	|| keys[KEY_INPUT_W] == true)
	{
		if(edge.top > 0)
		{
			speed.direction.y = -speed.config;
		}
	}

	if(keys[KEY_INPUT_DOWN] == true
	|| keys[KEY_INPUT_S] == true)
	{
		if(edge.bottom < WIN_HEIGHT)
		{
			speed.direction.y = speed.config;
		}
	}

	if(keys[KEY_INPUT_LEFT] == true
	|| keys[KEY_INPUT_A] == true)
	{
		if(edge.left > 0)
		{
			speed.direction.x = -speed.config;
		}
	}

	if(keys[KEY_INPUT_RIGHT] == true
	|| keys[KEY_INPUT_D] == true)
	{
		if(edge.right < WIN_WIDTH)
		{
			speed.direction.x = speed.config;
		}
	}

	transform.pos.x += speed.direction.x;
	transform.pos.y += speed.direction.y;
};

//bool Player::CollisionLight(Light light)
//{
//	int top = transform.pos.y - transform.radius;
//	int bottom = transform.pos.y + transform.radius;
//	int left = transform.pos.x - transform.radius;
//	int right = transform.pos.x + transform.radius;
//
//	int topLight = light.transform.pos.y - light.width.side;
//	int bottomLight = light.transform.pos.y + light.width.side;
//	int leftLight = light.transform.pos.x - light.width.length;
//	int rightLight = light.transform.pos.x + light.width.length;
//
//	if(bottom > topLight
//	&& top < bottomLight)
//	{
//		if(right > leftLight
//		&& left < rightLight)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool CollisionObject(Object obj)
//{
//	int top = transform.pos.y - transform.radius;
//	int bottom = transform.pos.y + transform.radius;
//	int left = transform.pos.x - transform.radius;
//	int right = transform.pos.x + transform.radius;
//
//	int topLight = obj.transform.pos.y - obj.transform.radius;
//	int bottomLight = obj.transform.pos.y + obj.transform.radius;
//	int leftLight = obj.transform.pos.x - obj.transform.radius;
//	int rightLight = obj.transform.pos.x + obj.transform.radius;
//
//	if(bottom > topLight
//	&& top < bottomLight)
//	{
//		if(right > leftLight
//		&& left < rightLight)
//		{
//			return true;
//		}
//	}
//
//	return false;
//};

//�`��
void Player::Draw()
{
	int top = transform.pos.y - transform.radius;
	int bottom = transform.pos.y + transform.radius;
	int left = transform.pos.x - transform.radius;
	int right = transform.pos.x + transform.radius;

	//if(CollisionLight(light) == true)
	//{
	//	color.R = 50;
	//	color.G = 50;
	//	color.B = 120;
	//}
	//else if(CollisionObject(goal) == true)
	//{
	//	color.R = 180;
	//	color.G = 180;
	//	color.B = 200;
	//}
	//else
	//{
	//	color.R = 150;
	//	color.G = 150;
	//	color.B = 210;
	//}

	color.RGB = GetColor(color.R,color.G,color.B);

	DrawBox(left,top,right,bottom,color.RGB,true);
};

//�X�V
void Player::UpDate(char *keys)
{
	GetCoordinate();

	Move(keys);
};