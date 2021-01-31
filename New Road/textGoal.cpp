
#include<iostream>
#include<vector>
#include <DxLib.h>
#include "textGoal.hpp"

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

