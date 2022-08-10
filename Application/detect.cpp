#include <opencv2/opencv.hpp>
#include <vector>
#include "detect.h"
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

int Detect::faceDetection(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue) {
	cascade.load("C:/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml");
	while (true) {
		if (!(detectMessage->empty())) {
			detectMessage->receive(&messageNum);
			switch (messageNum) {
			case escMessage:
				return 0;
			case getMessage:
				frameAddress = ringBuffer->GetAddress(3);
				ringBuffer->GetDetect(&frame);
				logqueue->send({ "detect", "msg", 1, frameAddress, notDetect, -1 });
				logMessage->send(2);
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