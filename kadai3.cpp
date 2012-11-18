/**
 * @file camcap.cpp
 * @brief capture frames from usb cam
 *
 * @author Tatsuya Harada
 * @date Oct. 30, 2010
 */
#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

void DrawKeyPoints(Mat &image,vector<KeyPoint> &keyv){
    // draw keypoints
    vector<KeyPoint>::iterator it;
    for(it=keyv.begin(); it!=keyv.end(); ++it)
	circle(image, Point(it->pt.x, it->pt.y), (int)(it->size/3), Scalar(255,0,255));
}

void ExtractSurf(Mat &gimg, vector<KeyPoint> &keyv, vector<float> descv){
    SURF surf_i = SURF(500,4,2,false);
    surf_i(gimg, Mat(), keyv, descv);
}

void DisplayImage(Mat &image, char *name){
    namedWindow("SURF",CV_WINDOW_AUTOSIZE);
    imshow("SURF", image);
}


int main(int argc, char* argv[])
{
    VideoCapture capture(0);
    if(!capture.isOpened()) {
	cerr << "Failed to open cam." << endl;
	return -1;
    }

    char winname[] = "cam capture";
    namedWindow(winname, CV_WINDOW_AUTOSIZE);

    Mat frame;
    Mat grayFrame;
    vector<float> descv; //< descriptors

    do {
	vector<KeyPoint> keyv; //< keypoints
	capture >> frame;
	cvtColor(frame, grayFrame, CV_BGR2GRAY);
	ExtractSurf(grayFrame, keyv, descv);
	DrawKeyPoints(frame, keyv);
	DisplayImage(frame, "Kadai3");
    } while(waitKey(10) != 'q');

    return 0;
}

