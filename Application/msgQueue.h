#pragma once
#include <queue>

using namespace std;

class MsgQueue {
private:
	queue<int> msg_que;
public:
	MsgQueue();
	void send(int message);
	void receive(int* message);
	bool empty();
};