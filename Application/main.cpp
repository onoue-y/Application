#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include "libs/json.hpp"
#include "capture.h"
#include "detect.h"
#include "viewer.h"
#include "ringBuffer.h"
#include "msgQueue.h"
#include "constants.h"
#include "log.h"
#include "logQueue.h"

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
	MsgQueue captureMessage, detectMessage, viewerMessage, logMessage;
	logQueue logqueue;
	Detect detect;
	Viewer viewer;
	Log log;
	fopen_s(&fp, "../config/setting.json", "r");
	auto j = json::parse(fp);
	fclose(fp);
	RingBuffer ringBuffer(j["bufferSize"]);

	Capture* capture;
	capture = new Capture(j["fps"]);
	try
	{
		if (capture->Check() == openError) throw "カメラが正常にオープンしませんでした。";
		thread capThread(&Capture::CapImage, capture, &ringBuffer, &captureMessage, &detectMessage, &viewerMessage, &logMessage, &logqueue);
		thread detThread(&Detect::faceDetection, &detect, &ringBuffer, &captureMessage, &detectMessage, &viewerMessage, &logMessage, &logqueue);
		thread viewThread(&Viewer::view, &viewer, &ringBuffer, &captureMessage, &detectMessage, &viewerMessage, &logMessage, &logqueue);
		thread logThread(&Log::makeLog, &log, &captureMessage, &detectMessage, &viewerMessage, &logMessage,&logqueue);
		capThread.join();
		detThread.join();
		viewThread.join();
		logThread.join();
	}
	catch (char *exception)
	{
		cout << exception << endl;
	}
	return 0;
}