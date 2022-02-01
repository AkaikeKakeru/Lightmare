#include "DxLib.h"
#include "Grobal.h"
#include "Struct.h"
#include "Mirror.h"

Mirror::Mirror()
{
	transform.pos.x = 0;
	transform.pos.y = 0;
	transform.radius = 32;

	alive = false;

	direction = 0;
	angle = 0;
	graph = 0;
}


Mirror::Mirror(int MirrorGraph)
{
	transform.pos.x = 0;
	transform.pos.y = 0;
	transform.radius = 32;

	alive = false;

	direction = 0;
	angle = 0;
	graph = MirrorGraph;
}

Mirror::~Mirror()
{
	DeleteGraph(graph);
}

void Mirror::Move(char* keys, char* oldkeys)
{
	if (keys[KEY_INPUT_UP] == true)
	{
		transform.pos.y -= 4;
	}

	if (keys[KEY_INPUT_DOWN] == true)
	{
		transform.pos.y += 4;
	}

	if (keys[KEY_INPUT_LEFT] == true)
	{
		transform.pos.x -= 4;
	}

	if (keys[KEY_INPUT_RIGHT] == true)
	{
		transform.pos.x += 4;
	}

	if (keys[KEY_INPUT_SPACE] == true
		&& oldkeys[KEY_INPUT_SPACE] == false)
	{
		if (direction < UpLeft)
		{
			direction++;
		}
		else
		{
			direction = UpRight;
		}
	}
}

void Mirror::Draw(int DirectionNum)
{
	bool reverseX = false;
	bool reverseY = false;

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	int yellow = GetColor(220, 220, 50);
	int green = GetColor(100, 230, 100);
	int white = GetColor(240, 240, 240);
	int aqua = GetColor(50, 180, 230);

	int left = transform.pos.x - transform.radius;
	int right = transform.pos.x + transform.radius;
	int top = transform.pos.y - transform.radius;
	int bottom = transform.pos.y + transform.radius;

	switch (DirectionNum)
	{
	case UpRight:
		a = left;
		b = right;
		c = top;
		d = bottom;

		reverseX = false;
		reverseY = false;
		break;

	case DownRight:
		a = left;
		b = right;
		c = bottom;
		d = top;

		reverseX = false;
		reverseY = true;
		break;

	case DownLeft:
		a = right;
		b = left;
		c = bottom;
		d = top;

		reverseX = true;
		reverseY = true;
		break;

	case UpLeft:
		a = right;
		b = left;
		c = top;
		d = bottom;

		reverseX = true;
		reverseY = false;
		break;

	default:
		break;
	}




	//DrawRotaGraph(transform.pos.x, transform.pos.y, 1.0, angle, graph, TRUE);
	DrawTriangle(transform.pos.x, c, transform.pos.x, transform.pos.y, b, transform.pos.y, white, true);

	DrawTriangle(a, c, a, d, b, d, yellow, true);

	DrawBox(a, c, transform.pos.x, d, white, true);

	DrawBox(a, transform.pos.y, b, d, white, true);

	if (reverseX == true)
	{
		if (reverseY == true)
		{
			DrawTriangle(a + -transform.radius / 2, c, a + -transform.radius / 4, transform.pos.y - -transform.radius / 2 - -transform.radius / 4, transform.pos.x - -transform.radius / 2, transform.pos.y - -transform.radius / 2, aqua, true);

			DrawTriangle(b, d - -transform.radius / 2, b - -transform.radius / 4, transform.pos.y + -transform.radius / 2 + -transform.radius / 4, transform.pos.x + -transform.radius / 2, transform.pos.y + -transform.radius / 2, aqua, true);

			DrawTriangle(a + -transform.radius / 4, c + -transform.radius / 4, a + -transform.radius / 4, d - -transform.radius / 4, b - -transform.radius / 4, d - -transform.radius / 4, aqua, true);

			DrawTriangle(a + -transform.radius / 2, c, a + -transform.radius / 2, d - -transform.radius / 2, b, d - -transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x - -transform.radius / 2, c, transform.pos.x, c + -transform.radius / 8, transform.pos.x, transform.pos.y - -transform.radius / 2, aqua, true);

			DrawTriangle(b - -transform.radius / 2, transform.pos.y, b - -transform.radius / 8, transform.pos.y, b, transform.pos.y + -transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x, c + -transform.radius / 8, transform.pos.x, transform.pos.y, b - -transform.radius / 8, transform.pos.y, aqua, true);

			DrawTriangle(a + -transform.radius / 8, transform.pos.y - -transform.radius / 4, a + -transform.radius / 8, d - -transform.radius / 8, transform.pos.x + -transform.radius / 4, d - -transform.radius / 8, white, true);

			DrawTriangle(a, transform.pos.y, a, d, transform.pos.x, d, green, true);
		}
		else
		{
			DrawTriangle(a + -transform.radius / 2, c, a + -transform.radius / 4, transform.pos.y - transform.radius / 2 - transform.radius / 4, transform.pos.x - -transform.radius / 2, transform.pos.y - transform.radius / 2, aqua, true);

			DrawTriangle(b, d - transform.radius / 2, b - -transform.radius / 4, transform.pos.y + transform.radius / 2 + transform.radius / 4, transform.pos.x + -transform.radius / 2, transform.pos.y + transform.radius / 2, aqua, true);

			DrawTriangle(a + -transform.radius / 4, c + transform.radius / 4, a + -transform.radius / 4, d - transform.radius / 4, b - -transform.radius / 4, d - transform.radius / 4, aqua, true);

			DrawTriangle(a + -transform.radius / 2, c, a + -transform.radius / 2, d - transform.radius / 2, b, d - transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x - -transform.radius / 2, c, transform.pos.x, c + transform.radius / 8, transform.pos.x, transform.pos.y - transform.radius / 2, aqua, true);

			DrawTriangle(b - -transform.radius / 2, transform.pos.y, b - -transform.radius / 8, transform.pos.y, b, transform.pos.y + transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x, c + transform.radius / 8, transform.pos.x, transform.pos.y, b - -transform.radius / 8, transform.pos.y, aqua, true);

			DrawTriangle(a + -transform.radius / 8, transform.pos.y - transform.radius / 4, a + -transform.radius / 8, d - transform.radius / 8, transform.pos.x + -transform.radius / 4, d - transform.radius / 8, white, true);

			DrawTriangle(a, transform.pos.y, a, d, transform.pos.x, d, green, true);
		}
	}
	else
	{
		if (reverseY == true)
		{
			DrawTriangle(a + transform.radius / 2, c, a + transform.radius / 4, transform.pos.y - -transform.radius / 2 - -transform.radius / 4, transform.pos.x - transform.radius / 2, transform.pos.y - -transform.radius / 2, aqua, true);

			DrawTriangle(b, d - -transform.radius / 2, b - transform.radius / 4, transform.pos.y + -transform.radius / 2 + -transform.radius / 4, transform.pos.x + transform.radius / 2, transform.pos.y + -transform.radius / 2, aqua, true);

			DrawTriangle(a + transform.radius / 4, c + -transform.radius / 4, a + transform.radius / 4, d - -transform.radius / 4, b - transform.radius / 4, d - -transform.radius / 4, aqua, true);

			DrawTriangle(a + transform.radius / 2, c, a + transform.radius / 2, d - -transform.radius / 2, b, d - -transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x - transform.radius / 2, c, transform.pos.x, c + -transform.radius / 8, transform.pos.x, transform.pos.y - -transform.radius / 2, aqua, true);

			DrawTriangle(b - transform.radius / 2, transform.pos.y, b - transform.radius / 8, transform.pos.y, b, transform.pos.y + -transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x, c + -transform.radius / 8, transform.pos.x, transform.pos.y, b - transform.radius / 8, transform.pos.y, aqua, true);

			DrawTriangle(a + transform.radius / 8, transform.pos.y - -transform.radius / 4, a + transform.radius / 8, d - -transform.radius / 8, transform.pos.x + transform.radius / 4, d - -transform.radius / 8, white, true);

			DrawTriangle(a, transform.pos.y, a, d, transform.pos.x, d, green, true);
		}
		else
		{
			DrawTriangle(a + transform.radius / 2, c, a + transform.radius / 4, transform.pos.y - transform.radius / 2 - transform.radius / 4, transform.pos.x - transform.radius / 2, transform.pos.y - transform.radius / 2, aqua, true);

			DrawTriangle(b, d - transform.radius / 2, b - transform.radius / 4, transform.pos.y + transform.radius / 2 + transform.radius / 4, transform.pos.x + transform.radius / 2, transform.pos.y + transform.radius / 2, aqua, true);

			DrawTriangle(a + transform.radius / 4, c + transform.radius / 4, a + transform.radius / 4, d - transform.radius / 4, b - transform.radius / 4, d - transform.radius / 4, aqua, true);

			DrawTriangle(a + transform.radius / 2, c, a + transform.radius / 2, d - transform.radius / 2, b, d - transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x - transform.radius / 2, c, transform.pos.x, c + transform.radius / 8, transform.pos.x, transform.pos.y - transform.radius / 2, aqua, true);

			DrawTriangle(b - transform.radius / 2, transform.pos.y, b - transform.radius / 8, transform.pos.y, b, transform.pos.y + transform.radius / 2, aqua, true);

			DrawTriangle(transform.pos.x, c + transform.radius / 8, transform.pos.x, transform.pos.y, b - transform.radius / 8, transform.pos.y, aqua, true);

			DrawTriangle(a + transform.radius / 8, transform.pos.y - transform.radius / 4, a + transform.radius / 8, d - transform.radius / 8, transform.pos.x + transform.radius / 4, d - transform.radius / 8, white, true);

			DrawTriangle(a, transform.pos.y, a, d, transform.pos.x, d, green, true);
		}


	}












	//DrawTriangle(transform.pos.x, top, transform.pos.x, transform.pos.y, right, transform.pos.y, white, true);

	//DrawTriangle(left, top, left, bottom, right, bottom, yellow, true);

	//DrawBox(left, top, transform.pos.x, bottom, white, true);

	//DrawBox(left, transform.pos.y, right, bottom, white, true);

	//DrawTriangle(left + transform.radius / 2, top, left + transform.radius / 4, transform.pos.y - transform.radius / 2 - transform.radius / 4, transform.pos.x - transform.radius / 2, transform.pos.y - transform.radius / 2, aqua, true);

	//DrawTriangle(right, bottom - transform.radius / 2, right - transform.radius / 4, transform.pos.y + transform.radius / 2 + transform.radius / 4, transform.pos.x + transform.radius / 2, transform.pos.y + transform.radius / 2, aqua, true);

	//DrawTriangle(left + transform.radius / 4, top + transform.radius / 4, left + transform.radius / 4, bottom - transform.radius / 4, right - transform.radius / 4, bottom - transform.radius / 4, aqua, true);

	//DrawTriangle(left + transform.radius / 2, top, left + transform.radius / 2, bottom - transform.radius / 2, right, bottom - transform.radius / 2, aqua, true);

	//DrawTriangle(transform.pos.x - transform.radius / 2, top, transform.pos.x, top + transform.radius / 8, transform.pos.x, transform.pos.y - transform.radius / 2, aqua, true);

	//DrawTriangle(right - transform.radius / 2, transform.pos.y, right - transform.radius / 8, transform.pos.y, right, transform.pos.y + transform.radius / 2, aqua, true);

	//DrawTriangle(transform.pos.x, top + transform.radius / 8, transform.pos.x, transform.pos.y, right - transform.radius / 8, transform.pos.y, aqua, true);

	//DrawTriangle(left + transform.radius / 4,transform.pos.y,left + transform.radius / 4,bottom - transform.radius / 4,transform.pos.x,bottom - transform.radius / 4,white, true);

	//DrawTriangle(left, transform.pos.y, left, bottom, transform.pos.x, bottom, green, true);
}