#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <stdio.h>
#include <time.h> 

using namespace std;
using namespace cv;

// MJPEG
char* get_camerasrc_mjpeg(int devIndex) {
#if 1
    // for T4, M4B
    const int cam_width=1920;
    const int cam_height=1080;
    const int cam_frames=15;
#else
    // for M4/M4v2
    const int cam_width=432;
    const int cam_height=240;
    const int cam_frames=30;
#endif

    static char str[255]={'\0'};
	snprintf(str, sizeof(str)-1
		, "v4l2src device=/dev/video%d io-mode=4 ! image/jpeg,width=%d,height=%d,framerate=%d/1 ! jpegdec ! videoconvert ! video/x-raw,format=BGR ! appsink sync=false"
		, devIndex
		, cam_width
		, cam_height
		, cam_frames
		);
	return str;
}

// NV12
char* get_camerasrc_nv12(int devIndex) {
    const int cam_width=640;
    const int cam_height=480;
    const int cam_frames=30;
    static char str[255]={'\0'};
	snprintf(str, sizeof(str)-1
		, "v4l2src device=/dev/video%d io-mode=4 ! videoconvert ! video/x-raw,format=NV12,width=%d,height=%d,framerate=%d/1 ! videoconvert ! video/x-raw,format=BGR ! appsink"
		, devIndex
		, cam_width
		, cam_height
		, cam_frames
		);
	return str;
}

int main(int argc,char* argv[]) 
{ 
	// check args
    if(argc < 2) {
        printf("Please provide the number of cameras, it must be 1,2 or 3.\n");
        exit(0);
    }
	errno = 0;
	char *endptr;
	long int count = strtol(argv[1], &endptr, 10);
	if (endptr == argv[1] || errno == ERANGE) {
		std::cerr << "Invalid parameter: " << argv[1] << '\n';
		exit (1);
	}
	if (count < 1 || count > 3) {
		std::cerr << "The parameter must be 1,2,3" << '\n';
		exit (1);
	}

	// check qt5 env
	const char* s = getenv("QTDIR");
	if (!s) {
		std::cerr << "Please execute the following command first: " << '\n';
		std::cerr << "\t. setqt5env" << '\n';
		exit (1);
	}

	VideoCapture *pCapture[3]={0};
	char windowName[10];
	int hasError;
	int devIndex=10;   // dev: /dev/video10
	for (int i=0; i<count; i++) {
		// mjpg
		pCapture[i] = new VideoCapture(get_camerasrc_mjpeg(devIndex),cv::CAP_GSTREAMER);
		if (!pCapture[i]->isOpened()) {
			printf("Fail to open camera.\n");
			exit (1);
		}
		// opencv window
		sprintf(windowName,"%d",i+1);
		namedWindow(windowName, 1);

		devIndex += 2;  // dev: /dev/video12, /dev/video14, etc ..
	}

	// fps counter begin
	time_t start, end;
	int fps_counter = 0;
	double sec;
	double fps;
        time(&start);
	// fps counter end

	while (1) { 
		Mat frame;
		hasError = 0;
		for (int i=0; i<count; i++) {
			*pCapture[i] >> frame;
			if (frame.empty()) {
				printf("Fail to read frame.\n");
				hasError = 1;
				break;
			}
			sprintf(windowName,"%d",i+1);
			imshow(windowName,frame);

			// only calc one camera
			if (i == 0) {
				// fps counter begin
				time(&end);
				fps_counter++;
				sec = difftime(end, start);
				if (sec > 1) {
					fps = fps_counter/sec;
					printf("%.2f fps\n", fps);
					fps_counter=0;
					time(&start);
                                }
				// fps counter end
			}
		}
		if (hasError) {
			break;
		}
		if (waitKey(30) & 0xFF == 'q') 
			break;
	} 
	
	// release
	for (int i=0; i<count; i++) {
		pCapture[i]->release();
		delete pCapture[i];
	}
	return 0; 
}




