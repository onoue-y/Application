#pragma once
#include <memory>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif



using namespace std;
using namespace cv;

class RingBuffer {
private:
	unsigned int m_capacity;
	unsigned int num;
	unique_ptr<Mat[]> img;
	unique_ptr<Rect[]> coord;
	int head, tail, headDetect;
public:
	RingBuffer(unsigned int capacity);
	void Put(Mat frame);
	void PutDetect(Rect contour);
	bool Get(Mat* frame, Rect* contour);
	void GetDetect(Mat* frame);
};
