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
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descirptor = cv::ORB::create();

    detector->detectAndCompute(inImg1, cv::noArray(), keypoint1, descriptors_1);
    detector->detectAndCompute(inImg2, cv::noArray(), keypoint2, descriptors_2);

    // Display
    cv::Mat keypointImg1, keypointImg2;
    cv::drawKeypoints(inImg1, keypoint1, keypointImg1);
    cv::drawKeypoints(inImg2, keypoint2, keypointImg2);
    cv::imshow("Keypoint1", keypointImg1);
    cv::imshow("Keypoint2", keypointImg2);

    // Step 2: Match keypoints
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create( "BruteForce-Hamming" );
    vector<cv::DMatch> matches;
    matcher->match(descriptors_1, descriptors_2, matches);
    cv::Mat matchImg;
    cv::drawMatches(inImg1, keypoint1, inImg2, keypoint2, matches, matchImg);
    cv::imshow("Match", matchImg);

    cv::waitKey(0);

    return EXIT_SUCCESS;
}