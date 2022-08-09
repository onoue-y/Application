#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "ringBuffer.h"
#include "msgQueue.h"
#include "constants.h"
#include "logQueue.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

class Detect {
private:
	CascadeClassifier cascade;
	Mat frame;					//取得したフレーム
	vector<Rect> contour;		//検出した顔の座標データ(x,y,width,height)
	int messageNum;
public:
	int faceDetection(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue);
};