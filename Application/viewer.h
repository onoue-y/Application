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

class Viewer {
private:
	Mat frame;
	Rect contour;
	int messageNum;
public:
	void view(RingBuffer* ringBuffer, queue<int>* coordGetMessage);
};