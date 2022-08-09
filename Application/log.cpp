#pragma once
#include "log.h"
#include "logQueue.h"
#include "constants.h"
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <ios>
#include <iomanip>

using namespace std;

Log::Log() {
	getDay();
	str << year;
	str << setfill('0') << right << setw(2) << month;
	str << setfill('0') << right << setw(2) << day;
	str << "-";
	str << setfill('0') << right << setw(2) << hour;
	str << setfill('0') << right << setw(2) << minute;
	str << setfill('0') << right << setw(2) << second;

	filename = str.str() + ".txt";
	fopen_s(&fp, filename.c_str(), "a+");
	str.str("");
	str.clear(stringstream::goodbit);
	fclose(fp);
}
void Log::makeLog(MsgQueue* captureMessage, MsgQueue* detectMessage, MsgQueue* viewerMessage, MsgQueue* logMessage, logQueue* logqueue) {
	while (true) {
		if (!(logMessage->empty())) {
			logMessage->receive(&messageNum);
			switch (messageNum) {
			case logRequestMessage:
				getDay();
				str << year;	//ƒƒ“ƒoŠÖ”ì‚é
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
				logqueue->receive(&info);
				str << "[" << info.threadName << "]";
				log = str.str() + "\n";
				fopen_s(&fp, filename.c_str(), "a+");
				fputs(log.c_str(), fp);
				fclose(fp);
				str.str("");
				str.clear(stringstream::goodbit);
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
}