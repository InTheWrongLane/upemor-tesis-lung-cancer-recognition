#include "lung.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <QtCore>

cv::Mat Lung::getOriginalLung()
{
    return originalLung;
}

void Lung::setOriginalLung(cv::Mat value)
{
    originalLung = value;
}

cv::Mat Lung::getBinaryLung()
{
    return binaryLung;
}

void Lung::setBinaryLung(cv::Mat value)
{
    binaryLung = value;
}

cv::Mat Lung::getSegmentedLung()
{
    return segmentedLung;
}

void Lung::setSegmentedLung(cv::Mat value)
{
    segmentedLung = value;
}

cv::Mat Lung::getFeaturesLung()
{
    return featuresLung;
}

void Lung::setFeaturesLung(cv::Mat value)
{
    featuresLung = value;
}
Lung::Lung()
{

}

Lung::Lung(cv::Mat originalLung)
{
    this->originalLung = originalLung;
}

void Lung::run()
{
    this->toBinaryLung();
}

void Lung::toBinaryLung()
{

    binaryLung = originalLung.clone();
    for( int x = 0; x < binaryLung.rows; x++ ) {
        for( int y = 0; y < binaryLung.cols; y++ ) {
            if ( binaryLung.at<cv::Vec3b>(x, y) == cv::Vec3b(255,255,255) ) {
                binaryLung.at<cv::Vec3b>(x, y)[0] = 0;
                binaryLung.at<cv::Vec3b>(x, y)[1] = 0;
                binaryLung.at<cv::Vec3b>(x, y)[2] = 0;
            }
        }
    }
    cv::ocl::setUseOpenCL(true);
    cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                      1,  1, 1,
                      1, -8, 1,
                      1,  1, 1);
    cv::Mat imgLaplacian;
    cv::Mat sharp;
    binaryLung.copyTo(sharp);
    cv::filter2D(sharp, imgLaplacian, CV_32F, kernel);
    binaryLung.convertTo(sharp, CV_32F);
    cv::Mat imgResult;
    cv::subtract(sharp,imgLaplacian,imgResult);

    imgResult.convertTo(imgResult, CV_8UC3);
    imgLaplacian.convertTo(imgLaplacian, CV_8UC3);

    //binaryLung = imgResult.getMat(cv::ACCESS_READ);
    binaryLung = imgResult;
    cv::Mat bw;
    cv::cvtColor(binaryLung, bw, CV_BGR2GRAY);
    cv::threshold(bw, bw, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    setBinaryLung(bw);
}
