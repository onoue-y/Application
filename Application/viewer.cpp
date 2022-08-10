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

void Viewer::view(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue) {
	while (true) {
		if (!(viewerMessage->empty())) {
			viewerMessage->receive(&messageNum);
			switch (messageNum) {
			case getMessage:
				frameAddress = ringBuffer->GetAddress(HEAD);	//headの位置のframeアドレスを取得
				ringBuffer->Get(&frame, &contour);
				logqueue->send({ "viewer", "msg", 1, frameAddress, contour, -1 });
				logMessage->send(2);
				if (contour != notDetect) rectangle(frame, Point(contour.x, contour.y), Point(contour.x + contour.width, contour.y + contour.height), Scalar(blue, green, red), thickness);
				imshow("image", frame);         //画像を表示．
				break;
			default:
				break;
			}
		}
		int key = waitKey(waitSecond);
		if (key == esc) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, esc });
			logMessage->send(2);
			// 各スレッドの終了メッセージ送信
			captureMessage->send(escMessage);
			detectMessage->send(escMessage);
			logMessage->send(escMessage);
			break;
		}
		else if (key == s) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, s });
			logMessage->send(2);
			//captureの一時停止・再開メッセージ送信
			captureMessage->send(sMessage);
		}
		else if (key == d) {
			logqueue->send({ "viewer", "Key-in", -1, nullptr, notDetect, d });
			logMessage->send(2);
			//検出枠のON/OFFメッセージ送信
			detectMessage->send(dMessage);
		}
	}
}