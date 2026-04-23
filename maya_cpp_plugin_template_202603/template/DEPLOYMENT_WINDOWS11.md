# Windows 11 部署说明

本说明面向使用本模板构建出来的 Maya C++ 插件，目标是把生成的 `.mll` 和必要的 Python 脚本部署到用户的 Windows 11 环境中，并确保用户可以在 Maya 2026.3 中正常加载。

当前模板采用的是 **最小可执行部署方案**：

- 插件文件部署到用户文档目录下的 Maya `plug-ins`
- 辅助 Python 脚本部署到用户文档目录下的 Maya `scripts`
- 用户通过 Plug-in Manager 或 Python 命令进行加载

这种方式的优点是：

- 简单直接
- 不依赖额外安装器
- 适合内部工具、测试版和早期长期项目
- 后续也容易迁移到 module 方式

---

## 1. 适用前提

用户机器需要满足以下条件：

- Windows 11 x64
- 已安装 Maya 2026.3
- 插件已经由开发侧成功构建
- 目标用户对自己的 Maya 用户目录有写入权限

默认用户目录通常类似于：

```text
C:\Users\<用户名>\Documents\maya\2026\
```

---

## 2. 当前模板的部署内容

本模板默认会部署以下内容：

### 2.1 mll 插件

来源：

```text
template/out/maya2026/Release/hello_world_mll.mll
```

目标：

```text
%USERPROFILE%\Documents\maya\2026\plug-ins\hello_world_mll.mll
```

### 2.2 Python 脚本

来源：

```text
template/scripts/load_hello_plugin.py
```

目标：

```text
%USERPROFILE%\Documents\maya\2026\scripts\load_hello_plugin.py
```

---

## 3. 推荐的部署顺序

推荐实际部署时按以下顺序进行：

1. 在开发机构建 Release 版本
2. 确认 `hello_world_mll.mll` 已生成
3. 运行模板自带的部署脚本
4. 在用户机启动 Maya 2026.3
5. 使用 Plug-in Manager 或 Python 命令加载插件
6. 执行命令验证功能

---

## 4. 使用模板自带脚本部署

模板目录内已经提供：

```text
deploy_to_windows11_user.bat
```

### 4.1 推荐做法

先构建 Release：

```bat
cmake -S . -B build\maya2026_vs2022 -G "Visual Studio 17 2022" -A x64
cmake --build build\maya2026_vs2022 --config Release
```

然后在 `template/` 目录下执行：

```bat
deploy_to_windows11_user.bat
```

脚本会自动：

- 检查 Release 版 `.mll` 是否存在
- 创建用户 Maya 的 `plug-ins` 目录
- 创建用户 Maya 的 `scripts` 目录
- 复制插件和脚本到目标位置

---

## 5. 用户侧加载方法

### 5.1 使用 Plug-in Manager

在 Maya 中打开：

- Windows
- Settings/Preferences
- Plug-in Manager

然后找到：

```text
hello_world_mll.mll
```

勾选：

- Loaded
- Auto load（如果希望下次自动加载）

### 5.2 使用 Python 加载

在 Maya Script Editor 中执行：

```python
import maya.cmds as cmds
cmds.loadPlugin("hello_world_mll.mll")
cmds.helloCmd()
```

### 5.3 使用部署后的脚本

在 Maya Script Editor 中执行：

```python
import load_hello_plugin
```

然后执行：

```python
import maya.cmds as cmds
cmds.helloCmd()
```

---

## 6. 验证是否部署成功

如果部署成功，执行：

```python
import maya.cmds as cmds
cmds.helloCmd()
```

应当能在 Maya 的输出中看到：

```text
hello_world_mll: Hello from Maya 2026.3 C++ plugin template.
```

---

## 7. 常见问题

## 7.1 找不到 hello_world_mll.mll

先确认 Release 是否已经构建成功。

检查以下路径是否存在：

```text
template/out/maya2026/Release/hello_world_mll.mll
```

如果不存在，说明还没有正确构建。

## 7.2 Maya 中无法看到插件

请确认插件是否已经复制到：

```text
%USERPROFILE%\Documents\maya\2026\plug-ins
```

并确认当前启动的 Maya 版本确实是 2026。

## 7.3 load_hello_plugin.py 无法 import

请确认脚本是否已经复制到：

```text
%USERPROFILE%\Documents\maya\2026\scripts
```

Maya 启动后一般会自动把该目录加入脚本搜索路径。

## 7.4 插件可以加载但执行失败

请优先检查：

- 编译配置是否正确
- Maya SDK 版本是否与目标 Maya 对应
- 是否把 Debug 产物误发给了用户

对外部署时，建议优先使用 Release。

---

## 8. 面向长期项目的建议

虽然当前模板采用的是最小部署方式，但长期建议逐步过渡到更稳定的交付方式：

- 使用模块化目录统一管理多个插件
- 增加版本号与变更记录
- 增加部署脚本的日志输出
- 增加卸载脚本
- 增加内部发布目录，例如 `releases/maya2026/`

当前阶段先使用用户目录部署，可以最快跑通整个交付闭环。

---

## 9. 建议的内部发布动作

建议项目负责人在发布给用户前，至少确认以下项目：

1. Release 构建成功
2. 插件能在干净环境中加载
3. 命令能执行
4. 部署脚本可用
5. 本次发布对应的 Maya 版本已明确标记

这样能避免大量由环境不一致导致的问题。
