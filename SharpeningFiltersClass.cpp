//
//  SharpeningFiltersClass.cpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#include "SharpeningFiltersClass.hpp"
#include "OrderStatisticFiltersClass.hpp"
#include "MeanFilteringClass.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;



bool addWeightedSharpening(Mat& src, Mat&dst)
{
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    
    GaussianBlur(src, dst, Size(3,3), 0);
    addWeighted(src, 1.5, dst, -0.5, 0, dst);
    
    return true;
}

bool kernelSharpening(Mat& src, Mat&dst)
{
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    
    Mat sharpening_kernel = (Mat_<double>(3, 3) << -1, -1, -1,
                             -1, 9, -1,
                             -1, -1, -1);
    filter2D(src, dst, -1, sharpening_kernel);
    return true;
}


bool sharpeningMethodThree(Mat &src,Mat& dst)
{
    
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    
    int imgRows,imgCols;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    //For all rows except first and last
    for(int i=1;i<src.rows-1;i++)
    {
        const uchar *previous = src.ptr<const uchar>(i-1);
        const uchar *next = src.ptr<const uchar>(i+1);
        const uchar *current = src.ptr<const uchar>(i);
        
        uchar *output = dst.ptr<uchar>(i);
        
        //For all columns except first and last
        for(int j=3;j<(src.cols-1)*3;j++)
        {
            output[j] = cv::saturate_cast<uchar>(5*current[j]-current[j-1]-current[j+1]-previous[j]-next[j]);
        }
        
    }
    
    dst.row(0).setTo(cv::Scalar(0));
    dst.row(dst.rows-1).setTo(cv::Scalar(0));
    dst.col(0).setTo(cv::Scalar(0));
    dst.col(dst.cols-1).setTo(cv::Scalar(0));
    
    return true;
}


bool meanSharpening(Mat &src,Mat& dst,int kernel){
    
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    
    Mat smoothed;
    arithMeanFilter(src, smoothed, kernel);
    Mat minus;
    subtract(src, smoothed, minus);
    addWeighted(src, 1.0, minus, 1.0, 0, dst);
    
    return true;
}

bool MedianSharpening(Mat &src,Mat& smoothed,Mat& dst,int kernel)
{
    
    if(src.empty())
    {
        cout<<"Input image is empty!";
        return false;
    }
    
    Mat minus;
    subtract(src, smoothed, minus);
    addWeighted(src, 1.0, minus, 2.0, 0, dst);
    
    
    return true;
}



