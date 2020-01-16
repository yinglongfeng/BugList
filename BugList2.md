# BugList  2019/12 

### Thema about pose estimation

### 1

##### error :   

could not find openssl

##### solution: 

sudo apt install libssl-dev.

### 2

##### error: 

nvcc fatal:

 Option '--generate-code arch=', missing code cuda 10

##### solution:   

CUDA_ARCH := #-gencode arch=compute_20,code=sm_20 \
                #-gencode arch=compute_20,code=sm_21 \
                -gencode arch=compute_30,code=sm_30 \
                -gencode arch=compute_35,code=sm_35 \
                -gencode arch=compute_50,code=sm_50 \
                -gencode arch=compute_52,code=sm_52 \
                -gencode arch=compute_60,code=sm_60 \
                -gencode arch=compute_61,code=sm_61 \
                -gencode arch=compute_61,code=compute_61
            cuda 10.2 nvidia-driver 440

### 3

##### error: 

caffe/proto/caffe.pb.h: No such file or directory

##### solution:

           # In the directory you installed Caffe to

           protoc src/caffe/proto/caffe.proto --cpp_out=.

           sudo mkdir include/caffe/proto

           sudo mv src/caffe/proto/caffe.pb.h include/caffe/proto

### 4

##### error: 

编译openpose时可能遇到的问题

提示找不到caffe/proto/caffe.pb.h，导致编译失败。

##### solution： 

在openpose/3rdparty/caffe/目录下，终端操作：

          caffe$ protoc src/caffe/proto/caffe.proto --cpp_out=.
          
          caffe$ mkdir include/caffe/proto

          caffe$ mv src/caffe/proto/caffe.pb.h include/caffe/proto/

### 5

##### error: 

编译完成后还可能遇到的问题 F0704 14:27:12.379647 5860 upgrade_proto.cpp:97] Check failed: ReadProtoFromBinaryFile(param_file, param) Failed to parse NetParameter file: models/pose/body_25/pose_iter_584000.caffemodel
Check failed: ReadProtoFromBinaryFile(param_file, param) Failed to parse NetParameter file: models/pose/body_25/pose_iter_584000.caffemodel

##### solution:

##### method one:

出现上述错误，不是你项目编译有问题，也不是caffe编译有问题，仅仅是caffe模型没有下载完全！！！需要重新下载！！

method two(my solution):

(1) From memory remove clip_layer.hpp and clip_layer.cpp from caffe_root/src/caffe/layers.

(2) In caffe_root/src/caffe/layers/clip_layer.cu comment out the include and the two templates and the instantiate. Comment out the include in caffe_root/src/caffe/layer_factory.cpp.

(3) Then in src/caffe/proto/caffe.proto comment out the ClipParameter message and the optional clipparameter.

// optional ClipParameter clip_param = 148;
...
//message ClipParameter {

// required float min = 1;

// required float max = 2;

//}

(4) then cd /<caffe_root> and "make clean" and then "make -j8"

(5) Ok,now you can go to /<openpose_root> and run:

./build/examples/openpose/openpose.bin --video examples/media/video.avi

### 6

##### error: 
opencv-contrib-python安装

##### solution:

        conda remove opencv

         conda install -c menpo opencv

         pip install --upgrade pip

         pip install opencv-contrib-python

### 7

##### error: 

ValueError: invalid literal for int() with base 10 ""

##### solution:
	 try:
            skeleton_sequence['numFrame'] = int(ss)
        except:
            print(file)
	delete the files S017C002P008R002A013.skeleton and S016C003P039R001A051.skeleton

    mmskl configs/recognition/st_gcn_aaai18/ntu-rgbd-xsub/test.yaml

### 8

error: Error: OpenPose library could not be found. Did you enable `BUILD_PYTHON` in CMake and have this Python script in the right folder?

solution:

    ## 1
	PYTHON_EXECUTABLE=/home/fyl/anaconda3/envs/st-gcn/bin/python3.7
	
    PYTHON_LIBRARY=/home/fyl/anaconda3/envs/st-gcn/lib/libpython3.7m.so

    ## 2
     If you run `make install` (default path is `/usr/local/python` for Ubuntu), you can also access the OpenPose/python module from there. This will install OpenPose and the python library at your desired installation path. Ensure that this is in your python path in order to use it.
    
    sys.path.append('/usr/local/python')

	## 3
    in cmake-gui add install pybind et

!!! you should run the code $ python openpose_python.py $ in build/examples/tutorial_api_python/ file instead of  examples/tutorial_api_python/

### 9 

##### error: 
make caffe error:  undefined reference to 'caffe::ReadIMageToDatum....'

##### solution:
    清除 /usr/lib/libcaffe.so 这个是之前安装的，有很大的干扰项

##### error：
 libprotobuf 2.6.1 may confict with libprotobuf 3

##### solution：
只要保留一个就可以了，这个问题不大的

##### error: 
licudart.so.10.0 can not open shared object file: no such file or directory

##### solution: 
        export PATH = $PATH:/usr/local/cuda-10.0/bin

          export LD_LIBRARY_PATH=$ ...

          export LIBRARY_PATH = $...

          add them on bashrc file

##### error:

CMake Error: The following variables are used in this project, but they are set to NOTFOUND.
Please set them or make sure they are set and tested correctly in the CMake files:
CUDA_cublas_device_LIBRARY (ADVANCED)
    linked by target "caffe" in directory /home/fyl/source_code/caffe/src/caffe

##### solution:

update cmake version with anaconda


##### error:

fatal error: google/protobuf/port_def.inc: No such file or directory

#### solution:

try to install the newest version of protobuf(3.10)

##### error:

外星人台式机重装系统以后没有了wifi

##### solution:

在只最后一行添加

blacklist nouneau

删除之前添加的

blacklist nouveau

options nouveau modeset=0


### 10

##### error

FATAL ERROR: dynlink_nvcuvid.h: no such file or directory

##### solution

during cmake, add cmake -D BUILD_opencv_cudacodec=OFF


### 11

##### error:


/home/ubuntu/anaconda3/envs/op/lib/libopencv_objdetect.so.3.3.2: undefined reference to std::thread::_State::~_State()@GLIBCXX_3.4.22

##### solution:

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-7 g++-7

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7

### 12

##### error:

undefined reference to `op::Array<float>::toString[abi:cxx11]() const'

##### solution:

make clean
sudo make -j10 in openpose/build file

### 13  A problem that has perfused me for a week

##### error：

fatal error: google/protobuf/port_def.inc: No such file or directory

#### solution：

(1） do not install protobuf 3.11

(2) conda install protobuf=3.10

(3) try to use sudo
    sudo make all -j5

(4) install cmake 3.15 from source instead of by conda

(5) copy the complied right folder to it

### 14

##### error:

include/caffe/proto/caffe.pb.h:17:2: error: #error This file was generated by an older version of protoc which is
 #error This file was generated by an older version of protoc which is

##### solution:

in openpose cmake-gui, change opencv lib from anaconda3/envs/op//share/OpenCV/ to usr/share/OpenCV



