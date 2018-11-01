// sudo modprobe bcm2835-v4l2
// https://www.raspberrypi.org/documentation/raspbian/applications/camera.md
// raspistill -vf -o image.jpg

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <sys/time.h>
#include <time.h>

using namespace cv;
using namespace std;

#define n_Frames 100

void drawText(Mat & image);

int main()
{
    struct timeval TS_Ini, TS_Fin,dt;
    unsigned long dt_us_ul;
    float dt_ms_fl;
    
    // La configuracion debemos cargarla con JSON
    // http://www.raspberry-projects.com/pi/programming-in-c/json/rapidjson
    // https://www.raspberrypi.org/forums/viewtopic.php?t=129950
    
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat image;
    VideoCapture capture;
    capture.open(0);
    //modos: 320 x 240, 1280 x 920, 2592 x 1944);
    // https://raspberrypi.stackexchange.com/questions/75120/increasing-fps-of-pi-camera-using-opencv-c-implementation
    // https://stackoverflow.com/questions/11420748/setting-camera-parameters-in-opencv-python
    capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
    int Width = capture.get(CV_CAP_PROP_FRAME_WIDTH);
    std::cout <<"FRAME_WIDTH (px) : "<< Width << endl;
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,420);
    int Height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    std::cout <<"FRAME_HEIGHT (px): "<< Height << endl;
    capture.set(CV_CAP_PROP_FPS,50);
    float fps = capture.get(CV_CAP_PROP_FPS);
    std::cout <<"FRAME_RATE (fps) : "<< fps << endl; 
    capture.set(CV_CAP_PROP_BRIGHTNESS,0.5); 
    float Brightness = capture.get(CV_CAP_PROP_BRIGHTNESS);
    std::cout <<"BRIGHTNESS (%)   : "<< Brightness*100 << endl;
    capture.set(CV_CAP_PROP_AUTO_EXPOSURE,0); 
    int Auto_Exposure = capture.get(CV_CAP_PROP_AUTO_EXPOSURE);
    std::cout <<"AUTO_EXPOSURE    : "<< Auto_Exposure << endl;
    capture.set(CV_CAP_PROP_EXPOSURE,0); 
    float Exposure = capture.get(CV_CAP_PROP_EXPOSURE);
    std::cout <<"EXPOSURE (us)    : "<< Exposure << endl;

    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        gettimeofday(&TS_Ini,NULL);
        capture >> image;
         if(image.empty())
                cout << "Fallo en primera imagen" << endl;
        
        for(int i=0; i<n_Frames; i+=1)
        {
            capture >> image;      
            if(image.empty())
                break;
        }
        cout << "Capture has finished" << endl;
        imwrite("image.jpg",image);
        gettimeofday(&TS_Fin,NULL);
        timersub(&TS_Fin, &TS_Ini, &dt);
        dt_us_ul = dt.tv_sec*1e6 + dt.tv_usec;
        dt_ms_fl = (float)dt_us_ul/1000;
        cout <<"Elapsed time (ms):" << dt_ms_fl << endl;
        cout <<"fps: "<< n_Frames*1000/dt_ms_fl << endl;
    }
    else
    {
        cout << "No capture" << endl;
    }
    return 0;
}
