# module 部署模板

这个目录用于演示 Maya module 方式的最小部署结构。

## 目录说明

- `MayaCppPluginTemplate.mod`：module 定义文件
- `plug-ins/`：放置 `.mll`
- `scripts/`：放置 Python 脚本
- `install_module_to_user.bat`：复制到用户文档目录下的 Maya modules

## 推荐流程

1. 将构建出的 `.mll` 复制到 `plug-ins/`
2. 将需要的 Python 脚本复制到 `scripts/`
3. 运行 `install_module_to_user.bat`
4. 启动 Maya 并在 Plug-in Manager 中加载插件

## 适合的场景

- 需要同时部署多个插件
- 长期项目
- 统一目录管理
- 后续需要升级与替换
