#include "rocketMapMove.hpp"

VOID ROCKETMAP(int mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX],)
{
	int plusYoko = 0;
	int newMapYoko = 0;
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_NEW; yoko++)
		{
			plusYoko = yoko + 3;
			//マップ移動更新
			mapData[tate][yoko] = mapData[tate][plusYoko];
			map[tate][yoko].kind = map[tate][plusYoko].kind;
		}
		for (int yoko = GAME_MAP_YOKO_NEW; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			newMapYoko = yoko - GAME_MAP_YOKO_NEW;
			mapData[tate][yoko] = mapDataNEW[tate][newMapYoko];
			map[tate][yoko].kind = mapDataNEW[tate][newMapYoko];
		}
	}
	return;
}