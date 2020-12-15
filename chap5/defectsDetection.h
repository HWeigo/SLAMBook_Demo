#ifndef __DETECTS_DETECTION__
#define __DETECTS_DETECTION__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>

using namespace std;
using namespace cv;

Mat EnhanceContraction(Mat & srcImg);
void ConnectedComponentLabeling(Mat srcImg);

class Set {
    private:
        int label;
        int parent;

        int FindRootHelper(const vector<Set> &setList, int x) {
            if (setList[x-1].parent != x)
                return FindRootHelper(setList, setList[x-1].parent);
            return x;
        }

    public:
        Set(int x) {
            parent = x;
            label = x;
        }

        void Link(const vector<Set> &setList, int target) {
            Set root = setList[target-1];
            parent = root.FindRoot(setList);
        }

        int FindRoot(const vector<Set> &setList) {
            if (parent !=  label) 
                return FindRootHelper(setList, parent);
            return parent;
        }

};

#endif