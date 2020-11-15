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

    // List Image's Infomation
    cout << "Image width:" << image.cols << endl;
    cout << "Image height:" << image.rows << endl;
    cout << "Image channels:" << image.channels() << endl;
    cout << "Image type:" << image.type() << endl;
    
    // Display Image
    cv::imshow("Ubuntu", image);
    cv::waitKey(0);

    
    return 0;
}
