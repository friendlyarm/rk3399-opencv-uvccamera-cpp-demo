## **rk3399-opencv-uvccamera-cpp-demo**

![image](https://github.com/friendlyarm/rk3399-opencv-uvccamera-cpp-demo/raw/master/sample.png)

Build
------------
```
git clone https://github.com/friendlyarm/rk3399-opencv-uvccamera-cpp-demo.git
cd rk3399-opencv-uvccamera-cpp-demo
mkdir build
cd build
cmake ..
make
```

Run one camera
------------
```
su pi
export DISPLAY=:0.0
. setqt5env
./opencamera 1
```

Run three cameras
------------
```
su pi
export DISPLAY=:0.0
. setqt5env
./opencamera 3
```

Reading mjpeg stream
------------
open the camera using the following code:
```
pCapture[i] = new VideoCapture(get_camerasrc_mjpeg(devIndex),cv::CAP_GSTREAMER);
```

Reading NV12 stream
------------
open the camera using the following code:
```
pCapture[i] = new VideoCapture(get_camerasrc_nv12(devIndex),cv::CAP_GSTREAMER);
```

Supported camera
------------
```
Logitech C922 (NV21, MJPG)
KS2A242  (NV21, MJPG)
```

Supported boards
------------
```
NanoPC T4
NanoPi M4/M4v2/M4B
NanoPi NEO4
SOM-RK3399
```

How can i find out the supported camera resolutions
------------
```
v4l2-ctl --list-formats-ext -d /dev/video10
```

More examples
------------
https://github.com/friendlyarm/rk3399-opencv-uvccamera-python-demo  
https://github.com/friendlyarm/install-opencv-on-friendlycore  
https://github.com/friendlyarm/s5pxx18-opencv-uvccamera-cpp-demo  

