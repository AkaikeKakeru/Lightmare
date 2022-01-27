#include "Grobal.h"
#include "Struct.h"
#include "Stage.h"

#include "Object.h"

void MapSetting(int num ,
	Coordinate goal,
	Coordinate start,
	Coordinate mirror,
	Coordinate light)
{
	switch (num)
	{
	case 1:
				goal.x = 4;
				goal.y = 0;
				start.x = 0;
				start.y = 9;
				mirror.x = 4;
				mirror.y = 9;
				light.x = 9;
				light.y = 9;
		break;

	/*case 2:
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				map[0][8] = GOAL;
				map[0][0] = START;
				map[4][9] = MIRROR;
				map[4][8] = MIRROR;
				map[9][8] = LIGHT_SOURCE;
			}
		}
		break;*/
	default:
		break;
	}

	goal.x *= BLOCK_SIZE + BLOCK_SIZE/2;
	goal.y *= BLOCK_SIZE + BLOCK_SIZE/2;
	start.x *= BLOCK_SIZE + BLOCK_SIZE/2;
	start.y *= BLOCK_SIZE + BLOCK_SIZE/2;
	mirror.x *= BLOCK_SIZE + BLOCK_SIZE/2;
	mirror.y *= BLOCK_SIZE + BLOCK_SIZE/2;
	light.x *= BLOCK_SIZE + BLOCK_SIZE/2;
	light.y *= BLOCK_SIZE + BLOCK_SIZE/2;

	

};

