#pragma once
#include <queue>
#include <opencv2/opencv.hpp>
#include "constants.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

class logQueue {
public:
	struct infoLog {
		char* threadName;
		char* timing;
		int messageNum;
		Mat* frameAdd;
		Rect coordinate;
		int key;
	};
	void send(infoLog info);
	void receive(infoLog* info);
	bool empty();
	
private:
	queue<infoLog> log_que;
};