cmake_minimum_required(VERSION 3.10)
project(gs_pclm)

# 打开默认可见性
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)

# 生成共享库
add_library(gs_pclm SHARED gs_pclm.cpp)

# 输出名 libgs_pclm.z.so
set_target_properties(gs_pclm PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "gs_pclm.z"
  SUFFIX ".so"
)

# Node-API 头
target_include_directories(gs_pclm PRIVATE /usr/include/node)

# 链接 N-API 库
find_library(NAPI_LIB napi HINTS /usr/lib /usr/lib64 /usr/local/lib)
if(NAPI_LIB)
  target_link_libraries(gs_pclm PRIVATE ${NAPI_LIB})
endif()
