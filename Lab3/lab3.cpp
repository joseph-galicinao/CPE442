#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;



Mat to442_grayscale(Mat image, uint16_t num_rows, uint16_t num_cols) {
    cv::Mat grayImage(num_rows, num_cols, CV_8UC1);

    for(int row = 0; row < num_rows; row++) {
        for(int col = 0; col < num_cols; col++) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(row, col);
            
            int blue = pixel[0];
            int green = pixel[1];
            int red = pixel[2];

            float gray = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
            grayImage.at<uchar>(row, col) = gray;
        }
    }
    return grayImage;
}

Mat to442_sobel(Mat grayImage, uint16_t num_rows, uint16_t num_cols) {

    cv::Mat sobelImage(num_rows - 2, num_cols - 2, CV_8UC1); // Subtract two because are ignoring the edges


    // Iterate through the image while ignoring the edges
    for (int row = 1; row < num_rows - 1; row++) {
        for (int col = 1; col < num_cols - 1; col++) {
            // Gets the pixel values from the grayImage
            uint16_t top_left = grayImage.at<uchar>(row - 1, col - 1);
            uint16_t top_middle = grayImage.at<uchar>(row - 1, col);
            uint16_t top_right = grayImage.at<uchar>(row - 1, col + 1);
            uint16_t left = grayImage.at<uchar>(row, col - 1);
            uint16_t middle = grayImage.at<uchar>(row, col);
            uint16_t right = grayImage.at<uchar>(row, col + 1);
            uint16_t bottom_left = grayImage.at<uchar>(row + 1, col - 1);
            uint16_t bottom_middle = grayImage.at<uchar>(row + 1, col);
            uint16_t bottom_right = grayImage.at<uchar>(row, col + 1);

            // Calculate value in the Gx matrix
            uint16_t gx_total = (-1 * top_left) + (0 * top_middle) + (1 * top_right) + 
                                (-2 * left) + (0 * middle) + (2 * right) + 
                                (-1 * bottom_left) + (0 * bottom_middle) + (1 * bottom_right);

            // Get absolute value
            if (gx_total < 0) {
                gx_total = -1 * gx_total;
            }

             // Calculate value in the Gy matrix
            uint16_t gy_total = (1 * top_left) + (2 * top_middle) + (1 * top_right) + 
                                (0 * left) + (0 * middle) + (0 * right) + 
                                (-1 * bottom_left) + (-2 * bottom_middle) + (-1 * bottom_right);

            // Get absolute value
            if (gy_total < 0) {
                gy_total = -1 * gy_total;
            }

            // Checks overflow
            uint16_t total = gx_total + gy_total;
            if (total > 255) {
                total = 255;
            }

            sobelImage.at<uchar>(row - 1, col - 1) = total;
        }
    }

    return sobelImage;
}

int main(int argc, char* argv[]) {
    // Case: valid number of arguments
    if (argc == 2) {
        Mat image = cv::imread(argv[1]); // Reads the image

        // Case: image does not exist
        if (image.empty()) {
            std::cout << "Image does not exist\n";
            return -1;
        }

        uint16_t num_rows = image.rows;
        uint16_t num_cols = image.cols;

        Mat grayImage = to442_grayscale(image, num_rows, num_cols);
        Mat sobelImage = to442_sobel(grayImage, num_rows, num_cols);

        cv::imshow("Image", sobelImage); // Displays the image

        waitKey(0); // Waits to close the new tab before exitting
        return 0;
    }
    // Case: invalid number of arguments (expects 1 argument)
    else {
        std::cout << "Invalid input\n";
        return -1;
    }
}