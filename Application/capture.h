#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
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

class Capture {
private:
	VideoCapture cap;
	Mat frame, display_frame;					//�擾�����t���[��
	Mat* frameAddress;
	int messageNum;
public:
	Capture(int fps);			//�R���X�g���N�^
	int Check();			//�J����������ɃI�[�v���������Ƃ̊m�F
	int CapImage(RingBuffer* ringBuffer, MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue);		//�摜�̎擾�A�ۑ�
};