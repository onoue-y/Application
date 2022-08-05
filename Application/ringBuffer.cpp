#include <memory>
#include <opencv2/opencv.hpp>
#include "ringBuffer.h"
#include "constants.h"

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
	size = 0;
	head = 0;
	tail = 0;
	headDetect = 0;
}
void RingBuffer::Put(Mat frame) {
	if ((head == tail) && (size>=m_capacity)) {
		head = (head + 1) % m_capacity;
		headDetect = (headDetect + 1) % m_capacity;
		size--;
	}
	img[tail] = frame;
	size++;
	tail = (tail + 1) % m_capacity;
}
void RingBuffer::PutDetect(Rect contour) {
	cout << headDetect<< endl;
	coord[headDetect] = contour;
	headDetect = (headDetect + 1) % m_capacity;
}
bool RingBuffer::Get(Mat* frame, Rect* contour) {
	if (size != 0) {
		*frame = img[head];
		*contour = coord[head];
		head = (head + 1) % m_capacity;
		size--;
		return true;
	}
	else {
		return false;
	}
}
void RingBuffer::GetDetect(Mat* frame) {
	*frame = img[headDetect];
}