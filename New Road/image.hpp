#ifndef IMAGE_HPP_DEFINED_
#define IMAGE_HPP_DEFINED_

#include<iostream>

#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

#define GAME_WIDTH     960
#define GAME_HEIGHT    576

#define IMAGE_CHAR_NUM			12	
#define WORK_CHAR_NUM			3	
#define CHAR_DIV_TATE		3
#define CHAR_DIV_YOKO		4

#define MAP_DIV_WIDTH		64
#define MAP_DIV_HEIGHT		64

#define IMAGE_TITLE_WORK_CNT   1
#define IMAGE_TITLE_WORK_CNT_MAX   20

#define MAP_DIV_TATE		10
#define MAP_DIV_YOKO		4
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO

#define GAME_MAP_KAKU_YOKO_MAX	30	//�g���}�b�v�̉��̐�
#define GAME_MAP_KIND_MAX	2	//�}�b�v�̎�ނ̐�


#define GAME_MAP_TATE_MAX	9	//�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX	18	//�}�b�v�̉��̐�

#define PATH_MAX	255
#define NAME_MAX	255



#define IMAGE_TITLE_BK_PATH		TEXT(".\\IMAGE\\STRAT_IMG\\strat�w�i.png")		//stratScene�w�i--------
#define IMAGE_TITLE_ROGO_PATH	TEXT(".\\IMAGE\\STRAT_IMG\\rogo2.png")			//���S
#define IMAGE_TITLE_START_PATH	TEXT(".\\IMAGE\\STRAT_IMG\\GAME_start.png")		//�Q�[���n�߂�摜
#define IMAGE_TITLE_RNK	TEXT(".\\IMAGE\\STRAT_IMG\\ranking.png")				//�����L���O�s���摜
#define IMAGE_TITLE_CHI	TEXT(".\\IMAGE\\STRAT_IMG\\Choies.png")					//�I�����w���摜

#define IMAGE_EXPO_BACK TEXT(".\\IMAGE\\EXPO_IMG\\�����w�i.png")	//ExpoScene�w�i--------
#define IMAGE_EX_NEWS1 TEXT(".\\IMAGE\\EXPO_IMG\\���[��.png")		//����1���ڂ̉摜
#define IMAGE_EX_NEWS2 TEXT(".\\IMAGE\\EXPO_IMG\\����.png")			//����2����

#define IMAGE_BACK_PATH       TEXT(".\\IMAGE\\PLAY_IMG\\�w�i1.png")		//playScene�w�i--------
#define IMAGE_SHADOW_PATH       TEXT(".\\IMAGE\\PLAY_IMG\\����.png")	//���ɕt����e

#define IMAGE_BACK_ENDC_PATH	  TEXT(".\\IMAGE\\END_IMG\\�w�iCONP.png")	//endScene�w�i--------
#define IMAGE_BACK_ENDF_PATH	  TEXT(".\\IMAGE\\END_IMG\\�w�iFALL.png")	//��ɓ���
#define IMAGE_END_FAIL_PATH			TEXT(".\\IMAGE\\END_IMG\\���s.png")		//���s���S
#define IMAGE_END_WITHDRAWAL_PATH	TEXT(".\\IMAGE\\END_IMG\\�E�o.png")		//�E�o���S

#define IMAGE_RNK_BACK TEXT(".\\IMAGE\\RANKING_IMG\\RNK�w�i.png")			//RankingScene�w�i--------
#define IMAGE_RNK_BACK_NONE TEXT(".\\IMAGE\\RANKING_IMG\\RNK�w�inone.png")	//���̏Ɩ��Ȃ��Ŕw�i
#define IMAGE_RNK_SHADOW TEXT(".\\IMAGE\\RANKING_IMG\\RNKkage.png")			//���p�̍őO�ʂ̉e

#define IMAGE_STOP_BACK TEXT(".\\IMAGE\\STOP_IMG\\stop�w�i.png")			//stopScene�w�i--------
#define IMAGE_ST_E_ROGO_PATH	TEXT(".\\IMAGE\\STOP_IMG\\End_Game.png")	//�Q�[������߂�摜
#define IMAGE_ST_B_ROGO_PATH	TEXT(".\\IMAGE\\STOP_IMG\\Back_Game.png")	//�Q�[���ɖ߂�摜

#define IMAGE_END_ROGO_PATH	TEXT(".\\IMAGE\\ENRE.png")					//�^�C�g���ɖ߂郍�S
#define IMAGE_NEXT_ROGO_PATH	TEXT(".\\IMAGE\\NEXT.png")				//�^�C�g���ɖ߂郍�S


#define IMAGE_CHAR_PATH       TEXT(".\\IMAGE\\PLAYER_IMG\\player.png")	//�v���C���[�i12�����j
#define IMAGE_CHAR2_PATH       TEXT(".\\IMAGE\\PLAYER_IMG\\player2.png")	//�v���C���[�i12�����j

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")			//�}�b�v

//
//enum GAME_MAP_KIND
//{
//	n = -1,	//(NONE)����
//	k = 0,	//��
//	m = 1,  //�ǂQ
//	r = 2,  //�ǂR
//	l = 4,  //������
//	t = 9,	//�ʘH
//	s = 5,	//�X�^�[�g
//	c = 6,  //�R�C��
//	g = 3	//�A�C�e��
//};
//
//typedef struct STRUCT_IMAGE
//{
//	char path[PATH_MAX];
//	int handle;
//	int handle2[IMAGE_CHAR_NUM];
//	int x;
//	int y;
//	int width;
//	int height;
//}IMAGE;
//
//
//typedef struct STRUCT_CHARA
//{
//	IMAGE image;
//	int speed;
//	int CenterX;
//	int CenterY;
//
//
//
//	RECT coll;
//	iPOINT collBeforePt;
//
//}CHARA;
//
//
//typedef struct STRUCT_IMAGE_BACK
//{
//	IMAGE image;
//	BOOL IsDraw;
//}IMAGE_BACK;
//
//typedef struct STRUCT_IMAGE_ROTA
//{
//	IMAGE image;
//
//}IMAGE_ROTA;
//
//typedef struct STRUCT_IMAGE_WORK
//{
//	IMAGE image;
//	int Cnt;
//	int CntMAX;
//	BOOL IsDraw;
//
//}IMAGE_WORK;
//
//typedef struct STRUCT_IMAGE_BLINK
//{
//	IMAGE image;
//	BOOL IsDraw;
//	double rate;
//	double angle;
//}IMAGE_BLINK;
//
//typedef struct STRUCT_MAP_IMAGE
//{
//	char path[PATH_MAX];
//	int handle[MAP_DIV_NUM];
//	int kind[MAP_DIV_NUM];
//	int width;
//	int height;
//}MAPCHIP;
//
//typedef struct STRUCT_MAP
//{
//	GAME_MAP_KIND kind;
//	int x;
//	int y;
//	int width;
//	int height;
//	BOOL IsDraw;
//}MAP;
//
//IMAGE_BACK ImageBack;
//IMAGE_BACK ImageBackEND;
//IMAGE_BACK ImageBackENDF;
//IMAGE_BACK ImageShadow;
//
//IMAGE ImageTitleBK;
//IMAGE RNKBACK;
//IMAGE RNKBACKNone;
//IMAGE RNKShadow;
//IMAGE stopBack;
//
//IMAGE_ROTA ImageTitleROGO;
//
//IMAGE_BLINK ImageSTeROGO;
//IMAGE_BLINK ImageSTbROGO;
//
//IMAGE_BLINK ImageTitleSTART;
//IMAGE_BLINK ImageTitleRNK;
//
//IMAGE ImageEXPOBK;
//
//IMAGE_BACK ImageExNews1;
//IMAGE_BACK ImageExNews2;
//
//IMAGE_BACK ImageEndFAIL;
//IMAGE_BACK ImageEndWD;
//
//IMAGE_BLINK ImageNextROGO;
//IMAGE_BLINK ImageEndROGO;
//IMAGE ImageChoiser;
//
//IMAGE_WORK ImageWork;
//
//IMAGE_WORK ImageChar[IMAGE_CHAR_NUM];
//
//CHARA playerSt;
//CHARA player;
//
//GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{ //3�u���b�N�Â�
//	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,
//		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
//		k,t,t,t,l,t,t,l,t,t,l,k,t,t,l,k,t,t,	// 1
//		k,t,t,l,t,l,t,l,t,k,t,t,l,t,t,t,l,t,	// 2
//		k,l,t,t,t,k,t,k,t,c,l,t,l,t,l,t,l,t,	// 3
//		k,t,t,l,t,k,s,k,l,k,l,l,k,t,c,l,k,t,	// 4
//		k,l,l,t,l,t,t,k,t,t,l,t,k,t,l,t,k,t,	// 5
//		k,t,c,k,t,l,t,k,l,t,g,t,k,g,g,t,k,g,	// 6
//		k,t,t,k,t,k,t,l,t,t,l,t,t,t,l,t,t,t,	// 7
//		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,	// 8
//
//};
//
////�}�b�v�������p�̃o�b�N�A�b�v
//GAME_MAP_KIND mapDataPR[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
//	//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7
//		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
//		k,t,t,t,l,t,t,l,t,t,l,k,t,t,l,k,t,t,	// 1
//		k,t,t,l,t,l,t,l,t,k,t,t,l,t,t,t,l,t,	// 2
//		k,l,t,t,t,k,t,k,t,c,l,t,l,t,l,t,l,t,	// 3
//		k,t,t,l,t,k,s,k,l,k,l,l,k,t,c,l,k,t,	// 4
//		k,l,l,t,l,t,t,k,t,t,l,t,k,t,l,t,k,t,	// 5
//		k,t,c,k,t,l,t,k,l,t,g,t,k,g,g,t,k,g,	// 6
//		k,t,t,k,t,k,t,l,t,t,l,t,t,t,l,t,t,t,	// 7
//		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,	// 8
//
//};
//
//GAME_MAP_KIND mapDataNEW[GAME_MAP_TATE_MAX][GAME_MAP_KAKU_YOKO_MAX]{ //3�u���b�N�Â�
//	//  0,1,2,3,4,5,6,7,8,9,1,1,2,3,4,5,6,7,8,9,2,1,2,3,4,5,6,7,8,9
//		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
//		k,t,t,t,l,t,t,l,t,t,l,k,t,t,l,k,t,t,t,k,t,t,l,k,t,l,t,t,k,t,	// 1
//		t,t,t,l,t,l,k,l,l,k,t,t,l,l,t,t,l,l,k,t,k,t,c,l,t,k,l,t,t,l,	// 2
//		k,l,t,t,l,k,g,k,l,t,l,t,c,l,l,t,l,t,l,k,l,t,k,t,k,g,t,k,t,t,	// 3
//		l,t,k,t,k,t,l,t,t,k,l,t,k,t,t,k,k,t,t,l,t,t,t,k,t,k,t,g,t,k,	// 4
//		l,c,l,t,l,t,t,k,t,t,l,l,k,t,l,t,k,t,k,g,l,k,t,l,l,l,k,t,c,t,	// 5
//		t,k,t,k,t,l,c,k,l,t,k,t,k,g,k,t,k,g,t,l,k,l,g,k,t,l,t,t,k,t,	// 6
//		k,k,t,k,c,k,t,l,t,t,l,t,t,t,l,c,t,t,t,k,t,t,k,t,k,k,l,t,k,t,	// 7
//		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,
//};
//
//GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
//MAPCHIP mapChip;
//MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
//iPOINT startPt{ -1,-1 };
//RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];


//
//BOOL MY_LOAD_IMAGE(VOID)
//{
//	//�^�C�g���w�i
//	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
//	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
//	if (ImageTitleBK.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);
//	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;
//	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;
//
//	//�^�C�g�����S
//	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);
//	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);
//	if (ImageTitleROGO.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);
//	ImageTitleROGO.image.x = GAME_WIDTH / 2 - ImageTitleROGO.image.width / 2;
//	ImageTitleROGO.image.y = GAME_HEIGHT / 2 - ImageTitleROGO.image.height / 2;
//
//	//�^�C�g���X�^�[�g
//	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);
//	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);
//	if (ImageTitleSTART.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);
//	ImageTitleSTART.image.x = GAME_WIDTH / 2;
//	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + 32;
//	ImageTitleSTART.angle = 0;
//	ImageTitleSTART.rate = 1.0;
//
//	//�����L���O�I��
//	strcpy_s(ImageTitleRNK.image.path, IMAGE_TITLE_RNK);
//	ImageTitleRNK.image.handle = LoadGraph(ImageTitleRNK.image.path);
//	if (ImageTitleRNK.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_RNK, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageTitleRNK.image.handle, &ImageTitleRNK.image.width, &ImageTitleRNK.image.height);
//	ImageTitleRNK.image.x = GAME_WIDTH / 2;
//	ImageTitleRNK.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + ImageTitleSTART.image.height + 40;
//	ImageTitleRNK.angle = 0;
//	ImageTitleRNK.rate = 1.0;
//
//	//�Q�[����߂郍�S
//	strcpy_s(ImageSTeROGO.image.path, IMAGE_ST_E_ROGO_PATH);
//	ImageSTeROGO.image.handle = LoadGraph(ImageSTeROGO.image.path);
//	if (ImageSTeROGO.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_ST_E_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageSTeROGO.image.handle, &ImageSTeROGO.image.width, &ImageSTeROGO.image.height);
//	ImageSTeROGO.image.x = GAME_WIDTH / 2;
//	ImageSTeROGO.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + 32;
//	ImageSTeROGO.angle = 0;
//	ImageSTeROGO.rate = 1.0;
//	//�Q�[���߂郍�S
//	strcpy_s(ImageSTbROGO.image.path, IMAGE_ST_B_ROGO_PATH);
//	ImageSTbROGO.image.handle = LoadGraph(ImageSTbROGO.image.path);
//	if (ImageSTbROGO.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_ST_B_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageSTbROGO.image.handle, &ImageSTbROGO.image.width, &ImageSTbROGO.image.height);
//	ImageSTbROGO.image.x = GAME_WIDTH / 2;
//	ImageSTbROGO.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + ImageTitleSTART.image.height + 40;
//	ImageSTbROGO.angle = 0;
//	ImageSTbROGO.rate = 1.0;
//
//	//�I����
//	strcpy_s(ImageChoiser.path, IMAGE_TITLE_CHI);
//	ImageChoiser.handle = LoadGraph(ImageChoiser.path);
//	if (ImageChoiser.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_CHI, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageChoiser.handle, &ImageChoiser.width, &ImageChoiser.height);
//	ImageChoiser.x = ImageTitleSTART.image.x + ImageTitleSTART.image.width / 2 + 32;
//	ImageChoiser.y = ImageTitleSTART.image.y + ImageTitleSTART.image.height / 4 - ImageChoiser.height / 2;
//
//
//	//�Q�[������
//	strcpy_s(ImageEXPOBK.path, IMAGE_EXPO_BACK);
//	ImageEXPOBK.handle = LoadGraph(ImageEXPOBK.path);
//	if (ImageEXPOBK.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_EXPO_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageEXPOBK.handle, &ImageEXPOBK.width, &ImageEXPOBK.height);
//	ImageEXPOBK.x = GAME_WIDTH / 2 - ImageEXPOBK.width / 2;
//	ImageEXPOBK.y = GAME_HEIGHT / 2 - ImageEXPOBK.height / 2;
//
//	//�����L���O�w�i
//	strcpy_s(RNKBACK.path, IMAGE_RNK_BACK);
//	RNKBACK.handle = LoadGraph(RNKBACK.path);
//	if (RNKBACK.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_RNK_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(RNKBACK.handle, &RNKBACK.width, &RNKBACK.height);
//	RNKBACK.x = GAME_WIDTH / 2 - RNKBACK.width / 2;
//	RNKBACK.y = GAME_HEIGHT / 2 - RNKBACK.height / 2;
//
//	//�����L���O�w�inone
//	strcpy_s(RNKBACKNone.path, IMAGE_RNK_BACK_NONE);
//	RNKBACKNone.handle = LoadGraph(RNKBACKNone.path);
//	if (RNKBACKNone.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_RNK_BACK_NONE, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(RNKBACKNone.handle, &RNKBACKNone.width, &RNKBACKNone.height);
//	RNKBACKNone.x = GAME_WIDTH / 2 - RNKBACKNone.width / 2;
//	RNKBACKNone.y = GAME_HEIGHT / 2 - RNKBACKNone.height / 2;
//
//
//	//�����L���O�w�i�ǉ��e
//	strcpy_s(RNKShadow.path, IMAGE_RNK_SHADOW);
//	RNKShadow.handle = LoadGraph(RNKShadow.path);
//	if (RNKShadow.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_RNK_SHADOW, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(RNKShadow.handle, &RNKShadow.width, &RNKShadow.height);
//	RNKShadow.x = GAME_WIDTH / 2 - RNKShadow.width / 2;
//	RNKShadow.y = GAME_HEIGHT / 2 - RNKShadow.height / 2;
//
//	//�X�g�b�v��ʔw�i
//	strcpy_s(stopBack.path, IMAGE_STOP_BACK);
//	stopBack.handle = LoadGraph(stopBack.path);
//	if (stopBack.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_STOP_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(stopBack.handle, &stopBack.width, &stopBack.height);
//	stopBack.x = GAME_WIDTH / 2 - stopBack.width / 2;
//	stopBack.y = GAME_HEIGHT / 2 - stopBack.height / 2;
//
//	//�L�����̐ݒ�
//	int charRes = LoadDivGraph(
//		IMAGE_CHAR_PATH,
//		IMAGE_CHAR_NUM, CHAR_DIV_TATE, CHAR_DIV_YOKO,
//		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
//		&player.image.handle2[0]);
//
//	if (charRes == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_CHAR_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	//�摜�̕��ƍ������擾
//	GetGraphSize(player.image.handle2[0], &player.image.width, &player.image.height);
//	ImageWork.Cnt = 0.0;
//	ImageWork.CntMAX = IMAGE_TITLE_WORK_CNT_MAX;
//	for (int imageCharNUM = 0; imageCharNUM < WORK_CHAR_NUM; imageCharNUM++)
//	{
//		ImageChar[imageCharNUM].IsDraw = FALSE;
//
//	}
//	playerSt.image.x = GAME_WIDTH / 2 - player.image.width / 2;	//���E��������
//	playerSt.image.y = GAME_HEIGHT - player.image.height;			//y�͌��_����
//
////�G���h�t�H�[��
//	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);
//	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);
//	if (ImageEndFAIL.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);
//	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;
//	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2 - 32;
//
//	//�G���h�P��
//	strcpy_s(ImageEndWD.image.path, IMAGE_END_WITHDRAWAL_PATH);
//	ImageEndWD.image.handle = LoadGraph(ImageEndWD.image.path);
//	if (ImageEndWD.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_END_WITHDRAWAL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageEndWD.image.handle, &ImageEndWD.image.width, &ImageEndWD.image.height);
//	ImageEndWD.image.x = GAME_WIDTH / 2 - ImageEndWD.image.width / 2;
//	ImageEndWD.image.y = GAME_HEIGHT / 2 - ImageEndWD.image.height / 2 - 32;
//
//	//�G�X�P�[�v�v�b�V��
//	strcpy_s(ImageEndROGO.image.path, IMAGE_END_ROGO_PATH);
//	ImageEndROGO.image.handle = LoadGraph(ImageEndROGO.image.path);
//	if (ImageEndROGO.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_END_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageEndROGO.image.handle, &ImageEndROGO.image.width, &ImageEndROGO.image.height);
//	ImageEndROGO.image.x = GAME_WIDTH - 70;
//	ImageEndROGO.image.y = GAME_HEIGHT - 50;
//	ImageEndROGO.angle = 0;
//	ImageEndROGO.rate = 1.0;
//
//	//NEXT PUSH
//	strcpy_s(ImageNextROGO.image.path, IMAGE_NEXT_ROGO_PATH);
//	ImageNextROGO.image.handle = LoadGraph(ImageNextROGO.image.path);
//	if (ImageNextROGO.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_NEXT_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageNextROGO.image.handle, &ImageNextROGO.image.width, &ImageNextROGO.image.height);
//	ImageNextROGO.image.x = GAME_WIDTH - 70;
//	ImageNextROGO.image.y = GAME_HEIGHT - 50;
//	ImageNextROGO.angle = 0;
//	ImageNextROGO.rate = 1.0;
//
//
//	//�w�i�摜
//	strcpy_s(ImageBack.image.path, IMAGE_BACK_PATH);
//	ImageBack.image.handle = LoadGraph(ImageBack.image.path);
//	if (ImageBack.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageBack.image.handle, &ImageBack.image.width, &ImageBack.image.height);
//	ImageBack.image.x = GAME_WIDTH / 2 - ImageBack.image.width / 2;
//	ImageBack.image.y = 0 - ImageBack.image.height * 0;
//	ImageBack.IsDraw = FALSE;
//
//	//shadow
//	strcpy_s(ImageShadow.image.path, IMAGE_SHADOW_PATH);
//	ImageShadow.image.handle = LoadGraph(ImageShadow.image.path);
//	if (ImageShadow.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_SHADOW_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageShadow.image.handle, &ImageShadow.image.width, &ImageShadow.image.height);
//	ImageShadow.image.x = GAME_WIDTH / 2 - ImageShadow.image.width / 2;
//	ImageShadow.image.y = 0 - ImageShadow.image.height * 0;
//	ImageShadow.IsDraw = FALSE;
//
//
//	//�w�i�摜END
//	strcpy_s(ImageBackEND.image.path, IMAGE_BACK_ENDC_PATH);
//	ImageBackEND.image.handle = LoadGraph(ImageBackEND.image.path);
//	if (ImageBackEND.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDC_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageBackEND.image.handle, &ImageBackEND.image.width, &ImageBackEND.image.height);
//	ImageBackEND.image.x = GAME_WIDTH / 2 - ImageBackEND.image.width / 2;
//	ImageBackEND.image.y = 0 - ImageBackEND.image.height * 0;
//	ImageBackEND.IsDraw = FALSE;
//
//	//�w�i�摜ENDF
//	strcpy_s(ImageBackENDF.image.path, IMAGE_BACK_ENDF_PATH);
//	ImageBackENDF.image.handle = LoadGraph(ImageBackENDF.image.path);
//	if (ImageBackENDF.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDF_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageBackENDF.image.handle, &ImageBackENDF.image.width, &ImageBackENDF.image.height);
//	ImageBackENDF.image.x = GAME_WIDTH / 2 - ImageBackENDF.image.width / 2;
//	ImageBackENDF.image.y = 0 - ImageBackENDF.image.height * 0;
//	ImageBackENDF.IsDraw = FALSE;
//
//
//	//�v���C���[�̉摜
//		//strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
//		//player.image.handle = LoadGraph(player.image.path);
//		//if (player.image.handle == -1)
//		//{
//		//	MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		//	return FALSE;
//		//}
//		//GetGraphSize(player.image.handle, &player.image.width, &player.image.height);
//	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;
//	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;
//	player.CenterX = player.image.x + player.image.width / 2;
//	player.CenterY = player.image.y + player.image.height / 2;
//	//player.speed = CHARA_SPEED_LOW;
//
////�����摜�P
//	strcpy_s(ImageExNews1.image.path, IMAGE_EX_NEWS1);
//	ImageExNews1.image.handle = LoadGraph(ImageExNews1.image.path);
//	if (ImageExNews1.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_EX_NEWS1, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageExNews1.image.handle, &ImageExNews1.image.width, &ImageExNews1.image.height);
//	ImageExNews1.image.x = MAP_DIV_WIDTH + (MAP_DIV_WIDTH / 4 - 2);
//	ImageExNews1.image.y = MAP_DIV_HEIGHT * 2 + (MAP_DIV_HEIGHT / 4 * 3 - 2);
//	ImageExNews1.IsDraw = FALSE;
//
//	//�����摜2
//	strcpy_s(ImageExNews2.image.path, IMAGE_EX_NEWS2);
//	ImageExNews2.image.handle = LoadGraph(ImageExNews2.image.path);
//	if (ImageExNews2.image.handle == -1)
//	{
//		MessageBox(GetMainWindowHandle(), IMAGE_EX_NEWS2, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//	GetGraphSize(ImageExNews2.image.handle, &ImageExNews2.image.width, &ImageExNews2.image.height);
//	ImageExNews2.image.x = MAP_DIV_WIDTH + (MAP_DIV_WIDTH / 4 - 2);
//	ImageExNews2.image.y = MAP_DIV_HEIGHT * 2 + (MAP_DIV_HEIGHT / 4 * 3 - 2);
//	ImageExNews2.IsDraw = FALSE;
//
//	//�}�b�v�̉摜�𕪊�����
//	int mapRes = LoadDivGraph(
//		GAME_MAP_PATH,
//		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
//		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
//		&mapChip.handle[0]);
//
//	if (mapRes == -1)
//	{
//		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
//		return FALSE;
//	}
//
//	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);
//
//	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
//	{
//		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
//		{
//			mapDataInit[tate][yoko] = mapData[tate][yoko];
//
//			map[tate][yoko].kind = mapData[tate][yoko];
//
//			map[tate][yoko].width = mapChip.width;
//			map[tate][yoko].height = mapChip.height;
//
//			map[tate][yoko].x = yoko * map[tate][yoko].width;
//			map[tate][yoko].y = tate * map[tate][yoko].height;
//		}
//	}
//
//	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
//	{
//		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
//		{
//			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
//			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
//			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
//			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
//		}
//	}
//
//	return TRUE;
//}
//
//VOID MY_DELETE_IMAGE(VOID)
//{
//
//	DeleteGraph(ImageBack.image.handle);
//	DeleteGraph(ImageShadow.image.handle);
//
//	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
//	{
//		DeleteGraph(ImageChar[0].image.handle);
//	}
//
//	DeleteGraph(player.image.handle);
//
//	DeleteGraph(ImageTitleBK.handle);
//	DeleteGraph(ImageEXPOBK.handle);
//	DeleteGraph(RNKBACK.handle);
//	DeleteGraph(RNKBACKNone.handle);
//	DeleteGraph(RNKShadow.handle);
//	DeleteGraph(stopBack.handle);
//	DeleteGraph(ImageTitleROGO.image.handle);
//	DeleteGraph(ImageTitleSTART.image.handle);
//	DeleteGraph(ImageTitleRNK.image.handle);
//	DeleteGraph(ImageSTeROGO.image.handle);
//	DeleteGraph(ImageSTbROGO.image.handle);
//	DeleteGraph(ImageEndFAIL.image.handle);
//	DeleteGraph(ImageEndWD.image.handle);
//	DeleteGraph(ImageEndROGO.image.handle);
//	DeleteGraph(ImageNextROGO.image.handle);
//	DeleteGraph(ImageChoiser.handle);
//	DeleteGraph(ImageExNews1.image.handle);
//	DeleteGraph(ImageExNews2.image.handle);
//
//
//	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }
//
//	return;
//}


#endif // !IMAGE_HPP_DEFINED_
