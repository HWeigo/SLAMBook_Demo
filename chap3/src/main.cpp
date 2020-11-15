#include <iostream>

#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
    cout << "Eign Test." << endl;
    Matrix<int,2,3> matrix_23;
    
    // Vector3d is equal to Matrix<double, 3, 1>
    Vector3d v_3d;

    matrix_23 << 1,2,3,4,5,6 ;
    cout << "Print matrix_23: \n" << matrix_23 << endl;

    v_3d << 11,12,13;
    cout << "Print v_3d: \n" << v_3d << endl;
    
    cout << "The (0,1) element in Matrix: " << matrix_23(0,1) << endl;

    cout << "Matrix transpose: \n" << matrix_23.transpose() << endl;

    Matrix3f matrix_33;
    matrix_33 << 1,0,0,5,2,6,2,8,1;
    cout << "Print matrix_33:\n" << matrix_33 << endl;
    cout << "matrix_33's inverse:\n" << matrix_33.inverse() << endl;

    
    return 0;
}