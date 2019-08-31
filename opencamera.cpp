#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;


int main() 
{ 
	VideoCapture capture("v4l2src device=/dev/video10 io-mode=4 ! videoconvert ! video/x-raw,format=NV12,width=800,height=448,framerate=30/1 ! videoconvert ! appsink",cv::CAP_GSTREAMER);
	if (!capture.isOpened()) {
		printf("Fail to open camera.\n");
		return 1;
	}
	namedWindow("win", 1);
	while (1) { 
		Mat frame;
		capture >> frame;
		if (frame.empty()) {
			printf("Fail to read frame.\n");
			break;
		}
		imshow("win",frame);
		if (waitKey(30) & 0xFF == 'q') 
			break;
	} 
	capture.release();
	return 0; 
}




