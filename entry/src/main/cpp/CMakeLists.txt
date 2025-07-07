cmake_minimum_required(VERSION 3.10)
project(gs_pclm)

add_library(gs_pclm SHARED gs_pclm.cpp)

# 强制输出名为 libgs_pclm.z.so
set_target_properties(gs_pclm PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "gs_pclm.z"
  SUFFIX ".so"
)

# ─── 新增开始 ────────────────────────────────────────────
# 把系统安装的 Node.js N-API 头文件目录加入
target_include_directories(gs_pclm PRIVATE
  /usr/include/node    # Ubuntu 下 libnode-dev 默认路径
)
# ─── 新增结束 ────────────────────────────────────────────
