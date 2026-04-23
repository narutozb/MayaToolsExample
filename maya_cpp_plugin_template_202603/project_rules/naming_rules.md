# 命名规则

## 1. 目录命名

- 插件目录：小写蛇形命名，例如 `hello_world_mll`
- 公共模块目录：小写蛇形命名，例如 `shared`
- CMake 模块目录：`cmake`

## 2. 文件命名

- 插件入口：`plugin_main.cpp`
- 命令类：`xxx_command.h/.cpp`
- 节点类：`xxx_node.h/.cpp`
- 工具类：`xxx_util.h/.cpp`

## 3. C++ 类型命名

- 类名：大驼峰，例如 `HelloCommand`
- 函数名：小驼峰，例如 `createSyntax`
- 常量：全大写下划线，例如 `PLUGIN_VENDOR`

## 4. Maya 命令命名

- 对外命令名保持简短且稳定，例如 `helloCmd`
- 不要频繁改动命令名，避免影响脚本侧调用

## 5. 构建 Target 命名

- 与插件目录保持一致，例如 `hello_world_mll`
- 一个插件一个 target，不要复用 target 名
