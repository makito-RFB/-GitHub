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
private:
	int finCnt = 0;
};

void setGoals::appendText(std::vector<std::string>& textGaol, std::string appText)
{
	textGaol.emplace_back(appText);
}

int setGoals::findText(std::vector<std::string>& textGaol, std::string lookText)
{
	auto reCnt = std::find(textGaol.begin(), textGaol.end(), lookText);
	if (reCnt != textGaol.end())
	{
		finCnt = std::distance(textGaol.begin(), reCnt);
		return finCnt;
	}
	else
	{
		return finCnt;
	}
}

#endif // !TEXTGOAL_HPP_DEFINED_
