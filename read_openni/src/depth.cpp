
#include <iostream>  
#include <OpenNI.h>  
#include <opencv2/photo.hpp>  
#include <opencv2/highgui.hpp>  
  
using namespace std;  
using namespace openni;
using namespace cv;
  
// int main(int argc,char **argv)
int main()
{  
    // //定义oni文件中视频的总帧数以及得到的图片的保存目录  
    int total = 0;  
    char* imagefile = "/home/anotherday/data/oni/depth";  
    Status rc = STATUS_OK;
    cout<< * imagefile << endl;
    /*********************************************/
    // if(argc!=3){
    //     printf("error using FormatConverter!!\nexample usage:\nFormatConverter test.oni test.klg\n");
    //     return -1;
    // }
    //定义oni文件中视频的总帧数以及得到的图片的保存目录  
    // int total = 0;  
    /***********************************/
    //初始化OpenNI环境  
    openni::OpenNI::initialize();  
  
    //声明设备并打开oni文件  
    openni::Device fromonifile;  
    fromonifile.open("/home/anotherday/data/oni/both.oni"); 
    cout<< " open oni file " << endl;
  
    //声明控制对象，这对视频流的控制起到了关键作用  
    openni::PlaybackControl* pController = fromonifile.getPlaybackControl();  
  
    //声明视频流对象以及帧对象  
    openni::VideoStream streamDepth;
    openni::VideoStream streamColor; 
    openni::VideoFrameRef frameColor;  
    openni::VideoFrameRef frameDepth; 

    cout<< " here is the problem " << endl;
    cout<< fromonifile.hasSensor(openni::SENSOR_COLOR) << endl;
    cout<< fromonifile.hasSensor(openni::SENSOR_DEPTH) << endl;
  
    //验证是否有彩色传感器（是否有彩色视频）和建立与设备想关联的视频流  
    if(fromonifile.hasSensor(openni::SENSOR_COLOR))         //(openni::SENSOR_COLOR))  
    {         
        if( streamDepth.create( fromonifile, openni::SENSOR_DEPTH ) == openni::STATUS_OK  //)
            && 
            streamColor.create( fromonifile, openni::SENSOR_COLOR ) == openni::STATUS_OK )  
        {  
            cout<<"建立视频流成功"<<endl;  
        }  
        else  
        {  
            cerr<<"ERROR: 建立视频流没有成功"<<endl;  
            system("pause");  
            return -1;  
        }  
    }  
    else  
    {  
        cerr << "ERROR: 该设备没有彩色传感器" << endl;  
        system("pause");  
        return -1;  
    }  
    
    //建立显示窗口  
    namedWindow("Depth Image", CV_WINDOW_AUTOSIZE);
    // namedWindow("Color Image");

    // 获得最大深度值
    int iMaxDepth = streamDepth.getMaxPixelValue();
  
    //获取总的视频帧数并将该设备的速度设为-1以便能留出足够的时间对每一帧进行处理、显示和保存  
    total = pController->getNumberOfFrames(streamDepth);  
    pController->setSpeed(-1);  
  
// //开启视频流
// 设置深度图像视频模式
    VideoMode mModeDepth;
    // 分辨率大小
    mModeDepth.setResolution(320, 240);
    // 每秒30帧
    mModeDepth.setFps(10);
    // 像素格式
    mModeDepth.setPixelFormat(PIXEL_FORMAT_DEPTH_1_MM);

    streamDepth.setVideoMode(mModeDepth);
    
    streamDepth.start();
    streamColor.start();
    
    for (int i = 1;i <= total; ++ i)  
    {  
        //读取视频流的当前帧  
        // 读取数据流
        // 将深度数据转换成OpenCV格式
        streamDepth.readFrame(&frameDepth);
        const Mat mImageDepth(frameDepth.getHeight(), frameDepth.getWidth(), CV_16UC1, (void*)frameDepth.getData());
        Mat mScaledDepth, hScaledDepth;
        mImageDepth.convertTo(mScaledDepth, CV_8U, 255.0 / iMaxDepth);
            // 显示出深度图像
        cout<< " frameDepth.getHeight() " << frameDepth.getHeight() << endl;
        cout<<" depth max is " <<  iMaxDepth << endl;
        cv::imshow("Depth Image", mScaledDepth);
         //将每一帧按顺序帧保存到图片目录下  
        char imagefullname[255];  
        char imagenum[50];  
        sprintf(imagenum,"/%010d depth.png",i);  
        strcpy(imagefullname,imagefile);  
        strcat(imagefullname,imagenum);  
        cv::imwrite(imagefullname,mScaledDepth);  

         // color image 
        //读取视频流的当前帧  
        streamColor.readFrame(&frameColor);  
  
        cout<<"当前正在读的帧数是："<<frameColor.getFrameIndex()<<endl;  
        cout<<" sensor type : "<<frameColor.getSensorType()<<endl;  
        cout<<"当前的循环次数是：  "<<i<<endl;  
  
        //将帧保存到Mat中并且将其转换到BGR模式，因为在OpenCV中图片的模式是BGR  
        cv::Mat rgbImg(frameColor.getHeight(), frameColor.getWidth(), CV_8UC3, (void*)frameColor.getData());  
        cv::Mat bgrImg;  
        cvtColor(rgbImg, bgrImg, CV_RGB2BGR);  
  
        //将每一帧按顺序帧保存到图片目录下  
        // char imagefullname[255];  
        // char imagenum[50];  
        sprintf(imagenum,"/%010d.png",i);  
        strcpy(imagefullname,imagefile);  
        strcat(imagefullname,imagenum);  
        cv::imwrite(imagefullname,bgrImg);  
  
        // //显示当前帧  
        // cv::imshow("Image",bgrImg);  
        if (cv::waitKey(30) == 27)  
        {  
            break;  
        }  
    }  
  
    //销毁显示窗口  
    cv::destroyWindow("Image");   
  
    //关闭视频流  
    streamColor.destroy();  
  
    //关闭设备  
    fromonifile.close();  
  
    //关闭OpenNI  
    openni::OpenNI::shutdown();  
      
    return 0;  
}  
