#ifndef TEXTGOAL_HPP_DEFINED_
#define TEXTGOAL_HPP_DEFINED_

#include<iostream>
#include<vector>
#include <DxLib.h>

class setGoals
{
public:
	void appendText(std::vector<std::string>& textGaol, std::string appText);
	int findText(std::vector<std::string>& textGaol, std::string lookText);
	void CharDraw(int);
private:
	int finCnt = 0;
};



#endif // !TEXTGOAL_HPP_DEFINED_
