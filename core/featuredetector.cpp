#include "featuredetector.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/core/ocl.hpp>

std::vector<cv::KeyPoint> FeatureDetector::getKeypoints()
{
    return keypoints;
}

void FeatureDetector::setKeypoints(std::vector<cv::KeyPoint> value)
{
    keypoints = value;
}
FeatureDetector::FeatureDetector(cv::Mat _image)
{
    cv::ocl::setUseOpenCL(true);
    _image.copyTo(image);
    int nfeatures=10000;
    float scaleFactor=1.2f;
    int nlevels=8;
    int edgeThreshold=31;
    int firstLevel=0;
    int WTA_K=2;
    int scoreType=cv::ORB::HARRIS_SCORE;
    int patchSize=31;
    int fastThreshold=20;

    cv::Ptr<cv::ORB> detector = cv::ORB::create(
                nfeatures,
                scaleFactor,
                nlevels,
                edgeThreshold,
                firstLevel,
                WTA_K,
                scoreType,
                patchSize,
                fastThreshold
                );
    detector->detect(image, keypoints);
    std::cout << "Found " << keypoints.size() << " Keypoints " << std::endl;
}

cv::Mat FeatureDetector::drawKeypoints()
{
    cv::ocl::setUseOpenCL(true);
    cv::Mat imgeKeypoints;
    cv::drawKeypoints( image, keypoints, imgeKeypoints, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );
    return imgeKeypoints;
}
