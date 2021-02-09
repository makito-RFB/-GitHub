#include <iostream>
#include <DxLib.h>
#include "music.hpp"

BOOL MUSIC::RoadMusic(MUSIC& obj, const char* name)
{
	strcpy_s(obj.path, name);
	obj.handle = LoadSoundMem(obj.path);
	if (obj.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), name, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
}

//strcpy_s(BGM.path, MUSIC_BGM_PATH);
	//BGM.handle = LoadSoundMem(BGM.path);
	//if (BGM.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
//strcpy_s(musicShot.path, MUSIC_PLAYER_SHOT_PATH);
//musicShot.handle = LoadSoundMem(musicShot.path);
//if (musicShot.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);
//BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);
//if (BGM_TITLE.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);
//BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);
//if (BGM_COMP.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);
//BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);
//if (BGM_FAIL.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(BGM_RANKING.path, MUSIC_BGM_RANK_PATH);
//BGM_RANKING.handle = LoadSoundMem(BGM_RANKING.path);
//if (BGM_RANKING.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(se_clock.path, MUSIC_BGM_RANK_PATH);
//se_clock.handle = LoadSoundMem(se_clock.path);
//if (se_clock.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(se_coin_g.path, MUSIC_BGM_RANK_PATH);
//se_coin_g.handle = LoadSoundMem(se_coin_g.path);
//if (se_coin_g.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(se_breke.path, MUSIC_BGM_RANK_PATH);
//se_breke.handle = LoadSoundMem(se_breke.path);
//if (se_breke.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(se_rogo_draw.path, MUSIC_BGM_RANK_PATH);
//se_rogo_draw.handle = LoadSoundMem(se_rogo_draw.path);
//if (se_rogo_draw.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(se_rain.path, MUSIC_BGM_RANK_PATH);
//se_rain.handle = LoadSoundMem(se_rain.path);
//if (se_rain.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
//
//strcpy_s(se_scene_sen.path, MUSIC_BGM_RANK_PATH);
//se_scene_sen.handle = LoadSoundMem(se_scene_sen.path);
//if (se_scene_sen.handle == -1)
//{
//	MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
//	return FALSE;
//}
