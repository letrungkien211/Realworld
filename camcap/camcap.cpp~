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
  do {
    capture >> frame;
    imshow(winname, frame);
  } while(waitKey(10) != 'q');

  return 0;
}
