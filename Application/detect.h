#pragma once
#include <opencv2/opencv.hpp>
#include <queue>
#include <vector>
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
	vector<Rect> contour;		//���o������̍��W�f�[�^(x,y,width,height)
	int messageNum;
public:
	void faceDetection(RingBuffer* ringBuffer, queue<int>* message1, queue<int>* message2);
};