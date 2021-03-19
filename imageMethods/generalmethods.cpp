#include "generalmethods.h"

GeneralMethods::GeneralMethods()
{

}

cv::Mat GeneralMethods::cart2polar(cv::Mat img, cv::Point center, int maxDegrees)
{
    /*Must treat each type of matrices*/
    /*
        CV_8U -> 0
        CV_8S-> 1
        CV_16U-> 2
        CV_16S-> 3
        CV_32S-> 4
        CV_32F-> 5
        CV_64F-> 6
    */
        int type = img.type();
        cv::Mat aux;
        ///Treating matrices types
        switch (type) {

        case 0:
            aux = cv::Mat::zeros(img.rows, img.cols, CV_8U);
        case 1:
            aux = cv::Mat::zeros(img.rows, img.cols, CV_8S);
        case 2:
            aux = cv::Mat::zeros(img.rows, img.cols, CV_16U);
        case 3:
            aux = cv::Mat::zeros(img.rows, img.cols, CV_16S);
        case 4:
            aux = cv::Mat::zeros(img.rows, img.cols, CV_32S);
        case 5:
            aux = cv::Mat::zeros(img.rows, img.cols, CV_32F);
        case 6:
            aux = cv::Mat::zeros(img.rows, img.cols, CV_64F);
    }

        // Sets the conversion factor (ratio) from cartesian to polar
        this->cRatio = 4;
        cv::Mat polar, rotated;
        this->cCenter = center;

        //Save the parameter to the inverse transform
        this->cSize = cv::Size(cvRound(this->cRatio*maxDegrees/CV_PI),0);
        this->cSize_i = img.size();
        this->cRadius = cvRound(img.size().height/2);

        // Changes the image 'img' to polar coordinates
        cv::warpPolar(img, polar, this->cSize, this->cCenter, this->cRadius, cv::INTER_LINEAR+cv::WARP_FILL_OUTLIERS);

        //  Resize to keep the aspect of the old images
        cv::resize(polar, polar, cv::Size(), 2, 0.25, cv::INTER_LINEAR);

        // Rotates the image so that the rings are placed in the horizontal direction
        cv::rotate(polar, rotated, cv::ROTATE_90_CLOCKWISE);

        return(rotated);
}

cv::Mat GeneralMethods::polar2cart(cv::Mat polar)
{
       cv::Mat unrotated, cartesian;

       // Undo rotation, lines in the vertical
       cv::rotate(polar, unrotated, cv::ROTATE_90_COUNTERCLOCKWISE);

       //Polar to cart transform
       cv::warpPolar(polar, cartesian, this->cSize_i, this->cCenter, this->cRadius, cv::INTER_LINEAR+cv::WARP_FILL_OUTLIERS+cv::WARP_INVERSE_MAP);

       return(cartesian);
}


cv::Point GeneralMethods::minMax(cv::Mat img)
{

	cv::Mat maskAux = dioptriasScaled>0;
    double minc[1], maxc[1];

    cv::minMaxLoc(img, minc, maxc,NULL,NULL,maskAux);
    qDebug()<<minc[0] << "----------";

    cv::Point result = (minc[0], maxc[0]);

    return(result)
}