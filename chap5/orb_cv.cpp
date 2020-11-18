#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <chrono>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "NOT ENOUGH ARGUMENT." << endl;
        return EXIT_FAILURE; 
    }

    cv::Mat inImg1 = cv::imread(argv[1], CV_HAL_DFT_STAGE_COLS);
    cv::Mat inImg2 = cv::imread(argv[2], CV_HAL_DFT_STAGE_COLS);
    
    // Step 1: Detect the keypoint using ORB detector
    vector<cv::KeyPoint> keypoint1, keypoint2;
    cv::Mat descriptors_1, descriptors_2;
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create;
    cv::Ptr<cv::DescriptorExtractor> descirptor = cv::ORB::create;

    detector->detectAndCompute(inImg1, cv::noArray(), keypoint1, descriptors_1);
    detector->detectAndCompute(inImg2, cv::noArray(), keypoint2, descriptors_2);

    // Step 2: Match keypoints
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create( "ORB" );
    
    cv::Mat outImg1, outImg2;
    cv::drawKeypoints(inImg1, keypoint1, outImg1);
    cv::drawKeypoints(inImg2, keypoint2, outImg2);
    cv::imshow(outImg1);
    cv::imshow(outImg2);


    return EXIT_SUCCESS;
}