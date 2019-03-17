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
    static VideoWriter writer;
    writer.open("log.avi",CV_FOURCC('X','V','I','D'),25,Size(640,480),0);
    PIDControl pid_x;
    PIDControl pid_y;
    PIDControl pid_z;
    Point3f distance;
    String str_1,str_2;
    float velocity_y,velocity_x,velocity_z;
    pid_x.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    pid_y.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    pid_z.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    pid_x.PIDSetpointSet(0);
    pid_y.PIDSetpointSet(0);
    pid_z.PIDSetpointSet(500);
    while(true){
        if(realsense.getDepthImg(depth) == 0){
            realsense.getColorImg(color);
            // cv::Point3f distance = ball_aim.getDistance(depth);
            // cout<<"distance z "<<distance.z<<endl;
            // cout<<"distance x "<<distance.x<<endl;
            // cout<<"distance y "<<distance.y<<endl;
            //cout<<depth.cols/2<<endl;
            //cout<<depth.rows/2<<endl;
            //if(cap->getDepthImg(src) == 0){
        distance = ball_aim.getDistance(depth);
        std::cout<<"distance.x:"<<distance.y<<"\tdistance.z:"<<distance.z<<endl;
        if(ball_aim.isdetect(color,distance)==1){ 
        //std::cout<<"distance.x:"<<distance.y<<endl;
        circle(color,Point(distance.x+320,distance.y+240),5,Scalar(0,0,255));
        pid_x.PIDInputSet(distance.x);
        pid_y.PIDInputSet(distance.y);
        pid_z.PIDInputSet(distance.z);
        if(pid_x.PIDCompute()==false)std::cout<<"error pid_x"<<std::endl;//fix
        if(pid_y.PIDCompute()==false)std::cout<<"error pid_y"<<std::endl;
        if(pid_z.PIDCompute()==false)std::cout<<"error pid_z"<<std::endl;
        velocity_y = pid_x.PIDOutputGet();
        velocity_x = pid_y.PIDOutputGet();
        //velocity_z = pid_z.PIDOutputGet();
        }else{
            velocity_x=velocity_y=velocity_z=0;
        }
        //float velocity_z = pid_z.PIDOutputGet();
	    std::cout<<"pid_y:"<<velocity_y<<std::endl;
        str_1= "velocity_y: "+to_string(velocity_y);
        str_2="distancez: "+to_string(distance.z);
        putText(color,str_1,Point(10,30),CV_FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),4,8);
        putText(color,str_2,Point(10,60),CV_FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),4,8);

        namedWindow("color",CV_WINDOW_AUTOSIZE);
        imshow("color",color);
        waitKey(50);
        writer.write(color);
        //     circle(color,Point(distance.x+320,distance.y+240),5,Scalar(0,0,255),5,16);
        //     pid_x.PIDInputSet(-distance.x);
        //     pid_y.PIDInputSet(distance.y);
        //     //pid_z.PIDInputSet(distance.z);
        //     if(false==pid_x.PIDCompute())std::cout<<"x error"<<std::endl;
        //     if(false==pid_y.PIDCompute())std::cout<<"y error"<<std::endl;
        // float velocity_x = pid_x.PIDOutputGet();
        // float velocity_y = pid_y.PIDOutputGet();
        // cout<<velocity_x<<endl;
        // cout<<velocity_y<<endl;
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
