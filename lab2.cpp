#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    // Case: valid number of arguments
    if (argc == 2) {
        Mat image = imread(argv[1]); // Reads the image

        // Case: image does not exist
        if (image.empty()) {
            std::cout << "Image does not exist\n";
            return -1;
        }

        imshow("Image", image); // Displays the image

        waitKey(0); // Waits to close the new tab before exitting
        return 0;
    }
    // Case: invalid number of arguments (expects 1 argument)
    else {
        std::cout << "Invalid input\n";
        return -1;
    }
}