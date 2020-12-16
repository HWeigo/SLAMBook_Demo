#include "defectsDetection.h"

// #define DEBUG_IMAGEDISPLAY
// #define DEBUG_IMAGESAVE
int main (int argc, char **argv) {

    auto start = std::chrono::system_clock::now();

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
#ifdef DEBUG_IMAGEDISPLAY
    imshow("Original Image: ", imageOri);
#endif

    Mat imageBlur, imageEnhanced, imageFilter, imageEdge, imageClosed;
    GaussianBlur(imageOri, imageBlur, Size(3,3), 1.0);
#ifdef DEBUG_IMAGEDISPLAY
    imshow("Blur Image: ", imageBlur);
#endif 

    imageEnhanced = EnhanceContraction(imageBlur);
    // equalizeHist(imageBlur, imageEnhanced);
#ifdef DEBUG_IMAGEDISPLAY
    imshow("Enhanced Image: ", imageEnhanced);
#endif

    bilateralFilter(imageEnhanced, imageFilter, 9, 75, 75);
#ifdef DEBUG_IMAGEDISPLAY
    imshow("Filter Image: ", imageFilter);
#endif

    // Implement Canny edge detection
    Canny(imageBlur, imageEdge, 20, 50);
#ifdef DEBUG_IMAGEDISPLAY
    imshow("Canny Detection", imageEdge);
#endif

    
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5), Point(-1, -1));
    morphologyEx(imageEdge, imageClosed, MORPH_CLOSE, kernel);
#ifdef DEBUG_IMAGEDISPLAY
    imshow("Closed image: ",imageClosed);
#endif

    vector<Set> setList;
    setList = ConnectedComponentLabeling(imageClosed);
    
    Mat imageColor = imread(argv[1], IMREAD_COLOR);
    for (Set s : setList) {
        if (s.IsRoot() && s.Size() > 100) {
            vector<pair<int, int>> pixels = s.Pixels();
            for (auto p : pixels) {
                imageColor.at<Vec3b>(p.second, p.first)[0] = 0;
                imageColor.at<Vec3b>(p.second, p.first)[1] = 0;
                imageColor.at<Vec3b>(p.second, p.first)[2] = 255;
            }
        } else if (s.IsRoot() && s.Size() <= 100){
            vector<pair<int, int>> pixels = s.Pixels();
            for (auto p : pixels) {
                imageColor.at<Vec3b>(p.second, p.first)[0] = 255;
                imageColor.at<Vec3b>(p.second, p.first)[1] = 0;
                imageColor.at<Vec3b>(p.second, p.first)[2] = 0;
            }
        }
    }
#ifdef DEBUG_IMAGEDISPLAY
    imshow("Detected image", imageColor);
#endif

#ifdef DEBUG_IMAGESAVE
    cout << "----- Saving Image -----" << endl;
    imwrite("result.jpg", imageColor);
    cout << "Done." << endl;
#endif
    // imwrite("result.jpg", imageColor);

    auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_sec = end - start;
	std::cout << "\n----- DONE! -----" << std::endl;
	std::cout << "Total used time: " << elapsed_sec.count() << "s." << std::endl;

    waitKey(0);
    return EXIT_SUCCESS;
}

vector<Set> ConnectedComponentLabeling(Mat srcImg) {
    Mat labelTable = Mat::zeros(srcImg.size(), srcImg.type());
    // Mat labelTable(srcImg.size(),  srcImg.type(), Scalar::all(255));
    int labelCurr = 0;
    vector<Set> setList;
    
    // Fisrt loop
    for (int v=0; v<srcImg.rows; v++) {
        for (int u=0; u<srcImg.cols; u++) {
            // If current pixel is black, then continue
            if (srcImg.at<uchar>(v,u) == 0)
                continue;

            vector<int> neighboorLabels;
            // West
            if (u != 0 && srcImg.at<uchar>(v,u-1) != 0) {
                neighboorLabels.emplace_back(labelTable.at<uchar>(v,u-1));
                // minLabel = MIN(labelTable.at<uchar>(v,u-1), minLabel);
            }
            // North West
            if (u != 0 && v!=0 && srcImg.at<uchar>(v-1,u-1) != 0) {
                neighboorLabels.emplace_back(labelTable.at<uchar>(v-1,u-1));
                // minLabel = MIN(labelTable.at<uchar>(v-1,u-1), minLabel);
            }
            // North 
            if (v!=0 && srcImg.at<uchar>(v-1,u) != 0) {
                neighboorLabels.emplace_back(labelTable.at<uchar>(v-1,u));
                // minLabel = MIN(labelTable.at<uchar>(v-1,u), minLabel);
            }
            // North East
            if (u!=(srcImg.cols-1) && v!=0 && srcImg.at<uchar>(v-1,u+1) != 0) {
                neighboorLabels.emplace_back(labelTable.at<uchar>(v-1,u+1));
                // minLabel = MIN(labelTable.at<uchar>(v-1,u+1), minLabel);
            }
      
            if (neighboorLabels.empty()) {
                // Doesn't have neighborhood
                labelCurr += 1;
                labelTable.at<uchar>(v,u) = labelCurr;
                Set temp(labelCurr);
                setList.emplace_back(temp);
            } else {
                sort(neighboorLabels.begin(), neighboorLabels.end());
                int minLabel = neighboorLabels[0];
                labelTable.at<uchar>(v,u) = minLabel;
                for (int l : neighboorLabels) {
                    setList[l-1].Link(setList, minLabel);
                }
            }
        }
    }

    // imshow("label", labelTable);

    cout << setList.size() << endl;
    for (int v=0; v<srcImg.rows; v++) {
        for (int u=0; u<srcImg.cols; u++) {
            if (srcImg.at<uchar>(v,u) == 0)
                continue;
            int labelCurr = (int) labelTable.at<uchar>(v,u);
            int labelRoot = setList[labelCurr-1].FindRoot(setList);
            // cout << "Current label: " << labelCurr << endl; 

            labelTable.at<uchar>(v,u) = (uchar) labelRoot;
            if (labelRoot == 1 || labelRoot == 10) {
                labelTable.at<uchar>(v,u) = 200;
            }
            setList[labelRoot-1].PushBackPixels(u, v);
            // cout << "Updated label: " << (int) labelTable.at<uchar>(v,u) << endl; 
        }
    }

    sort(setList.begin(), setList.end(), CompSet);

#ifdef DEBUG_INFO
    for (Set s : setList) {
        if (s.IsRoot()) {
            cout << "Label: " << s.Label();
            cout << "Size: " << s.Size() << endl;
        }
    }
#endif

#ifdef DEBUG_IMAGEDISPLAY
    imshow("label_new", labelTable);
#endif

    return setList;
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
    return outImg;
}