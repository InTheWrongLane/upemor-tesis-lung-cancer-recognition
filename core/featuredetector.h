#ifndef FEATUREDETECTOR_H
#define FEATUREDETECTOR_H

#include <opencv2/opencv.hpp>
#include <QList>

class FeatureDetector
{
private:
    cv::Mat image;
    std::vector<cv::KeyPoint> keypoints;
public:
    FeatureDetector(cv::Mat _image);
    cv::Mat drawKeypoints();
    std::vector<cv::KeyPoint> getKeypoints();
    void setKeypoints(std::vector<cv::KeyPoint> value);
};

#endif // FEATUREDETECTOR_H
