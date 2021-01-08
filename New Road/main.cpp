#include "DxLib.h"
#include "resource.h"
#include <random>
#include <stdlib.h>

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
#define FONT_TANU_NAME    TEXT("たぬき油性マジック")	

//#define FONT_TANU_PATH    TEXT(".\\FONT\\SoukouMincho.ttf")
//#define FONT_TANU_NAME    TEXT("装甲明朝")	


#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

#define IMAGE_BACK_PATH       TEXT(".\\IMAGE\\背景1.png")
#define IMAGE_SHADOW_PATH       TEXT(".\\IMAGE\\かげ.png")
#define IMAGE_BACK_ENDC_PATH	  TEXT(".\\IMAGE\\背景CONP.png")
#define IMAGE_BACK_ENDF_PATH	  TEXT(".\\IMAGE\\背景FALL.png")

#define IMAGE_CHAR_PATH       TEXT(".\\IMAGE\\char1.png")
#define IMAGE_CHAR_1_PATH	  TEXT(".\\IMAGE\\char2.png")
#define IMAGE_CHAR_2_PATH	  TEXT(".\\IMAGE\\char3.png")

#define IMAGE_CHAR_NUM			3	

#define IMAGE_EXPO_BACK TEXT(".\\IMAGE\\説明背景.png")
#define IMAGE_EX_NEWS1 TEXT(".\\IMAGE\\ルー説.png")
#define IMAGE_EX_NEWS2 TEXT(".\\IMAGE\\操説.png")


#define IMAGE_PLAYER_PATH	TEXT(".\\IMAGE\\ply1.png")

#define PLAYER_MOVE_COLLTIME 0.25 //秒

#define IMAGE_TITLE_BK_PATH		TEXT(".\\IMAGE\\strat背景.png")
#define IMAGE_TITLE_ROGO_PATH	TEXT(".\\IMAGE\\rogo2.png")
#define IMAGE_NEXT_ROGO_PATH		TEXT(".\\IMAGE\\NEXT.png")
#define IMAGE_TITLE_START_PATH	TEXT(".\\IMAGE\\GAME_start.png")
#define IMAGE_TITLE_RNK	TEXT(".\\IMAGE\\ranking.png")
#define IMAGE_TITLE_CHI	TEXT(".\\IMAGE\\Choies.png")

#define IMAGE_TITLE_WORK_CNT   1
#define IMAGE_TITLE_WORK_CNT_MAX   20

#define SCROLL_SPEED 1

#define IMAGE_END_FAIL_PATH		TEXT(".\\IMAGE\\失敗.png")
#define IMAGE_END_WITHDRAWAL_PATH		TEXT(".\\IMAGE\\成功.png")

#define IMAGE_END_ROGO_PATH	TEXT(".\\IMAGE\\ENRE.png")


#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define MUSIC_BGM_PATH			TEXT(".\\MUSIC\\PLAY.mp3")
#define MUSIC_PLAYER_SHOT_PATH	TEXT(".\\MUSIC\\ショット音.mp3")

#define MUSIC_BGM_TITLE_PATH	TEXT(".\\MUSIC\\OP.mp3")	//タイトルのBGM
#define MUSIC_BGM_COMP_PATH		TEXT(".\\MUSIC\\COMP.mp3")				//コンプリートBGM
#define MUSIC_BGM_FAIL_PATH		TEXT(".\\MUSIC\\FALL.mp3")					//フォールトBGM

#define GAME_MAP_TATE_MAX	9	//マップの縦の数
#define GAME_MAP_YOKO_MAX	18	//マップの横の数
#define GAME_MAP_KIND_MAX	2	//マップの種類の数

#define GAME_MAP_YOKO_NEW	15	//マップの更新横の数

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map.png")

#define MAP_DIV_WIDTH		64
#define MAP_DIV_HEIGHT		64
#define MAP_DIV_TATE		10
#define MAP_DIV_YOKO		4
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO

#define MOVE_ERIA 64

#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

#define GOAL_ERR_TITLE		TEXT("ゴール位置エラー")
#define GOAL_ERR_CAPTION	TEXT("ゴール位置が決まっていません")

#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、脱出しますか？")

enum GAME_MAP_KIND
{
	n = -1,	//(NONE)未定
	k = 0,	//壁
	m = 1,  //壁２
	r = 2,  //壁３
	l = 4,  //動く壁
	t = 9,	//通路
	s = 5,	//スタート
	c = 6,  //コイン
	g = 3	//アイテム
};	

enum GAME_MAP_KIND_PR
{
	np = -1,	//(NONE)未定
	kp = 0,	//壁
	mp = 1,  //壁２
	rp = 2,  //壁３
	lp = 4,  //動く壁
	tp = 9,	//通路
	sp = 5,	//スタート
	cp = 6,  //コイン
	gp = 3	//アイテム
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
	GAME_END_COMP,
	GAME_END_FAIL
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};

typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;

typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	
	iPOINT Point;		//マウスの座標が入る
	iPOINT OldPoint;	//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };
	int Button[MOUSE_BUTTON_CODE] = { 0 };
}MOUSE;

typedef struct STRUCT_FONT
{
	char path[PATH_MAX];
	char name[NAME_MAX];
	int handle;
	int size;
	int bold;
	int type;
}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];
	int handle;
	int x;
	int y;
	int width;
	int height;
}IMAGE;

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];
	int handle;
}MUSIC;

typedef struct STRUCT_CHARA
{
	IMAGE image;
	int speed;
	int CenterX;
	int CenterY;

	MUSIC musicShot;

	RECT coll;
	iPOINT collBeforePt;

}CHARA;


typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;
	BOOL IsDraw;
}IMAGE_BACK;

typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;

}IMAGE_ROTA;

typedef struct STRUCT_IMAGE_WORK
{
	IMAGE image;
	int Cnt;
	int CntMAX;
	BOOL IsDraw;

}IMAGE_WORK;

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;
	BOOL IsDraw;
	double rate;
	double angle;
}IMAGE_BLINK;

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
	GAME_MAP_KIND_PR kind2;
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

int newX = 0, newY = 0; //動かすブロックの座標

int waitCnt = 0;

int DrCharCnt = 0;

int ExDrawCnt = 1;

int ITEMCnt = 0, COINCnt = 0;

char AllKeyState[256] = { '\0' };
char OldAllKeyState[256] = { '\0' };

char direc; //向きのやつ

int timeCnt = 0;
float time = 0;
float mintime = 0;

float MAPmoveCnt = 0;

MOUSE mouse;

FONT FontTanu32;

int GameScene;

int GameEndKind;
RECT itemRect = { -1,-1, -1, -1 };

BOOL MY_KEY_TF = TRUE;

bool Kchoice = TRUE;

BOOL MY_CHAR_MOVE_ST = TRUE;

BOOL MY_MAP_RELOAD = TRUE;

BOOL FALL_RESON = FALSE;

BOOL CLICK_M = TRUE;

IMAGE_BACK ImageBack;
IMAGE_BACK ImageBackEND;
IMAGE_BACK ImageBackENDF;
IMAGE_BACK ImageShadow;

IMAGE ImageTitleBK;
IMAGE_ROTA ImageTitleROGO;
IMAGE_BLINK ImageTitleSTART;
IMAGE_BLINK ImageTitleRNK;

IMAGE ImageEXPOBK;

IMAGE_BACK ImageExNews1;
IMAGE_BACK ImageExNews2;

IMAGE_BACK ImageEndFAIL;
IMAGE_BACK ImageEndWD;

IMAGE_BLINK ImageNextROGO;
IMAGE_BLINK ImageEndROGO;
IMAGE ImageChoiser;

IMAGE_WORK ImageWork;

IMAGE_WORK ImageChar[IMAGE_CHAR_NUM];

CHARA player;

MUSIC BGM;

MUSIC BGM_TITLE;
MUSIC BGM_COMP;
MUSIC BGM_FAIL;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{ //3ブロックづつ
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,
		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
		k,t,t,t,l,t,t,l,t,t,l,k,t,t,l,k,t,t,	// 1
		k,t,t,l,t,l,t,l,t,k,t,t,l,t,t,t,l,t,	// 2
		k,l,t,t,t,k,t,k,t,c,l,t,l,t,l,t,l,t,	// 3
		k,t,t,l,t,k,s,k,l,k,l,l,k,t,l,l,k,t,	// 4
		k,l,l,t,l,t,t,k,t,t,l,t,k,t,l,t,k,t,	// 5
		k,t,t,k,t,l,t,k,l,t,g,t,k,g,g,t,k,g,	// 6
		k,t,t,k,t,k,t,l,t,t,l,t,t,t,l,t,t,t,	// 7
		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,	// 8

};

//マップ初期化用のバックアップ
GAME_MAP_KIND_PR mapDataPR[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7
		mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,mp,	// 0
		kp,tp,tp,tp,lp,tp,tp,lp,tp,tp,lp,kp,tp,tp,lp,kp,tp,tp,	// 1
		kp,tp,lp,tp,tp,lp,tp,lp,tp,kp,tp,tp,lp,tp,tp,tp,lp,tp,	// 2
		kp,lp,tp,tp,tp,kp,tp,kp,tp,cp,lp,tp,lp,tp,lp,tp,lp,tp,	// 3
		kp,tp,tp,lp,tp,kp,sp,kp,lp,kp,kp,lp,kp,tp,kp,lp,kp,tp,	// 4
		kp,lp,lp,tp,lp,tp,tp,kp,tp,tp,lp,tp,kp,tp,lp,tp,kp,tp,	// 5
		kp,tp,tp,kp,tp,lp,tp,kp,kp,tp,gp,tp,kp,gp,gp,tp,kp,gp,	// 6
		kp,tp,tp,kp,tp,kp,tp,lp,tp,tp,lp,tp,tp,tp,lp,tp,tp,tp,	// 7
		rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,rp,	// 8

};

GAME_MAP_KIND mapDataNEW[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{ //3ブロックづつ
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,
		m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,m,	// 0
		t,t,t,t,l,t,t,l,t,t,l,k,t,t,l,k,t,t,	// 1
		t,t,t,l,t,l,t,l,t,k,t,t,l,t,t,t,l,t,	// 2
		t,l,t,t,t,k,t,k,t,t,l,t,l,t,l,t,l,t,	// 3
		t,t,k,t,t,t,l,t,t,t,l,t,t,t,t,t,k,t,	// 4
		t,l,l,t,l,t,t,k,t,t,l,t,k,t,l,t,k,t,	// 5
		t,t,t,k,t,l,t,k,l,t,g,t,k,g,g,t,k,g,	// 6
		t,t,t,k,t,k,t,l,t,t,l,t,t,t,l,t,t,t,	// 7
		r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,
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

VOID MY_MOUSE_UPDATE(VOID);
BOOL MY_MOUSE_DOWN(int);
BOOL MY_MOUSE_UP(int);
BOOL MY_MOUSEDOWN_KEEP(int, int);

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
VOID MAP_DRAW(IMAGE_BACK ImageBack);
VOID ROCKETMAP(VOID);

CHAR MY_DIRECTION(double, double, double, double);

char* TEXT_DRAW(int);

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

	ChangeFont("たぬき油性マジック", DX_CHARSET_DEFAULT);
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

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }
		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();

		MY_MOUSE_UPDATE();

		MY_FPS_UPDATE();

		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_EXPO:
			MY_EXPO();
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();
			break;
		case GAME_SCENE_END:
			MY_END();
			break;
		case GAME_SCENE_RNKING:
			MY_RNKING();
			break;
		case GAME_SCENE_STOP:
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

VOID MY_MOUSE_UPDATE(VOID)
{
	mouse.OldPoint = mouse.Point;

	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	mouse.InputValue = GetMouseInput();

	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }

	return;
}

BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1
		&& mouse.Button[MOUSE_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

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

	return TRUE;
}

VOID MY_FONT_DELETE(VOID)
{
	DeleteFontToHandle(FontTanu32.handle);

	return;
}

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


	if (check == TRUE) {
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE || MY_KEY_DOWN(KEY_INPUT_UP) == TRUE) {
			Kchoice = !Kchoice;
			check = FALSE;
		}
	}
	if (MY_KEY_UP(KEY_INPUT_DOWN) == TRUE || MY_KEY_UP(KEY_INPUT_UP) == TRUE)
		check = TRUE;


	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE)
	{
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
			MusicPass = FALSE;
		}
		SetMouseDispFlag(FALSE);

		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		SetMousePoint(player.image.x, player.image.y);

		GameEndKind = GAME_END_FAIL;
	}

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE && Kchoice == TRUE) {
		//GameScene = GAME_SCENE_PLAY;
		MusicPass = TRUE;
		CLICK_M = TRUE;
		GameScene = GAME_SCENE_EXPO;
		MY_MAP_RELOAD = TRUE;
		return;
	}
//
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

//選択音
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
	}

	//後ろ歩く処理
	if (ImageChar[1].IsDraw == FALSE && MY_CHAR_MOVE_ST == TRUE) {
		ImageChar[1].IsDraw = TRUE;
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
			if (DrCharCnt == 1)
			ImageChar[0].IsDraw = FALSE;

			if (DrCharCnt == 0)
				ImageChar[2].IsDraw = FALSE;

			ImageChar[1].IsDraw = TRUE;
		}
		
		for (int num = 0; num < IMAGE_CHAR_NUM; num++) {
			ImageChar[num].image.x += 16;

			if (ImageChar[num].image.x > GAME_WIDTH) {
				ImageChar[num].image.x -= GAME_WIDTH + player.image.width;
			}
		}
		ImageWork.Cnt = 0;

	}

	//タイマ初期化
	timeCnt = 0;
	time = 0;
	mintime = 0;

	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);

	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
	{
		if (ImageChar[num].IsDraw == TRUE)
		{
			DrawGraph(ImageChar[num].image.x, ImageChar[num].image.y, ImageChar[num].image.handle, TRUE);
		}
	}

	DrawGraph(ImageTitleROGO.image.x, ImageTitleROGO.image.y, ImageTitleROGO.image.handle, TRUE);
	
	DrawRotaGraph(
		ImageTitleSTART.image.x, ImageTitleSTART.image.y,
		ImageTitleSTART.rate,
		ImageTitleSTART.angle,
		ImageTitleSTART.image.handle, TRUE);

	DrawRotaGraph(
		ImageTitleRNK.image.x, ImageTitleRNK.image.y,
		ImageTitleRNK.rate,
		ImageTitleRNK.angle,
		ImageTitleRNK.image.handle, TRUE);

	DrawGraph(ImageChoiser.x, ImageChoiser.y, ImageChoiser.handle, TRUE);

//上下選択の動き

	if (Kchoice == TRUE) {
		ImageTitleSTART.rate = 1.2; 
		ImageTitleRNK.rate = 1.0;
		ImageChoiser.x = ImageTitleSTART.image.x + ImageTitleSTART.image.width / 2 + 32;
		ImageChoiser.y = ImageTitleSTART.image.y + ImageTitleSTART.image.height / 4 - ImageChoiser.height / 2 ;
	}
	else {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.2;
		ImageChoiser.x = ImageTitleRNK.image.x + ImageTitleRNK.image.width / 2 + 32;
		ImageChoiser.y = ImageTitleRNK.image.y + ImageTitleRNK.image.height / 4 - ImageChoiser.height / 2;
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE) {
		if (Kchoice == TRUE) 
			ImageTitleSTART.rate = 0.8;
		else 
			ImageTitleRNK.rate = 0.8;
		ImageChoiser.x -= 32;
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.0;
		ImageChoiser.x += 32;
	}
	//DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

VOID MY_EXPO(VOID)
{
	MY_EXPO_PROC();
	MY_EXPO_DRAW();

	return;
}

VOID MY_EXPO_PROC(VOID) {
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	switch (ExDrawCnt)
	{
	case 1:
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			CLICK_M = TRUE;
			ExDrawCnt = 2;
		}
		break;
	//case 3:
	//	if (MY_KEY_UP(KEY_INPUT_RETURN)) {
	//		ExDrawCnt = 3;
	//		CLICK_M = TRUE;
	//	}  //ここパス
		break;
	case 2:
		if (MY_KEY_UP(KEY_INPUT_RETURN)) {
			ExDrawCnt = 1;
			if (CheckSoundMem(BGM_TITLE.handle) != 0)
			{
				StopSoundMem(BGM_TITLE.handle);
			}
			ITEMCnt = 0;
			CLICK_M = TRUE;
			GameScene = GAME_SCENE_PLAY;
		}
		break;
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN)) {

		if (CLICK_M == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
	}
	return;
}

VOID MY_EXPO_DRAW(VOID) {
	static int StrDraw = 0;
	DrawGraph(ImageEXPOBK.x, ImageEXPOBK.y, ImageEXPOBK.handle, TRUE);

	switch (ExDrawCnt)
	{
	case 1:
		GAME_RULE();
		DrawGraph(ImageExNews1.image.x, ImageExNews1.image.y, ImageExNews1.image.handle, TRUE);
		break;
	case 2:
		GAME_PILOT();
		DrawGraph(ImageExNews2.image.x, ImageExNews2.image.y, ImageExNews2.image.handle, TRUE);
		break;
	//case 3:
	//	GAME_STR();
	//	break;　　//ここパス
	}

	char* str = NULL;
	SetFontSize(44);
	str = TEXT_DRAW(ExDrawCnt);
	StrDraw = GetDrawStringWidth(str, -1);
	DrawString((GAME_WIDTH - StrDraw) / 2, 10, str, GetColor(255, 0, 0));

	DrawRotaGraph(
		ImageNextROGO.image.x, ImageNextROGO.image.y,
		ImageNextROGO.rate,
		ImageNextROGO.angle,
		ImageNextROGO.image.handle, TRUE);

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		ImageNextROGO.rate = 0.8;

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		FALL_RESON = FALSE;
		ImageNextROGO.rate = 1.0;
	}

	free(str);

	return;
}

VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

	return;
}

VOID MY_PLAY_PROC(VOID)
{
	static int colltime = 0;
	player.collBeforePt.x -= SCROLL_SPEED; //スクロール時の過去位置の誤差修正

	if (CheckSoundMem(BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);

		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	MAP_LOAD();

	//タイマ処理
	if (timeCnt >= 60)
	{
		time = time - 0.016 * timeCnt;
		timeCnt = 0;
		time++;
	}
	if (time >= 60)
	{
		time = 0;
		mintime++;
	}
	time += 0.016;
	timeCnt++;

	//マップ移動

	player.CenterX -= SCROLL_SPEED;

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップを移動当たり判定も移動
			map[tate][yoko].x -= SCROLL_SPEED;
			mapColl[tate][yoko].left -= SCROLL_SPEED;
			mapColl[tate][yoko].right -= SCROLL_SPEED;
			//if (map[tate][yoko].x >= GAME_WIDTH)
			//{
			//	map[tate][yoko].IsDraw = FALSE;
			//}
		}

	}

	MAPmoveCnt++;


	if (MAPmoveCnt >= MAP_DIV_WIDTH * 3)
	{
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//マップを移動当たり判定も移動
				map[tate][yoko].x += MAPmoveCnt;
				mapColl[tate][yoko].left += MAPmoveCnt;
				mapColl[tate][yoko].right += MAPmoveCnt;

			}
		
		}
		ROCKETMAP();
		MAPmoveCnt = 0;
	}


	if (MY_KEY_UP(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}
		/*iPOINT R_ClickPt = mouse.Point;

		SetMouseDispFlag(TRUE);

		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)
		{
			

			SetMouseDispFlag(TRUE);

			GameEndKind = GAME_END_COMP;

			GameScene = GAME_SCENE_END;
			return;

		}
		else if (Ret == IDNO)
		{
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			SetMouseDispFlag(FALSE);
		}*/


		GameScene = GAME_SCENE_STOP;
	}



	//一回の入力判定（押したととき）
	if (MY_KEY_TF == TRUE) {
		if (MY_KEY_DOWN(KEY_INPUT_W)) {
			player.CenterY -= MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

		if (MY_KEY_DOWN(KEY_INPUT_A)) {
			player.CenterX -= MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

		if (MY_KEY_DOWN(KEY_INPUT_S)) {
			player.CenterY += MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

		if (MY_KEY_DOWN(KEY_INPUT_D)) {
			player.CenterX += MOVE_ERIA;
			MY_KEY_TF = FALSE;
		}

	}

	//一回の入力判定（離したとき）
	if (MY_KEY_TF == FALSE) {
		if (colltime > PLAYER_MOVE_COLLTIME * GAME_FPS)
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

	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	//向きを入れる
	direc = MY_DIRECTION(player.CenterX, player.CenterY, player.collBeforePt.x, player.collBeforePt.y);

	BOOL IsMove = TRUE;

	RECT PlayerRect;
	int CollRange = 5;
	PlayerRect.left = player.image.x + player.image.width / 2 - CollRange;
	PlayerRect.top = player.image.y + player.image.height / 2 - CollRange;
	PlayerRect.right = player.image.x + player.image.width / 2 + CollRange;
	PlayerRect.bottom = player.image.y + player.image.height / 2 + CollRange;


	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		IsMove = FALSE;

		newX = ((player.CenterX + MAPmoveCnt) - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH; //移動のプラス
		newY = (player.CenterY - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;

		if (map[newY][newX].kind == l)
		{
			//マップの更新
			BOOL IsReMove = FALSE;

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


			//障害物をアイテムで破壊
				if (ITEMCnt > 0 && IsReMove == FALSE)
				{
					IsReMove = TRUE;
					ITEMCnt--;
				}
			}
			if (IsReMove == TRUE)
			{
				//当たり判定更新＆画像削除
				mapData[newY][newX] = t;
				map[newY][newX].kind = t;
				IsReMove = FALSE;
			}//マップ更新ここまで

			
		}

		////元の位置に戻る
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
	}

	/*if (MY_CHECK_RECT_COLL(PlayerRect, itemRect) == TRUE)*/
	

	if (IsMove == TRUE)
	{
		int x = ((player.CenterX + MAPmoveCnt) - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;  //移動分プラス
		int y = (player.CenterY - MAP_DIV_WIDTH / 2) / MAP_DIV_WIDTH;
		switch (map[y][x].kind)
		{
		case g:
			//アイテム取得とアイテムの当たり判定削除
			mapData[y][x] = t;
			map[y][x].kind = t;
			ITEMCnt++;
			break;
		case c:
			//コイン取得とコインの当たり判定削除
			mapData[y][x] = t;
			map[y][x].kind = t;
			COINCnt++;
			break;
		default:
			break;
			
		}
	
	//プレイヤー前の位置書き換え
		player.image.x = player.CenterX - player.image.width / 2;
		player.image.y = player.CenterY - player.image.height / 2;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;
	}

	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
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
//背景スクロール
	MAP_DRAW(ImageBack);
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

	//プレイヤーを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//shadow
	DrawGraph(ImageShadow.image.x, ImageShadow.image.y, ImageShadow.image.handle, TRUE);

	//タイマーとアイテム描画
	SetFontSize(25);

	if (time >= 60 || mintime >= 1) {
		DrawFormatString(0, 5, GetColor(0, 0, 200), "TIME:%d分%.2f秒", mintime, time);
	}
	else
	{
		DrawFormatString(0, 5, GetColor(0, 0, 200), "TIME:%.2f秒", time);

	}

	DrawFormatString(GAME_WIDTH - GetDrawFormatStringWidth("アイテム:% d個", ITEMCnt, -1), 5, GetColor(200, 0, 0), "アイテム:%d個", ITEMCnt);

	//当たり判定の描画（デバッグ用）
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//壁ならば
			if (mapData[tate][yoko] == k || mapData[tate][yoko] == l)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//通路ならば
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}
		}
	}

	////ゴールの描画（デバッグ用）
	//DrawBox(GoalRect.left, GoalRect.top, GoalRect.right, GoalRect.bottom, GetColor(255, 255, 0), TRUE);


	//当たり判定の描画（デバッグ用）
	DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);



	SetFontSize(30);
	StrWidth = GetDrawStringWidth("_/_/ 移動キー：W【↑】A【←】S【↓】D【→】| 停止:ESC _/_/", -1);//中央寄せ
	DrawString((GAME_WIDTH - StrWidth )/ 2, GAME_HEIGHT - 45, "_/_/ 移動キー：W【↑】A【←】S【↓】D【→】| 停止:ESC _/_/", GetColor(255, 255, 255));
	SetFontSize(20);
	//DrawString((GAME_WIDTH - GetDrawStringWidth("※制作途中のため「画面端に出る」もしくは「停止画面」から脱出してください※", -1)) / 2, GAME_HEIGHT - 64, "※制作途中のため画面端に出るもしくは停止画面からゴールへ行ってください※", GetColor(255, 0, 0));
	return;
}

VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();
	return;
}

VOID MY_END_PROC(VOID)
{
	static BOOL MusicPass1 = TRUE;
	if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
	{
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
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

		GameScene = GAME_SCENE_START;

		MusicPass1 = TRUE;

		return;
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
	static float Score = 0;
	static float TIMEScore = 0, COINScore = 0;
	MY_PLAY_DRAW();

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		DrawGraph(ImageBackEND.image.x, ImageBackEND.image.y, ImageBackEND.image.handle, TRUE);

		DrawGraph(ImageEndWD.image.x, ImageEndWD.image.y, ImageEndWD.image.handle, TRUE);

		break;

	case GAME_END_FAIL:
		DrawGraph(ImageBackENDF.image.x, ImageBackENDF.image.y, ImageBackENDF.image.handle, TRUE);

		DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);

		break;
	}

	SetFontSize(64);

	TIMEScore = time * 10 + mintime * 600 + 20;
	COINScore = COINCnt / 10 * 

	DrawFormatString((GAME_WIDTH - GetDrawFormatStringWidth("スコア: %.2f", Score, -1)) / 2, GAME_HEIGHT / 4 * 3, GetColor(255, 255, 255), "スコア: %.2f", Score);

	SetFontSize(16.5);

	DrawRotaGraph(
		ImageEndROGO.image.x, ImageEndROGO.image.y,
		ImageEndROGO.rate,
		ImageEndROGO.angle,
		ImageEndROGO.image.handle, TRUE);

	if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
		ImageEndROGO.rate = 0.8;

	if (MY_KEY_UP(KEY_INPUT_BACK) == TRUE) {
		FALL_RESON = FALSE;
		ImageEndROGO.rate = 1.0;
	}
	return;
}

BOOL MY_LOAD_IMAGE(VOID)
{
//タイトル背景
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	if (ImageTitleBK.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;

//タイトルロゴ
	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);
	if (ImageTitleROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);
	ImageTitleROGO.image.x = GAME_WIDTH / 2 - ImageTitleROGO.image.width / 2;
	ImageTitleROGO.image.y = GAME_HEIGHT / 2 - ImageTitleROGO.image.height / 2;

//タイトルスタート
	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);
	if (ImageTitleSTART.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);
	ImageTitleSTART.image.x = GAME_WIDTH / 2;
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + 32;
	ImageTitleSTART.angle = 0;
	ImageTitleSTART.rate = 1.0;

//ランキング選択
	strcpy_s(ImageTitleRNK.image.path, IMAGE_TITLE_RNK);
	ImageTitleRNK.image.handle = LoadGraph(ImageTitleRNK.image.path);
	if (ImageTitleRNK.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_RNK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleRNK.image.handle, &ImageTitleRNK.image.width, &ImageTitleRNK.image.height);
	ImageTitleRNK.image.x = GAME_WIDTH / 2;
	ImageTitleRNK.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height + ImageTitleSTART.image.height + 40;
	ImageTitleRNK.angle = 0;
	ImageTitleRNK.rate = 1.0;

//選択印
	strcpy_s(ImageChoiser.path, IMAGE_TITLE_CHI);
	ImageChoiser.handle = LoadGraph(ImageChoiser.path);
	if (ImageChoiser.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_CHI, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageChoiser.handle, &ImageChoiser.width, &ImageChoiser.height);
	ImageChoiser.x = ImageTitleSTART.image.x + ImageTitleSTART.image.width / 2 + 32;
	ImageChoiser.y = ImageTitleSTART.image.y + ImageTitleSTART.image.height / 4 - ImageChoiser.height / 2;


//ゲーム説明
	strcpy_s(ImageEXPOBK.path, IMAGE_EXPO_BACK);
	ImageEXPOBK.handle = LoadGraph(ImageEXPOBK.path);
	if (ImageEXPOBK.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_EXPO_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEXPOBK.handle, &ImageEXPOBK.width, &ImageEXPOBK.height);
	ImageEXPOBK.x = GAME_WIDTH / 2 - ImageEXPOBK.width / 2;
	ImageEXPOBK.y = GAME_HEIGHT / 2 - ImageEXPOBK.height / 2;

//動く画像（タイトル）
	strcpy_s(ImageChar[0].image.path, IMAGE_CHAR_PATH);			//パスの設定
	strcpy_s(ImageChar[1].image.path, IMAGE_CHAR_1_PATH);		//パスの設定(背景画像反転)
	strcpy_s(ImageChar[2].image.path, IMAGE_CHAR_2_PATH);			//パスの設定

	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
	{
		ImageChar[num].image.handle = LoadGraph(ImageChar[num].image.path);	//読み込み
		if (ImageChar[num].image.handle == -1)
		{
			//エラーメッセージ表示
			MessageBox(GetMainWindowHandle(), IMAGE_CHAR_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//画像の幅と高さを取得
		GetGraphSize(ImageChar[num].image.handle, &ImageChar[num].image.width, &ImageChar[num].image.height);
		ImageWork.Cnt = 0.0;
		ImageWork.CntMAX = IMAGE_TITLE_WORK_CNT_MAX;

	}
//キャラの設定
	ImageChar[0].image.x = GAME_WIDTH / 2 - ImageChar[0].image.width / 2;	//左右中央揃え
	ImageChar[0].image.y = GAME_HEIGHT - ImageChar[0].image.height;			//yは原点から
	ImageChar[0].IsDraw = FALSE;

	ImageChar[1].image.x = GAME_WIDTH / 2 - ImageChar[1].image.width / 2;	//左右中央揃え
	ImageChar[1].image.y = GAME_HEIGHT - ImageChar[1].image.height;			//yは原点から
	ImageChar[1].IsDraw = FALSE;

	ImageChar[2].image.x = GAME_WIDTH / 2 - ImageChar[2].image.width / 2;	//左右中央揃え
	ImageChar[2].image.y = GAME_HEIGHT - ImageChar[2].image.height;			//yは原点から
	ImageChar[2].IsDraw = FALSE;

//エンドフォール
	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);
	if (ImageEndFAIL.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);
	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2 - 32;

//エンド撤退
	strcpy_s(ImageEndWD.image.path, IMAGE_END_WITHDRAWAL_PATH);
	ImageEndWD.image.handle = LoadGraph(ImageEndWD.image.path);
	if (ImageEndWD.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_WITHDRAWAL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndWD.image.handle, &ImageEndWD.image.width, &ImageEndWD.image.height);
	ImageEndWD.image.x = GAME_WIDTH / 2 - ImageEndWD.image.width / 2;
	ImageEndWD.image.y = GAME_HEIGHT / 2 - ImageEndWD.image.height / 2 - 32;

//エスケーププッシュ
	strcpy_s(ImageEndROGO.image.path, IMAGE_END_ROGO_PATH);
	ImageEndROGO.image.handle = LoadGraph(ImageEndROGO.image.path);
	if (ImageEndROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndROGO.image.handle, &ImageEndROGO.image.width, &ImageEndROGO.image.height);
	ImageEndROGO.image.x = GAME_WIDTH - 70;
	ImageEndROGO.image.y = GAME_HEIGHT - 50;
	ImageEndROGO.angle = 0; 
	ImageEndROGO.rate = 1.0;

//NEXT PUSH
	strcpy_s(ImageNextROGO.image.path, IMAGE_NEXT_ROGO_PATH);
	ImageNextROGO.image.handle = LoadGraph(ImageNextROGO.image.path);
	if (ImageNextROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_NEXT_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageNextROGO.image.handle, &ImageNextROGO.image.width, &ImageNextROGO.image.height);
	ImageNextROGO.image.x = GAME_WIDTH - 70;
	ImageNextROGO.image.y = GAME_HEIGHT - 50;
	ImageNextROGO.angle = 0;
	ImageNextROGO.rate = 1.0;


//背景画像
	strcpy_s(ImageBack.image.path, IMAGE_BACK_PATH);
	ImageBack.image.handle = LoadGraph(ImageBack.image.path);
	if (ImageBack.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBack.image.handle, &ImageBack.image.width, &ImageBack.image.height);
	ImageBack.image.x = GAME_WIDTH / 2 - ImageBack.image.width / 2;
	ImageBack.image.y = 0 - ImageBack.image.height * 0;
	ImageBack.IsDraw = FALSE;

//shadow
	strcpy_s(ImageShadow.image.path, IMAGE_SHADOW_PATH);
	ImageShadow.image.handle = LoadGraph(ImageShadow.image.path);
	if (ImageShadow.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_SHADOW_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageShadow.image.handle, &ImageShadow.image.width, &ImageShadow.image.height);
	ImageShadow.image.x = GAME_WIDTH / 2 - ImageShadow.image.width / 2;
	ImageShadow.image.y = 0 - ImageShadow.image.height * 0;
	ImageShadow.IsDraw = FALSE;


//背景画像END
	strcpy_s(ImageBackEND.image.path, IMAGE_BACK_ENDC_PATH);
	ImageBackEND.image.handle = LoadGraph(ImageBackEND.image.path);
	if (ImageBackEND.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDC_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBackEND.image.handle, &ImageBackEND.image.width, &ImageBackEND.image.height);
	ImageBackEND.image.x = GAME_WIDTH / 2 - ImageBackEND.image.width / 2;
	ImageBackEND.image.y = 0 - ImageBackEND.image.height * 0;
	ImageBackEND.IsDraw = FALSE;

//背景画像ENDF
	strcpy_s(ImageBackENDF.image.path, IMAGE_BACK_ENDF_PATH);
	ImageBackENDF.image.handle = LoadGraph(ImageBackENDF.image.path);
	if (ImageBackENDF.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_ENDF_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBackENDF.image.handle, &ImageBackENDF.image.width, &ImageBackENDF.image.height);
	ImageBackENDF.image.x = GAME_WIDTH / 2 - ImageBackENDF.image.width / 2;
	ImageBackENDF.image.y = 0 - ImageBackENDF.image.height * 0;
	ImageBackENDF.IsDraw = FALSE;


//プレイヤーの画像
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
	player.image.handle = LoadGraph(player.image.path);
	if (player.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;
	player.CenterX = player.image.x + player.image.width / 2;
	player.CenterY = player.image.y + player.image.height / 2;
	player.speed = CHARA_SPEED_LOW;

//説明画像１
	strcpy_s(ImageExNews1.image.path, IMAGE_EX_NEWS1);
	ImageExNews1.image.handle = LoadGraph(ImageExNews1.image.path);
	if (ImageExNews1.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_EX_NEWS1, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageExNews1.image.handle, &ImageExNews1.image.width, &ImageExNews1.image.height);
	ImageExNews1.image.x = MAP_DIV_WIDTH + (MAP_DIV_WIDTH / 4 - 2);
	ImageExNews1.image.y = MAP_DIV_HEIGHT * 2 + (MAP_DIV_HEIGHT / 4 * 3 - 2);
	ImageExNews1.IsDraw = FALSE;

//説明画像2
	strcpy_s(ImageExNews2.image.path, IMAGE_EX_NEWS2);
	ImageExNews2.image.handle = LoadGraph(ImageExNews2.image.path);
	if (ImageExNews2.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_EX_NEWS2, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageExNews2.image.handle, &ImageExNews2.image.width, &ImageExNews2.image.height);
	ImageExNews2.image.x = MAP_DIV_WIDTH + (MAP_DIV_WIDTH /4 - 2);
	ImageExNews2.image.y = MAP_DIV_HEIGHT * 2 + (MAP_DIV_HEIGHT / 4 * 3 - 2);
	ImageExNews2.IsDraw = FALSE;

//マップの画像を分割する
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

	DeleteGraph(ImageBack.image.handle);
	DeleteGraph(ImageShadow.image.handle);

	for (int num = 0; num < IMAGE_CHAR_NUM; num++)
	{
		DeleteGraph(ImageChar[0].image.handle);
	}

	DeleteGraph(player.image.handle);

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageEXPOBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);
	DeleteGraph(ImageTitleRNK.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);
	DeleteGraph(ImageEndWD.image.handle);
	DeleteGraph(ImageEndROGO.image.handle);
	DeleteGraph(ImageNextROGO.image.handle);
	DeleteGraph(ImageChoiser.handle);
	DeleteGraph(ImageExNews1.image.handle);
	DeleteGraph(ImageExNews2.image.handle);


	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

BOOL MY_LOAD_MUSIC(VOID)
{
	strcpy_s(BGM.path, MUSIC_BGM_PATH);
	BGM.handle = LoadSoundMem(BGM.path);
	if (BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);
	if (player.musicShot.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM_TITLE.path, MUSIC_BGM_TITLE_PATH);
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);
	if (BGM_TITLE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_TITLE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);
	BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);
	if (BGM_COMP.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);
	BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);
	if (BGM_FAIL.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(player.musicShot.handle);
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);

	return;
}

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

//動いた向きをとる
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

VOID MAP_LOAD(VOID)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (mapData[tate][yoko] == g)
			{
				itemRect.left = mapChip.width * yoko;
				itemRect.top = mapChip.height * tate;
				itemRect.right = mapChip.width * (yoko + 1);
				itemRect.bottom = mapChip.height * (tate + 1);
			}
		}
	}

	if (MY_MAP_RELOAD == TRUE) {
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				if (mapDataPR[tate][yoko] == lp) {
					mapData[tate][yoko] = l;
					map[tate][yoko].kind = l;
				}
				else if (mapDataPR[tate][yoko] == tp) {
					mapData[tate][yoko] = t;
					map[tate][yoko].kind = t;
				}
				else if (mapDataPR[tate][yoko] == gp) {
					mapData[tate][yoko] = g;
					map[tate][yoko].kind = g;
				}
			}
		}
	//位置初期化
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//マップを移動当たり判定も移動
				map[tate][yoko].x += MAPmoveCnt;
				mapColl[tate][yoko].left += MAPmoveCnt;
				mapColl[tate][yoko].right += MAPmoveCnt;

			}

		}
		MAPmoveCnt = 0;
		MY_MAP_RELOAD = FALSE;
	}
}

char* TEXT_DRAW(int n)
{
	char* cp = NULL;

	


	cp = (char*)malloc(sizeof(char) * 30);

	if (cp == NULL) {
		printf("配列作成失敗\n");
	}

	switch (n)
	{
	case 1:
		strcpy_s(cp, 22, "ゲームのルールと目標");		break;
	case 2:
		strcpy_s(cp, 30, "操作説明とアイテムについいて");		break;
	case 3:
		strcpy_s(cp, 16, "ストーリー");		break;
	}

	return cp;

}

VOID GAME_RULE(VOID)
{
	SetFontSize(32);
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 3, "ゲーム目標", GetColor(160, 0, 80));
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 5.5, "ゲームルール", GetColor(160, 0, 80));
	SetFontSize(25);
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 3.5 + 5, "長く生き残り、\n高スコアを叩きだせ！", GetColor(0, 0, 0));
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 6 + 5, "流れるマップの障害物を\n避けて・動かして・破壊して\n移動できる道を新たに開拓、\nより長く画面内ににとどまり\n生き残れ", GetColor(0, 0, 0));

	return;
}

VOID GAME_PILOT(VOID)
{
	SetFontSize(32);
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 3, "操作方法", GetColor(160, 0, 80));
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 5 + 5, "アイテムについて", GetColor(160, 0, 80));
	SetFontSize(25);
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 3.5 + 5, "キャラの移動は「W A S D」\n一旦停止を行うには「ESCキー」\nその他選択は「エンターキー」", GetColor(0, 0, 0));
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 5.5 + 10, "マップ内に落ちているアイテム\nを使い可動障害物を破壊する\nことが可能。\nアイテムのストックが可能で\n使うタイミング次第で危機を\n脱せる可能性も！！", GetColor(0, 0, 0));

	return;
}

VOID GAME_STR(VOID)
{
	SetFontSize(32);
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 3, "はじまりの物語", GetColor(0, 0, 0));
	DrawString(MOVE_ERIA * 8, MOVE_ERIA * 5 + 5, "　", GetColor(0, 0, 0));
	SetFontSize(25);
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 3.5 + 5, "あなたは謎の空間に飛ばされ\n", GetColor(0, 0, 0));
	DrawString(MOVE_ERIA * 8.5 - 10, MOVE_ERIA * 5.5 + 10, "　", GetColor(0, 0, 0));

	return;
}

//背景スクロール
VOID MAP_DRAW(IMAGE_BACK ImageBack)
{
	DrawGraph(ImageBack.image.x, ImageBack.image.y, ImageBack.image.handle, TRUE);

	//二枚目描画
	DrawGraph(ImageBack.image.x - GAME_WIDTH, ImageBack.image.y, ImageBack.image.handle, TRUE);

	//一番下までスクロールしたら初期値に戻す
	if (ImageBack.image.x == GAME_WIDTH + 10)
		ImageBack.image.x = 10;

	ImageBack.image.x += SCROLL_SPEED;

	return;
}

VOID ROCKETMAP(VOID)
{
	int plusYoko = 0;
	int newMapYoko = 0;
	int rndInt = 0;
	rndInt = rand() % 5 + 1;
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
			newMapYoko = (yoko - GAME_MAP_YOKO_NEW) + rndInt * 3;
			mapData[tate][yoko] = mapDataNEW[tate][newMapYoko];
			map[tate][yoko].kind = mapDataNEW[tate][newMapYoko];
		}
	}
	return;
}


//stop画面処理
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

	if (CheckSoundMem(BGM_TITLE.handle) == 0 && MusicPass == TRUE)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}
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
		GameScene = GAME_SCENE_PLAY;
		return;
	}

//選択音
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		if (CLICK_M == TRUE)
		{
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			CLICK_M = FALSE;
		}
	}
	return;
}

VOID MY_STOP_DRAW(VOID)
{
	MY_PLAY_DRAW();
//DrawGraph(ImageEXPOBK.x, ImageEXPOBK.y, ImageEXPOBK.handle, TRUE);
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);

	DrawGraph(ImageTitleROGO.image.x, ImageTitleROGO.image.y, ImageTitleROGO.image.handle, TRUE);

	DrawRotaGraph(
		ImageTitleSTART.image.x, ImageTitleSTART.image.y,
		ImageTitleSTART.rate,
		ImageTitleSTART.angle,
		ImageTitleSTART.image.handle, TRUE);

	DrawRotaGraph(
		ImageTitleRNK.image.x, ImageTitleRNK.image.y,
		ImageTitleRNK.rate,
		ImageTitleRNK.angle,
		ImageTitleRNK.image.handle, TRUE);

	DrawGraph(ImageChoiser.x, ImageChoiser.y, ImageChoiser.handle, TRUE);


	if (Kchoice == TRUE) {
		ImageTitleSTART.rate = 1.2;
		ImageTitleRNK.rate = 1.0;
		ImageChoiser.x = ImageTitleSTART.image.x + ImageTitleSTART.image.width / 2 + 32;
		ImageChoiser.y = ImageTitleSTART.image.y + ImageTitleSTART.image.height / 4 - ImageChoiser.height / 2;
	}
	else {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.2;
		ImageChoiser.x = ImageTitleRNK.image.x + ImageTitleRNK.image.width / 2 + 32;
		ImageChoiser.y = ImageTitleRNK.image.y + ImageTitleRNK.image.height / 4 - ImageChoiser.height / 2;
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE) {
		if (Kchoice == TRUE)
			ImageTitleSTART.rate = 0.8;
		else
			ImageTitleRNK.rate = 0.8;
		ImageChoiser.x -= 32;
	}
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {
		ImageTitleSTART.rate = 1.0;
		ImageTitleRNK.rate = 1.0;
		ImageChoiser.x += 32;
	}

}
//ランキング
VOID MY_RNKING(VOID)
{
	MY_RNKING_PROC();
	MY_RNKING_DRAW();
	return;
}

VOID MY_RNKING_PROC(VOID)
{
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE) {

		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_START;

		return;
	}
}

VOID MY_RNKING_DRAW(VOID)
{
	DrawGraph(ImageEXPOBK.x, ImageEXPOBK.y, ImageEXPOBK.handle, TRUE);

}
