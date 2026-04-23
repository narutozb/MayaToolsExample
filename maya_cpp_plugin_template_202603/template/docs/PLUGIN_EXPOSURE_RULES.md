# 命令、节点与其他接口的曝露规则

为了让长期项目可维护，建议每个插件都使用固定的曝露入口文件。

## 规则

每个插件目录下都应至少有以下文件：

- `src/plugin_main.cpp`
- `include/plugin_features.h`
- `src/plugin_features.cpp`

## 职责划分

### plugin_main.cpp

只负责：

- `initializePlugin`
- `uninitializePlugin`
- 调用 `registerPluginFeatures()`
- 调用 `unregisterPluginFeatures()`

不要把具体命令和节点注册逻辑散落在 `plugin_main.cpp` 中。

### plugin_features.h / plugin_features.cpp

这两个文件就是“曝露接口文件”。

它们负责：

- 统一声明本插件要向 Maya 注册的命令
- 统一声明本插件要向 Maya 注册的节点
- 后续如果要增加 context、data、draw override 等接口，也统一在这里管理

## 推荐写法

- 每个命令和节点仍然保留自己的 `.h/.cpp`
- `plugin_features.cpp` 只做聚合与注册
- `shared/include/maya_plugin_manifest.h` 提供公共注册辅助函数

## 当前模板中的例子

### hello_world_mll

- `helloCmd`
- `echoTextCmd`
- `addValueNode`

### scene_tools_mll

- `mayaVersionCmd`
- `listSelectionCmd`
- `clampValueNode`

## 这样设计的好处

1. 入口文件稳定
2. 新人更容易定位“这个插件到底注册了什么”
3. 后续增加功能时不会把 `plugin_main.cpp` 改得越来越乱
4. 多插件长期维护时，结构统一
