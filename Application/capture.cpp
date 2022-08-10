#include "capture.h"
#include "ringBuffer.h"
#include "msgQueue.h"
#include "constants.h"
#include "logQueue.h"
#include <opencv2/opencv.hpp>
#include <vector>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

//コンストラクタ
Capture::Capture(int fps) {
    //カメラの起動
    cap.open(0);
    cap.set(CAP_PROP_FPS, fps);
    captureFlag = true;
}

//カメラが正常にオープンしたことの確認
int Capture::Check() {
    if (!cap.isOpened()) return openError;
    else return openSuccess;
}

//画像の表示
int Capture::CapImage(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue) {
    while (cap.read(frame)) {
        if (captureFlag) {
            display_frame = frame.clone();
            frameAddress = ringBuffer->GetAddress(TAIL);    //tailの位置のframeアドレスを取得
            logqueue->send({ "capture", "", -1, frameAddress, notDetect, -1 });
            logMessage->send(2);
            ringBuffer->Put(display_frame);
            detectMessage->send(getMessage);
        }
        if (!(captureMessage->empty())) {
            captureMessage->receive(&messageNum);
            switch (messageNum) {
            case escMessage:
                return 0;
            case sMessage:
                captureFlag = !captureFlag;
                break;
            default:
                break;
            }
        }
    }
    return 0;
}