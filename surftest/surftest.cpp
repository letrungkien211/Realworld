/**
 * @file surftest.cpp
 * @brief simplest SURF extraction code
 *
 * @author Tatsuya Harada
 * @date Oct. 30, 2010
 */
#include <iostream>
#include <string>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    // load image
    const char *fname = argc > 1 ? argv[1] : "box.png";
    Mat cimg = imread(fname,1);
    if(cimg.empty())
	return -1;

    // convert color to gray 
    Mat gimg;
    cvtColor(cimg, gimg, CV_BGR2GRAY);

    // extract SURF
    SURF surf_i = SURF(500,4,2,false); // true: 128dim, false: 64dim  vector<KeyPoint> kp_vec;
    vector<KeyPoint> keyv; //< keypoints
    vector<float> descv; //< descriptors
    surf_i(gimg, Mat(), keyv, descv); //< feature extraction

    // draw keypoints
    vector<KeyPoint>::iterator it;
    for(it=keyv.begin(); it!=keyv.end(); ++it)
	circle(cimg, Point(it->pt.x, it->pt.y), (int)(it->size/3), Scalar(255,0,255));

    // display image
    namedWindow("SURF",CV_WINDOW_AUTOSIZE);
    imshow("SURF", cimg);
    waitKey(0);

    return 0;
}
