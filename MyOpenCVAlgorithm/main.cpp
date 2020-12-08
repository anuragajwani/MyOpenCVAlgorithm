//
//  main.cpp
//  MyOpenCVAlgorithm
//
//  Created by Anurag Ajwani on 08/12/2020.
//

#include <iostream>
#include <opencv2/opencv.hpp>

int showImageFromDisk(std::string imagePath) {
    cv::Mat image = cv::imread(imagePath);
    // process image
    cv::imshow("Image from disk", image);
    cv::waitKey();
    return 0;
}

int showVideoFromDisk(std::string videoPath) {
    cv::VideoCapture videoCapture(videoPath);
    if (!videoCapture.isOpened()) {
        std::cout << "Error opening video stream of file" << std::endl;
        return -1;
    }
    while (true) {
        cv::Mat frame;
        videoCapture >> frame;
        // process frame here
        if (frame.empty()) break;
        cv::imshow("Video frame", frame);
        if (cv::waitKey(10) == 27) break;
    }
    videoCapture.release();
    cv::waitKey();
    return 0;
}

int streamWebcamFeed() {
    cv::VideoCapture videoCapture(0);
    if (!videoCapture.isOpened()) {
        std::cout << "Unable to connect to webcam"  << std::endl;
        return -1;
    }
    while(true) {
        cv::Mat frame;
        videoCapture >> frame;
        if(frame.empty()) break;
        cv::imshow("Camera feed", frame);
        if (cv::waitKey(10) == 27) break;
    }
    videoCapture.release();
    return 0;
}

int main(int argc, const char * argv[]) {
    if (argc == 3) {
        std::string readType(argv[1]);
        std::string filePath(argv[2]);
        if (readType == "--image") {
            return showImageFromDisk(filePath);
        } else if (readType == "--video") {
            return showVideoFromDisk(filePath);
        } else {
            return streamWebcamFeed();
        }
    } else {
        return streamWebcamFeed();
    }
    return 0;
}
