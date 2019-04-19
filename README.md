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
in windows  
File "C:\Users\fyl\Anaconda3\envs\tf\lib\site-packages\tensorflow\python\training\saver.py", line 1717, in restore
    + compat.as_text(save_path))
ValueError: The passed save_path is not a valid checkpoint:

 SOLUTION: restore_path = args.checkpoint_path #.split(".")[0]
