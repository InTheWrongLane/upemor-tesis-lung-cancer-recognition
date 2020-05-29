#include "watershedsegmenter.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>

WatershedSegmenter::WatershedSegmenter()
{

}

WatershedSegmenter::WatershedSegmenter(cv::Mat _image)
{
    cv::ocl::setUseOpenCL(true);
    cv::Mat binary;
    cv::Mat image;
    _image.copyTo(image);
    cv::cvtColor(image, binary, CV_BGR2GRAY);
    cv::threshold(binary, binary, 100, 255, cv::THRESH_BINARY);

    cv::Mat fg;
    cv::erode(binary,fg,cv::Mat(),cv::Point(-1,-1),2);

    cv::Mat bg;
    cv::dilate(binary,bg,cv::Mat(),cv::Point(-1,-1),3);
    cv::threshold(bg,bg,1, 128,cv::THRESH_BINARY_INV);

    cv::Mat markers(binary.size(),CV_8U,cv::Scalar(0));
    cv::add(fg,bg,markers);

    setMarkers(markers);
}

void WatershedSegmenter::setMarkers(cv::Mat &markerImage)
{
    cv::ocl::setUseOpenCL(true);
    markerImage.convertTo(markers, CV_32S);
}

cv::Mat WatershedSegmenter::process(cv::Mat image)
{
    cv::ocl::setUseOpenCL(true);
    cv::watershed(image, markers);
    markers.convertTo(markers,CV_8U);
    return markers;
}

void WatershedSegmenter::run()
{

}
