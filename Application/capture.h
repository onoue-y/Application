#pragma once

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

class Capture {
private:
	VideoCapture cap;
	Mat frame;					//�擾�����t���[��
public:
	Capture();			//�R���X�g���N�^
	int Check();			//�J����������ɃI�[�v���������Ƃ̊m�F
	void CapImage();		//�摜�̎擾�A�ۑ�
};