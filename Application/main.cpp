#include <iostream>
#include "libs/json.hpp"
#include "capture.h"
#include "detect.h"
#include "queue.h"
#include "viewer.h"

using namespace std;
using json = nlohmann::json;

int main() {
	FILE* fp;

	fopen_s(&fp, "../config/setting.json", "r");
	auto j = json::parse(fp);
	fclose(fp);

	cout << "bufferSize: " << j["bufferSize"] << endl;
	cout << "fps: " << j["fps"] << endl;

	return 0;
}