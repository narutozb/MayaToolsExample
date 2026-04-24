# 新增命令与节点的标准作业流程

这份文档面向日常开发人员，用于说明如何在当前模板中新增功能。

## 新增一个命令时

以 `sampleCommand` 为例。

### 1. 创建文件

在目标插件目录下新增：

- `include/sample_command.h`
- `src/sample_command.cpp`

### 2. 修改插件的 `CMakeLists.txt`

把新文件加入 `TARGET_SOURCES`。

### 3. 修改 `plugin_features.cpp`

把命令加入 `COMMAND_ENTRIES`。

### 4. 重新配置与构建

```bat
cmake --preset vs2022-maya2026
cmake --build --preset build-maya2026-debug
```

## 新增一个节点时

以 `sampleNode` 为例。

### 1. 创建文件

- `include/sample_node.h`
- `src/sample_node.cpp`

### 2. 在头文件中准备最小接口

- `TYPE_ID`
- `creator()`
- `initialize()`
- `compute()`
- 静态属性 `MObject`

### 3. 修改插件的 `CMakeLists.txt`

把文件加入 `TARGET_SOURCES`。

### 4. 修改 `plugin_features.cpp`

把节点加入 `NODE_ENTRIES`。

## 不要直接做的事情

- 不要把注册逻辑散落到 `plugin_main.cpp`
- 不要只把文件加到 VS 过滤器里而不改 `CMakeLists.txt`
- 不要跳过 `TYPE_ID` 规划

## 推荐检查点

- 头文件是否在 `include/`
- 源文件是否在 `src/`
- `TARGET_SOURCES` 是否已经加入
- `plugin_features.cpp` 是否已经注册
- 构建产物是否进入 `out/maya2026/Debug` 或 `Release`
