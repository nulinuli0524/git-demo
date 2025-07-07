cmake_minimum_required(VERSION 3.10)
project(gs_pclm)

add_library(gs_pclm SHARED gs_pclm.cpp)

# 输出名(.z.so)
set_target_properties(gs_pclm PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "gs_pclm.z"
  SUFFIX ".so"
)

# Node-API 头
target_include_directories(gs_pclm PRIVATE /usr/include/node)

# 把 libnapi.so 链接进来，否则 Init 的符号都不在 so 里
find_library(NAPI_LIB napi HINTS /usr/lib /usr/lib64 /usr/local/lib)
if(NAPI_LIB)
  target_link_libraries(gs_pclm PRIVATE ${NAPI_LIB})
endif()
