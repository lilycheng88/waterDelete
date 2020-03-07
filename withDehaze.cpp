#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <stdio.h>

// #include "stdafx.h"

// #include <cv.h>
// #include <highgui.h>
// #include <iostream>

using namespace std;
using namespace cv;

//median filtered dark channel
Mat getMedianDarkChannel(Mat src, int patch)
{
        Mat rgbmin = Mat::zeros(src.rows, src.cols, CV_8UC1);
        Mat MDCP;
        Vec3b intensity;

	for(int m=0; m<src.rows; m++)
	{
		for(int n=0; n<src.cols; n++)
		{
			intensity = src.at<Vec3b>(m,n);
			rgbmin.at<uchar>(m,n) = min(min(intensity.val[0], intensity.val[1]), intensity.val[2]);
		}
	}
	medianBlur(rgbmin, MDCP, patch);
	return MDCP;

}

//estimate airlight by the brightest pixel in dark channel (proposed by He et al.)
int estimateA(Mat DC)
{
	double minDC, maxDC;
	minMaxLoc(DC, &minDC, &maxDC);
	cout<<"estimated airlight is:"<<maxDC<<endl;
	return maxDC;
}

Mat estimateTransmission(Mat DCP, int ac)
{
	double w = 0.75;
	Mat transmission = Mat::zeros(DCP.rows, DCP.cols, CV_8UC1);
	Scalar intensity;

	for (int m=0; m<DCP.rows; m++)
	{
		for (int n=0; n<DCP.cols; n++)
		{
			intensity = DCP.at<uchar>(m,n);
			transmission.at<uchar>(m,n) = (1 - w * intensity.val[0] / ac) * 255;
		}
	}
	return transmission;
}

//dehazing foggy image
Mat getDehazed(Mat source, Mat t, int al)
{
	double tmin = 0.1;
	double tmax;
	
	Scalar inttran;
	Vec3b intsrc;
	Mat dehazed = Mat::zeros(source.rows, source.cols, CV_8UC3);

	for(int i=0; i<source.rows; i++)
	{
		for(int j=0; j<source.cols; j++)
		{
			inttran = t.at<uchar>(i,j);
			intsrc = source.at<Vec3b>(i,j);
			tmax = (inttran.val[0]/255) < tmin ? tmin : (inttran.val[0]/255);
			for(int k=0; k<3; k++)
			{
				dehazed.at<Vec3b>(i,j)[k] = abs((intsrc.val[k] - al) / tmax + al) > 255 ? 255 : abs((intsrc.val[k] - al) / tmax + al);
			}
		}
	}
	return dehazed;
}

void balance_white(cv::Mat mat) { //WHITE BALANCE CODE
  double discard_ratio = 0.05;
  int hists[3][256];
  memset(hists, 0, 3*256*sizeof(int));

  for (int y = 0; y < mat.rows; ++y) {
    uchar* ptr = mat.ptr<uchar>(y);
    for (int x = 0; x < mat.cols; ++x) {
      for (int j = 0; j < 3; ++j) {
        hists[j][ptr[x * 3 + j]] += 1;
      }
    }
  }

  // cumulative hist
  int total = mat.cols*mat.rows;
  int vmin[3], vmax[3];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 255; ++j) {
      hists[i][j + 1] += hists[i][j];
    }
    vmin[i] = 0;
    vmax[i] = 255;
    while (hists[i][vmin[i]] < discard_ratio * total)
      vmin[i] += 1;
    while (hists[i][vmax[i]] > (1 - discard_ratio) * total)
      vmax[i] -= 1;
    if (vmax[i] < 255 - 1)
      vmax[i] += 1;
  }


  for (int y = 0; y < mat.rows; ++y) {
    uchar* ptr = mat.ptr<uchar>(y);
    for (int x = 0; x < mat.cols; ++x) {
      for (int j = 0; j < 3; ++j) {
        int val = ptr[x * 3 + j];
        if (val < vmin[j])
          val = vmin[j];
        if (val > vmax[j])
          val = vmax[j];
        ptr[x * 3 + j] = static_cast<uchar>((val - vmin[j]) * 255.0 / (vmax[j] - vmin[j]));
      }
    }
  }
}

int main(int argc, char **argv)
{
    Mat image = imread(argv[1], 1);
    
    namedWindow("before", WINDOW_AUTOSIZE);
    imshow("before", image);
    
    balance_white(image); //ADDS WHITE BALANCE

    namedWindow("after", WINDOW_AUTOSIZE);
    imsh./ow("after", image);
  

    //for image defogging

    Mat darkChannel;
    Mat T;
    Mat fogfree;
    Mat beforeafter = Mat::zeros(image.rows, 2 * image.cols, CV_8UC3);
    Rect roil (0, 0, image.cols, image.rows);
    Rect roir (image.cols, 0, image.cols, image.rows);
   
    int Airlight;

    namedWindow("before dehaze", WINDOW_AUTOSIZE);

    darkChannel = getMedianDarkChannel(image, 5);
    Airlight = estimateA(darkChannel);
    T = estimateTransmission(darkChannel, Airlight);
    fogfree = getDehazed(image, T, Airlight);

    image.copyTo(beforeafter(roil));
    fogfree.copyTo(beforeafter(roir));
    
    // imwrite("./dehazed.jpg", fogfree);

    imshow("before and after", beforeafter);
  
    waitKey(0);
    return 0;
}
