#include <iostream>
#include <DxLib.h>
#include "image.hpp"

BOOL IMG::RoadImage(IMG &obj,const char* name)
{
	strcpy_s(obj.path, name);
	obj.handle = LoadGraph(obj.path);
	if (obj.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), name, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(obj.handle, &obj.width, &obj.height);
	return TRUE;
}
