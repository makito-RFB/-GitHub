#ifndef MUSIC_HPP_DEFINED_
#define MUSIC_HPP_DEFINED_


#define MUSIC_BGM_PATH			TEXT(".\\MUSIC\\Taste_Hell.mp3")
#define MUSIC_PLAYER_SHOT_PATH	TEXT(".\\MUSIC\\se_pikon23.mp3")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\�r���̒n.mp3")	//�^�C�g����BGM
#define MUSIC_BGM_COMP_PATH		TEXT(".\\MUSIC\\Yours.mp3")				//�R���v���[�gBGM
#define MUSIC_BGM_FAIL_PATH		TEXT(".\\MUSIC\\Yours.mp3")					//�t�H�[���gBGM
#define MUSIC_BGM_RANK_PATH		TEXT(".\\MUSIC\\�[���ɖ���N�g�[�j�A��.mp3")//�����L���OBGM

#define MUSIC_CLOCK_BGM_PATH			TEXT(".\\MUSIC\\se_clock.mp3")			//���v
#define MUSIC_COIN_BGM_PATH				TEXT(".\\MUSIC\\se_coin_get1.mp3")		//�R�C���Q�b�g�����Ƃ�
#define MUSIC_BRAKE_BGM_PATH			TEXT(".\\MUSIC\\se_gareki01.mp3")		//��Q���j��
#define MUSIC_STRAT_ROGO_BGM_PATH		TEXT(".\\MUSIC\\se_nanika01.mp3")		//�������o�銴���̉�
#define MUSIC_RANI_BGM_PATH				TEXT(".\\MUSIC\\se_rain2_loop.mp3")		//�J
#define MUSIC_SCEN_SEN_BGM_PATH			TEXT(".\\MUSIC\\se_scene_seni02.mp3")	//�V�[���J��
#define MUSIC_MOVE_BGM_PATH				TEXT(".\\MUSIC\\se_chakuchi03.mp3") 	//�ړ���
#define MUSIC_PACHIN_BGM_PATH			TEXT(".\\MUSIC\\crrect_answer3.mp3") 	//�����L���O������



#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

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
