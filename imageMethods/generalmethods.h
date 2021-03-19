#ifndef GENERALMETHODS_H
#define GENERALMETHODS_H


class GeneralMethods
{
public:
    GeneralMethods();
    cv::Mat cart2polar(cv::Mat img, cv::Point center, int maxDegrees);
    cv::Mat polar2cart(cv::Mat polar);
    cv::Point minMax(cv::Mat img);
};

#endif // GENERALMETHODS_H
