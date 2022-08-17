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

class Viewer {
private:
	Mat frame;
	Mat* frameAddress;
	Rect contour;
	int messageNum;
	bool viewerFlag;
	bool delayFlag;
	int m_delay;
public:
	Viewer(int delay);
	void view(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue);
};