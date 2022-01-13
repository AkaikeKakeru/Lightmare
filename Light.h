#pragma once
#include "Grobal.h"
#include "Struct.h"

typedef struct Light
{
//�֐�
	Light();
	~Light();

	//���W�擾
	void SetCoordinate(int posX,int posY,bool sideway);
	//�`��
	void Draw(bool sideway);

	void Move(char*keys,char *oldkeys);

	//�X�V
	void UpDate(char *keys,char*oldkeys);

//�ϐ�
	//�ʒu���W & ���a
	Transform transform;

	Width width;

	//���x
	Speed speed;

	//�ӂ̍��W
	Edge edge;

	//�p�̍��W
	Corner corner;

	//�F
	Color color;

	bool IsSideways;
}Light;