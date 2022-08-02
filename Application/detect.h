#pragma once
#include <opencv2/opencv.hpp>
#include <queue>
#include "ringBuffer.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

class Detect {
private:
	CascadeClassifier cascade;
	Mat frame;					//�擾�����t���[��
	Rect contour;		//���o������̍��W�f�[�^(x,y,width,height)
	int messageNum;
public:
	void faceDetection(RingBuffer* ringBuffer, queue<int>* message);
};