#include <memory>
#include <opencv2/opencv.hpp>
#include "ringBuffer.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace std;
using namespace cv;

RingBuffer::RingBuffer(unsigned int capacity) {
	m_capacity = capacity;
	img = make_unique<Mat[]>(m_capacity);
	coord = make_unique<Rect[]>(m_capacity);
	num = 0;
	head = 0;
	tail = 0;
	headDetect = 0;
}
void RingBuffer::Put(Mat frame) {
	if ((head == tail) && (num>=m_capacity)) {
		head = (head + 1) % m_capacity;
		headDetect = (headDetect + 1) % m_capacity;
		num--;
	}
	img[tail] = frame;
	num++;
	tail = (tail + 1) % m_capacity;
}
void RingBuffer::PutDetect(Rect contour) {
	coord[headDetect] = contour;
	headDetect = (headDetect + 1) % m_capacity;
}
bool RingBuffer::Get(Mat* frame, Rect* contour) {
	if (num != 0) {
		*frame = img[head];
		*contour = coord[head];
		head = (head + 1) % m_capacity;
		num--;
		return true;
	}
	else {
		return false;
	}
}
void RingBuffer::GetDetect(Mat* frame) {
	*frame = img[headDetect];
}
void RingBuffer::Clear() {
	num = 0;
	head = 0;
	tail = 0;
}