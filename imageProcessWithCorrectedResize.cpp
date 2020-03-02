#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <stdio.h>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
    Mat image = imread(argv[1], 1);
    int beforeHeight = image.rows;
    int beforeWidth = image.cols;
    resize(image, image, Size(200, 200));
    int height = image.rows;
    int width = image.cols;
    // if (!image.data)
    // {
    //     printf(“No image data \n”);
    //     return -1;
    // }
    namedWindow("before", WINDOW_AUTOSIZE);
    imshow("before", image);

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
            // std::cout << str<< std::endl;
            cv::namedWindow(str, WINDOW_AUTOSIZE);
                imshow(str, channel);
            results[i]= channel;
        //imshow(“sep” + i, results[i]);
    }
    Mat outval = Mat();
    // Mat outval;
    cv::merge(results, 3, outval);
    Mat test = outval;
    resize(outval, outval, Size(beforeWidth, beforeHeight));

    // auto end = chrono::high_resolution_clock::now();
    // auto dur = end - begin;
    // auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    // cout << ms << endl;
    namedWindow("after", WINDOW_AUTOSIZE);
    imshow("after", outval);

    waitKey(0);
    return 0;
}
