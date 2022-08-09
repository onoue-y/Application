#pragma once
#include <queue>
#include "constants.h"

using namespace std;

class MsgQueue {
private:
	queue<int> msg_que;
public:
	void send(int message);
	void receive(int* message);
	bool empty();
};