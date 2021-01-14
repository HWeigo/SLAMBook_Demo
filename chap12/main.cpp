#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>
#include <unordered_map> 

using namespace std;
using namespace cv;

int EpipolarSearch(Mat A, Mat right, int v, int halfWindowSize);
Mat funcSSDR2L(Mat leftImage, Mat rightImage, int windowSize, int dispMin, int dispMax, int STEP);

int main(int argc, char **argv) {

    if (argc != 3) {
        cerr << "[ERROR] Not enough arguments!" << endl;
        return EXIT_FAILURE;
    }

    Mat leftImgOri = imread(argv[1], IMREAD_GRAYSCALE);
    Mat rightImgOri = imread(argv[2], IMREAD_GRAYSCALE);
    if (!leftImgOri.data || !rightImgOri.data || leftImgOri.size() != rightImgOri.size()) {
        cerr << "[ERROR] Unable to load image." << endl;
        return EXIT_FAILURE;
    }

    cout << leftImgOri.size() << endl;
    cout << rightImgOri.size() << endl;
    // imshow("ori", leftImgOri);

    // Resize
    double scale = 0.25;
    int width = int(leftImgOri.size[0]*scale);
    int height = int(leftImgOri.size[1]*scale);
    Mat leftImgScale, rightImgScale;
    resize(leftImgOri, leftImgScale, cv::Size(), scale, scale);
    resize(rightImgOri, rightImgScale, cv::Size(), scale, scale);
    imshow("left",leftImgScale);
    cout << leftImgScale.size() << endl;
    cout << rightImgScale.size() << endl;

    int halfWindowSize = 3;
    int cnt = 0;

    // Mat depth(leftImgScale.size(), CV_16U);
    // for (int v=halfWindowSize; v<(leftImgScale.rows-halfWindowSize); ++v) {
    //     for (int u=halfWindowSize; u<(leftImgScale.cols-halfWindowSize); ++u) {
    //         Rect box(u-halfWindowSize, v-halfWindowSize, halfWindowSize*2+1, halfWindowSize*2+1);
    //         Mat A = leftImgScale(box);
    //         int correspondence = EpipolarSearch(A, rightImgScale, v, halfWindowSize);
    //         if (correspondence == -1) {
    //             cerr << "Epipolar search failed" << endl;
    //             return EXIT_FAILURE;
    //         }
    //     //    int disparity = u-correspondence;
    //        depth.at<uchar>(u, v) = (uchar)(u-correspondence);
    //     }
    //     cout << "Row: " << v << endl; 
    // }
    // normalize(depth, depth, 0, 255, NORM_MINMAX);
    
    Mat depth = funcSSDR2L(leftImgScale, rightImgScale, 11, 0, 20, 1);

    imshow("depth", depth);
    cout << "Done" << endl;
    waitKey(0);

    return EXIT_SUCCESS;
}

int EpipolarSearch(Mat A, Mat right, int v, int halfWindowSize) {  
    // vector<double> score;
    // score.reserve(right.cols);

    double score = DBL_MAX;
    int location = -1;
    for (int u= halfWindowSize; u<(right.cols-halfWindowSize); ++u) {
        Rect box(u-halfWindowSize, v-halfWindowSize, halfWindowSize*2+1, halfWindowSize*2+1);
        Mat B = right(box);
        double temp = norm(A-B, NORM_L2);
        if (temp < score) {
            score = temp;
            location = u;
        }
    }
    
    return location;
}


Mat funcSSDR2L(Mat leftImage, Mat rightImage, int windowSize, int dispMin, int dispMax, int STEP)
{
	CV_Assert(leftImage.rows == rightImage.rows && leftImage.cols == rightImage.cols);
	CV_Assert(windowSize % 2 == 1);
	CV_Assert(dispMax > dispMin);
	int nrLeft = leftImage.rows - 1;
	int ncLeft = leftImage.cols - 1;
	int win = (windowSize - 1) / 2;
	Mat dispMap = Mat::zeros(nrLeft, ncLeft, CV_8UC1);
	for (int i = 0 + win; i <= nrLeft - win; i = i + STEP)
	{
		for (int j = 0 + win; j <= ncLeft - win - dispMax; j = j + STEP)
		{
			double prevSDD = 65532;
			double temp = 0.0;
			int bestMatchSoFar = dispMin;
			for (int dispRange = dispMin; dispRange <= dispMax; dispRange++)
			{
				double ssd = 0.0;
				for (int a = -win; a <= win; a++)
				{
					for (int b = -win; b <= win; b++)
					{
						if (j + b + dispRange <= ncLeft)
						{
							temp = (double)rightImage.at<uchar>(i + a, j + b) - (double)leftImage.at<uchar>(i + a, j + b + dispRange);
							temp = temp*temp;
							ssd = ssd + temp;
						}
					}
				}
				if (prevSDD > ssd)
				{
					prevSDD = ssd;
					bestMatchSoFar = dispRange;
				}
			}
			dispMap.at<uchar>(i, j) = bestMatchSoFar;
		}
        cout << "Row: " << i << endl;
	}
	normalize(dispMap, dispMap, 0, 255, NORM_MINMAX);
	return dispMap;
}