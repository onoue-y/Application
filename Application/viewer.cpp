#include <opencv2/opencv.hpp>
#include <vector>
#include "viewer.h"
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

Viewer::Viewer(int delay) {
	m_delay = delay;
	delayFlag = false;
	viewerFlag = true;
}
void Viewer::view(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue) {
	while (true) {
		if (!(viewerMessage->empty())) {
			viewerMessage->receive(&messageNum);
			switch (messageNum) {
			case getMessage:
				ringBuffer->SetDelay(m_delay * delayFlag);
				frameAddress = ringBuffer->GetAddress(HEAD);	//head�̈ʒu��frame�A�h���X���擾
				ringBuffer->Get(&frame, &contour);
				logqueue->send({ "viewer", "msg", 1, frameAddress, contour, -1 });
				logMessage->send(2);
				if (viewerFlag) {
					if (contour != notDetect) rectangle(frame, Point(contour.x, contour.y), Point(contour.x + contour.width, contour.y + contour.height), Scalar(blue, green, red), thickness);
				}
				imshow("image", frame);         //�摜��\���D
				break;
			default:
				break;
			}
		}
		int key = waitKey(waitSecond);
		if (key == esc) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, esc });
			logMessage->send(2);
			// �e�X���b�h�̏I�����b�Z�[�W���M
			captureMessage->send(escMessage);
			detectMessage->send(escMessage);
			logMessage->send(escMessage);
			break;
		}
		else if (key == s) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, s });
			logMessage->send(2);
			//capture�̈ꎞ��~�E�ĊJ���b�Z�[�W���M
			captureMessage->send(sMessage);
		}
		else if (key == d) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, d });
			logMessage->send(2);
			//���o�g��ON/OFF���b�Z�[�W���M
			detectMessage->send(dMessage);
		}
		else if (key == v) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, v });
			logMessage->send(2);
			viewerFlag = !viewerFlag;
		}
		else if (key == e) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, e });
			logMessage->send(2);
			delayFlag = !delayFlag;
		}
	}
}