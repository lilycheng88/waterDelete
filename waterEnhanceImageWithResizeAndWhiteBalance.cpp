#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <stdio.h>
using namespace std;
using namespace cv;

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
    int beforeHeight = image.rows; //STORING VALUES FOR LATER RESIZE
    int beforeWidth = image.cols; //STORING VALUES FOR LATER RESIZE
    
    // if (!image.data)
    // {
    //     printf(“No image data \n”);
    //     return -1;
    // }
    namedWindow("before", WINDOW_AUTOSIZE);
    imshow("before", image);

    resize(image, image, Size(200, 200)); //RESIZE TO A SQUARE
    int height = image.rows;
    int width = image.cols;

    Mat results[3];
    int ro = image.rows;
    int co = image.cols;
    cout << ro << " " << co;
    int chan = image.channels();
    double thirdPercent = 0.16667;
    vector<Mat> rgbChannels(3);
    // if (chan == 3)
        cv::split(image, rgbChannels);
    // else
    //     rgbChannels.push_back(image);
    cout << "this one" << chan << endl;
    for (int i = 0; i < chan; i++)
    {
        Mat flat;
        rgbChannels[i].reshape(1, 1).copyTo(flat);
        cv::sort(flat, flat, SORT_ASCENDING);
        std::cout << (int)floor(flat.cols * thirdPercent)<< std::endl;
        std::cout << (int)ceil(flat.cols * (1.0 - thirdPercent))<< std::endl;
        double lowVal = flat.at<Vec3b>(0, (int)floor(flat.cols * thirdPercent))[i];
        std::cout << lowVal<< std::endl;
        double topVal = 255;///flat.at<Vec3b>(0, (int)ceil(flat.cols * (1.0 - thirdPercent)))[i];
        std::cout << topVal<< std::endl;
        Mat channel = rgbChannels[i];
        for (int m = 0; m < ro; m++)
        {
            for (int n = 0; n < co; n++)
            {
                 if (channel.at<Vec3b>(m, n)[0] < lowVal)
                      channel.at<cv::Vec3b>(m, n)[0]= lowVal;
                 if (channel.at<Vec3b>(m, n)[0] > topVal)
                     channel.at<cv::Vec3b>(m, n)[0] = topVal;
            }
        }
            cv::normalize(channel, channel, 0.0, 255.0 / 2, NORM_MINMAX, -1);
            stringstream ss;
            ss << i;
            string str = ss.str();
            std::cout << str<< std::endl;
            // cv::namedWindow(str, WINDOW_AUTOSIZE);
            //     imshow(str, channel);
            results[i]= channel;
        //imshow(“sep” + i, results[i]);
    }
    Mat outval = Mat();
    // Mat outval;
    cv::merge(results, 3, outval);
    Mat test = outval;
    resize(outval, outval, Size(beforeWidth, beforeHeight)); //RESIZE TO ORIGINAL

    namedWindow("without white balance", WINDOW_AUTOSIZE);
    imshow("without white balance", outval);
    
    balance_white(outval); //ADDS WHITE BALANCE

    // auto end = chrono::high_resolution_clock::now();
    // auto dur = end - begin;
    // auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    // cout << ms << endl;
    
    namedWindow("with white balance", WINDOW_AUTOSIZE);
    imshow("with white balance", outval);

    waitKey(0);
    return 0;
}
