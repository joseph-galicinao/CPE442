#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        Mat image = imread(argv[1]);
        
        if (image.empty()) {
            std::cout << "Image does not exist\n";
            return -1;
        }

        imshow("Image", image);

        waitKey(0);
        return 0;
    }
    else {
        std::cout << "Invalid input\n";
        return -1;
    }
}