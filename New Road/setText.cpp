
#include<iostream>
#include<vector>
#include <DxLib.h>
#include "setText.hpp"

void setText::appendText(std::vector<std::string>& textGaol, std::string appText)
{
	textGaol.emplace_back(appText);
}

int setText::findText(std::vector<std::string>& textGaol, std::string lookText)
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

