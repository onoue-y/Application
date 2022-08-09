#include <opencv2/opencv.hpp>
#include <vector>
#include "detect.h"
#include "ringBuffer.h"
#include "msgQueue.h"
#include "constants.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

int Detect::faceDetection(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage) {
	cascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");
	while (true) {
		if (!(detectMessage->empty())) {
			detectMessage->receive(&messageNum);
			switch (messageNum) {
			case escMessage:
				return 0;
			case getMessage:
				ringBuffer->GetDetect(&frame);
				cascade.detectMultiScale(frame, contour, scaleFactor, minNeighbors, flags, Size(minsize, minsize));
				if (contour.size() != 0) ringBuffer->PutDetect(contour[0]);
				else ringBuffer->PutDetect(notDetect);
				viewerMessage->send(getMessage);
				break;
			default:
				break;
			}
		}	
	}
}