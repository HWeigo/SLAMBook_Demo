#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat EnhanceContraction(Mat & srcImg) ;

int main (int argc, char **argv) {

    if (argc != 2) {
        cerr << "[ERROR] Not enough arguments!" << endl;
        return EXIT_FAILURE;
    }

    // Load the image as gray scale
    Mat imageOri = imread(argv[1], IMREAD_GRAYSCALE);
    if (!imageOri.data) {
        cout << "[ERROR] Unable to load image." << endl;
        return EXIT_FAILURE;
    }
    imshow("Original Image: ", imageOri);

    Mat imageBlur, imageEnhanced, imageEdge, imageClosed;
    GaussianBlur(imageOri, imageBlur, Size(3,3), 1.0);
    imshow("Blur Image: ", imageBlur);

    imageEnhanced = EnhanceContraction(imageBlur);
    imshow("Enhanced Image: ", imageEnhanced);

    // Implement Canny edge detection
    Canny(imageEnhanced, imageEdge, 15, 40);
    imshow("Canny Detection", imageEdge);


	Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5), Point(-1, -1));
    morphologyEx(imageEdge, imageClosed, MORPH_CLOSE, kernel);
    imshow("Closed image: ",imageClosed);
    // // imwrite("Blur.jpg", imageBlur);

    waitKey(0);
    return EXIT_SUCCESS;
}

Mat EnhanceContraction(Mat & srcImg) {
    Mat outImg = Mat::zeros(srcImg.size(), srcImg.type());

    // Calculate maximum and minimum pixel value in the image
    double *minPtr = new double;
    double *maxPtr = new double;
    minMaxIdx(srcImg, minPtr, maxPtr);
    cout << "Min vlaue: " << *minPtr << endl;
    cout << "Max vlaue: " << *maxPtr << endl;

    // Enhance contraction 
    for (int v=0; v<srcImg.rows; v++){
        uchar *data = srcImg.ptr<uchar>(v);
        uchar *out = outImg.ptr<uchar>(v);
        for (int u=0; u<srcImg.cols; u++) {
            out[u] =saturate_cast<uchar>(log(data[u]+1-100)/log(*maxPtr + 1)*255);
            // out[u] = saturate_cast<uchar>((data[u]-*minPtr)/(*maxPtr - *minPtr)*255);
            // out[u] = saturate_cast<uchar>(pow(data[u]/255.0,0.7)*255);
        }
    }
    // for (int v=0; v<srcImg.rows; v++){
    //     uchar *out = outImg.ptr<uchar>(v);
    //     for (int u=0; u<srcImg.cols; u++) {
    //         out[u] =saturate_cast<uchar>(log(out[u]+1)/log(*maxPtr + 1)*255);
    //         // out[u] = saturate_cast<uchar>((data[u]-*minPtr)/(*maxPtr - *minPtr)*255);
    //         // out[u] = saturate_cast<uchar>(pow(data[u]/255.0,3)*255);
    //     }
    // }

    minMaxIdx(outImg, minPtr, maxPtr);
    cout << "Min vlaue: " << *minPtr << endl;
    cout << "Max vlaue: " << *maxPtr << endl;
    // Mat lookUpTable(1, 256, CV_8U);
    // double temp = pow(1.1, 2);
    // uchar* p = lookUpTable.data;
    // for (int i = 0; i < 256; ++i) {
    //     // p[i] = saturate_cast<uchar>(i * temp);
    //     // p[i] = saturate_cast<uchar>(pow(i / 255.0, 2) * 255.0);
    //     p[i] = static_cast<uchar>(log(i+1)/log(*maxPtr + 1) * 255 * 0.8);
    // }
    // LUT(srcImg, lookUpTable, srcImg);
    return outImg;
}
