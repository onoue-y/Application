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
void Capture::CapImage(RingBuffer* ringBuffer, queue<int>* message1) {
    while (cap.read(frame)) {
        imshow("image", frame);         //画像を表示．

        ringBuffer->Put(frame, {0,0,0,0});
        message1->push(1);

        const int key = waitKey(1);
        if (key == 27) break; //キーコード [Esc]:27
    }
}