# BugList

### 1 

cannot import cv2

conda install -c https://conda.anaconda.org/menpo opencv3

### 2 

 cAttributeError: 'NoneType' object has no attribute 'astype'

 change the image name from .png to .jpg

### 3
 
[[Node: save/Assign_37 = Assign[T=DT_FLOAT, _class=["loc:@model/encoder/Conv/weights"], use_locking=true, validate_shape=true, _device="/job:localhost/replica:0/task:0/cpu:0"](model/encoder/Conv/weights, save/RestoreV2_37)]]

add --do_stereo

### 4 

NotFoundError (see above for traceback): /media/anotherday/fyl/masterthesis/KITTI/data_scene_flowtraining/image_2/000000_10.jpg
	 [[Node: cond/ReadFile = ReadFile[_device="/job:localhost/replica:0/task:0/cpu:0"](cond/ReadFile/Switch:1)]]

chang the test image to jpg, because the filenames is training/image_2/000004_10.jpg training/image_3/000004_10.jpg

### 5 
>> import caffe
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/home/anotherday/anaconda3/envs/caffe27/lib/python2.7/site-packages/caffe/__init__.py", line 1, in <module>
    from .pycaffe import Net, SGDSolver, NesterovSolver, AdaGradSolver, RMSPropSolver, AdaDeltaSolver, AdamSolver, NCCL, Timer
  File "/home/anotherday/anaconda3/envs/caffe27/lib/python2.7/site-packages/caffe/pycaffe.py", line 13, in <module>
    from ._caffe import Net, SGDSolver, NesterovSolver, AdaGradSolver, \
ImportError: /home/anotherday/anaconda3/envs/caffe27/lib/python2.7/site-packages/caffe/../../../libcaffe.so.1.0.0: undefined symbol: _ZN7leveldb2DB4OpenERKNS_7OptionsERKSsPPS0_

SOLUTION: conda install -c defaults protobuf libprotobuf

### 6 

ValueError: The truth value of an array with more than one element is ambiguous. Use a.any() or a.all()

SOLUTION: change if image == NONE: to if image is NODE:


### 7
IOError: cannot identify image file 'test.ppm'

change "import Image" to "from PIL import Image"

=======
### 8 
in windows  
File "C:\Users\fyl\Anaconda3\envs\tf\lib\site-packages\tensorflow\python\training\saver.py", line 1717, in restore
    + compat.as_text(save_path))
ValueError: The passed save_path is not a valid checkpoint:

 SOLUTION: restore_path = args.checkpoint_path #.split(".")[0]

### 9
TypeError: __init__() got an unexpected keyword argument 'constraint'

Solution: change the tensorflow version from 1.2 to the newerst version
          just because the name is diff in different version of tf
### 10
    not_loaded.remove(v.op.name)
ValueError: list.remove(x): x not in list

??? not solved: add continue or break

### 11
    cuda out of memeory
SOLUTION: config = tf.ConfigProto(allow_soft_placement=True) 
          ## let use 70% memeory of gpu
          gpu_options=tf.GPUOptionis()
### 12 
    seg_map[masks[n_]> 0,:] = colorize(n_, color=FL.color)
IndexError: boolean index did not match indexed array along dimension 0; dimension is 480 but corresponding boolean dimension is 640


add  if num is 1 :
      seg_map[masks > 0,:] = colorize(num, color=FL.color)
    elif num > 1:
    in the maskrcnn inference.py  line 90

### 13 
 
   source env.sh or change name from segim to segimg
### 14  way to generate the ico_op.so
   
error:ldd icp_op.so i see the error like: undefined symbol: cublasDsyr2k_v2, version libcublas.so.9.0	(/usr/local/lib/libtensorflow_framework.so)
solve: 1)export PATH=/usr/local/cuda-9.0/bin${PATH:+:${PATH}}
       2)export LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}

       export PATH=/usr/local/cuda-9.0/bin${PATH:+:${PATH}}
       export LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}

### 15  way to generate the ico_op.so

error: undefined symbol: _ZN10tensorflow12OpDefBuilder3DocESs	(./icp_op.so)
solve: delete GLIBCXX_USE_CXX11_ABI=0 in cmakelist file

### 16  way to generate the ico_op.so

error: ImportError: dynamic module does not define init function (initicp_op)
solve: rename icp_op.so to Icp_op.so

### 17  way to generate the ico_op.so

(1) download file from https://github.com/tensorflow/models/issues/5168

(2) sudo apt install libpcl-dev (1.7.2 is fine)

(3) sudo apt install libeigen3-dev (eigen must > 3.3/ my version is 3.3.5)

(4) export PATH=/usr/local/cuda-9.0/bin${PATH:+:${PATH}}
    export LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}

(5) delete GLIBCXX_USE_CXX11_ABI=0 in cmakelist file
    modify the CMakeLists.txt like change the tensorflow include the path and so on

(6) ldd -r icp_op.so 
    find if something else is wrong

(7) 
     copy file libtensorflow_framework.so to /usr/local/lib/

(8) cd models/research/vid2depth/ops
    mkdir build
    cd  build

(9) cmake -DCMAKE_BUILD_TYPE=Release ..

(10) mv libicp_op.so ../Icp_op.so

### 18 bazel to generate the icp_op.so
 
bazel build -c opt ops/...

########## vid2depth add icp PCL #################################################################
(1)ERROR: /home/anotherday/vid2depth_git/new/vid2depth/WORKSPACE:29:1: name 'http_archive' is not defined
solve:  add load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive") IN WORKSPACE

(2)ERROR: name 'new_http_archive' is not defined
       Analysis of target '//ops:icp_op_kernel' failed; build aborted: no such package '@com_github_pointcloudlibrary_pcl//': The native new_http_archive rule is deprecated. load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive") for a drop-in replacement.
  
solve:  CHANGE bazel version to 0.22 --> 0.18 --> 0.11

(3)ERROR: /home/.cache/bazel/_bazel_yz/0a99992d99badecd9853941fabef3318/external/jpeg/BUILD:126:12: Illegal ambiguous match on configurable attribute "deps" in @jpeg//:jpeg:
@jpeg//:k8
@jpeg//:armeabi-v7a

ERROR: cannot find mex.h
solve: install linux version's matlab  not indeed
       delete matlab file in flann file  ( vid2depth/bazel-vid2depth/external/flann/.. matlab/)
       delete mpi file in flann ( vid2depth/bazel-vid2depth/external/flann/src/cpp/flann/mpi)

(4) error:boost/mpi/config.hpp:20:17: fatal error: mpi.h: No such file or directory

sudo apt install libopenmpi-dev
pip install mpi4py

change to #include "/usr/include/mpi/openmpi/ompi/mpi/cxx/exception.h"
change to #include <mpi/mpi.h>
change to #include "/usr/include/mpi/mpi.h" 
解决：将 mpi.h 改为绝对路径
#include "/opt/intel/compilers_and_libraries_2017.0.098/linux/mpi/intel64/include/mpi.h"
copy usr/include/boost and usr/include/mpi


(5)ERROR: /home/anotherday/vid2depth_git/new/vid2depth/ops/BUILD:10:1: C++ compilation of rule '//ops:icp_op_kernel' failed (Exit 1)
ops/icp_op_kernel.cc: In member function 'void IcpOp<T>::Compute(tensorflow::OpKernelContext*)':
ops/icp_op_kernel.cc:147:27: error: 'int64' has not been declared
                     this](int64 start_row, int64 limit_row) {

(6) ERROR: fatal error: mex.h: No such file or directory

export PATH=$PATH:/usr/local/MATLAB/R2019a/bin
sudo rm mex in usr/bin/

delete matlab file in flann file
delete mpi file in flann ( vid2depth/bazel-vid2depth/external/flann/src/cpp/flann/mpi)

(7) error:  error: bazel-out/k8-opt/bin/external/net_zlib_zlib/_objs/zlib/external/net_zlib_zlib/adler32.pic.o: multiple definition of 'adler32_combine64'
/usr/bin/ld.gold: bazel-out/k8-opt/bin/external/zlib_archive/_objs/zlib/external/zlib_archive/adler32.pic.o: previous definition here

delete one of them "delete adler32_combine64.pic.o" not sucessufully
solution: in /home/anotherday/vid2depth_git/new/vid2depth/bazel-vid2depth/external/net_zlib_zlib/BUILD file, 
          use # to comment the .c file name, for example: # adler32.c
(8) ERROR: could not load icp.o
solution: copy the icp_op.o to ops file
ERROR: undefined symbol: _ZTIN10tensorflow8OpKernelE
SOLUTION: 这是 因为在用g++编译代码的时候没用使用tensorflow_framework.so动态库造成的，在gcc+ 的参数中添加-L /usr/local/lib/python3.5(2.7)/dist-packages/tensorflow 
    export PATH=/usr/local/cuda-9.0/bin${PATH:+:${PATH}}
    export LD_LIBRARY_PATH=/usr/local/cuda-9.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
    delete GLIBCXX_USE_CXX11_ABI=0 in cmakelist file

    use ldd -r icp_op.so to find the reason

### 19 	
failed call to cuInit: CUDA_ERROR_UNKNOWN 
        tensorflow gpu can not work
   Solution:sudo apt install nvidia-modprobe
### 20
 return _setlocale(category, locale)locale.Error: unsupported locale setting
 sudo dpkg-reconfigure locales

### 21 
 GPU OUT OF MEMORY 
 QUEUE_SIZE = 2000 to QUEUE_SIZE = 20
 also change the tensorflow gpu session to allow growth

### 22 
ERROR: SyntaxError: Missing parentheses in call to 'print'
SOLUTION: change python 3.6 to python 2.6

### 23 read the oni file && cannot find openni.h

(1)  git clone https://github.com/occipital/OpenNI2.git

(2) make

(3) go to /Packaging

(4) conda activate caffe_python2.7

(5) ReleaseVersion.py x64

(6) go to /Final

(7) extract OpenNI-Linux-x64-2.2.tar.bz2 

(8) go into OpenNI-Linux-x64-2.2

(9) sudo ./install.sh

(10) cat OpenNIDevEnvironment >> ~/.bashrc
     source ~/.bashrc
(11) compile the openni file

### 24 
ERROR: usb interface is not supported In Xtion

solution: udo nano /etc/openni/GlobalDefaults.ini 
          comment it and it should work
           ;UsbInterface=2
           reboot
### 25
error:hdf5.h no such file or directory

solution: export CPATH="/usr/include/hdf5/serial/"
          in make file
          USER_LIBS= -L/usr/include/hdf5/serial/ -lhdf5

### 26 USE JI KE YUN to train the model

(1) cp data /input  cp sourcecode /input

(2) install pcl

conda install -c conda-forge pcl

(3) change the CMakeLists.txt the tensorflow path (conda info -e)

e.g.

usr/local/miniconda3/envs/dl/...

(4) build icp so file

(5) mv libicp_op.so ../Icp_op.so

(6) run the code 

e.g.

python train.py --logtostderr --checkpoint_dir /output/jikeyun_test/ --data_dir /input/data/ --batch_size 4 --img_height 192 --img_width 320 --icp_weight 0.1 --legacy_mode true
