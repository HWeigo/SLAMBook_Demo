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
    _costLeft.resize(_width * _height * _diesparityRange);
    _disparityLeft.resize(_width * _height);
    _aggrationCostLR.resize(_width * _height * _diesparityRange);
    _aggrationCostRL.resize(_width * _height * _diesparityRange);
    _aggrationCostUD.resize(_width * _height * _diesparityRange);
    _aggrationCostDU.resize(_width * _height * _diesparityRange);
    _aggrationCostTotal.resize(_width * _height * _diesparityRange);
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
                    _costLeft[_diesparityRange*(v*_width + u) + i - _minDisparity] = INT16_MAX / 2;
                    continue;
                }
                uint32_t rightCensus = _censusRight[v*_width + u - i];
                uint16_t cost = Hamming32(leftCensus, rightCensus);
                
                _costLeft[_diesparityRange*(v*_width + u) + i - _minDisparity] = cost;
            }
        }
    }
}

Mat SGM::ConstructDisparityLeft() {
    Mat disparityMap = Mat(_height, _width, CV_8UC1);
    // for (int v=0; v<_height; ++v) {
    //     for (int u=0; u<_width; ++u) {
    //         uint16_t minCost = UINT16_MAX;
    //         uint16_t maxCost = 0;
    //         uint16_t bestMatch = 0;
    //         for (int i=_minDisparity; i<_maxDisparity; ++i) {
    //             uint16_t currCost = _costLeft[_diesparityRange*(v*_width + u) + i];
    //             if (currCost < minCost) {
    //                 bestMatch = i;
    //                 minCost = currCost;
    //             }
    //             maxCost = (currCost > maxCost)? currCost:maxCost;
    //         }
            
    //         disparityMap.at<uchar>(v, u) = bestMatch;
    //         // if (minCost != maxCost) {
    //         //     // _disparityLeft[]
                
    //         // } else {
    //         //      disparityMap.at<uchar>[v][u] = INVALID
    //         // }
    //     }
    // }

    /*********  USE AGGRAGATION ***************/
    for (int v=0; v<_height; ++v) {
        for (int u=0; u<_width; ++u) {
            uint16_t minCost = UINT16_MAX;
            uint16_t maxCost = 0;
            uint16_t bestMatch = 0;
            for (int i=_minDisparity; i<_maxDisparity; ++i) {
                uint16_t currCost = _aggrationCostTotal[_diesparityRange*(v*_width + u) + i];
                if (currCost < minCost) {
                    bestMatch = i;
                    minCost = currCost;
                }
                maxCost = (currCost > maxCost)? currCost:maxCost;
            }

            // Fitting
            // uint16_t prevMatch = (bestMatch != _minDisparity)? bestMatch-1 : bestMatch;
            // uint16_t nextMatch = (bestMatch != _maxDisparity)? bestMatch+1 : bestMatch;
            // uint16_t prevCost = _aggrationCostTotal[_diesparityRange*(v*_width + u) + prevMatch];
            // uint16_t nextCost = _aggrationCostTotal[_diesparityRange*(v*_width + u) + nextMatch];
            // uint16_t fitMatch = bestMatch + (prevCost - nextCost) / 2 / 

            disparityMap.at<uchar>(v, u) = bestMatch;

        }
    }
    /*******************************************/

    return disparityMap;
}

void SGM::Match(Mat leftImg, Mat rightImg) {
    // Compute census
    ComputeCensus(leftImg, _censusLeft);
    ComputeCensus(rightImg, _censusRight);

    // Construct cost volume
    ConstructCostVolume();

    // Aggregation
    int p1 = 10, p2Init = 150;
    AggregationLeftToRight(leftImg, p1, p2Init);
    AggregationRightToLeft(leftImg, p1, p2Init);
    AggregationUpToDown(leftImg, p1, p2Init);
    AggregationDownToUp(leftImg, p1, p2Init);
    
    uint32_t n = _aggrationCostTotal.size();
    for (uint32_t i=0; i<n; ++i) {
        // _aggrationCostTotal[i] = _aggrationCostLR[i] + _aggrationCostRL[i] ;
        _aggrationCostTotal[i] = _aggrationCostUD[i] + _aggrationCostDU[i] + _aggrationCostLR[i] + _aggrationCostRL[i];
    }
}

void SGM::AggregationLeftToRight(Mat src, int p1, int p2Init) {
    for (int v=0; v<_height; ++v) {
        // Initial the first pixel
        // _aggrationCostLR[v*_width * _diesparityRange]

        uint16_t lastPassMin = UINT16_MAX;
        for (int i=0; i<_diesparityRange; ++i) {
            uint16_t C = _costLeft[_diesparityRange*(v*_width) + i];
            _aggrationCostLR[v*_width*_diesparityRange + i] = C;
            lastPassMin = (C < lastPassMin) ? C : lastPassMin;
        }

        
        for (int u=1; u<_width; ++u) {
            uint16_t minCost = UINT16_MAX;
            uint16_t deltaGray = src.at<uchar>(v,u) - src.at<uchar>(v,u-1);
            for (int i=0; i<_diesparityRange; ++i) {
                uint16_t C = _costLeft[_diesparityRange*(v*_width + u) + i];
                uint16_t L1 = _aggrationCostLR[_diesparityRange*(v*_width + u - 1) + i];
                uint16_t L2 = (i > 0)? (_aggrationCostLR[_diesparityRange*(v*_width + u - 1) + i -1 ] + p1) : UINT16_MAX;
                uint16_t L3 = (i < (_diesparityRange - 1))? (_aggrationCostLR[_diesparityRange*(v*_width + u - 1) + i + 1] + p1) : UINT16_MAX;
                uint16_t L4 = lastPassMin + p2Init / (deltaGray + 1);

                uint16_t totalCost = C + MIN(MIN(L1,L2), MIN(L3,L4)) - lastPassMin;

                _aggrationCostLR[v*_width*_diesparityRange + u*_diesparityRange + i] = totalCost;
                minCost = (totalCost < minCost)? totalCost : minCost;
            }
            lastPassMin = minCost;
        }
    }
}

// ->
void SGM::AggregationRightToLeft(Mat src, int p1, int p2Init) {
    for (int v=0; v<_height; ++v) {
        // Initial the first pixel

        uint16_t lastPassMin = UINT16_MAX;
        for (int i=0; i<_diesparityRange; ++i) {
            uint16_t C = _costLeft[_diesparityRange*((v+1)*_width - 1) + i]; 
            _aggrationCostRL[_diesparityRange*((v+1)*_width - 1) + i] = C;
            lastPassMin = (C < lastPassMin) ? C : lastPassMin;
        }

        
        for (int u=_width - 1; u>=0; --u) {
            uint16_t minCost = UINT16_MAX;
            uint16_t deltaGray = src.at<uchar>(v,u) - src.at<uchar>(v,u+1);
            for (int i=0; i<_diesparityRange; ++i) {
                uint16_t C = _costLeft[_diesparityRange*(v*_width + u) + i];
                uint16_t L1 = _aggrationCostRL[_diesparityRange*(v*_width + u + 1) + i];
                uint16_t L2 = (i > 0)? (_aggrationCostRL[_diesparityRange*(v*_width + u + 1) + i -1 ] + p1) : UINT16_MAX;
                uint16_t L3 = (i < (_diesparityRange - 1))? (_aggrationCostRL[_diesparityRange*(v*_width + u + 1) + i + 1] + p1) : UINT16_MAX;
                uint16_t L4 = lastPassMin + p2Init / (deltaGray + 1);

                uint16_t totalCost = C + MIN(MIN(L1,L2), MIN(L3,L4)) - lastPassMin;

                _aggrationCostRL[v*_width*_diesparityRange + u*_diesparityRange + i] = totalCost;
                minCost = (totalCost < minCost)? totalCost : minCost;
            }
            lastPassMin = minCost;
        }
    }
}

void SGM::AggregationUpToDown(Mat src, int p1, int p2Init) {
    for (int u=0; u<_width; ++u) {
        // Initial the first pixel
        // _aggrationCostUD[v*_width * _diesparityRange]

        uint16_t lastPassMin = UINT16_MAX;
        for (int i=0; i<_diesparityRange; ++i) {
            uint16_t C = _costLeft[_diesparityRange*u  + i];
            _aggrationCostUD[_diesparityRange*u  + i] = C;
            lastPassMin = (C < lastPassMin) ? C : lastPassMin;
        }

        
        for (int v=1; v<_height; ++v) {
            uint16_t minCost = UINT16_MAX;
            uint16_t deltaGray = src.at<uchar>(v,u) - src.at<uchar>(v-1,u);
            for (int i=0; i<_diesparityRange; ++i) {
                uint16_t C = _costLeft[_diesparityRange*(v*_width + u) + i];
                uint16_t L1 = _aggrationCostUD[_diesparityRange*((v-1)*_width + u) + i];
                uint16_t L2 = (i > 0)? (_aggrationCostUD[_diesparityRange*((v-1)*_width + u) + i -1 ] + p1) : UINT16_MAX;
                uint16_t L3 = (i < (_diesparityRange - 1))? (_aggrationCostUD[_diesparityRange*((v-1)*_width + u) + i + 1] + p1) : UINT16_MAX;
                uint16_t L4 = lastPassMin + p2Init / (deltaGray + 1);

                uint16_t totalCost = C + MIN(MIN(L1,L2), MIN(L3,L4)) - lastPassMin;

                _aggrationCostUD[v*_width*_diesparityRange + u*_diesparityRange + i] = totalCost;
                minCost = (totalCost < minCost)? totalCost : minCost;
            }
            lastPassMin = minCost;
        }
    }
}

void SGM::AggregationDownToUp(Mat src, int p1, int p2Init) {
    for (int u=0; u<_width; ++u) {
        // Initial the first pixel
        // _aggrationCostDU[v*_width * _diesparityRange]

        uint16_t lastPassMin = UINT16_MAX;
        for (int i=0; i<_diesparityRange; ++i) {
            uint16_t C = _costLeft[_diesparityRange*(_height-1)*_width + _diesparityRange*u + i];
            _aggrationCostDU[_diesparityRange*(_height-1)*_width + _diesparityRange*u  + i] = C;
            lastPassMin = (C < lastPassMin) ? C : lastPassMin;
        }

        
        for (int v=_height - 1; v>=0; --v) {
            uint16_t minCost = UINT16_MAX;
            uint16_t deltaGray = src.at<uchar>(v,u) - src.at<uchar>(v+1,u);
            for (int i=0; i<_diesparityRange; ++i) {
                uint16_t C = _costLeft[_diesparityRange*(v*_width + u) + i];
                uint16_t L1 = _aggrationCostDU[_diesparityRange*((v+1)*_width + u) + i];
                uint16_t L2 = (i > 0)? (_aggrationCostDU[_diesparityRange*((v+1)*_width + u) + i -1 ] + p1) : UINT16_MAX;
                uint16_t L3 = (i < (_diesparityRange - 1))? (_aggrationCostDU[_diesparityRange*((v+1)*_width + u) + i + 1] + p1) : UINT16_MAX;
                uint16_t L4 = lastPassMin + p2Init / (deltaGray + 1);

                uint16_t totalCost = C + MIN(MIN(L1,L2), MIN(L3,L4)) - lastPassMin;

                _aggrationCostDU[v*_width*_diesparityRange + u*_diesparityRange + i] = totalCost;
                minCost = (totalCost < minCost)? totalCost : minCost;
            }
            lastPassMin = minCost;
        }
    }
}

Mat SGM::ConstructDisparityRight() {
    for (int v=0; v<_height; ++v) {
        for (int u=0; u<_width; ++u) {

        }
    }
}