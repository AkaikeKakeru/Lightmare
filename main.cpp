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
	SetBackgroundColor(0x00, 0x00, 0xFF);			

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
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

	// 最新のキーボード情報用
	char keys[KEY_QUA] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[KEY_QUA] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for ( i = 0; i < KEY_QUA; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		light.GetCoordinate();

		player.UpDate(keys);

		// 描画処理

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


	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}