#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

void drawText(Mat & image);

int main()
{
    struct timeval TS_Ini, TS_Fin,dt;
    unsigned long dt_us_ul;
    float dt_ms_fl;
    char Aux_Text[256]; 
    char File_Name[] ="Image_";

    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat image;
    Mat tmp;
    VideoCapture capture;
    capture.open(0);
    if(capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        gettimeofday(&TS_Ini,NULL);
        capture >> image;
         if(image.empty())
                cout << "Fallo en primera imagen" << endl;

        for(int i=0; i<10; i+=1)
        {
            capture >> tmp;
            flip( tmp,image, 0 );     // because you can't flip in-place (leads to segfault)
            //itoa(i,Aux_Text,10);
            strcpy (File_Name,"Image_");
            sprintf(Aux_Text,"%d",i) ;
            strncat (File_Name, Aux_Text, 10);
            strncat (File_Name, ".jpg", 4);
            cout << File_Name << endl;
            imwrite(File_Name,image);
           // htps://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/hough_circle/hough_circle.html

            if(image.empty())
                break;

//	    if(waitKey(10) >= 0)
//                break;
        }
        cout << "Capture has finished" << endl;
        imwrite("image.jpg",image);
        gettimeofday(&TS_Fin,NULL);
        timersub(&TS_Fin, &TS_Ini, &dt);
        dt_us_ul = dt.tv_sec*1e6 + dt.tv_usec;
        dt_ms_fl = (float)dt_us_ul/1000;
        cout <<"Elapsed time (ms):" << dt_ms_fl << endl;
    }
    else
    {
        cout << "No capture" << endl;
//        image = Mat::zeros(480, 640, CV_8UC1);
//        drawText(image);
//        imshow("Sample", image);
//        waitKey(0);
    }
    return 0;
}

void drawText(Mat & image)
{
    putText(image, "Hello OpenCV",
            Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, // font face and scale
            Scalar(255, 255, 255), // white
            1, LINE_AA); // line thickness and type
}
