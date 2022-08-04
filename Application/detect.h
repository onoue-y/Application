#pragma once
#include <opencv2/opencv.hpp>
#include <queue>
#include <vector>
#include "ringBuffer.h"

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
	void faceDetection(RingBuffer* ringBuffer, queue<int>* imgGetMessage, queue<int>* coordGetMessage);
};