#include "aim.h"
using namespace cv;
using namespace std;

Aim_ball::Aim_ball(){

}

Aim_ball::~Aim_ball(){

}

bool Aim_ball::isdetect(Mat src,Point3f distance_former){
    //cvtColor(src,src,CV_BGR2GRAY);
    //检验验证的矩形是否越界
    if (distance_former.x-10<0){
        distance_former.x=0;
        }
    if (distance_former.y-10<0){
        distance_former.y=0;    
    }
    Rect rect(distance_former.x,distance_former.y,10,10);
    src(rect).copyTo(roi_image);
     
    cvtColor(roi_image,roi_image,CV_BGR2GRAY);
    // namedWindow("roi_image",CV_WINDOW_AUTOSIZE);
    // imshow("roi_image",roi_image);
    // waitKey(1000);
    MatND histogram;
    //256个，范围是0，255
    int channels=0;
    const int histSize = 256;
    float range[] = {0, 255};
    const float *ranges[] = {range};
    // cout<<range[0]<<endl;
    // cout<<ranges[0]<<endl;
 
    //空掩膜，256通道，
    calcHist(&roi_image, 1, &channels, Mat(), histogram, 1, &histSize, &ranges[0], true, false);
    int row = histogram.rows;
    int col = histogram.cols;
    // cout<<row<<endl;
    // cout<<col<<endl;

    float *h = (float*)histogram.data;
    double hh[256];
    int msum=0;
    int sum=0;
    // int max=h[0];
    // int flag=0;
    // if (h) {
    //     for (int i = 0; i < 256; i++) {
    //         hh[i] = h[i];
    //         // cout<<i<<endl;
    //         // cout<<hh[i]<<endl;
    //         if(hh[i]>max){
    //             max=hh[i];
    //             flag=i;
    //             // cout<<hh[i]<<endl;
    //             // cout<<flag<<endl;
    //         }
    //     }
    //     // cout<<hh[flag]<<endl;
    //     // cout<<flag<<endl;
    // }
    // if(flag>128){
    //     return 1;
    // }
    // else 
    //     return 0;
    for(int i=0;i<128;i++){
        msum=msum+h[i];
    }
    sum=msum;
    for(int j=128;j<256;j++){
        sum+=sum+h[j];
    }
    float per=msum/sum;
    if(per<0.5){
        return 1;
    }else return 0;
}


// Point3f Aim_ball::getDistance(Mat depth){
//    int a = depth.rows/2;
//    int b = depth.cols/2;
//    Point3f distance;
//    for(int i = 0; i <depth.rows; i++){
//        for(int j = 0; j < depth.cols; j++){
//            if(depth.at<ushort>(i,j)==0) continue;
//            if(depth.at<ushort>(a,b)==0){
//                a++;
//                b++;
//                continue;
//            }
//            if(depth.at<ushort>(i,j) < depth.at<ushort>(a,b)){
//                a = i;
//                b = j;
//            }
//        }
//    }
//    distance.z = float(depth.at<ushort>(a,b));
//    distance.x = b- depth.cols/2;
//    distance.y = a- depth.rows/2;
//    return distance;
// }
// Point3f Aim_ball::getDistance(Mat depth){
//     int a = depth.rows/2;
//     int b = depth.cols/2;
//     Point3f distance;
//     for(int i = 0; i <depth.rows; i++){
//         for(int j = 0; j < depth.cols; j++){
//             if(depth.at<ushort>(i,j)==0) continue;
//             if(depth.at<ushort>(a,b)==0){
//                 a++;
//                 b++;
//                 continue;
//             }

//             if(depth.at<ushort>(i,j) < depth.at<ushort>(a,b)){

//                 a = i;
//                 b = j; 
//             }
//         }
//     }
//     //判断最小点是否是目标点，若为干扰点则输出图像中心，若为目标点则输出真实坐标和距离

// //     if(!isdetect(src,distance)){
// //         distance.z=20000;
// //         distance.x=depth.cols/2;
// //         distance.y=depth.rows/2;
// //     }      
// //     else {
//       distance.z = float(depth.at<ushort>(a,b));
//       //distance.x = b-depth.cols/2;
//       //distance.y = a-depth.rows/2;
//       distance.x = b;
//       distance.y = a;
// //         }
//     return distance;
// }

bool Aim_ball::filter(Mat depth,int m,int n){

    int sum,avg;
    if(m-1<0) m=1;
    if(n-1<0) n=1;
    if(m+1>640) m=639;
    if(n+1>480) n=479;
    sum=depth.at<ushort>(m-1,n-1)+depth.at<ushort>(m-1,n)+depth.at<ushort>(m-1,n+1);
    sum=sum+depth.at<ushort>(m,n-1)+depth.at<ushort>(m,n)+depth.at<ushort>(m,n+1);
    sum=sum+depth.at<ushort>(m+1,n-1)+depth.at<ushort>(m+1,n)+depth.at<ushort>(m+1,n+1);
    avg=sum/9;
    if(abs(avg-depth.at<ushort>(m,n))<500) return true;
    else false;
}

Point3f Aim_ball::getDistance(Mat depth){

    Point3f distance;
    int a=0;
    int b=0;
    //vector<Mat> abc;
    //split(depth,abc);
    //Mat dst=abc[0];
    //cout<<"depth type:"<<depth.type()<<endl;
    float d=depth.at<ushort>(a,b);
    for(int i = 0; i <depth.rows; i++){
       for(int j = 0; j < depth.cols; j++){
           if(depth.at<ushort>(i,j)==0) continue;
           if(depth.at<ushort>(i,j) > d&&depth.at<ushort>(i,j)<12000){
               a = i;
               b = j;
               d=depth.at<ushort>(a,b);
           }
       }
   }
   distance.z = float(depth.at<ushort>(a,b));
   distance.x = a;
   distance.y = b;
    // Mat dst=abc[0].reshape(0,1);
    // //cout<<"dst type:"<<dst.type()<<endl;
    // float d=dst.at<uint>(0,0);
    // int count=0;
    // for(int i=0;i<dst.rows;i++){

    //     if(dst.at<uint>(0,i)>d){
    //         d=dst.at<uint>(0,i);
    //         count=i;
    //     } 
    // }

    // distance.x=int(count%depth.cols);
    // cout<<"x:"<<distance.x<<endl;
    // distance.y=int(count/depth.rows);
    // distance.z=d;
    // Point p1,p2;
    // //int* minInd[3];
    // //int* maxInd[3];
    // double v_min,v_max;
    // cout<<"depth.type():"<<depth.type()<<endl;
    // //cout<<"2"<<endl;
    // depth.convertTo(depth,CV_8UC1);
    // cout<<"depth.type():"<<depth.type()<<endl;
    // cv::minMaxLoc(depth,&v_min,&v_max,&p1,&p2);
    // //cv::minMaxIdx(depth,&v_min,&v_max,*minInd,NULL,Mat());
    // cout<<"1"<<endl;
    // // cout<<"minInd[0]"<<p1<<endl;
    // // distance.x=p1.x;
    // // distance.y=p1.y;
    // cout<<"minInd[0]"<<p2<<endl;
    // distance.x=p2.x;
    // distance.y=p2.y;
    // distance.z=float(v_max);

    if(d==0) return Point3f(depth.rows/2,depth.cols/2,0);
    else return distance;
}