#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include "ringBuffer.h"
#include "msgQueue.h"
#include "constants.h"

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
	int messageNum;
public:
	Capture(int fps);			//コンストラクタ
	int Check();			//カメラが正常にオープンしたことの確認
	int CapImage(RingBuffer* ringBuffer, MsgQueue* imgGetMessage, MsgQueue* keyMessage);		//画像の取得、保存
};