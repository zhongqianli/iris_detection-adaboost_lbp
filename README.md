# iris_detection---虹膜检测

@(虹膜识别)[目标j检测]

## 开发环境
Linux、OpenCV、CMake

## 训练步骤
假设正样本位于images/pos.30x30，负样本位于images/neg，测试图像位于images/test

### 生成负样本描述文件
1-create_neg_desc_file.sh
```
image_dir_list=(
"images/neg"
)

echo "create neg.txt"

imagelist_file="neg.txt"
rm -rf $imagelist_file
touch $imagelist_file
for image_dir in ${image_dir_list[*]}
do
	find $image_dir -name "*" | grep -i -E "bmp|jpg|png" >> $imagelist_file
done

echo "finish."
```
	
### 生成正样本描述文件
2-create_pos_desc_file.sh
```
width=30
height=30

image_dir_list=(
"images/pos.30x30"
)

echo "create pos.txt"

imagelist_file="pos.txt"
rm -rf $imagelist_file
touch $imagelist_file
for image_dir in ${image_dir_list[*]}
do
	for imagepath in `find $image_dir -name "*" | grep -i -E "bmp|jpg|png"`
	do
		echo $imagepath 1 0 0 $width $height >> pos.txt
	done
done

echo "finish."
```
	
### 生成vec文件
3-run.opencv_createsamples.sh
```
sample_num=20
width=30
height=30
opencv_createsamples -info pos.txt -vec pos.vec -num $sample_num -w $width -h $height
```
	 
### 用opencv_traincascade训练模型
4-run.opencv_traincascade.LBP.sh
```
mkdir data_dir.lbp
pos_num=18
neg_num=54
threads_num=4
width=30
height=30
opencv_traincascade -data data_dir.lbp -vec pos.vec -bg neg.txt -numPos $pos_num -numNeg $neg_num -numStages 20 -precalcValBufSize 2048 -precalcIdxBufSize 2048 -numThreads $threads_num -featureType LBP -w $width -h $height
```

可以设置线程数，mem。训练可以中途停止的，下次开启时它会读取训练过程中保存的xml文件，接着进行上次未完成的训练。
	 
### 测试训练的分类器
cascade.detectMultiScale(gray, objects, 1.1, 3, CASCADE_FIND_BIGGEST_OBJECT, Size(10, 10), Size(40, 40));
需要根据使用的正样本大小，来确定Size大小。 		 

**CMakeLists.txt**


```
cmake_minimum_required( VERSION 2.8 )

project( test_cascade )

add_executable( ${PROJECT_NAME} main.cpp )

find_package( OpenCV REQUIRED )

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
```


**main.cpp**


```
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
  printf("%s <cascade file> <image>\n", argv[1]);
  }

  CascadeClassifier cascade;
  if(!cascade.load(argv[1]))
  {
  cout << "cascade load failed." << endl;
  return -1;
  }

  Mat image, gray;

  image = imread(argv[2], 1);

  if(!image.empty())
  {
  cvtColor(image, gray, CV_BGR2GRAY);
  vector<Rect> objects;
  cascade.detectMultiScale(gray, objects, 1.1, 3, CASCADE_FIND_BIGGEST_OBJECT, Size(10, 10), Size(40, 40));
  if(objects.size() == 1)
  rectangle(image, objects[0], Scalar(0,0,255));
  imwrite("image.bmp", image);
  cout << "finished." << endl;
  }
  else
  {
  cout << "no image" << endl;
  }
  return 0;
}
```
