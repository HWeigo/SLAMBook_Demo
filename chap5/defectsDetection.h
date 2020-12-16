#ifndef __DETECTS_DETECTION__
#define __DETECTS_DETECTION__

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>
#include <unordered_map> 

using namespace std;
using namespace cv;

class Set {
    private:
        int label;
        int parent;
        vector<pair<int, int>> pixels;

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

        void PushBackPixels(int u, int v) {
            pixels.push_back(make_pair(u, v));
        }

        bool IsRoot () {
            return parent == label;
        }

        int Label() {
            return label;
        }

        int Size() {
            return pixels.size();
        }

        vector<pair<int, int>>& Pixels() {
            return pixels;
        }
}; 

bool CompSet (Set a, Set b) {
    return (a.Size() > b.Size());
}

Mat EnhanceContraction(Mat & srcImg);
vector<Set> ConnectedComponentLabeling(Mat srcImg);

#endif