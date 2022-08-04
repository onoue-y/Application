#include "capture.h"
#include "ringBuffer.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>

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
void Capture::CapImage(RingBuffer* ringBuffer, queue<int>* imgGetMessage) {
    while (cap.read(frame)) {

        ringBuffer->Put(frame);
        imgGetMessage->push(1);
    }
}