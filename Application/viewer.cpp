#include <opencv2/opencv.hpp>
#include <vector>
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

int Viewer::view(RingBuffer* ringBuffer, MsgQueue* coordGetMessage, MsgQueue* keyMessage) {
	while (1) {
		if (!(keyMessage->empty())) {
			keyMessage->receive(&messageNum);
			switch (messageNum) {
			case 2:
				return 0;
			default:
				break;
			}
		}
		if (!(coordGetMessage->empty())) {
			coordGetMessage->receive(&messageNum);
			switch (messageNum) {
			case 1:
				ringBuffer->Get(&frame, &contour);
				if (contour != Rect{-1,-1,-1,-1}) rectangle(frame, Point(contour.x, contour.y), Point(contour.x + contour.width, contour.y + contour.height), Scalar(0, 0, 255), 3);
				imshow("image", frame);         //画像を表示．
				break;
			default:
				break;
			}
		}
		const int key = waitKey(1);
		if (key == 27) exit(0); //キーコード [Esc]:27
	}
}