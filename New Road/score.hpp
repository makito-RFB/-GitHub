#ifndef SCORE_HPP_DEFINED_
#define SCORE_HPP_DEFINED_

#include<iostream>
#include <DxLib.h>

#define GAME_WIDTH     960
#define GAME_HEIGHT    576

#define GAME_FPS	60

class SetScore
{
protected:
	float Score = 0;
private:
	float TIMEScore = 0;
	int COINScore = 0;
public:
	void setS(float, int, int);		//スコアをセットする
	float reS();					//スコアの返却

};

class DrawScore : public SetScore
{
public:
	bool drawS(float, int, int, int);	//スコアの描画と描画完了のフラグ返却
	void drawStop(float, int, int);
private:
	bool BTNIsDraw = false;
};

#endif // !SCORE_HPP_DEFINED_
