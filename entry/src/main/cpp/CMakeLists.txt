cmake_minimum_required(VERSION 3.10)
project(gs_pclm)

# 编译生成 libgs_pclm.z.so
add_library(gs_pclm SHARED gs_pclm.cpp)

# 强制输出名为 libgs_pclm.z.so
set_target_properties(gs_pclm PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "gs_pclm.z"
  SUFFIX ".so"
)
