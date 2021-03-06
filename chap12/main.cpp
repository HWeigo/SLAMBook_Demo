// #include <iostream>
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <chrono>
// #include <unordered_map> 
#include "SGM.h"

// using namespace std;
// using namespace cv;

int EpipolarSearch(Mat A, Mat right, int v, int halfWindowSize);
Mat funcSSDR2L(Mat leftImage, Mat rightImage, int windowSize, int dispMin, int dispMax, int STEP);
Mat funcNCCR2L(Mat leftImage, Mat rightImage, int windowSize, int dispMin, int dispMax, int STEP);
Mat funcSADR2L(Mat leftImage, Mat rightImage, int windowSize, int dispMin, int dispMax, int STEP);
#define SGM_ALGO

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

    cout << "Original left image size : " << leftImgOri.size();
    cout << "\tOriginal right image size : " <<rightImgOri.size() << endl;
    // imshow("ori", leftImgOri);

    // Resize
    double scale = 0.24;
    int width = int(leftImgOri.size[0]*scale);
    int height = int(leftImgOri.size[1]*scale);
    Mat leftImgScale, rightImgScale;
    resize(leftImgOri, leftImgScale, cv::Size(), scale, scale);
    resize(rightImgOri, rightImgScale, cv::Size(), scale, scale);
    imshow("left",leftImgScale);
    cout << "Scaled left image size : " << leftImgScale.size();
    cout << "\tScaled left image size : " << rightImgScale.size() << endl;
    imwrite("left_s.jpg", leftImgScale);
    imwrite("right_s.jpg", rightImgScale);
    
    int halfWindowSize = 3;
    int cnt = 0;

#ifndef SGM_ALGO
/*********************/
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
/*********************/

    auto start = std::chrono::system_clock::now();
    // Mat depth = funcSSDR2L(leftImgScale, rightImgScale, 5, 0, 64, 1);
    Mat depth = funcNCCR2L(leftImgScale, rightImgScale, 5, 0, 64, 1);
    // Mat depth = funcSADR2L(leftImgScale, rightImgScale, 5, 0, 64, 1);
    Mat depthFilter;
    bilateralFilter(depth, depthFilter, 9, 25, 50);
    // GaussianBlur(depth, depth, 9, 75, 75);

    auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_sec = end - start;
	std::cout << "\n----- DONE! -----" << std::endl;
	std::cout << "Total used time: " << elapsed_sec.count() << "s." << std::endl;

    imshow("depth", depth);
    imshow("filter", depthFilter);
    // imwrite("SAD.jpg", depthFilter);

    applyColorMap(depth, depth, COLORMAP_JET);
    applyColorMap(depthFilter, depthFilter, COLORMAP_JET);
    imshow("color", depth);
    imshow("color filter", depthFilter);
    // imwrite("SAD_c.jpg", depthFilter);
    
    


    cout << "Done" << endl;
    waitKey(0);
#endif

#ifdef SGM_ALGO
    auto start = std::chrono::system_clock::now();
    SGM sgmSolver(leftImgScale.cols, leftImgScale.rows, 0, 64, 5);
    sgmSolver.Match(leftImgScale, rightImgScale);
    Mat disparityLeft = sgmSolver.ConstructDisparityLeft();
    Mat disparityRight = sgmSolver.ConstructDisparityRight();
    imshow("disparity Left", disparityLeft);
    imshow("disparity Right", disparityRight);


	double fx = 3997.684 * scale * 0.001;
	double fy = 3997.684 * scale * 0.001;
	double cx = 1176.728 * scale;
	double cy = 1011.728 * scale;
	double b = 193.001;
	ofstream outFile;
	outFile.open("PointCloud.txt");
	outFile << "x/m\ty/m\tz/m\n";
	for (int v=disparityLeft.rows-1; v>=0; --v) {
		for (int u=disparityLeft.cols-1; u>= 0; --u) {
			double z = b * fx / disparityLeft.at<uchar>(v,u) ;
			double x = (u - cx) * z / fx * 0.001;
			double y = (v - cy) * z / fy * 0.001;
			if (x == INFINITY || y == INFINITY || z == INFINITY)
				continue;
			outFile << x << " " << y << " " << z << "\n";
		}
	}
	outFile.close();


    Mat colorLeft;
    applyColorMap(disparityLeft, colorLeft, COLORMAP_JET);
    medianBlur(colorLeft, colorLeft, 5);
    medianBlur(disparityLeft, disparityLeft, 5);


    auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_sec = end - start;
	std::cout << "\n----- DONE! -----" << std::endl;
	std::cout << "Total used time: " << elapsed_sec.count() << "s." << std::endl;

    imshow("color Left", colorLeft);  
    imwrite("Cen.jpg", disparityLeft);
    imwrite("Cen_c.jpg", colorLeft);

    waitKey(0);
#endif
    

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
        // cout << "Row: " << i << endl;
	}
	normalize(dispMap, dispMap, 0, 255, NORM_MINMAX);
	return dispMap;
}


Mat funcNCCR2L(Mat leftImage, Mat rightImage, int windowSize, int dispMin, int dispMax, int STEP = 1)
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
			double prevNCC = 0.0;
			int bestMatchSoFar = dispMin;
			for (int dispRange = dispMin; dispRange <= dispMax; dispRange++)
			{
				double ncc = 0.0;
				double nccNumberator = 0.0;
				double nccDenominator = 0.0;
				double nccDenominatorRightWindow = 0.0;
				double nccDenominatorLeftWindow = 0.0;
				for (int a = -win; a <= win; a++)
				{
					for (int b = -win; b <= win; b++)
					{
						nccNumberator += rightImage.at<uchar>(i + a, j + b)*leftImage.at<uchar>(i + a, j + b + dispRange);
						nccDenominatorRightWindow += rightImage.at<uchar>(i + a, j + b)*rightImage.at<uchar>(i + a, j + b);
						nccDenominatorLeftWindow += leftImage.at<uchar>(i + a, j + b + dispRange)*leftImage.at<uchar>(i + a, j + b + dispRange);
					}
				}
				nccDenominator = sqrt(nccDenominatorRightWindow*nccDenominatorLeftWindow);
				ncc = nccNumberator / nccDenominator;
				if (prevNCC < ncc)
				{
					prevNCC = ncc;
					bestMatchSoFar = dispRange;
				}
			}
			dispMap.at<uchar>(i, j) = bestMatchSoFar;
		}
	}
	normalize(dispMap, dispMap, 0, 255, NORM_MINMAX);
	return dispMap;
}

Mat funcSADR2L(Mat leftImage, Mat rightImage, int windowSize, int dispMin, int dispMax, int STEP)
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
		for (int j = 0 + win; j <= ncLeft - win - dispMax; j = j+STEP)
		{
			double prevSAD = 65532;
			double temp = 0.0;
			int bestMatchSoFar = dispMin;
			for (int dispRange = dispMin; dispRange <= dispMax; dispRange++)
			{
				double sad = 0.0;
				for (int a = -win; a <= win; a++)
				{
					for (int b = -win; b <= win; b++)
					{
						if (j + b + dispRange <= ncLeft)
						{
							temp = (double)rightImage.at<uchar>(i + a, j + b) - (double)leftImage.at<uchar>(i + a, j + b + dispRange);
							if (temp < 0.0)
							{
								temp = temp*(-1.0);
							}
							sad = sad + temp;
						}
					}
				}
				if (prevSAD > sad)
				{
					prevSAD = sad;
					bestMatchSoFar = dispRange;
				}
			}
			dispMap.at<uchar>(i, j) = bestMatchSoFar;
		}
	}
	normalize(dispMap, dispMap, 0, 255, NORM_MINMAX);
	return dispMap;
}