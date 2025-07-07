cmake_minimum_required(VERSION 3.10)
project(gs_pclm)

add_library(gs_pclm SHARED gs_pclm.cpp)

# 输出名： libgs_pclm.z.so
set_target_properties(gs_pclm PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "gs_pclm.z"
  SUFFIX ".so"
)
