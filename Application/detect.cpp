#include <opencv2/opencv.hpp>
#include <queue>
#include "detect.h"
#include "ringBuffer.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

void Detect::faceDetection(RingBuffer* ringBuffer, queue<int>* message) {
	cascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");
	while (1) {
		if (!(message->empty())) {
			messageNum = message->front();
			switch (messageNum) {
			case 0:
				break;
			case 1:
				ringBuffer->Get(&frame, &contour);
				cascade.detectMultiScale(frame, contour, 1.1, 3, 0, Size(30, 30));
				break;
			case 2:
				break;
			default:
				break;
			}
		}	
	}
}