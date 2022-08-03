#include <iostream>
#include <opencv2/opencv.hpp>
#include <queue>
#include <thread>
#include "libs/json.hpp"
#include "capture.h"
#include "detect.h"
#include "viewer.h"
#include "ringBuffer.h"

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
	queue<int> message1, message2;
	Detect detect;
	Viewer viewer;
	fopen_s(&fp, "../config/setting.json", "r");
	auto j = json::parse(fp);
	fclose(fp);
	RingBuffer ringBuffer(j["bufferSize"]);

	Capture* capture;
	capture = new Capture(j["fps"]);
	if (capture->Check() == -1) return -1;
	thread thread1(&Capture::CapImage, capture, &ringBuffer, &message1);
	thread thread2(&Detect::faceDetection, &detect, &ringBuffer, &message1, &message2);
	thread thread3(&Viewer::view, &viewer, &ringBuffer, &message2);
	thread1.join();
	thread2.join();
	thread3.join();
	return 0;
}