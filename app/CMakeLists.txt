cmake_minimum_required(VERSION 3.10)
project(dining_philosophers)

file(GLOB SRC_FILES *.cpp)
set(app_src ${SRC_FILES}  PARENT_SCOPE)
