#include<iostream>
#include <DxLib.h>

#define GAME_WIDTH     960
#define GAME_HEIGHT    576

class SetScore
{
protected:
	float Score = 0;
private:
	float TIMEScore = 0;
	int COINScore = 0;
public:
	void setS(float, float, float);
	float reS();
};

void SetScore::setS(float time_, float mintime_, float COINCnt_) {

	TIMEScore = floor(100 * (time_ * 10 + mintime_ * 600 + 20)) / 100;
	COINScore = COINCnt_ / 10 * 100;
	Score = TIMEScore + COINScore;

	return ;
}

float SetScore::reS() {
	return Score;
}

class DrawScore : public SetScore
{
public:
	void drawS(float, float, float);

};

void DrawScore::drawS(float time, float mintime, float COINCnt) {
	SetScore::setS(time, mintime, COINCnt);
	SetFontSize(64);
	DrawFormatString((GAME_WIDTH - GetDrawFormatStringWidth("スコア: %.2f", Score, -1)) / 2, GAME_HEIGHT / 4 * 3, GetColor(255, 255, 255), "スコア: %.2f", Score);
	return;
}
