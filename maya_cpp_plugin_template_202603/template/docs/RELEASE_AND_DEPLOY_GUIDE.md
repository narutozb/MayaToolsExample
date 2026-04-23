# 发布与部署说明

当前模板已经提供两种最小部署路线：

## 1. 用户目录直接部署

脚本：

- `deploy_release_to_windows11_user.bat`

用途：

- 将 `hello_world_mll.mll`
- 将 `scene_tools_mll.mll`
- 将配套 Python 脚本

复制到用户自己的 Maya 文档目录。

适合：

- 个人开发
- 快速测试
- 小范围验证

## 2. module 方式部署

脚本：

- `module_template/package_release_to_module.bat`
- `module_template/install_module_to_user.bat`

用途：

1. 先把 Release 产物打包进 `module_template/`
2. 再将 module 复制到用户的 Maya modules 目录

适合：

- 多插件同时交付
- 长期项目
- 后续升级替换

## 推荐顺序

### 快速验证

1. 构建 Release
2. 执行 `deploy_release_to_windows11_user.bat`
3. 启动 Maya 测试

### 正式交付

1. 构建 Release
2. 执行 `module_template/package_release_to_module.bat`
3. 执行 `module_template/install_module_to_user.bat`
4. 在 Maya 中验证加载
