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

    cv::Mat orbMatching(const cv::Mat& img1, const cv::Mat& img2);

    cv::Mat orbRotationTest(const cv::Mat& image, double angle);
    
    cv::Mat computeHomographyAndWarp(const cv::Mat& img1, const cv::Mat& img2);

    cv::Mat stitchImages(const cv::Mat& img1, const cv::Mat& img2);

    cv::Mat siftMatching(const cv::Mat& img1, const cv::Mat& img2);

    cv::Mat extractSIFTDescriptors(const cv::Mat& image);

    cv::Mat collectAllDescriptors(const std::vector<cv::Mat>& imaages);

    cv::Mat buildVocabulary(const cv::Mat& all_desc, int K);

    cv::Mat computeHistogram(const cv::Mat& descriptors, const cv::Mat& vocab);

    double compareHistograms(const cv::Mat& h1, const cv::Mat& h2);

    std::vector<std::pair<cv::Mat, std::string>> loadDataset(const std::string& root_path);

    cv::Mat drawLabel(const cv::Mat& img, const std::string& text);

    void saveImage(const std::string& path, const cv::Mat& image);
}