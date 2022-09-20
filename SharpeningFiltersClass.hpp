//
//  SharpeningFiltersClass.hpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 3/15/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#ifndef SharpeningFiltersClass_hpp
#define SharpeningFiltersClass_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


bool addWeightedSharpening(Mat& src, Mat&dst);
bool kernelSharpening(Mat& src, Mat&dst);
bool sharpeningMethodThree(Mat &src,Mat& dst);
bool meanSharpening(Mat &src,Mat& dst,int kernel);
bool MedianSharpening(Mat &src,Mat& smoothed,Mat& dst,int kernel);

#endif /* SharpeningFiltersClass_hpp */
