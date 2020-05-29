#ifndef WATERSHEDSEGMENTER_H
#define WATERSHEDSEGMENTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <QtCore>

class WatershedSegmenter : public QThread
{
private:
    cv::Mat imageToSegment;
    cv::Mat markers;
public:
    WatershedSegmenter();
    WatershedSegmenter(cv::Mat _image);
    void setMarkers(cv::Mat& markerImage);
    cv::Mat process(cv::Mat _image);
    void run();

};

#endif // WATERSHEDSEGMENTER_H
