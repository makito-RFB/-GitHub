#ifndef RNKINGRW_HPP_DEFINED_
#define RNKINGRW_HPP_DEFINED_

#include<iostream>
#include<vector>
#include<algorithm>
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
	void Rread(std::vector<float>& rarr);			//スコア呼び込み
	void Rwrite(std::vector<float>& warr, float s);	
	void ResetScore(std::vector<float>& arr);								//スコアリセット
private:
	int fCnt = 0;
	float temp = 0;
};

//スコア呼び込み
void R_WRITE::Rread(std::vector<float>& arr)		
{
	error = fopen_s(&fp, FILE_RNK_PATH, "r");
	if (!error && fp != NULL)
	{
		if (error == 0)
		{
			while (!feof(fp) && fCnt < FILE_NUM) {
				fscanf_s(fp, "%f", &arr[fCnt]);
				fCnt++;
			}
		}

		fclose(fp);
	}
	fCnt = 0;

	return;
}

//スコア書き込み
void R_WRITE::Rwrite(std::vector<float>& warr, float s)		
{
	if ((error2 = fopen_s(&fp2, FILE_RNK_PATH, "w")) != 0) {
		MessageBox(GetMainWindowHandle(), FILE_OPEN_CAPTION, FILE_OPEN_TITLE, MB_OK);
		exit(EXIT_FAILURE);
	}

	if (!error2 && fp2 != NULL)
	{
		warr.push_back(s);
		std::sort(warr.begin(), warr.end(), std::greater<float>());
		warr.pop_back();
		for (int rw = 0; rw < FILE_NUM; rw++)
		{
			fprintf(fp2, "%f \n", warr[rw]);
		}
		fclose(fp2);
	}
	return;
}

//リセット
void R_WRITE::ResetScore(std::vector<float>& arr)
{
	if ((error2 = fopen_s(&fp2, FILE_RNK_PATH, "w")) != 0) {
		MessageBox(GetMainWindowHandle(), FILE_OPEN_CAPTION, FILE_OPEN_TITLE, MB_OK);
		exit(EXIT_FAILURE);
	}
	if (!error2 && fp2 != NULL)
	{
		for (int rw = 0; rw < FILE_NUM; rw++)
		{
			fprintf(fp2, "%f \n", 0.0f);
			arr[rw] = 0.0f;
		}
		fclose(fp2);
	}
	return;
}

#endif // !RNKINGRW_HPP_DEFINED_
