#include "realsense.h"
#include <librealsense2/rs_advanced_mode.hpp>
RealsenseInterface::RealsenseInterface(){
    isOpen = false;

};
RealsenseInterface::~RealsenseInterface(){};
rs2::align align_to(RS2_STREAM_DEPTH);
int RealsenseInterface::init(){
    rs2::context ctx;
    auto devices = ctx.query_devices();
    size_t device_count = devices.size();
    if (!device_count)
    {
        cout <<"No device detected. Is it plugged in?\n";
        return -1;
    }
    auto dev = devices[0];
    if (dev.is<rs400::advanced_mode>())
    {
        
        auto advanced_mode_dev = dev.as<rs400::advanced_mode>();
        // Check if advanced-mode is enabled
        if (!advanced_mode_dev.is_enabled())
        {
            // Enable advanced-mode
            advanced_mode_dev.toggle_advanced_mode(true);
        }
    }
    else
    {
        cout << "Current device doesn't support advanced-mode!\n";
        return EXIT_FAILURE;
    }
    // rs2::device selected_device = dev;
    // auto depth_sensor = selected_device.first<rs2::depth_sensor>();
    // depth_sensor.set_option(rs2_option::RS2_OPTION_VISUAL_PRESET,rs2_rs400_visual_preset::RS2_RS400_VISUAL_PRESET_HIGH_ACCURACY);
    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_INFRARED,  color_img_width, color_img_height, RS2_FORMAT_Y8, 60);
    cfg.enable_stream(RS2_STREAM_DEPTH,     color_img_width, color_img_height, RS2_FORMAT_Z16, 60);

    //Instruct pipeline to start streaming with the requested configuration
    auto profile = pipe.start(cfg);
    auto sensor = profile.get_device().first<rs2::depth_sensor>();
    sensor.set_option(rs2_option::RS2_OPTION_VISUAL_PRESET,rs2_rs400_visual_preset::RS2_RS400_VISUAL_PRESET_HIGH_ACCURACY);


    //Add desired streams to configuration
    
    
    //cfg.enable_stream(RS2_STREAM_INFRARED,  color_img_width, color_img_height, RS2_FORMAT_Y8, 60);
    //cfg.enable_stream(RS2_STREAM_DEPTH,     color_img_width, color_img_height, RS2_FORMAT_Z16, 60);
    
    
    // cfg.enable_stream(RS2_STREAM_COLOR, color_img_width, color_img_height, RS2_FORMAT_BGR8, 60);

    // //  cfg_color.enable_stream(RS2_STREAM_COLOR, color_img_width, color_img_height, RS2_FORMAT_BGR8, 60);
    // //Instruct pipeline to start streaming with the requested configuration
    // auto profile=pipe.start(cfg);
    // auto sensor=profile.get_device().first<rs2::depth_sensor>();
    // sensor.set_option(rs2_option::RS2_OPTION_VISUAL_PRESET,rs2_rs400_visual_preset::RS2_RS400_VISUAL_PRESET_HIGH_ACCURACY);
    // pipe.stop();

    // cfg.enable_stream(RS2_STREAM_INFRARED,  color_img_width, color_img_height, RS2_FORMAT_Y8, 60);
    // cfg.enable_stream(RS2_STREAM_DEPTH,     color_img_width, color_img_height, RS2_FORMAT_Z16, 60);
    // pipe.start(cfg);

    
    // spat.set_option(RS2_OPTION_HOLES_FILL, 5);
    
    
    // // If the demo is too slow, make sure you run in Release (-DCMAKE_BUILD_TYPE=Release)
    // // but you can also increase the following parameter to decimate depth more (reducing quality)
    // dec.set_option(RS2_OPTION_FILTER_MAGNITUDE, 2);
    // // Define transformations from and to Disparity domain
        for(int i = 0; i < 5; i++)
    {
        //Wait for all configured streams to produce a frame
        auto data = pipe.wait_for_frames();
    }

    return 0;
}

int RealsenseInterface::init(int width, int height){
    color_img_height = height;
    color_img_width = width;
    depth_img_height = height;
    depth_img_width = width;
    int statue  = init();
    isOpen = true;
    if(statue == 0) start();
    return  statue; 
}
int RealsenseInterface::readImg(){
    try{
        data = pipe.wait_for_frames();
        rs2::frame color = data.first(RS2_STREAM_INFRARED);
        rs2::frame depth = data.get_depth_frame();
        const int w = depth.as<rs2::video_frame>().get_width();
        const int h = depth.as<rs2::video_frame>().get_height();
        Mat color_tmp(Size(color_img_width, color_img_height),CV_8UC1,(void*)color.get_data(),Mat::AUTO_STEP);
        Mat depth_tmp(Size(w, h),CV_16UC1,(void*)depth.get_data(),Mat::AUTO_STEP);
        pthread_mutex_lock(&imgMutex);
        color_tmp.copyTo(color_img);//写入color_img,加锁
        depth_tmp.copyTo(depth_img);
        pthread_mutex_unlock(&imgMutex);
        isColorImgUpdate = true;
        isDepthImgUpdate = true;
        return EXIT_SUCCESS;
    }
    catch (const rs2::error & e)
    {
        std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}


int RealsenseInterface::getColorImg(Mat &img){
    if(!isColorImgUpdate){
        //等待100ms
        int timeCounter=0;
        while(!isColorImgUpdate&&timeCounter<100){
            usleep(1000);//1ms等待
            timeCounter++;
        }
        if(!isColorImgUpdate){
            return -3;//更新超时
        }
    }
    pthread_mutex_lock(&imgMutex);
    color_img.copyTo(img);//读mImg,加锁
    pthread_mutex_unlock(&imgMutex);
    if(!img.empty()&&(img.cols==color_img_width)&&(img.rows==color_img_height)){
        isColorImgUpdate= false;
        return 0;
    } else{
        return -1;
    }

}

int RealsenseInterface::getDepthImg(Mat &img){
    if(!isDepthImgUpdate){
        //等待100ms
        int timeCounter=0;
        while(!isDepthImgUpdate&&timeCounter<100){
            usleep(1000);//1ms等待
            timeCounter++;
        }
        if(!isDepthImgUpdate){
            return -3;//更新超时
        }
    }
    pthread_mutex_lock(&imgMutex);
    depth_img.copyTo(img);//读mImg,加锁
    pthread_mutex_unlock(&imgMutex);
    if(!img.empty()&&(img.cols==depth_img_width)&&(img.rows==depth_img_height)){
        isDepthImgUpdate= false;
        return 0;
    } else{
        return -1;
    }

}

void RealsenseInterface::run(){
    while(true){
        readImg();
    }
}