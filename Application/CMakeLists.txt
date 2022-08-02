set(OpenCV_DIR "C:/opencv/build")
include_directories("C:/opencv/build/include")

# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)
# プロジェクト名を使用する言語を設定
project(Project)

find_package(OpenCV REQUIRED)

# a.outという実行ファイルを作成
add_executable(Project main.cpp capture.cpp detect.cpp viewer.cpp ringBuffer.cpp)


target_link_libraries(Project ${OpenCV_LIBS})