#include <opencv2/opencv.hpp>
#include <queue>
#include <vector>
#include "viewer.h"
#include "ringBuffer.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

void Viewer::view(RingBuffer* ringBuffer, queue<int>* message2) {
	while (1) {
		if (!(message2->empty())) {
			messageNum = message2->front();
			switch (messageNum) {
			case 0:
				break;
			case 1:
				ringBuffer->Get(&frame, &contour);
				rectangle(frame, Point(contour.x, contour.y), Point(contour.x + contour.width, contour.y + contour.height), Scalar(0, 0, 255), 3);
				imshow("image", frame);         //画像を表示．
				break;
			case 2:
				break;
			default:
				break;
			}
			message2->pop();
		}
		const int key = waitKey(1);
		if (key == 27) break; //キーコード [Esc]:27
	}
}