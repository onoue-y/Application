#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include "libs/json.hpp"
#include "capture.h"
#include "detect.h"
#include "viewer.h"
#include "ringBuffer.h"
#include "msgQueue.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;
using json = nlohmann::json;

int main() {
	FILE* fp;
	MsgQueue imgGetMessage, coordGetMessage, keyMessage;
	Detect detect;
	Viewer viewer;
	fopen_s(&fp, "../config/setting.json", "r");
	auto j = json::parse(fp);
	fclose(fp);
	RingBuffer ringBuffer(j["bufferSize"]);

	Capture* capture;
	capture = new Capture(j["fps"]);
	if (capture->Check() == -1) return -1;
	thread capThread(&Capture::CapImage, capture, &ringBuffer, &imgGetMessage, &keyMessage);
	thread detThread(&Detect::faceDetection, &detect, &ringBuffer, &imgGetMessage, &coordGetMessage, &keyMessage);
	thread viewThread(&Viewer::view, &viewer, &ringBuffer, &coordGetMessage, &keyMessage);
	capThread.join();
	detThread.join();
	viewThread.join();
	return 0;
}