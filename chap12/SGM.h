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
    vector<uint16_t> _costLeft;
    vector<uint16_t> _costRight;
    vector<uint32_t> _censusLeft;
    vector<uint32_t> _censusRight;
    vector<uint16_t> _disparityLeft;
    vector<uint16_t> _disparityRight;

    vector<uint16_t> _aggrationCostLR;
    vector<uint16_t> _aggrationCostRL;
    vector<uint16_t> _aggrationCostUD;
    vector<uint16_t> _aggrationCostDU;
    vector<uint16_t> _aggrationCostTotal;
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
    // ~SGM();

    void ComputeCensus(Mat src, vector<uint32_t> &census);
    void ComputeNCC(Mat leftImg, Mat rightImg, int windowSize, int STEP);
    void ConstructCostVolume();
    void Match(Mat leftImg, Mat rightImg);
    Mat ConstructDisparityLeft();
    void AggregationLeftToRight(Mat src, int p1, int p2Init);
    void AggregationRightToLeft(Mat src, int p1, int p2Init);
    void AggregationUpToDown(Mat src, int p1, int p2Init);
    void AggregationDownToUp(Mat src, int p1, int p2Init);
    Mat ConstructDisparityRight();
    void LeftRightConsistency();
    Mat FixInvalidPoint(Mat src);
};



// SGM::~SGM()
// {
// }

#endif