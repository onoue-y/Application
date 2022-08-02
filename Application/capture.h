#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include "ringBuffer.h"

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
	Mat frame;					//�擾�����t���[��
public:
	Capture(int fps);			//�R���X�g���N�^
	int Check();			//�J����������ɃI�[�v���������Ƃ̊m�F
	void CapImage(RingBuffer* ringBuffer, queue<int>* message1);		//�摜�̎擾�A�ۑ�
};