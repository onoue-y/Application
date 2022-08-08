#pragma once
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib, "opencv_world455d.lib")
#else
#pragma comment(lib, "opencv_world455.lib")
#endif

using namespace cv;

const int openError = -1;
const int openSuccess = 0;
const Rect notDetect = { 0,0,0,0 };
const int esc = 27;
const int escMessage = 2;
const int getMessage = 1;
const int blue = 0;
const int green = 0;
const int red = 255;
const int thickness = 3;
const int waitSecond = 1;
const double scaleFactor = 1.1;
const int minNeighbors = 3;
const int flags = 0;
const int minsize = 30;