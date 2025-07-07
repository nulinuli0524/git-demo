cmake_minimum_required(VERSION 3.10)
project(gs_pclm)

# 定义共享库目标，源码文件为 gs_pclm.cpp
add_library(gs_pclm SHARED gs_pclm.cpp)

# 强制输出名为 libgs_pclm.z.so（HarmonyOS 识别 .z.so）
set_target_properties(gs_pclm PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "gs_pclm.z"
  SUFFIX ".so"
)

# 指定 Node.js N-API 头文件目录（Ubuntu 上 install libnode-dev 后的路径）
target_include_directories(gs_pclm PRIVATE
  /usr/include/node
)
