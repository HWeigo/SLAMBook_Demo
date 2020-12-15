#include "defectsDetection.h"

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

    Mat imageBlur, imageEnhanced, imageFilter, imageEdge, imageClosed;
    GaussianBlur(imageOri, imageBlur, Size(3,3), 1.0);
    imshow("Blur Image: ", imageBlur);

    imageEnhanced = EnhanceContraction(imageBlur);
    // equalizeHist(imageBlur, imageEnhanced);
    imshow("Enhanced Image: ", imageEnhanced);

    bilateralFilter(imageEnhanced, imageFilter, 9, 75, 75);
    imshow("Filter Image: ", imageFilter);


    // Implement Canny edge detection
    Canny(imageBlur, imageEdge, 20, 50);
    imshow("Canny Detection", imageEdge);

    
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5), Point(-1, -1));
    morphologyEx(imageEdge, imageClosed, MORPH_CLOSE, kernel);
    imshow("Closed image: ",imageClosed);

    ConnectedComponentLabeling(imageEdge);

    // imwrite("Blur.jpg", imageBlur);



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
            out[u] =saturate_cast<uchar>(log(data[u]+1)/log(*maxPtr + 1)*255);
            // out[u] = saturate_cast<uchar>((data[u]-*minPtr)/(*maxPtr - *minPtr)*255);
            // out[u] = saturate_cast<uchar>(pow(data[u]/255.0,0.7)*255);
        }
    }
    minMaxIdx(outImg, minPtr, maxPtr);
    for (int v=0; v<srcImg.rows; v++){
        uchar *out = outImg.ptr<uchar>(v);
        for (int u=0; u<srcImg.cols; u++) {
            // out[u] =saturate_cast<uchar>(log(out[u]+1)/log(*maxPtr + 1)*255);
            // out[u] = saturate_cast<uchar>((out[u]-*minPtr)/(*maxPtr - *minPtr)*255);
            out[u] = saturate_cast<uchar>(pow(out[u]/255.0,1.7)*255);
        }
    }
    minMaxIdx(outImg, minPtr, maxPtr);
    for (int v=0; v<srcImg.rows; v++){
        uchar *out = outImg.ptr<uchar>(v);
        for (int u=0; u<srcImg.cols; u++) {
            // out[u] =saturate_cast<uchar>(log(out[u]+1)/log(*maxPtr + 1)*255);
            out[u] = saturate_cast<uchar>((out[u]-*minPtr)/(*maxPtr - *minPtr)*255);
            // out[u] = saturate_cast<uchar>(pow(out[u]/255.0,1.7)*255);
        }
    }
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

void ConnectedComponentLabeling(Mat srcImg) {
    int numW = 0, numB = 0, numT = 0;;
    for (int v=0; v<srcImg.rows; v++) {
        uchar *data = srcImg.ptr<uchar>(v);
        for (int u=0; u<srcImg.cols; u++) {
            if (data[u] == 255){
                // cout << "White" << endl;
                numW ++;
            }
            if (data[u] == 0) {
                // cout << "Black" << endl;
                numB ++;
            }
            numT++;
        }
    }
    cout << numW << " " << numB << endl;
    cout << numW+numB << endl;
    cout << numT << endl;
    cout << srcImg.rows*srcImg.cols << endl;
}