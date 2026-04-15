#include "image_processing/image_pipeline.hpp"
#include <iostream>

namespace imgproc {
    cv::Mat loadImage(const std::string& path) {
        cv::Mat img = cv::imread(path);
        if(img.empty()) {
            std::cerr << "[ERROR] Could not load image: " << path << std::endl;
            exit(1);
        }
        return img;
    }

    cv::Mat toGrayscale(const cv::Mat& image) {
        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        return gray;
    }

    cv::Mat normalizeImage(const cv::Mat& image) {
        cv::Mat norm;
        cv::normalize(image, norm, 0, 255, cv::NORM_MINMAX);
        return norm;
    }

    cv::Mat addGaussianNoise(const cv::Mat& image, double mean, double stddev) {
        cv::Mat noise(image.size(), image.type());
        cv::randn(noise, mean, stddev);
        
        cv::Mat noisy;
        cv::add(image, noise, noisy);
        return noisy;
    }

    cv::Mat gaussianBlur(const cv::Mat& image, int kernelSize) {
        cv::Mat blurred;
        cv::GaussianBlur(image, blurred, cv::Size(kernelSize, kernelSize), 0);
        return blurred;
    }

    cv::Mat medianBlur(const cv::Mat& image, int kernelSize) {
        cv::Mat blurred;
        cv::medianBlur(image, blurred, kernelSize);
        return blurred;
    }

    cv::Mat sobelX(const cv::Mat& image) {
        cv::Mat gradX;
        cv::Sobel(image, gradX, CV_64F, 1, 0, 3);
        return gradX;
    }

    cv::Mat sobelY(const cv::Mat& image) {
        cv::Mat gradY;
        cv::Sobel(image, gradY, CV_64F, 0, 1, 3);
        return gradY;
    }

    cv::Mat sobelMagnitude(const cv::Mat& gradX, const cv::Mat& gradY) {
        cv::Mat mag;
        cv::magnitude(gradX, gradY, mag);
        cv::normalize(mag, mag, 0, 255, cv::NORM_MINMAX);
        mag.convertTo(mag,CV_8U);
        return mag;
    }

    cv::Mat cannyEdge(const cv::Mat& image, int t1, int t2) {
        cv::Mat edges;
        cv::Canny(image, edges, t1, t2);
        return edges;
    }

    cv::Mat rotateImage(const cv::Mat& image, double angle) {
        cv::Point2f center(image.cols/2.0, image.rows/2.00);
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
        
        cv::Mat result;
        cv::warpAffine(image, result, rot, image.size());
        return result;
    }

    cv::Mat affineTransform(const cv::Mat& image) {
        std::vector<cv::Point2f> src = {
            {0, 0}, {image.cols - 1, 0}, {0, image.rows - 1}
        };

        std::vector<cv::Point2f> dst = {
            {0, 0}, {image.cols *  0.8f, image.rows * 0.2f}, {image.cols * 0.2f, image.rows * 0.9f}
        };

        cv::Mat M = cv::getAffineTransform(src,dst);

        cv::Mat result;
        cv::warpAffine(image, result, M, image.size());
        return result;
    }

    cv::Mat perspectiveTransform(const cv::Mat& image) {
        std::vector<cv::Point2f> src = {
            {0,0},
            {image.cols - 1, 0},
            {image.cols - 1, image.rows - 1},
            {0, image.rows - 1}
        };

        std::vector<cv::Point2f> dst = {
            {0, 0},
            {image.cols * 0.9f, image.rows * 0.1f},
            {image.cols * 0.8f, image.rows * 0.9f},
            {image.cols * 0.2f, image.rows * 0.8f}
        };

        cv::Mat M = cv::getPerspectiveTransform(src, dst);

        cv::Mat result;
        cv::warpPerspective(image, result, M, image.size());
        return result;
    }

    cv::Mat harrisCorners(const cv::Mat& image) {
        cv::Mat gray, dst, dst_norm;

        gray = image.clone();

        cv::cornerHarris(gray, dst, 2, 3, 0.04);
        
        cv::normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX);

        cv::Mat result;
        cv::cvtColor(gray, result, cv::COLOR_GRAY2BGR);

        for (int i = 0; i < dst_norm.rows; i++) {
            for (int j = 0; j<dst_norm.cols; j++) {
                if((int)dst_norm.at<float>(i,j) > 120){
                    cv::circle(result, cv::Point(j,i), 3, cv::Scalar(0,0,255), -1);
                }
            }
        }
        return result;
    }

    cv::Mat shiTomasiCorners(const cv::Mat& image) {
        std::vector<cv::Point2f> corners;

        cv::goodFeaturesToTrack(
            image,
            corners,
            200,    // max corners
            0.01,   // quality
            10      // min distance
        );
        
        cv::Mat result;
        cv::cvtColor(image, result, cv::COLOR_GRAY2BGR);

        for (auto& pt: corners) {
            cv::circle(result, pt, 3, cv::Scalar(0,255,0), -1);
        }
        return result;
    }

    cv::Mat fastKeypoints(const cv::Mat& image) {
        std::vector<cv::KeyPoint> keypoints;

        cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create(25,true);

        detector->detect(image, keypoints);

        cv::Mat result;
        cv::cvtColor(image, result, cv::COLOR_GRAY2BGR);

        cv::drawKeypoints(image, keypoints, result, cv::Scalar(255, 0 ,0));

        return result;
    }

    cv::Mat orbKeypoints(const cv::Mat& image) {
        std::vector<cv::KeyPoint> keypoints;
        cv::Mat descriptors;

        auto orb = cv::ORB::create(500);

        orb->detectAndCompute(image, cv::noArray(), keypoints, descriptors);

        cv::Mat result;
        cv::cvtColor(image, result, cv::COLOR_GRAY2BGR);

        cv::drawKeypoints(image, keypoints, result, cv::Scalar(0, 0, 255));

        std::cout << "Descriptors size: "
                << descriptors.rows << " x "
                << descriptors.cols << std::endl;

        return result;
    }

    cv::Mat orbMatching(const cv::Mat& img1, const cv::Mat& img2) {
        std::vector<cv::KeyPoint> kp1, kp2;
        cv::Mat desc1, desc2;

        auto orb = cv::ORB::create(500);

        // Detect and Compute
        orb->detectAndCompute(img1, cv::noArray(), kp1, desc1);
        orb->detectAndCompute(img2, cv::noArray(), kp2, desc2);

        if (desc1.empty() || desc2.empty()) {
            std::cerr << "[ERROR] No descriptors found!" << std::endl;
            return cv::Mat();
        }

        //Matcher (Hamming for Binary Distance)
        cv::BFMatcher matcher(cv::NORM_HAMMING);

        std::vector<cv::DMatch> matches;
        matcher.match(desc1, desc2, matches);

        // Sort matches (best First)
        std::sort(matches.begin(), matches.end(),
            [](cv::DMatch& a, cv::DMatch& b) {
                return a.distance < b.distance;
        });

        // Keep top matches
        int num = std::min(50, (int)matches.size());
        std::vector<cv::DMatch> good_matches(matches.begin(), matches.begin()+num);

        cv::Mat result;
        cv::drawMatches(img1, kp1, img2, kp2, good_matches, result);

        return result;
    }

    cv::Mat orbRotationTest(const cv::Mat& image, double angle) {
        auto rotated = imgproc::rotateImage(image, angle);

        auto gray1 = image.clone();
        auto gray2 = rotated.clone();

        return imgproc::orbMatching(gray1, gray2);
    }

    cv::Mat computeHomographyAndWarp(const cv::Mat& img1, const cv::Mat& img2) {
        std::vector<cv::KeyPoint> kp1, kp2;
        cv::Mat desc1, desc2;

        auto orb = cv::ORB::create(1500);

        // Detect and compute
        orb->detectAndCompute(img1, cv::noArray(), kp1, desc1);
        orb->detectAndCompute(img2, cv::noArray(), kp2, desc2);

        if (desc1.empty() || desc2.empty()) {
            std::cerr << "[ERROR] No descriptors found!" << std::endl;
            return cv::Mat();
        }

        // -------------------------------
        // KNN Matching + Ratio Test
        // -------------------------------
        cv::BFMatcher matcher(cv::NORM_HAMMING);

        std::vector<std::vector<cv::DMatch>> knn_matches;
        matcher.knnMatch(desc1, desc2, knn_matches, 2);

        std::vector<cv::DMatch> good_matches;

        for (const auto& m : knn_matches) {
            if (m.size() < 2) continue;

            if (m[0].distance < 0.75 * m[1].distance) {
                good_matches.push_back(m[0]);
            }
        }

        std::cout << "Good matches: " << good_matches.size() << std::endl;

        if (good_matches.size() < 10) {
            std::cerr << "[ERROR] Not enough good matches!" << std::endl;
            return cv::Mat();
        }

        // -------------------------------
        // Extract matched points
        // -------------------------------
        std::vector<cv::Point2f> pts1, pts2;

        for (const auto& m : good_matches) {
            pts1.push_back(kp1[m.queryIdx].pt);
            pts2.push_back(kp2[m.trainIdx].pt);
        }

        // -------------------------------
        // Compute Homography (RANSAC)
        // -------------------------------
        cv::Mat inlier_mask;
        cv::Mat H = cv::findHomography(pts1, pts2, cv::RANSAC, 3.0, inlier_mask);

        if (H.empty()) {
            std::cerr << "[ERROR] Homography computation failed!" << std::endl;
            return cv::Mat();
        }

        // -------------------------------
        // Warp Image
        // -------------------------------
        cv::Mat warped;
        cv::warpPerspective(img1, warped, H, img2.size());

        // -------------------------------
        // (Optional) Draw Inlier Matches
        // -------------------------------
        std::vector<cv::DMatch> inliers;

        for (size_t i = 0; i < good_matches.size(); i++) {
            if (inlier_mask.at<uchar>(i)) {
                inliers.push_back(good_matches[i]);
            }
        }

        cv::Mat match_vis;
        cv::drawMatches(img1, kp1, img2, kp2, inliers, match_vis);

        // Save debug image (VERY useful)
        cv::imwrite("../../outputs/exp07/inlier_matches.jpg", match_vis);

        std::cout << "Inliers: " << inliers.size() << std::endl;

        return warped;
    }
    
    void saveImage(const std::string& path, const cv::Mat& image) {
        cv::imwrite(path, image);
    }
}