#include "DxLib.h"
#include "Struct.h"
#include "Grobal.h"
#include "Player.h"
#include "Object.h"
#include "Light.h"
#include "MapChip.h"

bool Collision(int topA,int bottomA,int leftA,int rightA,int topB,int bottomB,int leftB,int rightB)
{
	if(topA < bottomB
	&& bottomA > topB)
	{
		if(leftA < rightB
		&& rightA > leftB)
		{
			return true;
		}
	}

	return false;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	
	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xFF);			

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int i;
	//int j;

	Player player(100,100,150,150,150);

	Light light;

	MapChip map[MAP_HEIGHT][MAP_WIDTH];

	Object goal(9 * BLOCK_SIZE + BLOCK_SIZE /2,9 * BLOCK_SIZE + BLOCK_SIZE /2,150,150,100);

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			map[y][x].transform.pos.x 
				= x * BLOCK_SIZE + BLOCK_SIZE /2;
			map[y][x].transform.pos.y 
				= y * BLOCK_SIZE + BLOCK_SIZE /2;

			map[y][x].edge.top 
				= map[y][x].transform.pos.y - map[y][x].transform.radius;
			map[y][x].edge.bottom 
				= map[y][x].transform.pos.y + map[y][x].transform.radius;
			map[y][x].edge.left 
				= map[y][x].transform.pos.x - map[y][x].transform.radius;
			map[y][x].edge.right 
				= map[y][x].transform.pos.x + map[y][x].transform.radius;
		}
	}

	// �ŐV�̃L�[�{�[�h���p
	char keys[KEY_QUA] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[KEY_QUA] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for ( i = 0; i < KEY_QUA; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		light.GetCoordinate();

		player.UpDate(keys);

		// �`�揈��

		if(Collision(player.edge.top,player.edge.bottom,player.edge.left,player.edge.right,
			light.edge.top,light.edge.bottom,light.edge.left,light.edge.right) == true)
		{
			player.color.R = 50;
			player.color.G = 50;
			player.color.B = 120;
		}

		else if(Collision(player.edge.top,player.edge.bottom,player.edge.left,player.edge.right,
			goal.edge.top,goal.edge.bottom,goal.edge.left,goal.edge.right) == true)
		{
			player.color.R = 180;
			player.color.G = 180;
			player.color.B = 200;
		}

		else
		{
			player.color.R = 150;
			player.color.G = 150;
			player.color.B = 210;
		}

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				map[y][x].Draw();
			}
		}


		light.Draw();

		goal.Draw();

		player.Draw();

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();	

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}


	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}