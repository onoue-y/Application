#include <opencv2/opencv.hpp>
#include <vector>
#include "detect.h"
#include "ringBuffer.h"
#include "msgQueue.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

void Detect::faceDetection(RingBuffer* ringBuffer, MsgQueue* imgGetMessage, MsgQueue* coordGetMessage) {
	cascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");
	while (1) {
		if (!(imgGetMessage->empty())) {
			imgGetMessage->receive(&messageNum);
			switch (messageNum) {
			case 0:
				break;
			case 1:
				ringBuffer->GetDetect(&frame);
				cascade.detectMultiScale(frame, contour, 1.1, 3, 0, Size(30, 30));
				if (contour.size() != 0) ringBuffer->PutDetect(contour[0]);
				else ringBuffer->PutDetect({ -1,-1,-1,-1 });
				coordGetMessage->send(1);
				break;
			case 2:
				break;
			default:
				break;
			}
		}	
	}
}