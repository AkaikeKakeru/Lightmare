#pragma once
#include "Grobal.h"
#include "Struct.h"

typedef struct Light
{
//�֐�
	Light();
	~Light();

	//���W�擾
	void GetCoordinate();
	//�`��
	void Draw();

	//�X�V
	void UpDate();

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