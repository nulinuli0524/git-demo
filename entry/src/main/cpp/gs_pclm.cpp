#include <node_api.h>
#include <cstdlib>
#include <string>

// 执行 shell 命令
static bool Exec(const std::string &cmd) {
  return std::system(cmd.c_str()) == 0;
}

// 真正的业务实现
static napi_value ConvertPdfToPclmImpl(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

  // 读取 inputPath
  size_t len;
  napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
  std::string input(len + 1, '\0');
  napi_get_value_string_utf8(env, argv[0], &input[0], len + 1, nullptr);

  // 读取 outputPath
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

// 这个符号是 N-API loader 查找的入口，必须导出
extern "C" __attribute__((visibility("default")))
napi_value napi_register_module_v1(napi_env env, napi_value exports) {
  napi_value fn;
  napi_create_function(
    env,
    "convertPdfToPclm",
    NAPI_AUTO_LENGTH,
    ConvertPdfToPclmImpl,
    nullptr,
    &fn
  );
  napi_set_named_property(env, exports, "convertPdfToPclm", fn);
  return exports;
}
