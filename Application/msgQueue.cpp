#include <queue>
#include "msgQueue.h"
#include "constants.h"

void MsgQueue::send(int message) {
	msg_que.push(message);
}
void MsgQueue::receive(int* message) {
	*message = msg_que.front();
	msg_que.pop();
}
bool MsgQueue::empty() {
	return msg_que.empty();
}