#pragma once
#include <time.h>
#include <string>
#include "msgQueue.h"
#include "logQueue.h"

using namespace std;

class Log {
private:
	time_t t;
	struct tm local;
	string filename;
	string log;
	FILE* fp;
	int messageNum;
	stringstream str;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int minsecond;
	logQueue::infoLog info;

public:
	Log();
	void makeLog(MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue);
	void getDay();
};