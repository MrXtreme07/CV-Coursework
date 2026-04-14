#include <iostream>
#include "image_processing/image_pipeline.hpp"

void run_exp01() {
    std::string input_path = "../../data/raw/hat_woman.png";

    std::cout << "[INFO] Loading image..." << std::endl;
    auto img = imgproc::loadImage(input_path);
    
    auto gray = imgproc::toGrayscale(img);
    auto norm = imgproc::normalizeImage(gray);
    auto noisy = imgproc::addGaussianNoise(norm, 0, 25);

    auto gaussian = imgproc::gaussianBlur(noisy, 5);
    auto median = imgproc::medianBlur(noisy,5);

    imgproc::saveImage("../../outputs/exp01/gray.jpg", gray);
    imgproc::saveImage("../../outputs/exp01/noisy.jpg", noisy);
    imgproc::saveImage("../../outputs/exp01/gaussian.jpg", gaussian);
    imgproc::saveImage("../../outputs/exp01/median.jpg", median);

    std::cout << "[INFO] Done. Check Outputs." << std::endl;
}

void run_exp02() {
    std::string input_path = "../../data/raw/hat_woman.png";

    auto img = imgproc::loadImage(input_path);
    auto gray = imgproc::toGrayscale(img);

    auto gradX = imgproc::sobelX(gray);
    auto gradY = imgproc::sobelY(gray);
    auto mag = imgproc::sobelMagnitude(gradX, gradY);

    auto edges = imgproc::cannyEdge(gray, 50, 150);

    imgproc::saveImage("../../outputs/exp02/gradX.jpg", gradX);
    imgproc::saveImage("../../outputs/exp02/gradY.jpg", gradY);
    imgproc::saveImage("../../outputs/exp02/magnitude.jpg", mag);
    imgproc::saveImage("../../outputs/exp02/canny.jpg", edges);
}

void run_exp03() {
    std::string input_path = "../../data/raw/hat_woman.png";

    auto img = imgproc::loadImage(input_path);

    auto rotated = imgproc::rotateImage(img, 30);
    auto affine = imgproc::affineTransform(img);
    auto perspective = imgproc::perspectiveTransform(img);

    imgproc::saveImage("../../outputs/exp03/rotated.jpg", rotated);
    imgproc::saveImage("../../outputs/exp03/affine.jpg", affine);
    imgproc::saveImage("../../outputs/exp03/perspective.jpg", perspective);
}

void run_exp04() {
    std::string input_path = "../../data/raw/hat_woman.png";

    auto img = imgproc::loadImage(input_path);
    auto gray = imgproc::toGrayscale(img);

    auto harris = imgproc::harrisCorners(gray);
    auto shi = imgproc::shiTomasiCorners(gray);

    imgproc::saveImage("../../outputs/exp04/harris.jpg", harris);
    imgproc::saveImage("../../outputs/exp04/shi_tomasi.jpg", shi);
}

void run_exp05() {
    std::string input_path = "../../data/raw/hat_woman.png";

    auto img = imgproc::loadImage(input_path);
    auto gray = imgproc::toGrayscale(img);

    auto fast = imgproc::fastKeypoints(gray);
    imgproc::saveImage("../../outputs/exp05/fast.jpg", fast);

    auto orb = imgproc::orbKeypoints(gray);
    imgproc::saveImage("../../outputs/exp05/orb.jpg", orb);
}

void run_exp06() {
    auto img1 = imgproc::loadImage("../../data/raw/f1_1.jpeg");
    auto img2 = imgproc::loadImage("../../data/raw/f1_2.jpeg");

    auto gray1 = imgproc::toGrayscale(img1);
    auto gray2 = imgproc::toGrayscale(img2);

    auto matches = imgproc::orbMatching(gray1, gray2);
    imgproc::saveImage("../../outputs/exp06/matches.jpeg", matches);

    auto rot_matches = imgproc::orbRotationTest(gray1, 60);
    imgproc::saveImage("../../outputs/exp06/rot_matches.jpeg", rot_matches);
}

int main() {
    run_exp06();
    return 0;
}