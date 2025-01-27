## Lite.AI.ToolKit.Demo 🚀🚀🌟
Demos for how to use the shared libs of [Lite.AI.ToolKit](https://github.com/DefTruth/lite.ai.toolkit). Star 🌟👆🏻 this repo if it does any helps to you ~ 🙃🤪🍀

## Releases Lists.  
You can download the released built lib of Lite.AI.ToolKit and all the needed dependencies.  
* [lite.ai.toolkit.macos.v0.1.0](https://github.com/DefTruth/lite.ai.toolkit.demo/tree/main/releases/macos/v0.1.0)

## 1. MacOS's demo. 

* Clone this repo and run *build.sh*.
```shell
git clone --depth=1 https://github.com/DefTruth/lite.ai.toolkit.demo.git
```
```shell
cd lite.ai.toolkit.demo/macos # or cd lite.ai.toolkit.demo/releases/macos/v0.1.0 for specific version.
sh ./build.sh
```  
See [macos/CMakeLists.txt](macos/CMakeLists.txt) to figure out how to link the shared lib of Lite.AI.ToolKit correctly. The build.sh will build and test a demo of YoloV5, or you can build it manually like:  
```shell
#!/bin/bash
rm -rf examples/build
cd examples && mkdir build && cd build  && cmake ../.. && make -j1
echo "Testing Start ..."
./lite_yolov5
echo "Testing Successful !"
```   

* Object Detection Using YoloV5 through Lite.AI.ToolKit.  
```c++
#include "lite/lite.h"

static void test_lite()
{
  std::string onnx_path = "../hub/onnx/cv/yolov5s.onnx";
  std::string test_img_path = "../resources/test_lite_yolov5_1.jpg";
  std::string save_img_path = "../logs/test_lite_yolov5_1.jpg";

  auto *yolov5 = new lite::cv::detection::YoloV5(onnx_path);

  std::vector<lite::cv::types::Boxf> detected_boxes;
  cv::Mat img_bgr = cv::imread(test_img_path);
  yolov5->detect(img_bgr, detected_boxes);

  lite::cv::utils::draw_boxes_inplace(img_bgr, detected_boxes);
  cv::imwrite(save_img_path, img_bgr);
  std::cout << "YoloV5 Detected Boxes Num: " << detected_boxes.size() << std::endl;
  delete yolov5;
}

int main(__unused int argc, __unused char *argv[])
{
  test_lite();
  return 0;
}
```

* CMakeLists.txt configuration details.  

```cmake
cmake_minimum_required(VERSION 3.17)
project(lite.ai.toolkit.demo.macos)
set(CMAKE_CXX_STANDARD 11)

# link opencv.
set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/opencv/lib/cmake/opencv4)
find_package(OpenCV 4 REQUIRED)

# link onnxruntime.
set(ONNXRUNTIME_DIR ${CMAKE_SOURCE_DIR}/onnxruntime/)
set(ONNXRUNTIME_INCLUDE_DIR ${ONNXRUNTIME_DIR}/include)
set(ONNXRUNTIME_LIBRARY_DIR ${ONNXRUNTIME_DIR}/lib)
include_directories(${ONNXRUNTIME_INCLUDE_DIR})
link_directories(${ONNXRUNTIME_LIBRARY_DIR})

# link lite.ai.toolkit
set(LITEHUB_DIR ${CMAKE_SOURCE_DIR}/lite.ai.toolkit)
set(LITEHUB_INCLUDE_DIR ${LITEHUB_DIR}/include)
set(LITEHUB_LIBRARY_DIR ${LITEHUB_DIR}/lib)
include_directories(${LITEHUB_INCLUDE_DIR})
link_directories(${LITEHUB_LIBRARY_DIR})

# add your executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/examples/build)
add_executable(lite_yolov5 examples/test_lite_yolov5.cpp)
target_link_libraries(lite_yolov5 lite.ai.toolkit onnxruntime ${OpenCV_LIBS})  # link lite.ai.toolkit
```

* Building information:  
```shell
macos git:(main) ✗ sh ./build.sh      
...
[ 50%] Building CXX object CMakeFiles/lite_yolov5.dir/examples/test_lite_yolov5.cpp.o
[100%] Linking CXX executable lite_yolov5
[100%] Built target lite_yolov5
Testing Start ...
LITEORT_DEBUG LogId: ../hub/onnx/cv/yolov5s.onnx
=============== Input-Dims ==============
input_node_dims: 1
...
=============== Output-Dims ==============
Output: 0 Name: pred Dim: 0 :1
Output: 0 Name: pred Dim: 1 :25200
...
detected num_anchors: 25200
generate_bboxes num: 66
YoloV5 Detected Boxes Num: 5
Testing Successful !
```

* Then the output can be found at *examples/logs* dir:   
<div align='center'>
  <img src='macos/examples/logs/test_lite_yolov5_1.jpg' height="400px"  width="600px">
</div>  
  
