#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    Mat image = imread(argv[1]);
    imshow("Image", image);

    waitKey(0);
    return 0;
}