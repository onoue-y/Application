#pragma once
#include "log.h"
#include "logQueue.h"
#include "constants.h"
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;
using chrono::duration_cast;
using chrono::milliseconds;
using chrono::system_clock;

Log::Log() {
	getDay();
	getFilename();
	filename = str.str() + ".txt";
	fopen_s(&fp, filename.c_str(), "a+");
	resetStr();
	fclose(fp);
}
int Log::makeLog(MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue) {
	while (true) {
		if (!(logMessage->empty())) {
			logMessage->receive(&messageNum);
			switch (messageNum) {
			case escMessage:
				return 0;
			case logRequestMessage:
				getDay();
				getLog(logqueue);
				fopen_s(&fp, filename.c_str(), "a+");
				fputs(log.c_str(), fp);
				fclose(fp);
				resetStr();
				break;
			default:
				break;
			}
		}
	}
}
void Log::getDay() {
	t = time(NULL);
	localtime_s(&local, &t);

	year = local.tm_year + 1900;
	month = local.tm_mon + 1;
	day = local.tm_mday;
	hour = local.tm_hour;
	minute = local.tm_min;
	second = local.tm_sec;
	millisec = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	millisec %= 1000;
}
void Log::getFilename() {
	str << year;
	str << setfill('0') << right << setw(2) << month;
	str << setfill('0') << right << setw(2) << day;
	str << "-";
	str << setfill('0') << right << setw(2) << hour;
	str << setfill('0') << right << setw(2) << minute;
	str << setfill('0') << right << setw(2) << second;
}
void Log::resetStr() {
	str.str("");
	str.clear(stringstream::goodbit);
}
void Log::getLog(logQueue* logqueue) {
	str << year;
	str << "-";
	str << setfill('0') << right << setw(2) << month;
	str << "-";
	str << setfill('0') << right << setw(2) << day;
	str << " ";
	str << setfill('0') << right << setw(2) << hour;
	str << ":";
	str << setfill('0') << right << setw(2) << minute;
	str << ":";
	str << setfill('0') << right << setw(2) << second;
	str << ":";
	str << setfill('0') << right << setw(3) << millisec;
	logqueue->receive(&info);
	str << "[" << info.threadName << "]";
	str << info.timing;
	if (info.messageNum != -1) str << "<" << info.messageNum << ">";
	if (info.frameAdd != nullptr) str << "<" << info.frameAdd << ">";
	if (info.coordinate != notDetect) str << "<" << info.coordinate << ">";
	if (info.key != -1) str << "<" << info.key << ">";
	log = str.str() + "\n";
}