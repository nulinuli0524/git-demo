#include <node_api.h>
#include <cstdlib>
#include <string>

// 执行 shell 命令，返回 true 表示成功
static bool Exec(const std::string &cmd) {
  return (std::system(cmd.c_str()) == 0);
}

// convertPdfToPclm(inputPdfPath, outputPclmPath) -> boolean
napi_value ConvertPdfToPclm(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value argv[2];
  napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

  // 读取第一个参数：input PDF 路径
  size_t len;
  napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
  std::string input(len + 1, '\0');
  napi_get_value_string_utf8(env, argv[0], &input[0], len + 1, nullptr);

  // 读取第二个参数：输出 PCLm 路径
  napi_get_value_string_utf8(env, argv[1], nullptr, 0, &len);
  std::string output(len + 1, '\0');
  napi_get_value_string_utf8(env, argv[1], &output[0], len + 1, nullptr);

  // 调用 gs 生成 PCLm，-q: 静默；-dNOPAUSE -dBATCH: 非交互
  std::string cmd = "./gs -q -dNOPAUSE -dBATCH -sDEVICE=pclm"
    + std::string(" -sOutputFile=\"") + output + "\" \"" + input + "\"";
  bool ok = Exec(cmd);

  napi_value result;
  napi_get_boolean(env, ok, &result);
  return result;
}

napi_value Init(napi_env env, napi_value exports) {
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

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
