#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <chrono>

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "NOT ENOUGH ARGUMENT." << std::endl;
        return EXIT_FAILURE; 
    }

    cv::Mat img_1 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_2 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);

    return EXIT_SUCCESS;
}