#include <iostream>
#include <opencv2/opencv.hpp>
#include "libs/json.hpp"
#include "capture.h"
#include "detect.h"
#include "queue.h"
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

	fopen_s(&fp, "../config/setting.json", "r");
	auto j = json::parse(fp);
	fclose(fp);
	RingBuffer ringBuffer(j["bufferSize"]);

	Capture* capture;
	capture = new Capture();
	cap.set(CAP_PROP_FPS, j["fps"]);
	if (face->cameraCheck() == -1) return -1;
	capture->CapImage();

	return 0;
}