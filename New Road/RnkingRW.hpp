#include<iostream>
#include <DxLib.h>

#define FILE_OPEN_TITLE		TEXT("ファイルオープンエラー")
#define FILE_OPEN_CAPTION	TEXT("ファイルオープンエラー")
#define FILE_RNK_PATH		TEXT("rnkingFile.txt")

#define FILE_NUM 5

FILE* fp = NULL, * fp2 = NULL;
errno_t error, error2;

class R_WRITE
{
public:
	float* Rread(float arr[]);
	float* Rwrite(float arr[], float s);
private:
	int fCnt = 0;
	float temp = 0;
};

float* R_WRITE::Rread(float arr[])
{
	error = fopen_s(&fp, FILE_RNK_PATH, "r");
	if (!error && fp != NULL)
	{
		if (error == 0)
		{
			while (!feof(fp) && fCnt < FILE_NUM) {
				fscanf_s(fp, "%f", &(arr[fCnt]));
				fCnt++;
			}
		}

		fclose(fp);
	}
	fCnt = 0;

	return arr;
}

float* R_WRITE::Rwrite(float arr[], float s)
{
	if ((error2 = fopen_s(&fp2, FILE_RNK_PATH, "w")) != 0) {
		MessageBox(GetMainWindowHandle(), FILE_OPEN_CAPTION, FILE_OPEN_TITLE, MB_OK);
		exit(EXIT_FAILURE);
	}
	if (!error2 && fp2 != NULL)
	{
		for (int rw = 0; rw < FILE_NUM; rw++)
		{
			if (arr[rw] <= s) {
				temp = arr[rw];
				arr[rw] = s;
				s = temp;
			}
			fprintf(fp2, "%f \n", arr[rw]);
		}
		fclose(fp2);
	}
	return arr;
}