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

void Viewer::view(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage) {
	while (true) {
		if (!(viewerMessage->empty())) {
			viewerMessage->receive(&messageNum);
			switch (messageNum) {
			case getMessage:
				ringBuffer->Get(&frame, &contour);
				if (contour != notDetect) rectangle(frame, Point(contour.x, contour.y), Point(contour.x + contour.width, contour.y + contour.height), Scalar(blue, green, red), thickness);
				imshow("image", frame);         //�摜��\���D
				break;
			default:
				break;
			}
		}
		int key = waitKey(waitSecond);
		if (key == esc) {
			// �e�X���b�h�̏I�����b�Z�[�W���M
			captureMessage->send(escMessage);
			detectMessage->send(escMessage);
			break;
		}
	}
}