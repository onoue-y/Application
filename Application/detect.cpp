#include <opencv2/opencv.hpp>
#include <queue>
#include <vector>
#include "detect.h"
#include "ringBuffer.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

void Detect::faceDetection(RingBuffer* ringBuffer, queue<int>* message1, queue<int>* message2) {
	cascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");
	while (1) {
		if (!(message1->empty())) {
			messageNum = message1->front();
			switch (messageNum) {
			case 0:
				break;
			case 1:
				ringBuffer->GetDetect(&frame);
				cascade.detectMultiScale(frame, contour, 1.1, 3, 0, Size(30, 30));
				if (contour.size() != 0) ringBuffer->PutDetect(contour);
				message2->push(1);
				break;
			case 2:
				break;
			default:
				break;
			}
		}	
	}
}