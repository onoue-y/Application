#include "capture.h"
#include "ringBuffer.h"
#include "msgQueue.h"
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
}

//カメラが正常にオープンしたことの確認
int Capture::Check() {
    if (!cap.isOpened()) return -1;
}

//画像の表示
int Capture::CapImage(RingBuffer* ringBuffer, MsgQueue* imgGetMessage, MsgQueue* keyMessage) {
    while (cap.read(frame)) {
        if (!(keyMessage->empty())) {
            keyMessage->receive(&messageNum);
            switch (messageNum) {
            case 2:
                return 0;
            default:
                break;
            }
        }
        ringBuffer->Put(frame);
        imgGetMessage->send(1);
    }
}