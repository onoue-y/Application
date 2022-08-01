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

//�R���X�g���N�^
Capture::Capture() {
    //�J�����̋N��
    cap.open(0);
}

//�J����������ɃI�[�v���������Ƃ̊m�F
int Capture::Check() {
    if (!cap.isOpened()) return -1;
}

//�摜�̕\��
void Capture::CapImage() {
    while (cap.read(frame)) {
        imshow("image", frame);         //�摜��\���D

        const int key = waitKey(1);
        if (key == 27) break; //�L�[�R�[�h [Esc]:27
    }
}