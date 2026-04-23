# Maya 2026.3 C++ Plugin Template

这是一个面向 **Maya 2026.3** 的长期维护型 C++ 插件项目模板。

目标：

- 为管理者提供可持续维护的项目结构与管理规则
- 为开发者提供最小可执行的日常开发入口
- 为未来升级到其他 Maya 版本预留稳定流程
- 默认采用 **CMake + Visual Studio 2022 + mll** 的构建策略

## 目录说明

```text
maya_cpp_plugin_template_202603/
├─ README.md
├─ docs/
│  ├─ manager_guide.md
│  └─ developer_guide.md
├─ template/
│  ├─ .gitignore
│  ├─ CMakeLists.txt
│  ├─ CMakePresets.json
│  ├─ cmake/
│  │  └─ MayaCommon.cmake
│  ├─ plugins/
│  │  └─ hello_world_mll/
│  │     ├─ CMakeLists.txt
│  │     ├─ include/
│  │     │  └─ hello_command.h
│  │     └─ src/
│  │        ├─ hello_command.cpp
│  │        └─ plugin_main.cpp
│  └─ scripts/
│     └─ load_hello_plugin.py
└─ project_rules/
   └─ naming_rules.md
```

## 最小可执行方案

1. 安装 Maya 2026.3
2. 安装 Visual Studio 2022（Desktop development with C++）
3. 设置环境变量 `MAYA_LOCATION`
4. 使用 CMake 生成 Visual Studio 工程
5. 构建 `hello_world_mll`
6. 在 Maya 中加载生成的 `.mll`
7. 执行命令 `helloCmd`

## 推荐的长期维护原则

- **一个仓库管理多个插件**，每个插件独立目录
- **公共构建规则统一放在 `cmake/`**
- **插件入口文件与功能类分离**
- **每次升级 Maya 版本时，不直接覆盖旧版本设置，而是新增版本配置**
- **输出目录按 Maya 版本与配置隔离**，避免混用

详细内容请分别查看：

- `docs/manager_guide.md`
- `docs/developer_guide.md`
