#include <opencv2/opencv.hpp>
#include "realsense.h"
#include "pid.h"
#include "aim.h"
#include "socket.hpp"
#include "ACsaliencydetect.h"
//#include <curses.h>
#include <time.h>        

int main(){
    RealsenseInterface realsense_getxyz;
    Aim_ball ball_aim;
    //AC_saliency ac;
    CAMERA_INRINSIC_PARAMETERS c;
    c.fx=645;
    c.fy=648;
    //645.277749 648.004580 331.576464 231.011424 -0.004489 0.002333 0.169973 -0.357225
    c.cx=331;
    c.cy=231;
    c.scale=1.0;
    if(realsense_getxyz.init(640,480) == 0){
        cout << "RealsenseCapture init successed!" <<endl;
        usleep(5000000);
    }
    Mat depth;
    Mat color;
    // static VideoWriter writer_color,writer_depth;
    // writer_color.open("log_color.avi",CV_FOURCC('M','J','P','G'),25,Size(640,480),1);
    // writer_depth.open("log_depth.avi",CV_FOURCC('M','P','4','2'),25,Size(640,480),1);
    //writer.open("log.avi",CV_FOURCC('M','J','P','G'),25,Size(640,480),0);
    // PIDControl pid_x;
    // PIDControl pid_y;
    // PIDControl pid_z;
    Point3f d_d,d_a,d_ac;
    String str_1,str_2;
    //float velocity_y,velocity_x,velocity_z;
    // pid_x.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    // pid_y.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    // pid_z.init(0.001,0,0,0.0f,-5,5,AUTOMATIC,DIRECT);
    // pid_x.PIDSetpointSet(0);
    // pid_y.PIDSetpointSet(0);
    // pid_z.PIDSetpointSet(500);
    //time_t c=time(NULL);
    //while(std::difftime(time(NULL),c)<60)
    ushort d;
    Mat image_tmp(Size(640,480),CV_16UC1); 
    Mat image_tmp1,image_tmp2; 
    Socket client;
    client.client_init("192.168.50.162");
    //VideoCapture cap1("/home/vayneli/test_video/0327/8_depth.avi");
    //VideoCapture cap1("/home/vayneli/test_video/0719/depth.avi");
    //VideoCapture cap2("/home/vayneli/test_video/0719/color.avi");
    while(true)
    {
        if(realsense_getxyz.getDepthImg(depth) == 0){
             //realsense_getxyz.getColorImg(color);
        //if(cap1.isOpened()){
        //cap1>>depth;
        //cout<<"depth.type()"<<depth.type()<<endl;
        //cout<<depth.depth()<<endl;
        //cap2>>color;
        //cout<<color.type()<<endl; 
        //cout<<"2"<<endl; 
            
            for(int i=0;i<depth.rows;i++){
                //cout<<"depth.rows:"<<depth.rows<<endl;
                for(int j=0;j<depth.cols;j++){
                   d=depth.at<ushort>(i,j)*10.0;
                   image_tmp.at<ushort>(i,j)=d;
                }
            }
            d_d=ball_aim.getDistance(depth);
            // cout<<"1"<<endl;
            //d_d=ball_aim.getDistance(depth);
            //d_a=ac.getXY(color,depth);
            //circle(color,Point(d_a.x,d_a.y),5,Scalar(255,0,0),4,8);
            //convertTo转换是channel得相同；
            image_tmp.convertTo(image_tmp1,CV_8UC1);
            cvtColor(image_tmp1,image_tmp2,COLOR_GRAY2BGR);
            //cout<<"imagetmp:"<<image_tmp2.type()<<endl;
            circle(image_tmp2,Point(d_d.y,d_d.x),10,Scalar(0,0,255),4,8);
            //double e=(d_d.x-d_a.x)*(d_d.x-d_a.x)+(d_d.x-d_a.x)*(d_d.y-d_a.y)+(d_d.x-d_a.x)*(d_d.z-d_a.z);
            cout<<"xyz:"<<d_d<<endl;
            //client.client_init("192.168.50.162");
            client.send_data(d_d.x,d_d.y,0);
            cout << "send successful" << endl;
            //str_1= "distance: "+to_string(d_d.x)+","+to_string(d_d.y)+","+to_string(d_d.z);
            //str_2="distancez: "+to_string(distance.z);
            //putText(color,str_1,Point(10,30),CV_FONT_HERSHEY_SIMPLEX,0.8,Scalar(0,0,255),4,8);
            //putText(color,str_2,Point(10,60),CV_FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),4,8);

            // if(sqrt(e)<20){
            //     d_ac=ac.getC_xyz(d_d,c);
            //     cout<<"distance:"<<" "<<d_ac<<endl;
            // }
            // else cout<<"not the same points"<<endl;
            //namedWindow("color",CV_WINDOW_AUTOSIZE);
            namedWindow("depth",CV_WINDOW_AUTOSIZE);
            //imshow("color",color);
            imshow("depth",depth);
            imshow("image_tmp",image_tmp2);

            if(waitKey(1)>0) break;
        }else{
             cout<<"error"<<endl;
        }
        //float velocity_z = pid_z.PIDOutputGet();
	    
        
    }
        return 0;
}
