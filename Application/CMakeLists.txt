# CMakeのバージョンを設定
cmake_minimum_required(VERSION 3.13)
# プロジェクト名を使用する言語を設定
project(test_cmake CXX)
# a.outという実行ファイルを作成
add_executable(a.out main.cpp capture.cpp detect.cpp viewer.cpp queue.cpp)
