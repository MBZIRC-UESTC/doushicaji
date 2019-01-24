#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include "pnp_solver.h"
using namespace cv;
class Aim_ball{
    public:
        Aim_ball();
        ~Aim_ball();
    public:  
        bool isdetect(Mat src,Point3f distance_former);
        Point3f getDistance(Mat depth);
    private:
        Mat src;
        Mat roi_image;

};