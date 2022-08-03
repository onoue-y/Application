#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include "ringBuffer.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

class Capture {
private:
	VideoCapture cap;
	Mat frame;					//取得したフレーム
public:
	Capture(int fps);			//コンストラクタ
	int Check();			//カメラが正常にオープンしたことの確認
	void CapImage(RingBuffer* ringBuffer, queue<int>* message1);		//画像の取得、保存
};