#include <iostream>
#include <chrono>

using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{
    cv::Mat image;
    image = cv::imread(argv[1]);

    if(image.data == nullptr)
    {
        cerr << "File " << argv[1] << " is empty." << endl;
        return 0;
    }

    cout << "Image width:" << image.cols << endl;
    cout << "Image height" << image.rows << endl;

    return 0;
}
