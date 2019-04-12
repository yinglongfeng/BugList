# BugList
## 1 cannot import cv2
conda install -c https://conda.anaconda.org/menpo opencv3
## 2 c AttributeError: 'NoneType' object has no attribute 'astype'
change the image name from .png to .jpg
### 3 [[Node: save/Assign_37 = Assign[T=DT_FLOAT, _class=["loc:@model/encoder/Conv/weights"], use_locking=true, validate_shape=true, _device="/job:localhost/replica:0/task:0/cpu:0"](model/encoder/Conv/weights, save/RestoreV2_37)]]
add --do_stereo
###4 NotFoundError (see above for traceback): /media/anotherday/fyl/masterthesis/KITTI/data_scene_flowtraining/image_2/000000_10.jpg
	 [[Node: cond/ReadFile = ReadFile[_device="/job:localhost/replica:0/task:0/cpu:0"](cond/ReadFile/Switch:1)]]

chang the test image to jpg, because the filenames is training/image_2/000004_10.jpg training/image_3/000004_10.jpg
