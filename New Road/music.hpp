#ifndef MUSIC_HPP_DEFINED_
#define MUSIC_HPP_DEFINED_


#define MUSIC_BGM_PATH			TEXT(".\\MUSIC\\Taste_Hell.mp3")
#define MUSIC_PLAYER_SHOT_PATH	TEXT(".\\MUSIC\\se_pikon23.mp3")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\荒涼の地.mp3")	//タイトルのBGM
#define MUSIC_BGM_COMP_PATH		TEXT(".\\MUSIC\\Yours.mp3")				//コンプリートBGM
#define MUSIC_BGM_FAIL_PATH		TEXT(".\\MUSIC\\Yours.mp3")					//フォールトBGM
#define MUSIC_BGM_RANK_PATH		TEXT(".\\MUSIC\\深淵に眠るクトーニアン.mp3")//ランキングBGM

#define MUSIC_CLOCK_BGM_PATH			TEXT(".\\MUSIC\\se_clock.mp3")			//時計
#define MUSIC_COIN_BGM_PATH				TEXT(".\\MUSIC\\se_coin_get1.mp3")		//コインゲットしたとき
#define MUSIC_BRAKE_BGM_PATH			TEXT(".\\MUSIC\\se_gareki01.mp3")		//障害物破壊
#define MUSIC_STRAT_ROGO_BGM_PATH		TEXT(".\\MUSIC\\se_nanika01.mp3")		//何かが出る感じの音
#define MUSIC_RANI_BGM_PATH				TEXT(".\\MUSIC\\se_rain2_loop.mp3")		//雨
#define MUSIC_SCEN_SEN_BGM_PATH			TEXT(".\\MUSIC\\se_scene_seni02.mp3")	//シーン遷移
#define MUSIC_MOVE_BGM_PATH				TEXT(".\\MUSIC\\se_chakuchi03.mp3") 	//移動音
#define MUSIC_PACHIN_BGM_PATH			TEXT(".\\MUSIC\\crrect_answer3.mp3") 	//ランキング消去音



#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define PATH_MAX	255
#define NAME_MAX	255


class MUSIC
{
public:
	char path[PATH_MAX];
	int handle;
	BOOL RoadMusic(MUSIC&, const char*);
};

#endif //MUSIC_HPP_DEFINED_
