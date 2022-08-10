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

//�R���X�g���N�^
Capture::Capture(int fps) {
    //�J�����̋N��
    cap.open(0);
    cap.set(CAP_PROP_FPS, fps);
}

//�J����������ɃI�[�v���������Ƃ̊m�F
int Capture::Check() {
    if (!cap.isOpened()) return openError;
    else return openSuccess;
}

//�摜�̕\��
int Capture::CapImage(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue) {
    while (cap.read(frame)) {
        display_frame = frame.clone();
        logqueue->send({"capture", "", -1, &display_frame, notDetect, -1});
        logMessage->send(2);
        if (!(captureMessage->empty())) {
            captureMessage->receive(&messageNum);
            switch (messageNum) {
            case escMessage:
                return 0;
            default:
                break;
            }
        }
        if (ringBuffer->GetSize() != ringBuffer->GetCapacity()) {
            ringBuffer->Put(display_frame);
            detectMessage->send(getMessage);
        }
    }
    return 0;
}