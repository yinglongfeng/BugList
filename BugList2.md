# BugList  2019/12

### 1 

error :   could not find openssl

solution: sudo apt install libssl-dev.

### 2

error: nvcc fatal   : Option '--generate-code arch=', missing code cuda 10

solution:   CUDA_ARCH := #-gencode arch=compute_20,code=sm_20 \
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

error: caffe/proto/caffe.pb.h: No such file or directory

solution:  protoc src/caffe/proto/caffe.proto --cpp_out=.
           sudo mkdir include/caffe/proto
           sudo mv src/caffe/proto/caffe.pb.h include/caffe/proto

### 4

error: 编译openpose时可能遇到的问题
提示找不到caffe/proto/caffe.pb.h，导致编译失败。

solution： 在openpose/3rdparty/caffe/目录下，终端操作：
          caffe$ protoc src/caffe/proto/caffe.proto --cpp_out=.
          caffe$ mkdir include/caffe/proto
          caffe$ mv src/caffe/proto/caffe.pb.h include/caffe/proto/

### 5

error: 编译完成后还可能遇到的问题 F0704 14:27:12.379647 5860 upgrade_proto.cpp:97] Check failed: ReadProtoFromBinaryFile(param_file, param) Failed to parse NetParameter file: models/pose/body_25/pose_iter_584000.caffemodel
Check failed: ReadProtoFromBinaryFile(param_file, param) Failed to parse NetParameter file: models/pose/body_25/pose_iter_584000.caffemodel

solution: 

method one: 

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
error: opencv-contrib-python安装

solution: conda remove opencv
         conda install -c menpo opencv
         pip install --upgrade pip
         pip install opencv-contrib-python

### 7 

error: ValueError: invalid literal for int() with base 10 ""

solution:
	 try:
            skeleton_sequence['numFrame'] = int(ss)
        except:
            print(file)
	delete the files S017C002P008R002A013.skeleton and S016C003P039R001A051.skeleton

    mmskl configs/recognition/st_gcn_aaai18/ntu-rgbd-xsub/test.yaml

### 8

error: Error: OpenPose library could not be found. Did you enable `BUILD_PYTHON` in CMake and have this Python script in the right folder?

solution: 
	PYTHON_EXECUTABLE=/home/fyl/anaconda3/envs/st-gcn/bin/python3.7
	PYTHON_LIBRARY=/home/fyl/anaconda3/envs/st-gcn/lib/libpython3.7m.so
	in cmake-gui add install pybind et
