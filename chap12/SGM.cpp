#include "SGM.h"

void SGM::ComputeCensus(Mat src, vector<uint32_t> &censusList) {
    if (_height != src.size[1] || _width != src.size[0]) {
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
                    _cost[_diesparityRange*(v*_width + u) + i - _minDisparity] = 0;
                    continue;
                }
                uint32_t rightCensus = _censusRight[v*_width + u - i];
                uint16_t cost = Hamming32(leftCensus, rightCensus);
                _cost[_diesparityRange*(v*_width + u) + i - _minDisparity] = cost;
            }
        }
    }
}

