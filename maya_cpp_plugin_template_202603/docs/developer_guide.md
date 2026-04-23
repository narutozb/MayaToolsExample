# 面向开发者的日常开发指南

## 1. 目标

本指南用于帮助开发者尽快进入 Maya 2026.3 C++ 插件开发状态，并完成最基本的日常工作：

- 初始化开发环境
- 生成工程
- 新建插件文件
- 构建 mll
- 在 Maya 中加载测试

---

## 2. 环境准备

需要准备以下环境：

- Maya 2026.3
- Visual Studio 2022
- CMake 3.24+
- Windows x64

Visual Studio 建议安装：

- Desktop development with C++
- MSVC v143
- Windows 10/11 SDK
- CMake support

---

## 3. 初始化环境

### 3.1 设置 Maya 安装路径

在命令行中设置：

```bat
set MAYA_LOCATION=C:\Program Files\Autodesk\Maya2026
```

也可以设置为系统环境变量，避免每次重复输入。

### 3.2 进入模板目录

```bat
cd path\to\MayaToolsExample\maya_cpp_plugin_template_202603\template
```

### 3.3 生成 Visual Studio 工程

```bat
cmake -S . -B build\maya2026_vs2022 -G "Visual Studio 17 2022" -A x64
```

### 3.4 构建插件

```bat
cmake --build build\maya2026_vs2022 --config Debug
```

构建完成后，可以在输出目录找到 `.mll`。

---

## 4. 日常开发流程

推荐日常流程如下：

1. 拉取最新代码
2. 打开生成的 Visual Studio 工程
3. 在对应插件目录下新增头文件和 cpp
4. 更新插件自己的 `CMakeLists.txt`
5. 编译 Debug
6. 进入 Maya 做加载测试
7. 验证通过后再提交

---

## 5. 如何新增一个命令类

以 `hello_world_mll` 为例：

### 5.1 新建头文件

放到：

```text
plugins/hello_world_mll/include/
```

### 5.2 新建 cpp

放到：

```text
plugins/hello_world_mll/src/
```

### 5.3 在插件入口中注册

通常在 `plugin_main.cpp` 中：

- 初始化插件
- 注册命令或节点
- 反初始化时注销

### 5.4 更新 CMakeLists.txt

确保新文件被加入 target。

---

## 6. 如何在 Maya 中测试

### 6.1 手动加载

在 Maya Script Editor 中执行：

```python
import maya.cmds as cmds
cmds.loadPlugin(r"C:/path/to/hello_world_mll.mll")
cmds.helloCmd()
```

### 6.2 使用模板自带脚本

可以运行：

```python
exec(open(r"C:/path/to/load_hello_plugin.py", "r").read())
```

再调用：

```python
import maya.cmds as cmds
cmds.helloCmd()
```

---

## 7. 日常开发时的注意事项

### 7.1 不要把所有逻辑写进 plugin_main.cpp

`plugin_main.cpp` 只负责：

- initializePlugin
- uninitializePlugin
- 注册与注销

实际逻辑请放到独立类中。

### 7.2 新文件命名要明确

建议：

- 命令类：`xxx_command.h/.cpp`
- 节点类：`xxx_node.h/.cpp`
- 工具类：`xxx_util.h/.cpp`

### 7.3 头文件依赖尽量收敛

不要在头文件中无必要地 include 大量 Maya 头文件，能前置声明就前置声明。

### 7.4 改代码前先看影响范围

特别是修改以下内容时：

- 公共 cmake
- shared 公共代码
- 插件输出目录
- 插件入口注册逻辑

这些改动通常会影响多个插件。

---

## 8. Debug 与 Release 的使用建议

### Debug

用于：

- 本地调试
- 命令行为验证
- 查看错误输出

### Release

用于：

- 提交测试版本
- 对外发布
- 与部署脚本配合

不要把 Debug 产物直接当成发布产物。

---

## 9. 新增插件时的推荐做法

当需要新建一个插件时：

1. 复制 `plugins/hello_world_mll/`
2. 修改目录名
3. 修改 `CMakeLists.txt`
4. 修改 target 名称
5. 修改插件入口中的厂商名、版本号、命令名
6. 在根 `CMakeLists.txt` 中注册新子目录

不要直接在旧插件中堆叠完全无关的功能。

---

## 10. Maya 版本升级时开发者需要做什么

当项目增加新的 Maya 版本支持时，开发者要重点验证：

- 是否能成功生成工程
- 是否能成功编译
- 是否能在 Maya 中成功加载
- 命令和节点是否能正常执行
- 是否出现库链接错误或头文件兼容问题

发现问题后，要把差异记录到文档中，而不是只在本地修改。

---

## 11. 最小可执行建议

如果你是第一次接手这个项目，先只做这三件事：

1. 让模板编译成功
2. 在 Maya 中成功加载 `hello_world_mll`
3. 成功执行 `helloCmd`

只要这三步跑通，后续再增加节点、命令和工具类就会顺畅很多。
