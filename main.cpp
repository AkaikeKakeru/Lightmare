#include "DxLib.h"
#include "Struct.h"
#include "Grobal.h"
#include "Player.h"
#include "Object.h"
#include "Light.h"
#include "MapChip.h"
#include "Mirror.h"

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
	int resultNow = EMP;

	int stage = 1;
	int stageReset = 0;

	bool clearTutrial = false;

	int countEvent = 250;

	bool isContMirror = false;

	Player player(100, 100, 150, 150, 150);

	Light light[LIGHT_MAX];

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
	}

	for (int i = 0; i < MIRROR_MAX; i++)
	{
		light[i].transform.pos.x = -1;
		light[i].transform.pos.y = -1;
		light[i].transform.radius = 32;

		light[i].alive = false;
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
				if (clearTutrial == true)
				{
					sceneNow = StageSelect;
				}
				else
				{
					sceneNow = INIT;
				}
				break;
			case StageSelect:
				sceneNow = INIT;
				break;

			case Play:
				sceneNow = Pause;
				break;

			default:
				break;
			}
		}

		if (sceneNow == StageSelect)
		{
			resultNow = EMP;

			if (keys[KEY_INPUT_RIGHT] == true
				&& oldkeys[KEY_INPUT_RIGHT] == false)
			{
				//�����ő�Stage��
				if (stage < 4)
					stage++;
			}

			if (keys[KEY_INPUT_LEFT] == true
				&& oldkeys[KEY_INPUT_LEFT] == false)
			{
				if (stage > 1)
					stage--;
			}
		}
		//�X�e�[�W�ړ���������
		if (sceneNow == INIT)
		{
			resultNow = EMP;

			for (int i = 0; i < MIRROR_MAX; i++)
			{
				mirror[i].alive = false;
			}

			if (clearTutrial == true)
			{
				switch (stage)
				{
				case 1:
					//�o�Ă��鋾�̌�
					mirrorMax = 3;

					goal.transform.pos.x = 8;
					goal.transform.pos.y = 0;

					player.transform.pos.x = 0;
					player.transform.pos.y = 0;

					mirror[0].transform.pos.x = 8;
					mirror[0].transform.pos.y = 4;

					mirror[1].transform.pos.x = 0;
					mirror[1].transform.pos.y = 4;

					mirror[2].transform.pos.x = 3;
					mirror[2].transform.pos.y = 9;

					light[0].transform.pos.x = 8;
					light[0].transform.pos.y = 9;
					break;

				case 2:
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
					light[0].transform.pos.x = 8;
					light[0].transform.pos.y = 9;

				case 3:
					//�o�Ă��鋾�̌�
					mirrorMax = 2;

					goal.transform.pos.x = 3;
					goal.transform.pos.y = 0;
					player.transform.pos.x = 7;
					player.transform.pos.y = 6;
					mirror[0].transform.pos.x = 9;
					mirror[0].transform.pos.y = 9;
					mirror[1].transform.pos.x = 9;
					mirror[1].transform.pos.y = 6;
					light[0].transform.pos.x = 3;
					light[0].transform.pos.y = 9;
					break;
				default:
					break;
				}
			}
			else
			{
				switch (stage)
				{
				case 1:
					//�o�Ă��鋾�̌�
					mirrorMax = 0;

					goal.transform.pos.x = 8;
					goal.transform.pos.y = 6;
					player.transform.pos.x = 0;
					player.transform.pos.y = 1;
					light[0].transform.pos.x = 8;
					light[0].transform.pos.y = 0;
					light[0].IsSideways = false;
					break;

				case 2:
					//�o�Ă��鋾�̌�
					mirrorMax = 1;

					goal.transform.pos.x = 8;
					goal.transform.pos.y = 1;
					player.transform.pos.x = 0;
					player.transform.pos.y = 1;
					mirror[0].transform.pos.x = 3;
					mirror[0].transform.pos.y = 3;
					light[0].transform.pos.x = 0;
					light[0].transform.pos.y = 3;
					light[0].IsSideways = true;
					break;

				case 3:
					//�o�Ă��鋾�̌�
					mirrorMax = 1;

					goal.transform.pos.x = 4;
					goal.transform.pos.y = 0;
					player.transform.pos.x = 0;
					player.transform.pos.y = 7;
					mirror[0].transform.pos.x = 7;
					mirror[0].transform.pos.y = 9;
					light[0].transform.pos.x = 9;
					light[0].transform.pos.y = 9;
					light[0].IsSideways = true;
					break;
				}
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

			for (int i = 0; i < lightMax; i++)
			{

				light[i].transform.pos.x = light[i].transform.pos.x * BLOCK_SIZE + BLOCK_SIZE / 2;
				light[i].transform.pos.y = light[i].transform.pos.y * BLOCK_SIZE + BLOCK_SIZE / 2;

			}
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
			//mirrorMax = 2;

			//		//���̏����l+�ŏ��̌��̌���

			//		mirror[0].transform.pos.x = WIN_WIDTH / 2 - BLOCK_SIZE * 2 + BLOCK_SIZE /2;
			//		mirror[0].transform.pos.y = WIN_HEIGHT / 2 + BLOCK_SIZE /2;
			//mirror[0].direction = 0;
			//mirror[0].alive = true;


			//		mirror[1].transform.pos.x = WIN_WIDTH / 2 + BLOCK_SIZE * 2 + BLOCK_SIZE /2;
			//		mirror[1].transform.pos.y = WIN_HEIGHT / 2 + BLOCK_SIZE /2;
			//		mirror[1].direction = 2;
			//		mirror[1].alive = true;
			//		//lightDirection[0] = 2;

			//		//�S�[���̏����ʒu

			//		goal.transform.pos.x = WIN_WIDTH - goal.transform.radius;
			//		goal.transform.pos.y = WIN_HEIGHT - goal.transform.radius;

			//	}

			//stageReset = 1;

			sceneNow = Play;
		}

		if (sceneNow == Play)
		{
			//Pause�̃{�^���p
			if (keys[KEY_INPUT_LSHIFT] == true
				&& oldkeys[KEY_INPUT_LSHIFT] == false)
			{
				sceneNow = Pause;
			}

			//����؂�ւ��̃{�^���p
			if (keys[KEY_INPUT_C] == true
				&& oldkeys[KEY_INPUT_C] == false)
			{
				if (isContMirror == false)
				{
					isContMirror = true;
				}
				else
				{
					isContMirror = false;
				}
			}
			for (int i = 0; i < lightMax; i++)
			{
				light[i].UpDate(keys, oldkeys);
			}

			if (isContMirror == true)
			{
				for (int i = 0; i < mirrorMax; i++)
				{
					mirror[i].Move(keys, oldkeys);
				}
			}
			else
			{
				player.UpDate(keys);
			}


			if (Collision(player.edge.top, player.edge.bottom, player.edge.left, player.edge.right,
				goal.edge.top, goal.edge.bottom, goal.edge.left, goal.edge.right) == true)
			{
				resultNow = Clear;
			}

		}

		if (sceneNow == Pause)
		{
			if (keys[KEY_INPUT_LSHIFT] == true
				&& oldkeys[KEY_INPUT_LSHIFT] == false)
			{
				sceneNow = Play;
			}

			if (keys[KEY_INPUT_BACK] == true
				&& oldkeys[KEY_INPUT_BACK] == false)
			{
				sceneNow = OutIt;
			}
		}

		if (sceneNow == OutIt)
		{
			for (int i = 0; i < MIRROR_MAX; i++)
			{
				mirror[i].transform.pos.x = 0;
				mirror[i].transform.pos.y = 0;

				mirror[i].alive = false;
			}
			sceneNow = Title;
		}


		if (resultNow == Clear)
		{
			countEvent = 150;

			if (keys[KEY_INPUT_LSHIFT] == true
				&& oldkeys[KEY_INPUT_LSHIFT] == false)
			{
				stage++;
				sceneNow = INIT;
			}

			if (clearTutrial == true)
			{
				if (keys[KEY_INPUT_BACK] == true
					&& oldkeys[KEY_INPUT_BACK] == false)
				{
					sceneNow = StageSelect;
				}
			}
			else if (stage > 3)
			{
				clearTutrial = true;
				sceneNow = INIT;
				stage = 1;
			}
		}

		// �`�揈��
		int white = GetColor(255, 255, 255);

		if (sceneNow == Title)
		{
			DrawFormatString(100, WIN_HEIGHT / 2, GetColor(255, 255, 255), "TITLE");
		}

		if (sceneNow == StageSelect)
		{
			DrawFormatString(100, WIN_HEIGHT / 2, GetColor(255, 255, 255), "STAGE SELECT \n %d\n", stage);
		}


		if (sceneNow == Play)
		{
			for (int i = 0; i < lightMax; i++)
			{

				if (Collision(goal.edge.top, goal.edge.bottom, goal.edge.left, goal.edge.right,
					light[i].edge.top, light[i].edge.bottom, light[i].edge.left, light[i].edge.right) == true)
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
						light[i].edge.top, light[i].edge.bottom, light[i].edge.left, light[i].edge.right) == true)
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
					light[i].edge.top, light[i].edge.bottom, light[i].edge.left, light[i].edge.right) == true)
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

			}
			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < MAP_WIDTH; x++)
				{
					map[y][x].Draw();
				}
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);

			for (int i = 0; i < lightMax; i++)
			{

				light[i].Draw(light[i].IsSideways);
			}

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

			if (clearTutrial == false)
			{
				switch (stage)
				{
				case 1:
					if (player.transform.pos.x < BLOCK_SIZE * 3
						&& player.transform.pos.y < BLOCK_SIZE * 3)
					{
						DrawFormatString(200, WIN_HEIGHT / 2, white, " �������� �ňړ��ł���\n");
					}
					else
					{
						DrawCircle(goal.transform.pos.x, goal.transform.pos.y, BLOCK_SIZE + 8, white, false);

						DrawFormatString(200, WIN_HEIGHT / 2, white, "�܂��̓S�[����ڎw����\n");
					}
					break;

				case 2:
					if (player.transform.pos.x < BLOCK_SIZE * 3
						&& player.transform.pos.y < BLOCK_SIZE * 3)
					{
						if (countEvent > 0)
						{
							countEvent--;
						}
						else
						{
							if (isContMirror == false)
							{
								DrawFormatString(200, WIN_HEIGHT / 2 + 100, white, " C �ő�������ɐ؂�ւ�����\n");
							}
							else
							{
								DrawFormatString(200, WIN_HEIGHT / 2 + 100, white, "���� �������� �œ������āA\n�����̕ǂ���o���Ă����悤\n");
							}
						}
						DrawFormatString(200, WIN_HEIGHT / 2, white, "���̎q�̑̂ł́A\n������ς����Ȃ�\n");
					}
					else
					{
						DrawFormatString(200, WIN_HEIGHT / 2, white, "�S�[���͌��������𓖂Ă邱�ƂŋN������\n");
					}

					break;

				case 3:
					if (isContMirror == true)
					{
						DrawFormatString(200, WIN_HEIGHT / 2 + 100, white, "Space�ŋ�����]�ł���\n");
					}
					else
					{
						if (Collision(goal.edge.top, goal.edge.bottom, goal.edge.left, goal.edge.right,
							light[i].edge.top, light[i].edge.bottom, light[i].edge.left, light[i].edge.right) == true)
						{
							DrawFormatString(200, WIN_HEIGHT / 2 + 100, white, "�����ɐG��Ȃ��悤�ɃS�[����ڎw����\n");
						}
						else
						{
							DrawFormatString(200, WIN_HEIGHT / 2 + 100, white, "�܂��͋��𑀍삵�ăS�[�����N�������悤\n");
						}
					}

					break;
				default:
					break;
				}

			}
		}

		if (sceneNow == Pause)
		{
			DrawFormatString(100, WIN_HEIGHT / 2, GetColor(255, 255, 255), "PAUSE");
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