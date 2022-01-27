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
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int mirrorGH = LoadGraph("mirror.png");
	int searchGH = LoadGraph("search.png");

	// ゲームループで使う変数の宣言
	int i;

	int alpha = 150;


	//光の最大個数
	const int LIGHT_MAX = 5;
	int lightMax = 1;

	//鏡の最大個数
	const int MIRROR_MAX = 5;
	int mirrorMax = 0;//ステージごとに変える用


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

	// 最新のキーボード情報用
	char keys[KEY_QUA] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[KEY_QUA] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (i = 0; i < KEY_QUA; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理


	//ステージ移動
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
		//ステージ移動時初期化
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
				//出てくる鏡の個数
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
				//出てくる鏡の個数
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
				//出てくる鏡の個数
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
						//ステージ1

					//	if (stage == 1)
					//	{

					//		stageReset = 1;

					//		////最初の光の座標
					//		//lightStartPosX[0] = WIN_WIDTH / 2;
					//		//lightStartPosY[0] = startY;
					//		//lightEndPosX[0] = WIN_WIDTH / 2;
					//		//lightEndPosY[0] = endY;

					//		////初期座標の保存
					//		//lightOldStartPosX[0] = lightStartPosX[0];
					//		//lightOldStartPosY[0] = lightStartPosY[0];
					//		//lightOldEndPosX[0] = lightEndPosX[0];
					//		//lightOldEndPosY[0] = lightEndPosY[0];

					//		//出てくる鏡の個数
			mirrorMax = 2;

			//		//鏡の初期値+最初の光の向き

			//		mirror[0].transform.pos.x = WIN_WIDTH / 2 - BLOCK_SIZE * 2 + BLOCK_SIZE /2;
			//		mirror[0].transform.pos.y = WIN_HEIGHT / 2 + BLOCK_SIZE /2;
			mirror[0].direction = 0;
			mirror[0].alive = true;


			//		mirror[1].transform.pos.x = WIN_WIDTH / 2 + BLOCK_SIZE * 2 + BLOCK_SIZE /2;
			//		mirror[1].transform.pos.y = WIN_HEIGHT / 2 + BLOCK_SIZE /2;
			//		mirror[1].direction = 2;
			//		mirror[1].alive = true;
			//		//lightDirection[0] = 2;

			//		//ゴールの初期位置

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
		// 描画処理
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
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	DeleteGraph(mirrorGH);
	DeleteGraph(searchGH);

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}