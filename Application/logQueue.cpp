#include <queue>
#include "logQueue.h"
#include "constants.h"

void logQueue::send(infoLog info) {
	log_que.push(info);
}
void logQueue::receive(infoLog* info) {
	*info = log_que.front();
	log_que.pop();
}
bool logQueue::empty() {
	return log_que.empty();
}