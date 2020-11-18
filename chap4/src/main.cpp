#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "sophus/se3.hpp"

using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
    Matrix3d R = AngleAxisd(M_PI /2,  Vector3d(0,0,1)).toRotationMatrix();
    Sophus::SO3d SO3_R(R);
    
    return 0;
}