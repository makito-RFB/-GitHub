#ifndef BTN_HPP_DEFINED_
#define BTN_HPP_DEFINED_

#include<iostream>
#include<DxLib.h>

class BTN
{
public:
	void DrawBackBTN();
};

void BTN::DrawBackBTN()
{
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
}

#endif // !IMAGE_HPP_DEFINED_

