PROJECT(CppBaseTest)
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# 支持C++11
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -O2 -std=c11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -O2 -std=c++11")
# 支持C++14, when gcc version > 5.1, use -std=c++14 instead of c++1y
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g -Wall -O2 -std=c++1y")

# set support C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

MESSAGE(STATUS "project source dir: ${PROJECT_SOURCE_DIR}")
SET(PATH_SRC_FILES ${PROJECT_SOURCE_DIR}/./../../demo/CppBaseTest)
MESSAGE(STATUS "path src files: ${PATH_SRC_FILES}")

# 指定头文件的搜索路径
INCLUDE_DIRECTORIES(${PATH_SRC_FILES})

# 递归查询所有匹配的文件:*.cpp
FILE(GLOB_RECURSE CPP_LIST ${PATH_SRC_FILES}/*.cpp)
FILE(GLOB_RECURSE C_LIST ${PATH_SRC_FILES}/*.c)
#MESSAGE(STATUS "cpp list: ${C_LIST}")

# 编译可执行程序
ADD_EXECUTABLE(CppBaseTest ${CPP_LIST} ${C_LIST})
# 用来为target添加需要链接的共享库，指定工程所用的依赖库，包括动态库和静态库
TARGET_LINK_LIBRARIES(CppBaseTest pthread)

