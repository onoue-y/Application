#pragma once

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

class Capture {
private:
	VideoCapture cap;
	Mat frame;					//取得したフレーム
public:
	Capture();			//コンストラクタ
	int Check();			//カメラが正常にオープンしたことの確認
	void CapImage();		//画像の取得、保存
};