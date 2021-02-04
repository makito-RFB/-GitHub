#ifndef SETTEXT_HPP_DEFINED_
#define SETTEXT_HPP_DEFINED_

#include<iostream>
#include<vector>
#include <DxLib.h>

class setText
{
public:
	void appendText(std::vector<std::string>& textGaol, std::string appText);
	int findText(std::vector<std::string>& textGaol, std::string lookText);
	void CharDraw(int);
private:
	int finCnt = 0;
};



#endif // !TEXT_HPP_DEFINED_
