#ifndef LUNG_H
#define LUNG_H

#include <opencv2/opencv.hpp>
#include <QtCore>

class Lung : public QThread
{
private:
    cv::Mat originalLung;
    cv::Mat binaryLung;
    cv::Mat segmentedLung;
    cv::Mat featuresLung;

public:
    Lung();
    Lung(cv::Mat originalLung);
    void run();
    cv::Mat getOriginalLung();
    void setOriginalLung(cv::Mat value);
    cv::Mat getBinaryLung();
    void setBinaryLung(cv::Mat value);
    cv::Mat getSegmentedLung();
    void setSegmentedLung(cv::Mat value);
    cv::Mat getFeaturesLung();
    void setFeaturesLung(cv::Mat value);
    void toBinaryLung();
};

#endif // LUNG_H
