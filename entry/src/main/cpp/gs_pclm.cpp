#include <node_api.h>
#include <cstdlib>
#include <string>

// 如果 NODE_GYP_MODULE_NAME 没定义，就用 gs_pclm
#ifndef NODE_GYP_MODULE_NAME
#define NODE_GYP_MODULE_NAME gs_pclm
#endif

static bool Exec(const std::string &cmd) {
  return std::system(cmd.c_str()) == 0;
}

napi_value ConvertPdfToPclm(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

  // 读 inputPdfPath
  size_t len;
  napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
  std::string input(len + 1, '\0');
  napi_get_value_string_utf8(env, argv[0], &input[0], len + 1, nullptr);

  // 读 outputPclmPath
  napi_get_value_string_utf8(env, argv[1], nullptr, 0, &len);
  std::string output(len + 1, '\0');
  napi_get_value_string_utf8(env, argv[1], &output[0], len + 1, nullptr);

  // 调用同目录下的 gs
  std::string cmd = "./gs -q -dNOPAUSE -dBATCH -sDEVICE=pclm"
    + std::string(" -sOutputFile=\"") + output + "\" \"" + input + "\"";
  bool ok = Exec(cmd);

  napi_value result;
  napi_get_boolean(env, ok, &result);
  return result;
}

// 这个宏会自动用 NODE_GYP_MODULE_NAME 注册 Init
NAPI_MODULE_INIT() {
  napi_value fn;
  napi_create_function(env,
                       "convertPdfToPclm",
                       NAPI_AUTO_LENGTH,
                       ConvertPdfToPclm,
                       nullptr,
                       &fn);
  napi_set_named_property(env, exports, "convertPdfToPclm", fn);
  return exports;
}
