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
	//���W�擾
	void GetCoordinate();

	//���W�ړ�
	void Move(char *keys);

	/*bool CollisionLight(Light light);
	bool CollisionObject(Object obj);*/

	//�`��
	void Draw();

	//�X�V
	void UpDate(char *keys);

//�ϐ�
	//�ʒu���W & ���a
	Transform transform;

	//���x
	Speed speed;

	//�ӂ̍��W
	Edge edge;

	//�p�̍��W
	Corner corner;

	//�F
	Color color;

	Light light;

	Object goal;
}Player;