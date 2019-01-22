#include "aim.h"
using namespace cv;
using namespace std;

Aim_ball::Aim_ball(){

}

Aim_ball::~Aim_ball(){

}

// bool Aim_ball::isdetect(Mat src,Point3f distance_former){
//     cvtColor(src,src,CV_BGR2GRAY);
//     //检验验证的矩形是否越界
//     if (distance_former.x-10<0){
//         distance_former.x==0;
//         }
//     if (distance_former.y-10<0){
//         distance_former.y==0;    
//     }
//     Rect rect(distance_former.x-10,distance_former.y-10,10,10);
//     src(rect).copyTo(roi_image);
	
//     cvtColor(roi_image,roi_image,CV_BGR2GRAY);
//     // namedWindow("roi_image",CV_WINDOW_AUTOSIZE);
//     // imshow("roi_image",roi_image);
//     // waitKey(1000);
//     MatND histogram;
//     //256个，范围是0，255
//     int channels=0;
//     const int histSize = 256;
//     float range[] = {0, 255};
//     const float *ranges[] = {range};
//     // cout<<range[0]<<endl;
//     // cout<<ranges[0]<<endl;
    
//     //空掩膜，256通道，
//     calcHist(&roi_image, 1, &channels, Mat(), histogram, 1, &histSize, &ranges[0], true, false);
//     int row = histogram.rows;
//     int col = histogram.cols;
//     // cout<<row<<endl;
//     // cout<<col<<endl;

//     float *h = (float*)histogram.data;
//     double hh[256];
//     int max=h[0];
//     int flag=0;
//     if (h) {
//         for (int i = 0; i < 256; i++) {
//             hh[i] = h[i];
//             // cout<<i<<endl;
//             // cout<<hh[i]<<endl;
//             if(hh[i]>max){
//                 max=hh[i];
//                 flag=i;
//                 // cout<<hh[i]<<endl;
//                 // cout<<flag<<endl;
//             }
//         }
//         // cout<<hh[flag]<<endl;
//         // cout<<flag<<endl;
//     }
//     if(flag>128){
//         return 1;
//     }
//     else 
//         return 0;
// }


Point3f Aim_ball::getDistance(Mat depth){
    int a = 0;
    int b = 0;
    Point3f distance;
    for(int i = 0; i <depth.rows; i++){
        for(int j = 0; j < depth.cols; j++){
            if(depth.at<ushort>(i,j)==0) continue;
            if(depth.at<ushort>(a,b)==0){
                a++;
                b++;
                continue;
            }
            if(depth.at<ushort>(i,j) < depth.at<ushort>(a,b)){
                a = i;
                b = j;
            }
        }
    }
    distance.z = float(depth.at<ushort>(a,b));
    distance.x = b- depth.cols/2;
    distance.y = a- depth.rows/2;
    return distance;
}
// Point3f Aim_ball::getDistance(Mat depth){
//     int a = 0;
//     int b = 0;
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

//     // if(!isdetect(src,distance)){
//     //     distance.z=5000;
//     //     distance.x=depth.cols/2;
//     //     distance.y=depth.rows/2;
//     // }      
//     // else {
//         distance.z = float(depth.at<ushort>(a,b));
//         distance.x = b-depth.cols/2;
//         distance.y = a-depth.rows/2;
//         // }
//     return distance;
// }
