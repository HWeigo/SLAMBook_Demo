#ifndef __DETECTS_DETECTION__
#define __DETECTS_DETECTION__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>

using namespace std;
using namespace cv;

Mat EnhanceContraction(Mat & srcImg);
void ConnectedComponentLabeling(Mat srcImg);

#endif