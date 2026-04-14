#pragma once
#include <opencv2/opencv.hpp>

namespace imgproc{
    cv::Mat loadImage(const std::string& path);
    
    cv::Mat toGrayscale(const cv::Mat& image);

    cv::Mat normalizeImage(const cv::Mat& image);

    cv::Mat addGaussianNoise(const cv::Mat& image, double mean, double stddev);

    cv::Mat gaussianBlur(const cv::Mat& image, int kernelSize);

    cv::Mat medianBlur(const cv::Mat& image, int kernelSize);

    cv::Mat sobelX(const cv::Mat& image);

    cv::Mat sobelY(const cv::Mat& image);

    cv::Mat sobelMagnitude(const cv::Mat& gradX, const cv::Mat& gradY);

    cv::Mat cannyEdge(const cv::Mat& image, int t1, int t2);

    cv::Mat rotateImage(const cv::Mat& image, double angle);

    cv::Mat affineTransform(const cv::Mat& image);

    cv::Mat perspectiveTransform(const cv::Mat& image);

    cv::Mat harrisCorners(const cv::Mat& image);

    cv::Mat shiTomasiCorners(const cv::Mat& image);

    cv::Mat fastKeypoints(const cv::Mat& image);

    cv::Mat orbKeypoints(const cv::Mat& image);

    void saveImage(const std::string& path, const cv::Mat& image);
}