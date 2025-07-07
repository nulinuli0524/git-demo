cmake_minimum_required(VERSION 3.10)
project(gs_pclm)

# 生成共享库
add_library(gs_pclm SHARED gs_pclm.cpp)

# 强制输出名 libgs_pclm.z.so
set_target_properties(gs_pclm PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "gs_pclm.z"
  SUFFIX ".so"
  CXX_VISIBILITY_PRESET default
  VISIBILITY_INLINES_HIDDEN OFF
)

# Node-API 头文件目录（由 libnode-dev 提供）
target_include_directories(gs_pclm PRIVATE /usr/include/node)
