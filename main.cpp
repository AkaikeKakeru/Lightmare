#include "DxLib.h"
#include "Struct.h"
#include "Grobal.h"
#include "Player.h"
#include "Object.h"
#include "Light.h"
#include "MapChip.h"
#include "Mirror.h"
#include "Stage.h"

bool Collision(int topA, int bottomA, int leftA, int rightA, int topB, int bottomB, int leftB, int rightB)
{
	if (topA < bottomB
		&& bottomA > topB)
	{
		if (leftA < rightB
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
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int mirrorGH = LoadGraph("mirror.png");
	int searchGH = LoadGraph("search.png");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	int i;

	int alpha = 150;


	//���̍ő��
	const int LIGHT_MAX = 5;
	int lightMax = 1;

	//���̍ő��
	const int MIRROR_MAX = 5;
	int mirrorMax = 0;//�X�e�[�W���Ƃɕς���p


	int sceneNow = Title;

	int stage = 1;
	int stageReset = 0;


	Player player(100, 100, 150, 150, 150);

	Light light;

	MapChip map[MAP_HEIGHT][MAP_WIDTH];

	Object goal;

	Mirror mirror[MIRROR_MAX];

	for (int i = 0; i < MIRROR_MAX; i++)
	{
		mirror[i].transform.pos.x = -1;
		mirror[i].transform.pos.y = -1;
		mirror[i].transform.radius = 32;

		mirror[i].alive = false;
		mirror[i].direction = 0;
		mirror[i].angle = 0;
		//mirror[i].graph = mirrorGH;
	}

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			map[y][x].transform.pos.x
				= x * BLOCK_SIZE + BLOCK_SIZE / 2;
			map[y][x].transform.pos.y
				= y * BLOCK_SIZE + BLOCK_SIZE / 2;

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
		for (i = 0; i < KEY_QUA; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����


	//�X�e�[�W�ړ�
		if (keys[KEY_INPUT_RETURN] == 1
			&& oldkeys[KEY_INPUT_RETURN] == 0)
		{
		switch (sceneNow)
		{
		case Title:
			sceneNow = StageSelect;
			break;
		case StageSelect:
			sceneNow = Play;
			break;
		default:
			sceneNow =Title;
			break;
		}
		}

		if(sceneNow == StageSelect)
		{
			if(keys[KEY_INPUT_RIGHT] == true
			&& oldkeys[KEY_INPUT_RIGHT] == false)
			stage++;
			stageReset = 0;
		}
		//�X�e�[�W�ړ���������
		if (stageReset == 0)
		{
			for (int i = 0; i < MIRROR_MAX; i++)
			{
				mirror[i].alive = false;
			}

			//MapSetting(stage,goal.transform.pos,player.transform.pos,mirror[0].transform.pos,light.transform.pos);


			switch (stage)
			{
			case 1:
				//�o�Ă��鋾�̌�
				mirrorMax = 1;

				goal.transform.pos.x = 4;
				goal.transform.pos.y = 0;
				player.transform.pos.x = 0;
				player.transform.pos.y = 7;
				mirror[0].transform.pos.x = 4;
				mirror[0].transform.pos.y = 9;
				light.transform.pos.x = 9;
				light.transform.pos.y = 9;
				break;

			case 2:
				//�o�Ă��鋾�̌�
				mirrorMax = 2;

				goal.transform.pos.x = 8;
				goal.transform.pos.y = 0;
				player.transform.pos.x = 0;
				player.transform.pos.y = 0;
				mirror[0].transform.pos.x = 9;
				mirror[0].transform.pos.y = 4;
				mirror[1].transform.pos.x = 0;
				mirror[1].transform.pos.y = 4;
				light.transform.pos.x = 8;
				light.transform.pos.y = 9;
				break;

			case 3:
				//�o�Ă��鋾�̌�
				mirrorMax = 2;

				goal.transform.pos.x = 9;
				goal.transform.pos.y = 0;
				player.transform.pos.x = 2;
				player.transform.pos.y = 2;
				mirror[0].transform.pos.x = 5;
				mirror[0].transform.pos.y = 0;
				mirror[1].transform.pos.x = 5;
				mirror[1].transform.pos.y = 9;
				light.transform.pos.x = 8;
				light.transform.pos.y = 9;
				break;
			default:
				break;
			}

			goal.transform.pos.x = goal.transform.pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
			goal.transform.pos.y = goal.transform.pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;
			player.transform.pos.x = player.transform.pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
			player.transform.pos.y = player.transform.pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;
			for (int i = 0; i < mirrorMax; i++)
			{

				mirror[i].transform.pos.x = mirror[i].transform.pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
				mirror[i].transform.pos.y = mirror[i].transform.pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;

				mirror[i].alive = true;
			}
			light.transform.pos.x = light.transform.pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
			light.transform.pos.y = light.transform.pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;

			goal.GetCoordinate();
			//			
						//�X�e�[�W1

					//	if (stage == 1)
					//	{

					//		stageReset = 1;

					//		////�ŏ��̌��̍��W
					//		//lightStartPosX[0] = WIN_WIDTH / 2;
					//		//lightStartPosY[0] = startY;
					//		//lightEndPosX[0] = WIN_WIDTH / 2;
					//		//lightEndPosY[0] = endY;

					//		////�������W�̕ۑ�
					//		//lightOldStartPosX[0] = lightStartPosX[0];
					//		//lightOldStartPosY[0] = lightStartPosY[0];
					//		//lightOldEndPosX[0] = lightEndPosX[0];
					//		//lightOldEndPosY[0] = lightEndPosY[0];

					//		//�o�Ă��鋾�̌�
			mirrorMax = 2;

			//		//���̏����l+�ŏ��̌��̌���

			//		mirror[0].transform.pos.x = WIN_WIDTH / 2 - BLOCK_SIZE * 2 + BLOCK_SIZE /2;
			//		mirror[0].transform.pos.y = WIN_HEIGHT / 2 + BLOCK_SIZE /2;
			mirror[0].direction = 0;
			mirror[0].alive = true;


			//		mirror[1].transform.pos.x = WIN_WIDTH / 2 + BLOCK_SIZE * 2 + BLOCK_SIZE /2;
			//		mirror[1].transform.pos.y = WIN_HEIGHT / 2 + BLOCK_SIZE /2;
			//		mirror[1].direction = 2;
			//		mirror[1].alive = true;
			//		//lightDirection[0] = 2;

			//		//�S�[���̏����ʒu

			//		goal.transform.pos.x = WIN_WIDTH - goal.transform.radius;
			//		goal.transform.pos.y = WIN_HEIGHT - goal.transform.radius;

			//	}

			stageReset = 1;
		}

		if(sceneNow == Play)
		{
		for (int i = 0; i < mirrorMax; i++)
		{
			mirror[i].Move(keys, oldkeys);
		}

		light.UpDate(keys, oldkeys);
		player.UpDate(keys);

		}
		// �`�揈��
		if(sceneNow == Title)
		{
			DrawFormatString(100,WIN_HEIGHT/2,GetColor(255,255,255),"TITLE");
		}
		
		if(sceneNow == StageSelect)
		{
			DrawFormatString(100,WIN_HEIGHT/2,GetColor(255,255,255),"STAGE SELECT");
		}


		if(sceneNow == Play)
		{

		if (Collision(goal.edge.top, goal.edge.bottom, goal.edge.left, goal.edge.right,
			light.edge.top, light.edge.bottom, light.edge.left, light.edge.right) == true)
		{
			goal.color.R = 250;
			goal.color.G = 250;
			goal.color.B = 100;
		}
		else
		{
			goal.color.R = 150;
			goal.color.G = 150;
			goal.color.B = 100;
		}

		if (Collision(player.edge.top, player.edge.bottom, player.edge.left, player.edge.right,
			goal.edge.top, goal.edge.bottom, goal.edge.left, goal.edge.right) == true)
		{

			if (Collision(goal.edge.top, goal.edge.bottom, goal.edge.left, goal.edge.right,
				light.edge.top, light.edge.bottom, light.edge.left, light.edge.right) == true)
			{
				player.color.R = 220;
				player.color.G = 220;
				player.color.B = 200;
			}
			else
			{
				goal.color.R = 50;
				goal.color.G = 50;
				goal.color.B = 50;
			}
		}

		else if (Collision(player.edge.top, player.edge.bottom, player.edge.left, player.edge.right,
			light.edge.top, light.edge.bottom, light.edge.left, light.edge.right) == true)
		{
			player.color.R = 50;
			player.color.G = 50;
			player.color.B = 120;
		}

		else
		{
			player.color.R = 150;
			player.color.G = 150;
			player.color.B = 210;
		}

		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				map[y][x].Draw();
			}
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

		light.Draw(light.IsSideways);

		goal.Draw();

		for (int i = 0; i < mirrorMax; i++)
		{
			if (mirror[i].alive == true)
			{
				//mirror[i].Draw();
				DrawBox(mirror[i].transform.pos.x - mirror[i].transform.radius,
					mirror[i].transform.pos.y - mirror[i].transform.radius,
					mirror[i].transform.pos.x + mirror[i].transform.radius,
					mirror[i].transform.pos.y + mirror[i].transform.radius,
					GetColor(200, 50, 50), true);

				DrawRotaGraph(mirror[i].transform.pos.x, mirror[i].transform.pos.y, 1.0, mirror[i].angle, mirrorGH, TRUE);
			}
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(player.transform.pos.x - BLOCK_SIZE * 2, player.transform.pos.y - BLOCK_SIZE * 2, searchGH, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
		player.Draw();

		}
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

	DeleteGraph(mirrorGH);
	DeleteGraph(searchGH);

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}