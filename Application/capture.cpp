#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

#include "capture.h"
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

//コンストラクタ
Capture::Capture() {
    //カメラの起動
    cap.open(0);
}

//カメラが正常にオープンしたことの確認
int Capture::Check() {
    if (!cap.isOpened()) return -1;
}

//画像の表示
void Capture::CapImage() {
    while (cap.read(frame)) {
        imshow("image", frame);         //画像を表示．

        const int key = waitKey(1);
        if (key == 27) break; //キーコード [Esc]:27
    }
}