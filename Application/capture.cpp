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

//�R���X�g���N�^
Capture::Capture(int fps) {
    //�J�����̋N��
    cap.open(0);
    cap.set(CAP_PROP_FPS, fps);
}

//�J����������ɃI�[�v���������Ƃ̊m�F
int Capture::Check() {
    if (!cap.isOpened()) return -1;
}

//�摜�̕\��
void Capture::CapImage(RingBuffer* ringBuffer, queue<int>* imgGetMessage) {
    while (cap.read(frame)) {

        ringBuffer->Put(frame);
        imgGetMessage->push(1);
    }
}