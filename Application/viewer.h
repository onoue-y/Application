#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "ringBuffer.h"
#include "msgQueue.h"

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
	int view(RingBuffer* ringBuffer, MsgQueue* coordGetMessage, MsgQueue* keyMessage);
};