////////////////////////////////////////////////////////////////////////////////
///Copyright(c)      UESTC MBZIRC     Model Code for UAV
///ALL RIGHTS RESERVED
///@file:control_model.cpp
///@brief: UAV 控制模型，包含对所有应用的管理，创建应用，并改变应用
/// 
///@vesion 1.0
///@author: PC
///@email: 694977655@qq.com
///@date: 18-11-6
///修订历史：
////////////////////////////////////////////////////////////////////////////////
#include "control_model.h"
#include "basic_tool.h"
#include "usb_capture_with_thread.h"
#include "string"
#include "aim.h"
using namespace cv;
using namespace std;

ControlModel::ControlModel(){}

ControlModel::~ControlModel(){}
static VideoWriter writer;
void ControlModel::init(RobotModel* robotModel){
    pRobotModel=robotModel;
    //配置文件
    usleep(1000000);//等待1s，等摄像头稳定
    //初始模式初始化
    mSetMode=ROBOT_MODE_TRACKBALL;
    //writer.open("log.avi",CV_FOURCC('X','V','I','D'),25,Size(640,480),0);    
    writer.open("log.avi",CV_FOURCC('M','J','P','G'),25,Size(640,480),0);
}

//串口数据接收处理入口
void ControlModel::serialListenDataProcess(SerialPacket recvPacket) {
//复杂自定义数据包，需要自定义析单独处理
    pRobotModel->DataUpdate(recvPacket);
}

void ControlModel::processFSM(){
    //模式切换预处理
    if(mSetMode!=pRobotModel->getCurrentMode()){
        pRobotModel->setCurrentMode(mSetMode);
        switch (mSetMode){
            case ROBOT_MODE_TRACKBALL:{
                pid_x.init(0.01,0,0.0001,0.015f,-3,3,AUTOMATIC,DIRECT);
                pid_y.init(0.01,0,0.0001,0.015f,-3,3,AUTOMATIC,DIRECT);
                pid_z.init(0.005,0,0,0.015f,-3,3,AUTOMATIC,DIRECT);
                pid_x.PIDSetpointSet(0);
                pid_y.PIDSetpointSet(0);
                pid_z.PIDSetpointSet(500);
                cout<<"[control model mode ]:Switch to BALL TRACKING Mode!"<<endl;
                break;
            }
            case ROBOT_MODE_RETURN:{
                cout<<"[control model mode ]:Switch to RETURN Mode!"<<endl;
                break;
            }
            case ROBOT_MODE_EMPTY:{
                cout<<"[control model mode ]:Do Nothing"<<endl;
                break;
            }
        }
    }

    switch(pRobotModel->getCurrentMode()){
        case ROBOT_MODE_TRACKBALL:{
            trackBall();
            break;
        }
        case ROBOT_MODE_RETURN:{

            break;
        }
        
    }

}

void ControlModel::trackBall(){
    RealsenseInterface* cap = pRobotModel->getRealsenseCpature();
    SerialInterface* interface = pRobotModel->getpSerialInterface();
    Mat src;
    Mat ori;
    cap->getColorImg(ori);
    Point3f distance;
    String str1,str2;
    float velocity_y,velocity_x,velocity_z;
    //VideoWriter writer;
    //writer.open("log.avi",CV_FOURCC('X','V','I','D'),25,Size(640,480),0);
    distance.x = distance .y = distance.z = 0xff;
    if(cap->getDepthImg(src) == 0){
        distance = ball_aim.getDistance(src);
      if(ball_aim.isdetect(ori,distance)==1){
        std::cout<<"distance.x:"<<distance.y<<"\tdistance.z:"<<distance.z<<endl;
        circle(ori,Point(distance.x+320,distance.y+240),5,Scalar(0,0,255));
        pid_x.PIDInputSet(distance.x);
        pid_y.PIDInputSet(distance.y);
        pid_z.PIDInputSet(distance.z);
        if(pid_x.PIDCompute()==false)std::cout<<"error pid_x"<<std::endl;//fix
        if(pid_y.PIDCompute()==false)std::cout<<"error pid_y"<<std::endl;
        if(pid_z.PIDCompute()==false)std::cout<<"error pid_z"<<std::endl;
        velocity_x= pid_x.PIDOutputGet();
        velocity_y = pid_y.PIDOutputGet();
        //velocity_z = pid_z.PIDOutputGet();
        }else{
            velocity_x=velocity_y=velocity_z=0;
        }
        //float velocity_z = pid_z.PIDOutputGet();
	    std::cout<<"pid_y:"<<velocity_y<<std::endl;
        // if(abs(distance.x)<50&&abs(distance.y)<50)
       // str1 = "velocity_y: "+to_string(velocity_y);
        str1 = "velocity_x: "+to_string(velocity_x);
        str2="distancez:"+to_string(distance.z);
        putText(ori,str1,Point(10,30),CV_FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),4,8);
        
        putText(ori,str2,Point(10,60),CV_FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255),4,8);
        writer.write(ori);
             interface->movebyVelocity(-velocity_x,0,0,0);
             usleep(100000);

           //  interface->movebyVelocity(0,velocity_y,0,0);
// else interface->movebyVelocity(velocity_x,velocity_y,0,0);
            // interface->movebyVelocity(0,-velocity_y,0,0);
// else interface->movebyVelocity(velocity_x,velocity_y,0,0);
        // if(distance.z<800)  cout<<"收网!!!!"<<endl;
}   
} 
