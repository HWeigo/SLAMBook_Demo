#ifndef __DETECTS_DETECTION__
#define __DETECTS_DETECTION__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>

using namespace std;
using namespace cv;

// #define MAX(a,b)            (((a) > (b)) ? (a) : (b))
// #define MIN(a,b)            (((a) < (b)) ? (a) : (b))

Mat EnhanceContraction(Mat & srcImg);
void ConnectedComponentLabeling(Mat srcImg);

#endif