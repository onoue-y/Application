#include <opencv2/opencv.hpp>
#include <vector>
#include "viewer.h"
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

int Viewer::view(RingBuffer* ringBuffer, MsgQueue* coordGetMessage, MsgQueue* keyMessage) {
	while (true) {
		if (!(keyMessage->empty())) {
			keyMessage->receive(&messageNum);
			switch (messageNum) {
			case escMessage:
				return 0;
			default:
				break;
			}
		}
		if (!(coordGetMessage->empty())) {
			coordGetMessage->receive(&messageNum);
			switch (messageNum) {
			case getMessage:
				ringBuffer->Get(&frame, &contour);
				if (contour != notDetect) rectangle(frame, Point(contour.x, contour.y), Point(contour.x + contour.width, contour.y + contour.height), Scalar(blue, green, red), thickness);
				imshow("image", frame);         //画像を表示．
				break;
			default:
				break;
			}
		}
		const int key = waitKey(waitSecond);
		if (key == esc) exit(0); //キーコード [Esc]:27
	}
}