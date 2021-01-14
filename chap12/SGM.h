#ifndef __SGM_H__
#define __SGM_H__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>
#include <unordered_map> 

using namespace std;
using namespace cv;

class SGM
{
private:
    /* data */
    vector<uint16_t> _cost;
    vector<uint32_t> _censusLeft;
    vector<uint32_t> _censusRight;
    // Mat disparityMap = Mat::zeros()

    int _minDisparity;
    int _maxDisparity;
    int _diesparityRange;
    int _width;
    int _height;
    int _halfWindowSize;

    uint16_t Hamming32(const uint32_t & x, const uint32_t & y);

public:
    SGM(int width, int height, int minDisparity, int maxDisparity, int halfWindowSize);
    ~SGM();

    void ComputeCensus(Mat src, vector<uint32_t> &census);
    void ConstructCostVolume();
};

SGM::SGM(int width, int height, int minDisparity, int maxDisparity, int halfWindowSize)
{
    _maxDisparity = maxDisparity;
    _minDisparity = minDisparity;
    _diesparityRange = maxDisparity - minDisparity;
    _width = width;
    _height = height;
    _halfWindowSize = halfWindowSize;

    _censusLeft.resize(_width * _height);
    _censusRight.resize(_width * _height);
    _cost.resize(_width * _height * _diesparityRange);
}

SGM::~SGM()
{
}



#endif