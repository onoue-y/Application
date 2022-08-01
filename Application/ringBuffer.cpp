#include <memory>
#include <opencv2/opencv.hpp>
#include "ringBuffer.h"

RingBuffer::RingBuffer(unsigned int capacity) {
	m_capacity = capacity;
	img = make_unique<int[]>(m_capacity);
	coord = make_unique<int[]>(m_capacity);
	num = 0;
	head = 0;
	tail = 0;
}
void RingBuffer::Put(Mat frame, Rect contour) {
	if ((head == tail) && (num>=m_capacity)) {
		head = (head + 1) % m_capacity;
		num--;
	}
	img[tail] = frame;
	coord[tail] = contour;
	num++;
	tail = (tail + 1) % m_capacity;
}
bool RingBuffer::Get(Mat* frame, Rect* contour) {
	if (num != 0) {
		*frame = img[head];
		*contour = coord[head];
		head = (head + 1) % m_capacity;
		return true;
	}
	else {
		return false;
	}
}
void RingBuffer::Clear() {
	num = 0;
	head = 0;
	tail = 0;
}