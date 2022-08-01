#pragma once

#include <memory>

class RingBuffer {
private:
	unsigned int m_capacity;
	int num;
	unique_ptr<int[]> rb;
	int head, tail;
public:
	RingBuffer(unsigned int capacity);
	void Put(int value);
	bool Get(int* value);
	void Clear();
};
