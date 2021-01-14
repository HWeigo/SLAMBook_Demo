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

void SGM::Construct
