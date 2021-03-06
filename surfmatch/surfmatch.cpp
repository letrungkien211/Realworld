/**
 * @file surfmatch.cpp
 * @brief simplest SURF matching code
 *
 * @author Tatsuya Harada
 * @date Nov. 4, 2010
 */

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

const int SDIM = 64; //< dimension of SURF
const float THRES = 0.01; //< dimension of SURF

void calc_distmat(vector<float> &desc_v1, vector<float> &desc_v2,
			  Mat &distmat, Mat &idxmat)
{
  // convert vector to matrix
  // descmat1 and descmat2: (n_keypoints x dim) matrix
  Mat descmat1=Mat(desc_v1).reshape(0,distmat.rows);
  Mat descmat2=Mat(desc_v2).reshape(0,distmat.cols);

  // build distance matrix
  for(int i=0;i<descmat1.rows;i++){
    Mat tmpmat1=descmat1.row(i);
    for(int j=0;j<descmat2.rows;j++){
      Mat tmpmat2=(descmat2.row(j)-tmpmat1);
      distmat.at<float>(i,j)=(float)tmpmat2.dot(tmpmat2); //< measure distance
    }
  }
  sortIdx(distmat,idxmat,CV_SORT_EVERY_ROW+CV_SORT_ASCENDING);
}

int main(int argc, char** argv)
{
  // load images
  const char* fname1 = argc == 3 ? argv[1] : "graffiti1.jpg";
  const char* fname2 = argc == 3 ? argv[2] : "graffiti3.jpg";
  Mat cimg1 = imread(fname1,1);
  Mat cimg2 = imread(fname2,1);
  if(cimg1.empty() || cimg2.empty()){
    cerr << "error: loading files" << endl;
    return -1;
  }
  

  // convert color images to gray scale images
  Mat gimg1, gimg2;
  cvtColor(cimg1, gimg1, CV_BGR2GRAY);
  cvtColor(cimg2, gimg2, CV_BGR2GRAY);

  // prepare displaying image 
  Mat dispimg(Size(cimg1.cols+cimg2.cols, cimg1.rows+cimg2.rows), CV_8UC3);
  Mat roi1(dispimg, Rect(0, 0, cimg1.cols, cimg1.rows));
  cimg1.copyTo(roi1);
  Mat roi2(dispimg, Rect(cimg1.cols, cimg1.rows, cimg2.cols, cimg2.rows));
  cimg2.copyTo(roi2);



  // extract SURF
  SURF surf1 = SURF(1000,4,2,false); // true: 128dim, false: 64dim
  SURF surf2 = SURF(1000,4,2,false); // true: 128dim, false: 64dim
  vector<KeyPoint> key_v1, key_v2;
  vector<float> desc_v1, desc_v2;
  surf1(gimg1, Mat(), key_v1, desc_v1);
  surf2(gimg2, Mat(), key_v2, desc_v2);

  // build distance matrix
  Mat distmat=Mat::zeros(key_v1.size(), key_v2.size(), CV_32F); //< distance matrix
  Mat idxmat=Mat::zeros(key_v1.size(), key_v2.size(), CV_32S);; //< index matrix
  calc_distmat(desc_v1, desc_v2, distmat, idxmat); //< measure distance


  
  // draw lines between matched points
  for(int i=0;i<key_v1.size();i++) {
    int p=idxmat.at<int>(i,0);
    cout << " LA " << key_v1[700].pt.x<< endl;

    float d=distmat.at<float>(i,p);
     if(d<THRES){
	 line(dispimg,
	      Point(key_v1[i].pt.x, key_v1[i].pt.y),
	      Point(cimg1.cols+key_v2[p].pt.x, cimg1.rows+key_v2[p].pt.y),
	      Scalar(255,0,255),1,8);
    }
     // circle(dispimg, Point(key_v1[i].pt.x, key_v1[i].pt.y),
     // 	   2, Scalar(255,255,0));
     // circle(dispimg, Point(cimg1.cols+key_v2[i].pt.x, cimg1.rows+key_v2[i].pt.y),
     // 	   2, Scalar(255,255,0));
  }



  namedWindow("SURF matching",CV_WINDOW_AUTOSIZE);
  imshow("SURF matching", dispimg);

  waitKey(0);

  return 0;
}

