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
	void setS(float, int, int);		//�X�R�A���Z�b�g����
	float reS();					//�X�R�A�̕ԋp

};

class DrawScore : public SetScore
{
public:
	bool drawS(float, int, int, int);	//�X�R�A�̕`��ƕ`�抮���̃t���O�ԋp
	void drawStop(float, int, int);
private:
	bool BTNIsDraw = false;
};

#endif // !SCORE_HPP_DEFINED_
