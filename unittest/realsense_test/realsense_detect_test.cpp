#include "opencv2/opencv.hpp"
#include "realsense.h"
#include "pid.h"
#include "aim.h"

int main(){
    RealsenseInterface realsense;
    Aim_ball ball_aim;
    if(realsense.init(640,480) == 0){
        cout << "RealsenseCapture init successed!" <<endl;
        usleep(1000000);
    }
    Mat depth;
    Mat color;
    PIDControl pid_x;
    PIDControl pid_y;
    PIDControl pid_z;
    pid_x.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    pid_y.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    pid_z.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    pid_x.PIDSetpointSet(0);
    pid_y.PIDSetpointSet(0);
    pid_z.PIDSetpointSet(500);
    while(true){
        if(realsense.getDepthImg(depth) == 0){
            realsense.getColorImg(color);
            cv::Point3f distance = ball_aim.getDistance(depth);
            cout<<"distance z "<<distance.z<<endl;
            cout<<"distance x "<<distance.x<<endl;
            cout<<"distance y "<<distance.y<<endl;
            cout<<depth.cols/2<<endl;
            cout<<depth.rows/2<<endl;
            circle(color,Point(distance.x+320,distance.y+240),5,Scalar(0,0,255),5,16);
            pid_x.PIDInputSet(-distance.x);
            pid_y.PIDInputSet(distance.y);
            //pid_z.PIDInputSet(distance.z);
            if(false==pid_x.PIDCompute())std::cout<<"x error"<<std::endl;
            if(false==pid_y.PIDCompute())std::cout<<"y error"<<std::endl;
        float velocity_x = pid_x.PIDOutputGet();
        float velocity_y = pid_y.PIDOutputGet();
        cout<<velocity_x<<endl;
        cout<<velocity_y<<endl;
        //float velocity_z = pid_z.PIDOutputGet();
//        if(abs(distance.x)<50&&abs(distance.y)<50)
            // interface->movebyVelocity(velocity_x,velocity_y,0,0);
           // imshow("depth", depth);
            //imshow("color",color);
           // waitKey(5);
        }
        else cout<<"error"<<endl;
    }
}
