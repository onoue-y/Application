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