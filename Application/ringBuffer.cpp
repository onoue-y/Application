#include <memory>
#include "ringBuffer.h"

RingBuffer::RingBuffer(unsigned int capacity) {
	m_capacity = capacity;
	rb = make_unique<int[]>(m_capacity);
	num = 0;
	head = 0;
	tail = 0;
}
void RingBuffer::Put(int value) {
	if ((head == tail) && (num>=m_capacity)) {
		head = (head + 1) % m_capacity;
		num--;
	}
	rb[tail] = value;
	num++;
	tail = (tail + 1) % m_capacity;
}
bool RingBuffer::Get(int* value) {
	if (num != 0) {
		*value = rb[head];
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