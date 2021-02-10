#include "DxLib.h"
#include "resource.h"
#include "RnkingRW.hpp"
#include "image.hpp"
#include "score.hpp"
#include "setText.hpp"
#include "music.hpp"
#include <random>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define GAME_WIDTH     960
#define GAME_HEIGHT    576
#define GAME_COLOR	   32

#define GAME_WINDOW_BAR		0
#define GAME_WINDOW_NAME	"New Road"

#define GAME_FPS	60

#define MOUSE_BUTTON_CODE	129

#define PATH_MAX	255
#define NAME_MAX	255

#define FONT_TANU_PATH    TEXT(".\\FONT\\TanukiMagic.ttf")
#define FONT_TANU_NAME    TEXT("���ʂ������}�W�b�N")	
#define FONT_GEN_PATH    TEXT(".\\FONT\\doheta_j.ttf")
#define FONT_GEN_NAME    TEXT("�h�w�^�� J")	


#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

#define IMAGE_CHAR_NUM			12	
#define WORK_CHAR_NUM			3	
#define CHAR_DIV_TATE		3
#define CHAR_DIV_YOKO		4

#define CHAR_DREC_NUM		4

#define VARNCE_CHAR  GAME_FPS * 0.15 //�b
#define TANKA_CHAR	GAME_FPS * 0.3 //�b

#define CHAR_BAG_NUM		3 //�L�����N�^�[�̃o�b�N�̗e��

#define IMAGE_TITLE_WORK_CNT   1
#define IMAGE_TITLE_WORK_CNT_MAX   20

#define SCROLL_SPEED	1
#define SPEED_UP_CNT	5
#define SPEED_UP_TIME	3
#define UP_SPEED		2

#define GAME_MAP_TATE_MAX	9	//�}�b�v�̏c�̐�
#define GAME_MAP_YOKO_MAX	18	//�}�b�v�̉��̐�
#define GAME_MAP_KAKU_YOKO_MAX	30	//�g���}�b�v�̉��̐�
#define GAME_MAP_KIND_MAX	2	//�}�b�v�̎�ނ̐�

#define GAME_MAP_YOKO_NEW	15	//�}�b�v�̍X�V���̐�

#define MAP_DIV_WIDTH		64
#define MAP_DIV_HEIGHT		64
#define MAP_DIV_TATE		10
#define MAP_DIV_YOKO		4
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO

#define MOVE_ERIA 64

#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

#define GOAL_ERR_TITLE		TEXT("�S�[���ʒu�G���[")
#define GOAL_ERR_CAPTION	TEXT("�S�[���ʒu�����܂��Ă��܂���")

#define FILE_OPEN_TITLE		TEXT("�t�@�C���I�[�v���G���[")
#define FILE_OPEN_CAPTION	TEXT("�t�@�C���I�[�v���G���[")
#define FILE_RNK_PATH		TEXT("rnkingFile.txt")


#define GOAL1  TEXT("�Q�[���ڕW�ƃ��[��")
#define GOAL2  TEXT("��������ƃA�C�e���ɂ�����")
#define GOAL3  TEXT("�L�����I��")

#define STATUSTEMP		TEXT("���O�@�@�F\n�^�C�v�@�F\n�X�s�[�h�F\n�o�b�O�@�F")
#define STATUS1		TEXT("�A���X\n�o�����X\n������\n��")
#define STATUS2		TEXT("���b�L�[\n�^���N\n��\n������")
#define CHARA_ARROW TEXT("�\���L�[\n���@�@��")
#define CHARBIGSIZE	1.5
#define CHARRESIZE	1

#define FILE_NUM	5
#define CHECKEMPTY  1

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)����
	k = 0,	//��
	m = 1,  //�ǂQ
	r = 2,  //�ǂR
	l = 4,  //������
	t = 9,	//�ʘH
	s = 5,	//�X�^�[�g
	c = 6,  //�R�C��
	g = 3	//�A�C�e��
};	

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_EXPO,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_RNKING,
	GAME_SCENE_STOP,
};

enum GAME_END {
	GAME_END_EXIT,
	GAME_END_FAIL
};

enum CHARA_TYPE_SET {
	CHARA_BALANCE,
	CHARA_TANK,
};

//enum CHARA_RELOAD {
//	CHARA_RELOAD_LOW = 60,
//	CHARA_RELOAD_MIDI = 30,
//	CHARA_RELOAD_HIGH = 15
//};



//typedef struct STRUCT_MOUSE
//{
//	int InputValue = 0;	
//	iPOINT Point;		//�}�E�X�̍��W������
//	iPOINT OldPoint;	//�}�E�X�̍��W(���O)������
//	int OldButton[MOUSE_BUTTON_CODE] = { 0 };
//	int Button[MOUSE_BUTTON_CODE] = { 0 };
//}MOUSE;

typedef struct STRUCT_FONT
{
	char path[PATH_MAX];
	char name[NAME_MAX];
	int handle;
	int size;
	int bold;
	int type;
}FONT;

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];
	int handle[MAP_DIV_NUM];
	int kind[MAP_DIV_NUM];
	int width;
	int height;
}MAPCHIP;

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;
	int x;
	int y;
	int width;
	int height;
	BOOL IsDraw;
}MAP;


int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;

int newX = 0, newY = 0; //�������u���b�N�̍��W

//�v���C��ʊ֌W
int waitCnt = 0;
int gameSpeed = SCROLL_SPEED;
int MAPmoveCnt = 0;
int speedUpTime = 0;

//�X�^�[�g��ʊ֌W
int DrCharCnt = 0;

char AllKeyState[256] = { '\0' };
char OldAllKeyState[256] = { '\0' };

//�L�����N�^�[�֌W
char direc; //�����̂��
int driecChar = 2;
int PlayChar = 0;
int cooltimeType = 0; 

//�}�b�v�̃X�s�[�h�A�b�v�ƌ덷�t���O
bool speedUPflg = false;
bool diffMarginFlg = false;

//�^�C�}�[�X�R�A�֌W
int ITEMCnt = 0, COINCnt = 0;
int timeCnt = 0;
int mintime = 0;
float secondtime = 0.0f;
float Score = 0.0f;
int ScoreDrawCnt = 0;
bool BackBtnIsDraw =false;

//�X�R�A�z��
std::vector<float> fsArry(5);

//�Q�[�������̕����z��ƃt���O�Ȃ�
std::vector<std::string> textGaol, charstatus;
int ExDrawCnt = 1;
//bool textIsRoad = true;

//�X�g�b�v�t���O
bool StopFlg = false;

//2���̐V�����}�b�v�����݂ɓǂނ��߂̃t���O
bool MAPChoice = true;

FONT FontTanu32;
FONT FontGen32;

int GameScene;
int GameEndKind;

RECT itemRect = { -1,-1, -1, -1 };

BOOL MY_KEY_TF = TRUE;
BOOL Kchoice = TRUE;
BOOL MY_CHAR_MOVE_ST = TRUE;
BOOL MY_MAP_RELOAD = TRUE;
BOOL FALL_RESON = FALSE;
BOOL CLICK_M = TRUE;
BOOL RANKINGflag = TRUE;

BOOL COINflag = FALSE;

BOOL IsReMove = FALSE;

//FILE* fp = NULL, * fp2 = NULL;
//errno_t error, error2;

IMG ImageBack;
IMG ImageBackEND;
IMG ImageBackENDF;
IMG ImageShadow;

IMG ImageTitleBK;
IMG RNKBACK;
IMG RNKBACKNone;
IMG RNKShadow;
IMG stopBack;

IMG ImageTitleROGO;

IMG_BLINK ImageSTeROGO;
IMG_BLINK ImageSTbROGO;

IMG_BLINK ImageTitleSTART;
IMG_BLINK ImageTitleRNK;

IMG ImageEXPOBK;

IMG ImageExNews1;
IMG ImageExNews2;

IMG ImageEndFAIL;
IMG ImageEndWD;

IMG_BLINK ImageNextROGO;
IMG_BLINK ImageEndROGO;
IMG ImageChoiser;

IMG_CHAR ImageWork;

IMG_CHAR ImageChar[IMAGE_CHAR_NUM];

IMG_CHAR playerSt;
IMG_CHAR player;
IMG_CHAR player2;


MUSIC BGM;

MUSIC BGM_TITLE;
MUSIC BGM_COMP;
MUSIC BGM_FAIL;
MUSIC BGM_RANKING;
MUSIC musicShot;

MUSIC se_clock;
MUSIC se_coin_g;
MUSIC se_brake;
MUSIC se_rogo_draw;
MUSIC se_rain;
MUSIC se_scene_sen;
MUSIC se_move;
MUSIC se_pachin;


GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{ //3�u���b�N�Â�
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,
		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
		k,t,t,t,l,t,t,l,t,t,l,k,t,t,l,k,t,t,	// 1
		k,t,t,l,t,l,t,l,t,k,t,t,l,t,t,t,l,t,	// 2
		k,l,t,t,t,k,t,k,t,c,l,t,l,t,l,t,l,t,	// 3
		k,t,t,l,t,k,s,k,l,k,l,l,k,t,c,l,k,t,	// 4
		k,l,l,t,l,t,t,k,t,t,l,t,k,t,l,t,k,t,	// 5
		k,t,c,k,t,l,t,k,l,t,g,t,k,g,g,t,k,g,	// 6
		k,t,t,k,t,k,t,l,t,t,l,t,t,t,l,t,t,t,	// 7
		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,	// 8

};

//�}�b�v�������p�̃o�b�N�A�b�v
GAME_MAP_KIND mapDataPR[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7
		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
		k,t,t,t,l,t,t,l,t,t,l,k,t,t,l,k,t,t,	// 1
		k,t,t,l,t,l,t,l,t,k,t,t,l,t,t,t,l,t,	// 2
		k,l,t,t,t,k,t,k,t,c,l,t,l,t,l,t,l,t,	// 3
		k,t,t,l,t,k,s,k,l,k,l,l,k,t,c,l,k,t,	// 4
		k,l,l,t,l,t,t,k,t,t,l,t,k,t,l,t,k,t,	// 5
		k,t,c,k,t,l,t,k,l,t,g,t,k,g,g,t,k,g,	// 6
		k,t,t,k,t,k,t,l,t,t,l,t,t,t,l,t,t,t,	// 7
		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,	// 8

};

GAME_MAP_KIND mapDataNEW[GAME_MAP_TATE_MAX][GAME_MAP_KAKU_YOKO_MAX]{ //3�u���b�N�Â�
	//  0,1,2,3,4,5,6,7,8,9,1,1,2,3,4,5,6,7,8,9,2,1,2,3,4,5,6,7,8,9
		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
		k,t,t,k,t,l,t,l,t,t,l,k,t,t,l,k,t,t,t,k,t,t,l,k,t,l,t,t,k,t,	// 1
		t,t,t,l,t,l,k,l,l,k,t,t,l,l,t,t,g,l,k,t,k,t,c,l,t,k,l,t,t,l,	// 2
		k,l,t,t,l,k,g,k,l,t,l,t,c,l,l,t,l,t,l,k,l,t,k,t,k,g,t,k,t,t,	// 3
		l,t,k,l,k,t,l,t,t,k,l,t,k,t,t,k,k,t,t,l,t,t,t,k,t,k,t,g,t,k,	// 4
		l,c,l,t,l,t,t,k,t,t,l,l,k,t,l,t,k,t,k,g,l,k,t,l,l,l,k,t,c,t,	// 5
		t,k,t,k,t,l,c,k,l,t,k,t,k,g,k,t,k,t,t,l,k,l,k,k,t,l,t,t,k,t,	// 6
		k,k,t,k,c,k,t,l,t,t,l,t,t,t,l,c,t,t,t,k,t,t,g,t,k,k,l,t,k,t,	// 7
		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,
};

GAME_MAP_KIND mapDataNEW2[GAME_MAP_TATE_MAX][GAME_MAP_KAKU_YOKO_MAX]{ //3�u���b�N�Â�
	//  0,1,2,3,4,5,6,7,8,9,1,1,2,3,4,5,6,7,8,9,2,1,2,3,4,5,6,7,8,9
		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
		l,k,t,t,l,t,t,l,k,t,t,l,k,t,c,k,t,l,k,t,l,t,g,t,t,l,t,t,k,t,	// 1
		t,t,l,k,t,l,k,l,l,t,k,t,c,k,t,l,k,l,l,t,t,k,k,t,k,l,k,l,t,t,	// 2
		k,l,t,t,l,k,g,k,l,l,t,l,t,l,t,k,t,l,t,k,l,l,k,k,t,t,k,g,t,k,	// 3
		l,t,k,l,t,t,l,t,t,k,l,t,k,l,t,k,t,k,l,t,l,t,g,l,t,t,k,t,t,k,	// 4
		l,c,l,t,l,k,k,t,k,t,l,t,l,t,l,t,l,t,t,g,c,l,t,k,l,t,l,l,c,l,	// 5
		t,k,t,l,l,t,l,l,c,l,g,k,t,t,l,t,k,l,t,l,t,l,t,k,t,l,t,t,k,l,	// 6
		k,g,t,k,l,t,k,t,t,l,k,l,t,l,k,t,g,l,k,t,k,t,t,k,k,l,t,t,k,t,	// 7
		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,
};

GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAPCHIP mapChip;
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
iPOINT startPt{ -1,-1 };
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_WAIT(VOID);

VOID MY_ALL_KEYDOWN_UPDATE(VOID);
BOOL MY_KEY_DOWN(int);
BOOL MY_KEY_UP(int);
BOOL MY_KEYDOWN_KEEP(int, int);

//VOID MY_MOUSE_UPDATE(VOID);
//BOOL MY_MOUSE_DOWN(int);
//BOOL MY_MOUSE_UP(int);
//BOOL MY_MOUSEDOWN_KEEP(int, int);

BOOL MY_FONT_INSTALL_ONCE(VOID);
VOID MY_FONT_UNINSTALL_ONCE(VOID);
BOOL MY_FONT_CREATE(VOID);
VOID MY_FONT_DELETE(VOID);

VOID MY_START(VOID);
VOID MY_START_PROC(VOID);
VOID MY_START_DRAW(VOID);

VOID MY_EXPO(VOID);
VOID MY_EXPO_PROC(VOID);
VOID MY_EXPO_DRAW(VOID);

VOID MY_PLAY(VOID);
VOID MY_PLAY_PROC(VOID);
VOID MY_PLAY_DRAW(VOID);

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);
VOID MY_END_DRAW(VOID);

VOID MY_RNKING(VOID);
VOID MY_RNKING_PROC(VOID);
VOID MY_RNKING_DRAW(VOID);

VOID MY_STOP(VOID);
VOID MY_STOP_PROC(VOID);
VOID MY_STOP_DRAW(VOID);

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

BOOL MY_LOAD_MUSIC(VOID);
VOID MY_DELETE_MUSIC(VOID);

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

VOID MAP_LOAD(VOID);
VOID MAP_DRAW();
VOID ROCKETMAP(VOID);

CHAR MY_DIRECTION(double, double, double, double);

void TEXT_DRAW();

void CHAR_TYPE_SET();

VOID GAME_RULE(VOID);
VOID GAME_PILOT(VOID);
VOID GAME_STR(VOID);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));
	SetAlwaysRunFlag(TRUE);
	SetWindowIconID(IDI_ICON1);

	if (DxLib_Init() == -1) { return -1; }

	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	ChangeFont("�h�w�^�� J", DX_CHARSET_DEFAULT);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);

	SetMouseDispFlag(TRUE);

	GameScene = GAME_SCENE_START;

	SetDrawScreen(DX_SCREEN_BACK);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (mapData[tate][yoko] == s)
			{
				startPt.x = mapChip.width * yoko + mapChip.width / 2;
				startPt.y = mapChip.height * tate + mapChip.height / 2;
			}
		}
	}

	if (startPt.x == -1 && startPt.y == -1)
	{
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

//�����L���O�ǂ݂��݃����L���O�z��Ɋi�[
	R_WRITE ranking;
	ranking.Rread(fsArry);

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();

		//MY_MOUSE_UPDATE();

		MY_FPS_UPDATE();

		switch (GameScene)
		{
		case GAME_SCENE_START:	//�X�^�[�g���
			MY_START();
			break;
		case GAME_SCENE_EXPO:	//�������
			MY_EXPO();
			break;
		case GAME_SCENE_PLAY:	//�v���C���
			MY_PLAY();
			break;
		case GAME_SCENE_END:	//�G���h���
			MY_END();
			break;
		case GAME_SCENE_RNKING:	//�����L���O�\�����
			MY_RNKING();
			break;
		case GAME_SCENE_STOP:	//�v���C���̒�~���
			MY_STOP();
			break;
		}

		ScreenFlip();

		MY_FPS_WAIT();
	}

	MY_FONT_DELETE();

	MY_FONT_UNINSTALL_ONCE();

	MY_DELETE_IMAGE();

	MY_DELETE_MUSIC();

	DxLib_End();

	return 0;
}

VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) 
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps)
	{
		int now = GetNowCount();
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;

	if (waitTime > 0)
	{
		WaitTimer(waitTime);
	}
	return;
}

VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];

	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}
	GetHitKeyStateAll(TempKey);

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)
		{
			AllKeyState[i]++;
		}
		else
		{
			AllKeyState[i] = 0;	
		}
	}
	return;
}

BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1
		&& AllKeyState[KEY_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{

	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//VOID MY_MOUSE_UPDATE(VOID)
//{
//	mouse.OldPoint = mouse.Point;
//
//	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }
//
//	GetMousePoint(&mouse.Point.x, &mouse.Point.y);
//
//	mouse.InputValue = GetMouseInput();
//
//	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }
//	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }
//
//	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }
//	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }
//
//	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }
//	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }
//
//	return;
//}
//BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
//{
//	if (mouse.Button[MOUSE_INPUT_] != 0)
//	{
//		return TRUE;
//	}
//	else
//	{
//		return FALSE;
//	}
//}
//
//BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
//{
//	if (mouse.OldButton[MOUSE_INPUT_] >= 1
//		&& mouse.Button[MOUSE_INPUT_] == 0)
//	{
//		return TRUE;
//	}
//	else
//	{
//		return FALSE;
//	}
//}
//BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
//{
//	int UpdateTime = DownTime * GAME_FPS;
//
//	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
//	{
//		return TRUE;
//	}
//	else
//	{
//		return FALSE;
//	}
//}

BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}
	if (AddFontResourceEx(FONT_GEN_PATH, FR_PRIVATE, NULL) == 0)
	{
		MessageBox(GetMainWindowHandle(), FONT_GEN_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);
	RemoveFontResourceEx(FONT_GEN_PATH, FR_PRIVATE, NULL);
	return;
}

BOOL MY_FONT_CREATE(VOID)
{
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);
	FontTanu32.handle = -1;
	FontTanu32.size = 32;
	FontTanu32.bold = 1;
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;

	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);

	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	strcpy_s(FontGen32.path, sizeof(FontGen32.path), FONT_GEN_PATH);
	strcpy_s(FontGen32.name, sizeof(FontGen32.name), FONT_GEN_NAME);
	FontGen32.handle = -1;
	FontGen32.size = 32;
	FontGen32.bold = 1;
	FontGen32.type = DX_FONTTYPE_ANTIALIASING_EDGE;

	FontGen32.handle = CreateFontToHandle(FontGen32.name, FontGen32.size, FontGen32.bold, FontGen32.type);

	if (FontGen32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_GEN_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	return TRUE;
}

VOID MY_FONT_DELETE(VOID)
{
	DeleteFontToHandle(FontTanu32.handle);
	DeleteFontToHandle(FontGen32.handle);

	return;
}

/*----------------------------------�X�^�[�g�V�[��------------------------------------------------------*/

VOID MY_START(VOID)
{
	MY_START_PROC();
	MY_START_DRAW();

	return;
}

VOID MY_START_PROC(VOID)
{
	static BOOL MusicPass = TRUE; 
	static BOOL check = TRUE;

	if (CheckSoundMem(BGM_TITLE.handle) == 0 && MusicPass == TRUE)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

// ����������
	if (ImageChar[1].IsDraw == FALSE && MY_CHAR_MOVE_ST == TRUE) {
		ImageChar[1].IsDraw = TRUE;
		DrCharCnt = 0;
		MY_CHAR_MOVE_ST = FALSE;
	}

	if (ImageWork.Cnt < ImageWork.CntMAX)
	{
		ImageWork.Cnt += IMAGE_TITLE_WORK_CNT;
	}
	else
	{
		if (ImageChar[1].IsDraw == TRUE)
		{
			ImageChar[1].IsDraw = FALSE;

			switch (DrCharCnt)
			{
			case 0:
				ImageChar[0].IsDraw = TRUE;
				DrCharCnt = 1;
				break;
			case 1:
				ImageChar[2].IsDraw = TRUE;
				DrCharCnt = 0;
				break;
			default:
				break;
			}
		}
		else if (ImageChar[0].IsDraw == TRUE || ImageChar[2].IsDraw == TRUE)//1
		{
			switch (DrCharCnt)
			{
			case 1:
				ImageChar[0].IsDraw = FALSE;
				break;

			case 0:
				ImageChar[2].IsDraw = FALSE;
				break;
			}
			ImageChar[1].IsDraw = TRUE;
		}


		playerSt.x += MOVE_ERIA / 4;

		if (playerSt.x > GAME_WIDTH) {
			playerSt.x -= GAME_WIDTH + player.width;
		}
		ImageWork.Cnt = 0;

	}

//�Q�[���X�^�[�gor�����L���O�I���L�[�ړ�����
	if (check == TRUE) {
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE || MY_KEY_DOWN(KEY_INPUT_UP) == TRUE) {
			Kchoice = !Kchoice;
			ChangeVolumeSoundMem(255 * 80 / 100, se_scene_sen.handle);
			PlaySoundMem(se_scene_sen.handle, DX_PLAYTYPE_BACK);
			check = FALSE;
		}
	}
	if (MY_KEY_UP(KEY_INPUT_DOWN) == TRUE || MY_KEY_UP(KEY_INPUT_UP) == TRUE)
		check = TRUE;

//�I������
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE)
	{
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
		/*	StopSoundMem(BGM_TITLE.handle);*/
			MusicPass = FALSE;
		}
		SetMouseDispFlag(FALSE);

		GameEndKind = GAME_END_FAIL;
	}

//�Q�[���X�^�[�g��
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE) {
		//GameScene = GAME_SCENE_PLAY;
		MusicPass = TRUE;
		CLICK_M = TRUE;

		//�^�C�}������
		timeCnt = 0;
		secondtime = 0;
		mintime = 0;
		DrCharCnt = 0;

		GameScene = GAME_SCENE_EXPO;

		MY_MAP_RELOAD = TRUE;
		return;
	}

//�����L���O��
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE && Kchoice == FALSE)
	{

		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
			MusicPass = FALSE;
		}
	}

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE && Kchoice == FALSE) {
		MusicPass = TRUE;
		Kchoice = TRUE;
		CLICK_M = TRUE;
		GameScene = GAME_SCENE_RNKING;
		return;
	}

//�I����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
	}

	
//�����L���O�������݌Ăяo���t���O
	if (!RANKINGflag)
	{
		RANKINGflag = TRUE;
	}

	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);

//���̃L�����N�^�[�`��
	for (int num = 0, Pnum = 0; num < WORK_CHAR_NUM; num++)
	{
		if (ImageChar[num].IsDraw == TRUE)
		{
			Pnum = num + 3;
			DrawGraph(playerSt.x, playerSt.y, player.handle2[Pnum], TRUE);
		}
	}

//���S
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);
	
//�X�^�[�g���S�`��
	DrawRotaGraph(
		ImageTitleSTART.x, ImageTitleSTART.y,
		ImageTitleSTART.rate,
		ImageTitleSTART.angle,
		ImageTitleSTART.handle, TRUE);
//�����L���O���S�`��
	DrawRotaGraph(
		ImageTitleRNK.x, ImageTitleRNK.y,
		ImageTitleRNK.rate,
		ImageTitleRNK.angle,
		ImageTitleRNK.handle, TRUE);

	DrawGraph(ImageChoiser.x, ImageChoiser.y, ImageChoiser.handle, TRUE);

//�㉺�I���̓����i�T�C�Y�ύX�j
	if (Kchoice == TRUE) {
		ImageTitleSTART.rate = 1.2; 
		ImageTitleRNK.rate = 1.0;
		ImageChoiser.x = ImageTitleSTART.x + ImageTitleSTART.width / 2 + 32;
		ImageChoiser.y = ImageTitleSTART.y + ImageTitleSTART.height / 4 - ImageChoiser.height / 2 ;
	}
	else {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.2;
		ImageChoiser.x = ImageTitleRNK.x + ImageTitleRNK.width / 2 + 32;
		ImageChoiser.y = ImageTitleRNK.y + ImageTitleRNK.height / 4 - ImageChoiser.height / 2;
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE) {
		if (Kchoice == TRUE) 
			ImageTitleSTART.rate = 0.8; //0.8%
		else 
			ImageTitleRNK.rate = 0.8;
		ImageChoiser.x -= MAP_DIV_WIDTH / 2;
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.0;
		ImageChoiser.x += MAP_DIV_WIDTH / 2;
	}
	//DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

/*----------------------------------�Q�[�������V�[��------------------------------------------------------*/

VOID MY_EXPO(VOID)
{
	MY_EXPO_PROC();
	MY_EXPO_DRAW();

	return;
}

VOID MY_EXPO_PROC(VOID) {
	/*if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}*/

//�I���̃y�[�W����
	switch (ExDrawCnt)
	{
	case 1:		//�Q�[���ڕW
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			CLICK_M = TRUE;
			ExDrawCnt = 2;
		}
		break;
	case 2:		//�������
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			ExDrawCnt = 3;
			CLICK_M = TRUE;
		}
		break;
	case 3:
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			ExDrawCnt = 1;
			CLICK_M = TRUE;
			if (CheckSoundMem(BGM_TITLE.handle) != 0)
			{
				StopSoundMem(BGM_TITLE.handle);
			}
			for (int charS = 0; charS < IMAGE_CHAR_NUM; charS++)
			{
				if (ImageChar[charS].IsDraw == TRUE)
					ImageChar[charS].IsDraw = FALSE;
			}
			switch (PlayChar)
			{
				case CHARA_BALANCE:
					cooltimeType = VARNCE_CHAR;
				break;
				case CHARA_TANK:
					cooltimeType = TANKA_CHAR;
					break;
			default:
				break;
			}

			player.CenterX = startPt.x;
			player.CenterY = startPt.y;

			player.x = player.CenterX;
			player.y = player.CenterY;

			player.collBeforePt.x = player.CenterX;
			player.collBeforePt.y = player.CenterY;

			ITEMCnt = 0;
			COINCnt = 0;
			driecChar = 2;
			speedUPflg = false;
			speedUpTime = 0;
			gameSpeed = SCROLL_SPEED;
			GameScene = GAME_SCENE_PLAY;
		}
		break;
	}

//�I����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN)) {

		if (CLICK_M == TRUE)
		{
			PlaySoundMem(musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
	}
	return;
}

VOID MY_EXPO_DRAW(VOID) {

	DrawGraph(ImageEXPOBK.x, ImageEXPOBK.y, ImageEXPOBK.handle, TRUE);

//�I��`��w�i
	switch (ExDrawCnt)
	{
	case 1:
		GAME_RULE();
		DrawGraph(ImageExNews1.x, ImageExNews1.y, ImageExNews1.handle, TRUE);
		break;
	case 2:
		GAME_PILOT();
		DrawGraph(ImageExNews2.x, ImageExNews2.y, ImageExNews2.handle, TRUE);
		PlayChar = CHARA_BALANCE;
		break;
	case 3:
		GAME_PILOT();
		DrawGraph(ImageExNews2.x, ImageExNews2.y, ImageExNews2.handle, TRUE);
		DrawGraph(stopBack.x, stopBack.y, stopBack.handle, TRUE);
		CHAR_TYPE_SET();
		break;		//�����p�X
	}

//���͂̕`��
	/*char* str = NULL;*/
	SetFontSize(44);
	TEXT_DRAW();
	
	DrawRotaGraph(
		ImageNextROGO.x, ImageNextROGO.y,
		ImageNextROGO.rate,
		ImageNextROGO.angle,
		ImageNextROGO.handle, TRUE);

//�I���i�T�C�Y�j
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		ImageNextROGO.rate = 0.8;

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		FALL_RESON = FALSE;
		ImageNextROGO.rate = 1.0;
	}

	/*free(str);*/

	return;
}

/*----------------------------------�v���C�V�[��------------------------------------------------------*/

VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

	return;
}

VOID MY_PLAY_PROC(VOID)
{
	static int colltime = 0;

	static bool dirDrwFlag = false;

//��Փx����
	if (COINCnt > 0 && (COINCnt % SPEED_UP_CNT) == 0 && speedUPflg == false) {
		speedUPflg = true;
		speedUpTime = 0;
	}
	
//�X�s�[�h�A�b�v����
	if (speedUPflg)
	{
		if (speedUpTime < (GAME_FPS * SPEED_UP_TIME)) {
			gameSpeed = SCROLL_SPEED;
			gameSpeed *= UP_SPEED;
			speedUpTime++;
		}
		else if(speedUpTime >= (GAME_FPS * SPEED_UP_TIME))
		{
			gameSpeed = SCROLL_SPEED;
			if (COINCnt > 0 && (COINCnt % SPEED_UP_CNT) != 0) {
				speedUPflg = false;
			}
		}
	}

	if (CheckSoundMem(BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

//�}�b�v���[�h
	MAP_LOAD();

//�^�C�}����
	if (timeCnt >= 60)
	{
		secondtime = secondtime - 0.016 * timeCnt;
		timeCnt = 0;
		secondtime++;
	}
	if (secondtime >= 60)
	{
		secondtime = 0;
		mintime++;
	}
	secondtime += 0.016;
	timeCnt++;

	//�L�����̃X�N���[��
	player.CenterX -= gameSpeed;
	player.collBeforePt.x -= gameSpeed;	//�X�N���[������܂��̓������Ă��Ȃ��ʒu�ƍ��̑O�̈ʒu�͈Ⴄ

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�}�b�v���ړ������蔻����ړ�
			map[tate][yoko].x -= gameSpeed;
			mapColl[tate][yoko].left -= gameSpeed;
			mapColl[tate][yoko].right -= gameSpeed;
			//if (map[tate][yoko].x >= GAME_WIDTH)
			//{
			//	map[tate][yoko].IsDraw = FALSE;
			//}
		}

	}
	//�}�b�v�������ŃX�N���[��
	MAPmoveCnt += gameSpeed;

	if (MAPmoveCnt >= MAP_DIV_WIDTH * 3)
	{
		if (MAPmoveCnt != MAP_DIV_WIDTH * 3) {
			MAPmoveCnt--;
			diffMarginFlg = true;
		}
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//�}�b�v���ړ������蔻����ړ�
				map[tate][yoko].x += MAPmoveCnt;
				mapColl[tate][yoko].left += MAPmoveCnt;
				mapColl[tate][yoko].right += MAPmoveCnt;
			}

		}
		ROCKETMAP();
		MAPmoveCnt = diffMarginFlg ? 1 : 0; 
		//�}�b�v�z��̕`��덷�t���O������
		if (diffMarginFlg)
			diffMarginFlg = !diffMarginFlg;
	}

//�X�g�b�v��ʈڍs
	if (MY_KEY_UP(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}
		GameScene = GAME_SCENE_STOP;
	}
	if (StopFlg)
		StopFlg = false;



//���̓��͔���i�������ƂƂ��j
	if (MY_KEY_TF == TRUE) {
		if (MY_KEY_DOWN(KEY_INPUT_W)) {
			player.CenterY -= MOVE_ERIA;
			ImageChar[driecChar].IsDraw = FALSE;
			driecChar = 0;
			ChangeVolumeSoundMem(255 * 80 / 100, se_move.handle);
			PlaySoundMem(se_move.handle, DX_PLAYTYPE_BACK);
			MY_KEY_TF = FALSE;
		}
		else if (MY_KEY_DOWN(KEY_INPUT_A)) {
			player.CenterX -= MOVE_ERIA;
			ImageChar[driecChar].IsDraw = FALSE;
			driecChar = 3;
			ChangeVolumeSoundMem(255 * 80 / 100, se_move.handle);
			PlaySoundMem(se_move.handle, DX_PLAYTYPE_BACK);
			MY_KEY_TF = FALSE;
		}
		else if (MY_KEY_DOWN(KEY_INPUT_S)) {
			player.CenterY += MOVE_ERIA;
			ImageChar[driecChar].IsDraw = FALSE;
			driecChar = 2;
			ChangeVolumeSoundMem(255 * 80 / 100, se_move.handle);
			PlaySoundMem(se_move.handle, DX_PLAYTYPE_BACK);
			MY_KEY_TF = FALSE;
		}
		else if (MY_KEY_DOWN(KEY_INPUT_D)) {
			player.CenterX += MOVE_ERIA;
			ImageChar[driecChar].IsDraw = FALSE;
			driecChar = 1;		
			ChangeVolumeSoundMem(255 * 80 / 100, se_move.handle);
			PlaySoundMem(se_move.handle, DX_PLAYTYPE_BACK);
			MY_KEY_TF = FALSE;
		}
		if (!ImageChar[driecChar].IsDraw)
		{
			ImageChar[driecChar].IsDraw = TRUE;
		}

	}

	//���̓��͔���i�������Ƃ��j
	if (MY_KEY_TF == FALSE) {		//�v���C���[�̈ړ����͂̃N�[���^�C���ݒ�
		if (colltime >= cooltimeType)
		{
			if (MY_KEY_DOWN(KEY_INPUT_W) || MY_KEY_DOWN(KEY_INPUT_A) || MY_KEY_DOWN(KEY_INPUT_S) || MY_KEY_DOWN(KEY_INPUT_D)) {}
			else {
				MY_KEY_TF = TRUE;
				colltime = 0;
			}
		}
		else
			colltime++;

	}

	if (MY_KEY_UP(KEY_INPUT_W) || MY_KEY_UP(KEY_INPUT_A) || MY_KEY_UP(KEY_INPUT_S) || MY_KEY_UP(KEY_INPUT_D)) {
		//�v���C���[�̌������
		if (DrCharCnt < 3 && DrCharCnt > -1) {
			if (!dirDrwFlag)
				DrCharCnt++;
			else
				DrCharCnt--;
		}
		if (DrCharCnt >= 3 || DrCharCnt <= -1) {
			if (!dirDrwFlag)
				DrCharCnt -= 2;
			else
				DrCharCnt += 2;
			dirDrwFlag = !dirDrwFlag;
		}
	}



	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

//����������
	direc = MY_DIRECTION(player.CenterX, player.CenterY, player.collBeforePt.x, player.collBeforePt.y);

	BOOL IsMove = TRUE;

	RECT PlayerRect;
	int CollRange = 5;
	PlayerRect.left = player.x + player.width / 2 - CollRange;
	PlayerRect.top = player.y + player.height / 2 - CollRange;
	PlayerRect.right = player.x + player.width / 2 + CollRange;
	PlayerRect.bottom = player.y + player.height / 2 + CollRange;


	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		IsMove = FALSE;

		newX = ((player.CenterX + MAPmoveCnt) - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;  //�ړ����v���X
		newY = (player.CenterY - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;

		if (map[newY][newX].kind == l)
		{
			//�}�b�v�̍X�V


			if (IsReMove == FALSE)
			{
				int reN = 0;
				switch (direc)
				{
				case 'W':
					reN = newY - 1;
					if (mapData[reN][newX] == t)
					{
						mapData[reN][newX] = mapData[newY][newX];
						map[reN][newX].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				case 'S':
					reN = newY + 1;
					if (mapData[reN][newX] == t)
					{
						mapData[reN][newX] = mapData[newY][newX];
						map[reN][newX].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				case 'A':
					reN = newX - 1;
					if (mapData[newY][reN] == t)
					{
						mapData[newY][reN] = mapData[newY][newX];
						map[newY][reN].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				case 'D':
					reN = newX + 1;
					if (mapData[newY][reN] == t)
					{
						mapData[newY][reN] = mapData[newY][newX];
						map[newY][reN].kind = map[newY][newX].kind;
						IsReMove = TRUE;
					}
					break;
				default:
					break;

				}


			//��Q�����A�C�e���Ŕj��
				if (ITEMCnt > 0 && IsReMove == FALSE)
				{
					IsReMove = TRUE;
					ITEMCnt--;

						PlaySoundMem(se_brake.handle, DX_PLAYTYPE_BACK);

				}
			}
			if (IsReMove == TRUE)
			{
				//�����蔻��X�V���摜�폜
				mapData[newY][newX] = t;
				map[newY][newX].kind = t;
				IsReMove = FALSE;
			}//�}�b�v�X�V�����܂�

			
		}

		////���̈ʒu�ɖ߂�
		player.CenterX = player.collBeforePt.x;	//�X�N���[������܂��̓������Ă��Ȃ��ʒu�ƍ��̑O�̈ʒu�͈Ⴄ
		player.CenterY = player.collBeforePt.y;
	}

	/*if (MY_CHECK_RECT_COLL(PlayerRect, itemRect) == TRUE)*/
	

	if (IsMove == TRUE)
	{

		int x = ((player.CenterX + MAPmoveCnt) - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;  //�ړ����v���X
		int y = (player.CenterY - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;
		switch (map[y][x].kind)
		{
		case g:
			//�A�C�e���擾�ƃA�C�e���̓����蔻��폜
			if (PlayChar == CHARA_BALANCE && ITEMCnt >= CHAR_BAG_NUM) {}
			else {
				mapData[y][x] = t;
				map[y][x].kind = t;
				ITEMCnt++;
			}
			break;
		case c:
			//�R�C���擾�ƃR�C���̓����蔻��폜
			mapData[y][x] = t;
			map[y][x].kind = t;
			COINCnt++;
			if (!COINflag)
			{
				COINflag = TRUE;

			}
			ChangeVolumeSoundMem(255 * 75 / 100, se_coin_g.handle);

			PlaySoundMem(se_coin_g.handle, DX_PLAYTYPE_BACK);
			break;
		default:
			break;
			
		}
	
	//�v���C���[�O�̈ʒu��������
		player.x = player.CenterX - player.width / 2;
		player.y = player.CenterY - player.height / 2;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;
	}



	if (player.x > GAME_WIDTH || player.y > GAME_HEIGHT
		|| player.x + player.width < 0 || player.y + player.height < 0)
	{

		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		SetMouseDispFlag(TRUE);

		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_END;

		return;
	}

	return;
}

VOID MY_PLAY_DRAW(VOID)
{
	static int StrWidth = 0;
	static int CdrawCnt = 0;
//�w�i�X�N���[��
		MAP_DRAW();
	//DrawGraph(ImageBack.image.x, ImageBack.image.y, ImageBack.image.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}

	//�v���C���[��`�悷��
	//DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);
	for (int num = 0, Pnum = 0; num < CHAR_DREC_NUM; num++)
	{
		if (ImageChar[num].IsDraw == TRUE)
		{
			Pnum = num + (2 * num);
			Pnum += DrCharCnt;
			switch (PlayChar)
			{
			case CHARA_BALANCE:
				DrawGraph(player.x, player.y, player.handle2[Pnum], TRUE);
				break;
			case CHARA_TANK:
				DrawGraph(player.x, player.y, player2.handle2[Pnum], TRUE);
				break;
			default:
				break;
			}
		}
	}

	//shadow
	DrawGraph(ImageShadow.x, ImageShadow.y, ImageShadow.handle, TRUE);

	//�^�C�}�[�ƃA�C�e���`��
	SetFontSize(25);

	if (secondtime >= 60 || mintime >= 1) {
		DrawFormatString(0, 5, GetColor(0, 0, 200), " TIME:%d��%.2f�b", mintime, secondtime);
	}
	else
	{
		DrawFormatString(0, 5, GetColor(0, 0, 200), " TIME:%.2f�b", secondtime);

	}

	if (PlayChar == CHARA_BALANCE && ITEMCnt >= CHAR_BAG_NUM) {
		DrawFormatString(GAME_WIDTH - GetDrawFormatStringWidth("�s�b�P��: MAX ", ITEMCnt, -1), 5, GetColor(200, 0, 0), "�s�b�P��: MAX ", ITEMCnt);
	}
	else
	DrawFormatString(GAME_WIDTH - GetDrawFormatStringWidth("�s�b�P��:% d�� ", ITEMCnt, -1), 5, GetColor(255, 0, 0), "�s�b�P��:%d�� ", ITEMCnt);

	////�����蔻��̕`��i�f�o�b�O�p�j
	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		//�ǂȂ��
	//		if (mapData[tate][yoko] == k || mapData[tate][yoko] == l)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
	//		}

	//		//�ʘH�Ȃ��
	//		if (mapData[tate][yoko] == t)
	//		{
	//			DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
	//		}
	//	}
	//}

	////////�S�[���̕`��i�f�o�b�O�p�j
	//////DrawBox(GoalRect.left, GoalRect.top, GoalRect.right, GoalRect.bottom, GetColor(255, 255, 0), TRUE);


	//////�����蔻��̕`��i�f�o�b�O�p�j
	//DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);



	SetFontSize(30);
	StrWidth = GetDrawStringWidth("_/_/ �ړ��L�[�FW�y���zA�y���zS�y���zD�y���z| ��~:ESC _/_/", -1);//������
	DrawString((GAME_WIDTH - StrWidth )/ 2, GAME_HEIGHT - 45, "_/_/ �ړ��L�[�FW�y���zA�y���zS�y���zD�y���z| ��~:ESC _/_/", GetColor(255, 255, 255));
	SetFontSize(40);
	if (COINflag)
	{
		if (CdrawCnt < GAME_FPS / 2) {
			DrawString(10, 80- CdrawCnt, "1C Get!!", GetColor(255, 255, 255));
			CdrawCnt++;
		}
		else
		{
			CdrawCnt = 0;
			COINflag = FALSE;
		}
	}
	//DrawString((GAME_WIDTH - GetDrawStringWidth("������r���̂��߁u��ʒ[�ɏo��v�������́u��~��ʁv����E�o���Ă���������", -1)) / 2, GAME_HEIGHT - 64, "������r���̂��߉�ʒ[�ɏo��������͒�~��ʂ���S�[���֍s���Ă���������", GetColor(255, 0, 0));
	return;
}

/*----------------------------------�G���h�V�[��------------------------------------------------------*/

VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();
	return;
}

VOID MY_END_PROC(VOID)
{
	static BOOL MusicPass1 = TRUE;
	if (BackBtnIsDraw)
	{
		if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
		{
			if (CLICK_M == TRUE)
			{
				PlaySoundMem(musicShot.handle, DX_PLAYTYPE_BACK);
				CLICK_M = FALSE;
			}
			if (CheckSoundMem(BGM_COMP.handle) != 0)
			{
				StopSoundMem(BGM_COMP.handle);
			}

			if (CheckSoundMem(BGM_FAIL.handle) != 0)
			{
				StopSoundMem(BGM_FAIL.handle);
			}

			MusicPass1 = FALSE;
		}

		if (MY_KEY_UP(KEY_INPUT_BACK) == TRUE) {
			CLICK_M = TRUE;

			SetMouseDispFlag(TRUE);

			for (int charS = 0; charS < IMAGE_CHAR_NUM; charS++)
			{
				if (ImageChar[charS].IsDraw == TRUE)
					ImageChar[charS].IsDraw = FALSE;
			}

			MY_CHAR_MOVE_ST = TRUE;

			GameScene = GAME_SCENE_START;

			ScoreDrawCnt = 0;

			MusicPass1 = TRUE;

			return;
		}
	}

	//switch (GameEndKind)
	//{
	//case GAME_END_COMP:

	//	if (CheckSoundMem(BGM_COMP.handle) == 0 && MusicPass1 == TRUE)
	//	{
	//		ChangeVolumeSoundMem(255 * 50 / 100, BGM_COMP.handle);
	//		PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
	//	}
	//	break;

	//case GAME_END_FAIL:

		if (CheckSoundMem(BGM_FAIL.handle) == 0 && MusicPass1 == TRUE)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_FAIL.handle);
			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

	//	break;
	//}

	return;
}

VOID MY_END_DRAW(VOID)
{

	switch (GameEndKind)
	{
	case GAME_END_EXIT:
		DrawGraph(ImageBackEND.x, ImageBackEND.y, ImageBackEND.handle, TRUE);

		DrawGraph(ImageEndWD.x, ImageEndWD.y, ImageEndWD.handle, TRUE);

		break;

	case GAME_END_FAIL:
		DrawGraph(ImageBackENDF.x, ImageBackENDF.y, ImageBackENDF.handle, TRUE);

		DrawGraph(ImageEndFAIL.x, ImageEndFAIL.y, ImageEndFAIL.handle, TRUE);

		break;
	}

	DrawScore DScore;
	//setScore.setS(secondtime, mintime, COINCnt);
	BackBtnIsDraw = DScore.drawS(secondtime, mintime, COINCnt, ScoreDrawCnt);
	Score = DScore.reS();

	if(ScoreDrawCnt <= (GAME_FPS * 3))
	ScoreDrawCnt++;

	SetFontSize(16.5);

	if (BackBtnIsDraw)
	{
		DrawRotaGraph(
			ImageEndROGO.x, ImageEndROGO.y,
			ImageEndROGO.rate,
			ImageEndROGO.angle,
			ImageEndROGO.handle, TRUE);
	}

	if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
		ImageEndROGO.rate = 0.8;

	if (MY_KEY_UP(KEY_INPUT_BACK) == TRUE) {
		FALL_RESON = FALSE;
		ImageEndROGO.rate = 1.0;
	}
	
//�����L���O�`�����ݏ���
	if (RANKINGflag)
	{
		R_WRITE ranking;
		COINCnt = COINCnt;
		ranking.Rwrite(fsArry, Score);
		RANKINGflag = FALSE;
	}
	return;
}

/*----------------------------------stop�V�[��------------------------------------------------------*/

VOID MY_STOP(VOID)
{
	MY_STOP_PROC();
	MY_STOP_DRAW();
	return;
}

VOID MY_STOP_PROC(VOID)
{
	static BOOL MusicPass = TRUE;
	static BOOL check = TRUE;

	if (CheckSoundMem(BGM_TITLE.handle) != 0)
	{
		StopSoundMem(BGM_TITLE.handle);
	}

	if (!StopFlg)
		StopFlg = true;

	//-----------------------
	if (check == TRUE) {
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE || MY_KEY_DOWN(KEY_INPUT_UP) == TRUE) {
			Kchoice = !Kchoice;
			check = FALSE;
		}
	}
	if (MY_KEY_UP(KEY_INPUT_DOWN) == TRUE || MY_KEY_UP(KEY_INPUT_UP) == TRUE)
		check = TRUE;
	//------------------------
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE)
	{
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
			MusicPass = FALSE;
		}
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE) {
		MusicPass = TRUE;
		CLICK_M = TRUE;
		GameScene = GAME_SCENE_END;
		GameEndKind = GAME_END_EXIT;

		return;
	}
	//-------------------------
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE && Kchoice == FALSE)
	{

		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
			MusicPass = FALSE;
		}
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE && Kchoice == FALSE) {
		MusicPass = TRUE;
		Kchoice = TRUE;
		CLICK_M = TRUE;
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP, FALSE);
		GameScene = GAME_SCENE_PLAY;
		return;
	}

	//�I����
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
	}
	return;
}

VOID MY_STOP_DRAW(VOID)
{
	MY_PLAY_DRAW();

	DrawGraph(stopBack.x, stopBack.y, stopBack.handle, TRUE);

	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);

	DrawRotaGraph(
		ImageSTeROGO.x, ImageSTeROGO.y,
		ImageSTeROGO.rate,
		ImageSTeROGO.angle,
		ImageSTeROGO.handle, TRUE);

	DrawRotaGraph(
		ImageSTbROGO.x, ImageSTbROGO.y,
		ImageSTbROGO.rate,
		ImageSTbROGO.angle,
		ImageSTbROGO.handle, TRUE);

	DrawGraph(ImageChoiser.x, ImageChoiser.y, ImageChoiser.handle, TRUE);


	if (Kchoice == TRUE) {
		ImageSTeROGO.rate = 1.2;
		ImageSTbROGO.rate = 1.0;
		ImageChoiser.x = ImageSTeROGO.x + ImageSTeROGO.width / 2 + MAP_DIV_WIDTH / 2;
		ImageChoiser.y = ImageSTeROGO.y + ImageSTeROGO.height / 4 - ImageChoiser.height / 2;
	}
	else {
		ImageSTeROGO.rate = 1.0;
		ImageSTbROGO.rate = 1.2;
		ImageChoiser.x = ImageSTbROGO.x + ImageSTbROGO.width / 2 + MAP_DIV_WIDTH / 2;
		ImageChoiser.y = ImageSTbROGO.y + ImageSTbROGO.height / 4 - ImageChoiser.height / 2;
	}

	DrawScore intervalScore;
	intervalScore.drawStop(secondtime, mintime, COINCnt);

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE) {
		if (Kchoice == TRUE)
			ImageSTeROGO.rate = 0.8;
		else
			ImageSTbROGO.rate = 0.8;
		ImageChoiser.x -= MAP_DIV_WIDTH / 2;
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		ImageSTeROGO.rate = 1.0;
		ImageSTbROGO.rate = 1.0;
		ImageChoiser.x += MAP_DIV_WIDTH / 2;
	}
	SetFontSize(30);

	//DrawString((GAME_WIDTH - GetDrawStringWidth("_/_/���w�i�E�����S�i�X�g�b�v��ʂɂȂ�\��ł��j _/_/", -1)) / 2, GAME_HEIGHT - 45, "_/_/���w�i�E�����S�i�X�g�b�v��ʂɂȂ�\��ł��j _/_/", GetColor(255, 255, 255));

}

/*----------------------------------�����L���O�V�[��------------------------------------------------------*/

VOID MY_RNKING(VOID)
{
	MY_RNKING_PROC();
	MY_RNKING_DRAW();
	return;
}

VOID MY_RNKING_PROC(VOID)
{
	if (CheckSoundMem(BGM_RANKING.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 40 / 100, BGM_RANKING.handle);
		PlaySoundMem(BGM_RANKING.handle, DX_PLAYTYPE_LOOP);
	}
	//if (CheckSoundMem(se_clock.handle) == 0)
	//{
	//	ChangeVolumeSoundMem(255 * 40 / 100, se_clock.handle);
	//	PlaySoundMem(se_clock.handle, DX_PLAYTYPE_LOOP);
	//}
	if (MY_KEY_UP(KEY_INPUT_DELETE) == TRUE) {
		//ChangeVolumeSoundMem(255 * 80 / 100, se_pachin.handle);
		PlaySoundMem(se_pachin.handle, DX_PLAYTYPE_BACK);
		R_WRITE resetRnk;
		resetRnk.ResetScore(fsArry);
		RANKINGflag = TRUE;
	}

	//�I����
	if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE && CLICK_M == TRUE)
	{
		PlaySoundMem(musicShot.handle, DX_PLAYTYPE_BACK);
		CLICK_M = FALSE;
	}


	if (MY_KEY_UP(KEY_INPUT_BACK) == TRUE) {

		/*SetMouseDispFlag(TRUE);*/
		if (CheckSoundMem(BGM_RANKING.handle) != 0)
		{
			StopSoundMem(BGM_RANKING.handle);
		}

		GameScene = GAME_SCENE_START;
		CLICK_M = TRUE;
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP, FALSE);

		return;
	}
}

VOID MY_RNKING_DRAW(VOID)
{
	static BOOL RNKBackDrawFlag = TRUE;
	static int fSize = 0;
	static int RBKdrawCnt = 0;
	if (RNKBackDrawFlag) {
		if (RBKdrawCnt < (GAME_FPS * 3)) {
			DrawGraph(RNKBACK.x, RNKBACK.y, RNKBACK.handle, TRUE);
			RBKdrawCnt++;
		}
		else
		{
			RBKdrawCnt = 0;
			RNKBackDrawFlag = FALSE;
		}
	}
	else {
		if (RBKdrawCnt < (GAME_FPS / 2)) {
			DrawGraph(RNKBACKNone.x, RNKBACKNone.y, RNKBACKNone.handle, TRUE);
			RBKdrawCnt++;
		}
		else
		{
			RBKdrawCnt = 0;
			RNKBackDrawFlag = TRUE;
		}
	}

	if (RANKINGflag)
	{
		if (!fsArry[CHECKEMPTY]) {
			R_WRITE rankingWatch;
			rankingWatch.Rread(fsArry);
		}
		RANKINGflag = FALSE;
	}
	fSize = 64;
	for (int i = 0; i < FILE_NUM; i++)
	{
		SetFontSize(fSize);
		DrawFormatString((GAME_WIDTH - GetDrawFormatStringWidth("%d��: %.2f", i + 1, fsArry[i], -1)) / 2, GAME_HEIGHT / 9 * 4 + 64 * i, GetColor(0, 0, 0), "%d��: %.2f", i + 1, fsArry[i]);
		fSize -= 4;
	}

	if (!RNKBackDrawFlag)
	{
		DrawGraph(RNKShadow.x, RNKShadow.y, RNKShadow.handle, TRUE);
		SetFontSize(25);
		DrawString((GAME_WIDTH - GetDrawFormatStringWidth("DELETE�F�X�R�A������", -1)), 0, "DELETE�F�X�R�A������", GetColor(255, 255, 255));
	}
	else
	{
		SetFontSize(25);
		DrawString((GAME_WIDTH - GetDrawFormatStringWidth("DELETE�F�X�R�A������", -1)), 0, "DELETE�F�X�R�A������", GetColor(0, 0, 0));
	}


	DrawRotaGraph(
		ImageEndROGO.x, ImageEndROGO.y,
		ImageEndROGO.rate,
		ImageEndROGO.angle,
		ImageEndROGO.handle, TRUE);


	if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
		ImageEndROGO.rate = 0.8;

	if (MY_KEY_UP(KEY_INPUT_BACK) == TRUE) {
		FALL_RESON = FALSE;
		ImageEndROGO.rate = 1.0;
	}


}

/*----------------------------------�V�[���ȊO�̊֐�------------------------------------------------------*/

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				if (map[tate][yoko].kind == k) { return TRUE; }
				if (map[tate][yoko].kind == l) { return TRUE; }
				if (map[tate][yoko].kind == m) { return TRUE; }
				if (map[tate][yoko].kind == r) { return TRUE; }
				//if (map[tate][yoko].kind == g) { return TRUE; }

			}
		}
	}

	return FALSE;
}

BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;
	}

	return FALSE;
}

//�������������Ƃ�
CHAR MY_DIRECTION(double x, double y, double oldx, double oldy)
{
	if (x != oldx) {
		if (x < oldx)
			return 'A';
		else
			return 'D';
	}
	if (y != oldy) {
		if (y < oldy)
			return 'W';
		else
			return 'S';
	}
}

//���������Q

VOID MAP_LOAD(VOID)
{
	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		if (mapData[tate][yoko] == g)
	//		{
	//			itemRect.left = mapChip.width * yoko;
	//			itemRect.top = mapChip.height * tate;
	//			itemRect.right = mapChip.width * (yoko + 1);
	//			itemRect.bottom = mapChip.height * (tate + 1);
	//		}
	//	}
	//}

	if (MY_MAP_RELOAD == TRUE) {
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				mapData[tate][yoko] = mapDataPR[tate][yoko];
				map[tate][yoko].kind = mapDataPR[tate][yoko];
			}
		}
		//�ʒu������
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//�}�b�v���ړ������蔻����ړ�
				map[tate][yoko].x += MAPmoveCnt;
				mapColl[tate][yoko].left += MAPmoveCnt;
				mapColl[tate][yoko].right += MAPmoveCnt;

			}

		}
		MAPmoveCnt = 0;
		MY_MAP_RELOAD = FALSE;
	}
}

void CHAR_TYPE_SET()
{
	static int Template = 0, Cnt = 0, play1y = GAME_HEIGHT / 2, play2y = GAME_HEIGHT / 2;
	static float lx = 0.0f, ly = 0.0f, rx = 0.0f, ry = 0.0f;
	//�����̏�������
	setText setText;
	if (auto findt = std::find(charstatus.begin(), charstatus.end(), STATUSTEMP) == charstatus.end())
	{
		setText.appendText(charstatus, STATUSTEMP);
		setText.appendText(charstatus, STATUS1);
		setText.appendText(charstatus, STATUS2);
	}

	//�L�����N�^�̌��̐}�`
	DrawBoxAA(lx, ly, rx, ry, GetColor(220, 220, 220), TRUE);

	//�`�恕�T�C�Y�w��
	DrawRotaGraph(
		player.x = GAME_WIDTH / 4, player.y = play1y,
		player.rate * 2,
		player.angle,
		player.handle2[1], TRUE);

	DrawRotaGraph(
		player2.x = GAME_WIDTH / 4 * 3, player2.y = play2y,
		player2.rate * 2,
		player2.angle,
		player2.handle2[1], TRUE);

	if (charstatus[Template] == STATUSTEMP) {
		switch (PlayChar)
		{
		case CHARA_BALANCE:
			lx = (player.x - player.width / 2) - player.width * 2;			//�w�i�}�`�̈ʒu�ݒ�
			ly = (player.y - player.height / 2) - player.width;
			rx = (player.x + player.width / 2) + player.width * 2;
			ry = (player.y + player.height / 2) + player.height * 3.5;
			if (charstatus[Cnt] == STATUS1) {
				play1y = GAME_HEIGHT / 5 * 2;
				play2y = GAME_HEIGHT / 2;
				player.rate = CHARBIGSIZE;
				player2.rate = CHARRESIZE;

				//�����̏ꏊ�w��
				DrawString((player.x - GetDrawStringWidth(charstatus[Template].c_str(), -1)), (player.y + player.height / 2) + player.height * CHARBIGSIZE + MAP_DIV_TATE / 4, charstatus[Template].c_str(), GetColor(255, 0, 0));
				DrawString(player.x + 10, (player.y + player.height / 2) + player.height * CHARBIGSIZE + MAP_DIV_TATE / 4, charstatus[Cnt].c_str(), GetColor(255, 0, 0));
			}
			else
			{
				Cnt = setText.findText(charstatus, STATUS1); 	//�L�����̐����Ăяo��

			}
			if (MY_KEY_UP(KEY_INPUT_RIGHT) || MY_KEY_UP(KEY_INPUT_LEFT)) { //�L�����̕ύX
				ChangeVolumeSoundMem(255 * 80 / 100, se_scene_sen.handle);
				PlaySoundMem(se_scene_sen.handle, DX_PLAYTYPE_BACK);
				PlayChar = CHARA_TANK;
			}
			break;
		case CHARA_TANK:
			if (charstatus[Cnt] == STATUS2) {
				lx = (player2.x - player2.width / 2) - player2.width * 2;			//�w�i�}�`�̈ʒu�ݒ�
				ly = (player2.y - player2.height / 2) - player2.width;
				rx = (player2.x + player2.width / 2) + player2.width * 2;
				ry = (player2.y + player2.height / 2) + player2.height * 3.5;
				play2y = GAME_HEIGHT / 5 * 2;
				play1y = GAME_HEIGHT / 2;
				player2.rate = CHARBIGSIZE;
				player.rate = CHARRESIZE;

				//�����̏ꏊ�w��
				DrawString((player2.x - GetDrawStringWidth(charstatus[Template].c_str(), -1)), (player2.y + player2.height / 2) + player2.height * CHARBIGSIZE + MAP_DIV_TATE / 4, charstatus[Template].c_str(), GetColor(255, 0, 0));
				DrawString(player2.x + 10, (player2.y + player2.height / 2) + player2.height * CHARBIGSIZE + MAP_DIV_TATE / 4, charstatus[Cnt].c_str(), GetColor(255, 0, 0));
			}
			else
			{
				Cnt = setText.findText(charstatus, STATUS2); 	//�L�����̐����Ăяo��
			}
			if (MY_KEY_UP(KEY_INPUT_RIGHT) || MY_KEY_UP(KEY_INPUT_LEFT)) {	//�L�����̕ύX
				ChangeVolumeSoundMem(255 * 80 / 100, se_scene_sen.handle);
				PlaySoundMem(se_scene_sen.handle, DX_PLAYTYPE_BACK);
				PlayChar = CHARA_BALANCE;
			}

			break;
		default:
			break;
		}
	}
	else
	{
		Template = setText.findText(charstatus, STATUSTEMP); 	//�L�����̐����e���v���[�g�Ăяo��
	}
	DrawString(GAME_WIDTH / 2 - GetDrawStringWidth(CHARA_ARROW, -1) / 2, GAME_HEIGHT / 2 - 44, CHARA_ARROW, GetColor(255, 255, 255));

	return;
}

VOID TEXT_DRAW()
{
	int Cnt = 0;
	setText setText;
	if (auto findt = std::find(textGaol.begin(), textGaol.end(), GOAL1) == textGaol.end())
	{
		setText.appendText(textGaol, GOAL1);
		setText.appendText(textGaol, GOAL2);
		setText.appendText(textGaol, GOAL3);
	}
	switch (ExDrawCnt)
	{
	case 1:
		Cnt = setText.findText(textGaol, GOAL1);		break;
	case 2:
		Cnt = setText.findText(textGaol, GOAL2);		break;
	case 3:
		Cnt = setText.findText(textGaol, GOAL3);		break;
	}

	DrawString((GAME_WIDTH - GetDrawStringWidth(textGaol[Cnt].c_str(), -1)) / 2, 10, textGaol[Cnt].c_str(), GetColor(255, 0, 0));

	/*char* cp = NULL;

	cp = (char*)malloc(sizeof(char) * 30);

	if (cp == NULL) {
		printf("�z��쐬���s\n");
	}

	switch (n)
	{
	case 1:
		strcpy_s(cp, 22, "�Q�[���ڕW�ƃ��[��");		break;
	case 2:
		strcpy_s(cp, 30, "��������ƃA�C�e���ɂ�����");		break;
	case 3:
		strcpy_s(cp, 16, "�X�g�[���[");		break;
	}
	*/
	return;

}

VOID GAME_RULE(VOID)
{
	SetFontSize(32);
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 3, "�Q�[���ڕW", GetColor(160, 0, 80));
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 5.5, "�Q�[�����[��", GetColor(160, 0, 80));
	SetFontSize(25);
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 3.5 + 5, "���������c��A\n���X�R�A��@�������I", GetColor(0, 0, 0));
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 6 + 5, "�����}�b�v�̏�Q����\n�����āE�������āE�j�󂵂�\n�ړ��ł��铹��V���ɊJ��A\n��蒷����ʓ��ɂɂƂǂ܂�\n�����c��I�I", GetColor(0, 0, 0));

	return;
}

VOID GAME_PILOT(VOID)
{
	SetFontSize(32);
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 3, "������@", GetColor(160, 0, 80));
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 5 + 5, "�A�C�e���ɂ���", GetColor(160, 0, 80));
	SetFontSize(25);
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 3.5 + 5, "�L�����̈ړ��́uW A S D�v\n��U��~���s���ɂ́uESC�L�[�v", GetColor(0, 0, 0));
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 5.5 + 10, "�}�b�v���ɗ����Ă���s�b�P��\n���g������Q����j�󂷂�\n���Ƃ��\�B\n�s�b�P���̃X�g�b�N���\��\n�g���^�C�~���O����Ŋ�@��\n�E����\�����I�I", GetColor(0, 0, 0));

	return;
}

//VOID GAME_STR(VOID)
//{
//	SetFontSize(32);
//	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 3, "�͂��܂�̕���", GetColor(0, 0, 0));
//	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 5 + 5, "�@", GetColor(0, 0, 0));
//	SetFontSize(25);
//	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 3.5 + 5, "���Ȃ��͓�̋�Ԃɔ�΂���\n", GetColor(0, 0, 0));
//	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 5.5 + 10, "�@", GetColor(0, 0, 0));
//
//	return;
//}

//�w�i�X�N���[��
VOID MAP_DRAW()
{
	DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

	//�񖇖ڕ`��
	DrawGraph(ImageBack.x + GAME_WIDTH, ImageBack.y, ImageBack.handle, TRUE);

	//��ԉ��܂ŃX�N���[�������珉���l�ɖ߂�
	if (ImageBack.x <= -(GAME_WIDTH + 10))
		ImageBack.x = -10;
	if (!StopFlg)
		ImageBack.x -= gameSpeed;

	return;
}

VOID ROCKETMAP(VOID)
{
	int plusYoko = 0;
	int newMapYoko = 0;
	int rndInt = 0;

	srand((unsigned int)time(NULL));
	rndInt = rand() % 9 + 1;

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_NEW; yoko++)
		{
			plusYoko = yoko + 3;
			//�}�b�v�ړ��X�V
			mapData[tate][yoko] = mapData[tate][plusYoko];
			map[tate][yoko].kind = map[tate][plusYoko].kind;
		}
		for (int yoko = GAME_MAP_YOKO_NEW; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			newMapYoko = (yoko - GAME_MAP_YOKO_NEW) + rndInt * 3;
			if (MAPChoice) {
				mapData[tate][yoko] = mapDataNEW[tate][newMapYoko];
				map[tate][yoko].kind = mapDataNEW[tate][newMapYoko];
			}
			else
			{
				mapData[tate][yoko] = mapDataNEW2[tate][newMapYoko];
				map[tate][yoko].kind = mapDataNEW2[tate][newMapYoko];
			}

		}
	}
	MAPChoice = !MAPChoice;
	return;
}


/*----------------------------------�摜���ǂݍ��݌n------------------------------------------------------*/
BOOL MY_LOAD_IMAGE(VOID)
{
	//�^�C�g���w�i
	IMG roadImage;
	if (!roadImage.RoadImage(ImageTitleBK, IMAGE_TITLE_BK_PATH)) { return FALSE; }
	//strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	//ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	//if (ImageTitleBK.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;

	//�^�C�g�����S
	if (!roadImage.RoadImage(ImageTitleROGO, IMAGE_TITLE_ROGO_PATH)) { return FALSE; }
	//strcpy_s(ImageTitleROGO.path, IMAGE_TITLE_ROGO_PATH);
	//ImageTitleROGO.handle = LoadGraph(ImageTitleROGO.path);
	//if (ImageTitleROGO.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageTitleROGO.handle, &ImageTitleROGO.width, &ImageTitleROGO.height);
	ImageTitleROGO.x = GAME_WIDTH / 2 - ImageTitleROGO.width / 2;
	ImageTitleROGO.y = GAME_HEIGHT / 2 - ImageTitleROGO.height / 2;

	//�^�C�g���X�^�[�g
	if (!roadImage.RoadImage(ImageTitleSTART, IMAGE_TITLE_START_PATH)) { return FALSE; }
	//strcpy_s(ImageTitleSTART.path, IMAGE_TITLE_START_PATH);
	//ImageTitleSTART.handle = LoadGraph(ImageTitleSTART.path);
	//if (ImageTitleSTART.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageTitleSTART.handle, &ImageTitleSTART.width, &ImageTitleSTART.height);
	ImageTitleSTART.x = GAME_WIDTH / 2;
	ImageTitleSTART.y = ImageTitleROGO.y + ImageTitleROGO.height + 32;
	ImageTitleSTART.angle = 0;
	ImageTitleSTART.rate = 1.0;

	//�����L���O�I��
	if (!roadImage.RoadImage(ImageTitleRNK, IMAGE_TITLE_RNK)) { return FALSE; }
	//strcpy_s(ImageTitleRNK.path, IMAGE_TITLE_RNK);
	//ImageTitleRNK.handle = LoadGraph(ImageTitleRNK.path);
	//if (ImageTitleRNK.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_TITLE_RNK, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageTitleRNK.handle, &ImageTitleRNK.width, &ImageTitleRNK.height);
	ImageTitleRNK.x = GAME_WIDTH / 2;
	ImageTitleRNK.y = ImageTitleROGO.y + ImageTitleROGO.height + ImageTitleSTART.height + 40;
	ImageTitleRNK.angle = 0;
	ImageTitleRNK.rate = 1.0;

	//�Q�[����߂郍�S
	if (!roadImage.RoadImage(ImageSTeROGO, IMAGE_ST_E_ROGO_PATH)) { return FALSE; }
	//strcpy_s(ImageSTeROGO.path, IMAGE_ST_E_ROGO_PATH);
	//ImageSTeROGO.handle = LoadGraph(ImageSTeROGO.path);
	//if (ImageSTeROGO.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_ST_E_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageSTeROGO.handle, &ImageSTeROGO.width, &ImageSTeROGO.height);
	ImageSTeROGO.x = GAME_WIDTH / 2;
	ImageSTeROGO.y = ImageTitleROGO.y + ImageTitleROGO.height + 32;
	ImageSTeROGO.angle = 0;
	ImageSTeROGO.rate = 1.0;

	//�Q�[���߂郍�S
	if (!roadImage.RoadImage(ImageSTbROGO, IMAGE_ST_B_ROGO_PATH)) { return FALSE; }
	//strcpy_s(ImageSTbROGO.path, IMAGE_ST_B_ROGO_PATH);
	//ImageSTbROGO.handle = LoadGraph(ImageSTbROGO.path);
	//if (ImageSTbROGO.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_ST_B_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageSTbROGO.handle, &ImageSTbROGO.width, &ImageSTbROGO.height);
	ImageSTbROGO.x = GAME_WIDTH / 2;
	ImageSTbROGO.y = ImageTitleROGO.y + ImageTitleROGO.height + ImageTitleSTART.height + 40;
	ImageSTbROGO.angle = 0;
	ImageSTbROGO.rate = 1.0;

	//�I����
	if (!roadImage.RoadImage(ImageChoiser, IMAGE_TITLE_CHI)) { return FALSE; }
	//strcpy_s(ImageChoiser.path, IMAGE_TITLE_CHI);
	//ImageChoiser.handle = LoadGraph(ImageChoiser.path);
	//if (ImageChoiser.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_TITLE_CHI, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageChoiser.handle, &ImageChoiser.width, &ImageChoiser.height);
	ImageChoiser.x = ImageTitleSTART.x + ImageTitleSTART.width / 2 + 32;
	ImageChoiser.y = ImageTitleSTART.y + ImageTitleSTART.height / 4 - ImageChoiser.height / 2;

	//�Q�[������
	if (!roadImage.RoadImage(ImageEXPOBK, IMAGE_EXPO_BACK)) { return FALSE; }
	//strcpy_s(ImageEXPOBK.path, IMAGE_EXPO_BACK);
	//ImageEXPOBK.handle = LoadGraph(ImageEXPOBK.path);
	//if (ImageEXPOBK.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_EXPO_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageEXPOBK.handle, &ImageEXPOBK.width, &ImageEXPOBK.height);
	ImageEXPOBK.x = GAME_WIDTH / 2 - ImageEXPOBK.width / 2;
	ImageEXPOBK.y = GAME_HEIGHT / 2 - ImageEXPOBK.height / 2;

	//�����L���O�w�i
	if (!roadImage.RoadImage(RNKBACK, IMAGE_RNK_BACK)) { return FALSE; }
	//strcpy_s(RNKBACK.path, IMAGE_RNK_BACK);
	//RNKBACK.handle = LoadGraph(RNKBACK.path);
	//if (RNKBACK.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_RNK_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(RNKBACK.handle, &RNKBACK.width, &RNKBACK.height);
	RNKBACK.x = GAME_WIDTH / 2 - RNKBACK.width / 2;
	RNKBACK.y = GAME_HEIGHT / 2 - RNKBACK.height / 2;

	//�����L���O�w�inone
	if (!roadImage.RoadImage(RNKBACKNone, IMAGE_RNK_BACK_NONE)) { return FALSE; }
	//strcpy_s(RNKBACKNone.path, IMAGE_RNK_BACK_NONE);
	//RNKBACKNone.handle = LoadGraph(RNKBACKNone.path);
	//if (RNKBACKNone.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_RNK_BACK_NONE, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(RNKBACKNone.handle, &RNKBACKNone.width, &RNKBACKNone.height);
	RNKBACKNone.x = GAME_WIDTH / 2 - RNKBACKNone.width / 2;
	RNKBACKNone.y = GAME_HEIGHT / 2 - RNKBACKNone.height / 2;

	//�����L���O�w�i�ǉ��e
	if (!roadImage.RoadImage(RNKShadow, IMAGE_RNK_SHADOW)) { return FALSE; }
	//strcpy_s(RNKShadow.path, IMAGE_RNK_SHADOW);
	//RNKShadow.handle = LoadGraph(RNKShadow.path);
	//if (RNKShadow.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_RNK_SHADOW, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(RNKShadow.handle, &RNKShadow.width, &RNKShadow.height);
	RNKShadow.x = GAME_WIDTH / 2 - RNKShadow.width / 2;
	RNKShadow.y = GAME_HEIGHT / 2 - RNKShadow.height / 2;

	//�X�g�b�v��ʔw�i
	if (!roadImage.RoadImage(stopBack, IMAGE_STOP_BACK)) { return FALSE; }
	//strcpy_s(stopBack.path, IMAGE_STOP_BACK);
	//stopBack.handle = LoadGraph(stopBack.path);
	//if (stopBack.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_STOP_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(stopBack.handle, &stopBack.width, &stopBack.height);
	stopBack.x = GAME_WIDTH / 2 - stopBack.width / 2;
	stopBack.y = GAME_HEIGHT / 2 - stopBack.height / 2;

//�G���h�t�H�[��
	if (!roadImage.RoadImage(ImageEndFAIL, IMAGE_END_FAIL_PATH)) { return FALSE; }
	//strcpy_s(ImageEndFAIL.path, IMAGE_END_FAIL_PATH);
	//ImageEndFAIL.handle = LoadGraph(ImageEndFAIL.path);
	//if (ImageEndFAIL.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageEndFAIL.handle, &ImageEndFAIL.width, &ImageEndFAIL.height);
	ImageEndFAIL.x = GAME_WIDTH / 2 - ImageEndFAIL.width / 2;
	ImageEndFAIL.y = GAME_HEIGHT / 2 - ImageEndFAIL.height / 2 - 32;

	//�G���h�P��
	if (!roadImage.RoadImage(ImageEndWD, IMAGE_END_WITHDRAWAL_PATH)) { return FALSE; }
	//strcpy_s(ImageEndWD.path, IMAGE_END_WITHDRAWAL_PATH);
	//ImageEndWD.handle = LoadGraph(ImageEndWD.path);
	//if (ImageEndWD.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_END_WITHDRAWAL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageEndWD.handle, &ImageEndWD.width, &ImageEndWD.height);
	ImageEndWD.x = GAME_WIDTH / 2 - ImageEndWD.width / 2;
	ImageEndWD.y = GAME_HEIGHT / 2 - ImageEndWD.height / 2 - 32;

	//�G�X�P�[�v�v�b�V��
	if (!roadImage.RoadImage(ImageEndROGO, IMAGE_END_ROGO_PATH)) { return FALSE; }
	//strcpy_s(ImageEndROGO.path, IMAGE_END_ROGO_PATH);
	//ImageEndROGO.handle = LoadGraph(ImageEndROGO.path);
	//if (ImageEndROGO.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_END_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageEndROGO.handle, &ImageEndROGO.width, &ImageEndROGO.height);
	ImageEndROGO.x = GAME_WIDTH - 70;
	ImageEndROGO.y = GAME_HEIGHT - 50;
	ImageEndROGO.angle = 0;
	ImageEndROGO.rate = 1.0;

	//NEXT PUSH
	if (!roadImage.RoadImage(ImageNextROGO, IMAGE_NEXT_ROGO_PATH)) { return FALSE; }
	//strcpy_s(ImageNextROGO.path, IMAGE_NEXT_ROGO_PATH);
	//ImageNextROGO.handle = LoadGraph(ImageNextROGO.path);
	//if (ImageNextROGO.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_NEXT_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageNextROGO.handle, &ImageNextROGO.width, &ImageNextROGO.height);
	ImageNextROGO.x = GAME_WIDTH - 70;
	ImageNextROGO.y = GAME_HEIGHT - 50;
	ImageNextROGO.angle = 0;
	ImageNextROGO.rate = 1.0;

	//�w�i�摜
	if (!roadImage.RoadImage(ImageBack, IMAGE_BACK_PATH)) { return FALSE; }
	//strcpy_s(ImageBack.path, IMAGE_BACK_PATH);
	//ImageBack.handle = LoadGraph(ImageBack.path);
	//if (ImageBack.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;
	ImageBack.y = 0 - ImageBack.height * 0;
	ImageBack.IsDraw = FALSE;

	//shadow
	if (!roadImage.RoadImage(ImageShadow, IMAGE_SHADOW_PATH)) { return FALSE; }
	//strcpy_s(ImageShadow.path, IMAGE_SHADOW_PATH);
	//ImageShadow.handle = LoadGraph(ImageShadow.path);
	//if (ImageShadow.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_SHADOW_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageShadow.handle, &ImageShadow.width, &ImageShadow.height);
	ImageShadow.x = GAME_WIDTH / 2 - ImageShadow.width / 2;
	ImageShadow.y = 0 - ImageShadow.height * 0;
	ImageShadow.IsDraw = FALSE;


	//�w�i�摜END
	if (!roadImage.RoadImage(ImageBackEND, IMAGE_BACK_ENDC_PATH)) { return FALSE; }
	//strcpy_s(ImageBackEND.path, IMAGE_BACK_ENDC_PATH);
	//ImageBackEND.handle = LoadGraph(ImageBackEND.path);
	//if (ImageBackEND.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDC_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageBackEND.handle, &ImageBackEND.width, &ImageBackEND.height);
	ImageBackEND.x = GAME_WIDTH / 2 - ImageBackEND.width / 2;
	ImageBackEND.y = 0 - ImageBackEND.height * 0;
	ImageBackEND.IsDraw = FALSE;

	//�w�i�摜ENDF
	if (!roadImage.RoadImage(ImageBackENDF, IMAGE_BACK_ENDF_PATH)) { return FALSE; }
	//strcpy_s(ImageBackENDF.path, IMAGE_BACK_ENDF_PATH);
	//ImageBackENDF.handle = LoadGraph(ImageBackENDF.path);
	//if (ImageBackENDF.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDF_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageBackENDF.handle, &ImageBackENDF.width, &ImageBackENDF.height);
	ImageBackENDF.x = GAME_WIDTH / 2 - ImageBackENDF.width / 2;
	ImageBackENDF.y = 0 - ImageBackENDF.height * 0;
	ImageBackENDF.IsDraw = FALSE;

	//�����摜�P
	if (!roadImage.RoadImage(ImageExNews1, IMAGE_EX_NEWS1)) { return FALSE; }
	//strcpy_s(ImageExNews1.path, IMAGE_EX_NEWS1);
	//ImageExNews1.handle = LoadGraph(ImageExNews1.path);
	//if (ImageExNews1.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_EX_NEWS1, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageExNews1.handle, &ImageExNews1.width, &ImageExNews1.height);
	ImageExNews1.x = MAP_DIV_WIDTH + (MAP_DIV_WIDTH / 4 - 2);
	ImageExNews1.y = MAP_DIV_HEIGHT * 2 + (MAP_DIV_HEIGHT / 4 * 3 - 2);
	ImageExNews1.IsDraw = FALSE;

	//�����摜2
	if (!roadImage.RoadImage(ImageExNews2, IMAGE_EX_NEWS2)) { return FALSE; }
	//strcpy_s(ImageExNews2.path, IMAGE_EX_NEWS2);
	//ImageExNews2.handle = LoadGraph(ImageExNews2.path);
	//if (ImageExNews2.handle == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), IMAGE_EX_NEWS2, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}
	//GetGraphSize(ImageExNews2.handle, &ImageExNews2.width, &ImageExNews2.height);
	ImageExNews2.x = MAP_DIV_WIDTH + (MAP_DIV_WIDTH / 4 - 2);
	ImageExNews2.y = MAP_DIV_HEIGHT * 2 + (MAP_DIV_HEIGHT / 4 * 3 - 2);
	ImageExNews2.IsDraw = FALSE;



	//�v���C���[�̉摜�i�����j1�L������
	int charRes = LoadDivGraph(
		IMAGE_CHAR_PATH,
		IMAGE_CHAR_NUM, CHAR_DIV_TATE, CHAR_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&player.handle2[0]);

	if (charRes == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_CHAR_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//�v���C���[�̉摜�i�����j�Q�L������
	int char2Res = LoadDivGraph(
		IMAGE_CHAR2_PATH,
		IMAGE_CHAR_NUM, CHAR_DIV_TATE, CHAR_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&player2.handle2[0]);

	if (char2Res == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_CHAR2_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�摜�̕��ƍ������擾
	GetGraphSize(player.handle2[0], &player.width, &player.height);
	GetGraphSize(player2.handle2[0], &player2.width, &player2.height);
	//�ʒu�E�T�C�Y�̐ݒ�
	player.x = GAME_WIDTH / 4;
	player.y = GAME_HEIGHT / 4;
	player.angle = 0;
	player.rate = 1.0;

	player2.x = GAME_WIDTH / 4 * 3;
	player2.y = GAME_HEIGHT / 2;
	player2.angle = 0;
	player2.rate = 1.0;

	//���������摜�̕`�揈��
	ImageWork.Cnt = 0.0;
	ImageWork.CntMAX = IMAGE_TITLE_WORK_CNT_MAX;
	for (int imageCharNUM = 0; imageCharNUM < WORK_CHAR_NUM; imageCharNUM++)
	{
		ImageChar[imageCharNUM].IsDraw = FALSE;

	}

	//�X�^�[�g��ʂ̃L�����N�^�[�X�^�[�g�ʒu
	playerSt.x = 0 + player.width;	//���E��������
	playerSt.y = GAME_HEIGHT - player.height;			//y�͌��_����

	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChip.handle[0]);

	if (mapRes == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			map[tate][yoko].kind = mapData[tate][yoko];

			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID)
{

	DeleteGraph(ImageBack.handle);
	DeleteGraph(ImageShadow.handle);

	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
	{
		DeleteGraph(ImageChar[0].handle);
	}

	DeleteGraph(player.handle);
	DeleteGraph(player2.handle);

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageEXPOBK.handle);
	DeleteGraph(RNKBACK.handle);
	DeleteGraph(RNKBACKNone.handle);
	DeleteGraph(RNKShadow.handle);
	DeleteGraph(stopBack.handle);
	DeleteGraph(ImageTitleROGO.handle);
	DeleteGraph(ImageTitleSTART.handle);
	DeleteGraph(ImageTitleRNK.handle);
	DeleteGraph(ImageSTeROGO.handle);
	DeleteGraph(ImageSTbROGO.handle);
	DeleteGraph(ImageEndFAIL.handle);
	DeleteGraph(ImageEndWD.handle);
	DeleteGraph(ImageEndROGO.handle);
	DeleteGraph(ImageNextROGO.handle);
	DeleteGraph(ImageChoiser.handle);
	DeleteGraph(ImageExNews1.handle);
	DeleteGraph(ImageExNews2.handle);


	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

BOOL MY_LOAD_MUSIC(VOID)
{
	MUSIC RoadM;
	if (!RoadM.RoadMusic(BGM, MUSIC_BGM_PATH)) { return FALSE; }					//�v���C��BGM
	if (!RoadM.RoadMusic(musicShot, MUSIC_PLAYER_SHOT_PATH)) { return FALSE; }		//�I����
	if (!RoadM.RoadMusic(BGM_TITLE, MUSIC_BGM_TITLE_PATH)) { return FALSE; }		//�^�C�g����BGM
	if (!RoadM.RoadMusic(BGM_COMP, MUSIC_BGM_COMP_PATH)) { return FALSE; }			//�E�o��BGM�iSTOP��ʂ���Q�[�����E�����Ƃ��j
	if (!RoadM.RoadMusic(BGM_FAIL, MUSIC_BGM_FAIL_PATH)) { return FALSE; }			//�Q�[���I�[�o�[��BGM�i��ʊO�ɏo���Ƃ��j
	if (!RoadM.RoadMusic(BGM_RANKING, MUSIC_BGM_RANK_PATH)) { return FALSE; }		//�����L���O��BGM
	if (!RoadM.RoadMusic(se_clock, MUSIC_CLOCK_BGM_PATH)) { return FALSE; }			//���v��SE
	if (!RoadM.RoadMusic(se_coin_g, MUSIC_COIN_BGM_PATH)) { return FALSE; }			//�R�C���Q�b�g��SE
	if (!RoadM.RoadMusic(se_brake, MUSIC_BRAKE_BGM_PATH)) { return FALSE; }			//�͂������ꂽSE
	if (!RoadM.RoadMusic(se_rogo_draw, MUSIC_STRAT_ROGO_BGM_PATH)) { return FALSE; }//������������SE
	if (!RoadM.RoadMusic(se_rain, MUSIC_RANI_BGM_PATH)) { return FALSE; }			//�J��SE
	if (!RoadM.RoadMusic(se_scene_sen, MUSIC_SCEN_SEN_BGM_PATH)) { return FALSE; }	//�V�[���J�ڂ�SE
	if (!RoadM.RoadMusic(se_move, MUSIC_MOVE_BGM_PATH)) { return FALSE; }			//�ړ���
	if (!RoadM.RoadMusic(se_pachin, MUSIC_PACHIN_BGM_PATH)) { return FALSE; }		//�w�p�b�`��
	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(musicShot.handle);
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);
	DeleteSoundMem(BGM_RANKING.handle);
	DeleteSoundMem(se_clock.handle);
	DeleteSoundMem(se_coin_g.handle);
	DeleteSoundMem(se_brake.handle);
	DeleteSoundMem(se_rogo_draw.handle);
	DeleteSoundMem(se_rain.handle);
	DeleteSoundMem(se_scene_sen.handle);
	DeleteSoundMem(se_move.handle);
	DeleteSoundMem(se_pachin.handle);

	return;
}


