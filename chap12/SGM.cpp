#include "SGM.h"

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
    _disparityLeft.resize(_width * _height);
    _aggrationCost.resize(_width * _height * _diesparityRange);
}

void SGM::ComputeCensus(Mat src, vector<uint32_t> &censusList) {
    if (_height != src.rows || _width != src.cols) {
        cerr << "Size ERROR" << endl;
        return;
    }

    for (int v=_halfWindowSize; v<(_height-_halfWindowSize); ++v) {
        for (int u=_halfWindowSize; u<(_width-_halfWindowSize); ++u) {
            uchar center = src.at<uchar>(v, u);
            uint32_t census = 0;
            for (int i=-_halfWindowSize; i<=_halfWindowSize; ++i) {
                for (int j=-_halfWindowSize; j<=_halfWindowSize; ++j) {
                    census <<= 1;
                    uchar curr = src.at<uchar>(v+i, u+j);
                    if (center > curr) {
                        census += 1;
                    }
                }
            }
            
            censusList[v*_width + u] = census;
        }
    }
}

uint16_t SGM::Hamming32(const uint32_t & x, const uint32_t & y) {
    uint32_t dist = 0, val = x ^ y;

	// Count the number of set bits
	while (val) {
		++dist;
		val &= val - 1;
	}

	return dist;
}

void SGM::ConstructCostVolume() {
    for (int v=0; v<_height; ++v) {
        for (int u=0; u<_width; ++u) {
            uint32_t leftCensus = _censusLeft[v*_width + u];
            for (int i=_minDisparity; i<_maxDisparity; ++i) {
                if (u-i < 0 || u-i >= _width) {
                    _cost[_diesparityRange*(v*_width + u) + i - _minDisparity] = INT16_MAX;
                    continue;
                }
                uint32_t rightCensus = _censusRight[v*_width + u - i];
                uint16_t cost = Hamming32(leftCensus, rightCensus);
                
                _cost[_diesparityRange*(v*_width + u) + i - _minDisparity] = cost;
            }
        }
    }
}

Mat SGM::ConstructDisparity() {
    Mat disparityMap = Mat(_height, _width, CV_8UC1);
    for (int v=0; v<_height; ++v) {
        for (int u=0; u<_width; ++u) {
            uint16_t minCost = UINT16_MAX;
            uint16_t maxCost = 0;
            uint16_t bestMatch = 0;
            for (int i=_minDisparity; i<_maxDisparity; ++i) {
                uint16_t currCost = _cost[_diesparityRange*(v*_width + u) + i];
                if (currCost < minCost) {
                    bestMatch = i;
                    minCost = currCost;
                }
                maxCost = (currCost > maxCost)? currCost:maxCost;
            }
            
            disparityMap.at<uchar>(v, u) = bestMatch;
            // if (minCost != maxCost) {
            //     // _disparityLeft[]
                
            // } else {
            //      disparityMap.at<uchar>[v][u] = INVALID
            // }
            
        }
    }
    return disparityMap;
}

void SGM::Match(Mat leftImg, Mat rightImg) {
    ComputeCensus(leftImg, _censusLeft);
    ComputeCensus(rightImg, _censusRight);

    ConstructCostVolume();
}

void SGM::AggregationLeftToRight(int p1, int p2Init) {
    for (int v=0; v<_height; ++v) {
        // Initial the first pixel
        _aggrationCost[v*_width * _diesparityRange]
        uint16_t lastPassMin = 0;
        for (int u=1; u<_width; ++u) {
            uint16_t minCost = UINT16_MAX;
            for (int i=0; i<_diesparityRange; ++i) {
                uint16_t C = _cost[_diesparityRange*(v*_width + u) + i];
                uint16_t L1 = 
                uint16_t L2 = 
                uint16_t L3 = 
                uint16_t L4 = 


                _aggrationCost[v*_width*_diesparityRange + u*_diesparityRange + i] = 
                minCost = (minCost > *** )? *** : minCost;
            }
            lastPassMin = minCost;
        }

    }
}
