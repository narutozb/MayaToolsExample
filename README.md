# MayaToolsExample
简单的Maya工具，使用python编写。

## 新增示例：在 Maya 中高效率执行 SVN 命令

本仓库现已加入一个最小可执行方案，用于解决在 `maya.exe` 中直接执行 `svn info / svn log / svn status` 明显变慢的问题。

方案位置：

- `maya_svn_worker_minimal/`
- `docs/deploy_maya_svn_worker.md`

## 方案概要

核心思路不是在 Maya 中反复启动 `svn.exe`，而是：

1. Maya 启动后，仅启动一次常驻 Worker 进程
2. Maya 通过 JSON 行协议把请求发送给 Worker
3. Worker 在独立 Python 进程中调用 `pysvnlite.SVNRepo`
4. 执行结果再以结构化 JSON 的形式返回给 Maya

这样既可以显著降低 Maya 环境下外部命令启动的额外开销，也可以直接复用你已经封装好的 `pysvnlite` 后端。

## 最小文件说明

- `maya_svn_worker_minimal/backend_pysvnlite.py`
  - 基于 `pysvnlite.SVNRepo` 的 Worker 后端
- `maya_svn_worker_minimal/worker.py`
  - 常驻 Worker 进程
- `maya_svn_worker_minimal/bridge.py`
  - Maya 侧桥接器
- `maya_svn_worker_minimal/example_maya_usage.py`
  - 最小调用示例
- `docs/deploy_maya_svn_worker.md`
  - 部署步骤说明

## 部署文档

请直接阅读：

`docs/deploy_maya_svn_worker.md`

## 备注

当前提交的是一个最小可运行版本，并且默认后端已经切换为 `pysvnlite`。

如果后续你还想扩展 `checkout / update / commit / cleanup` 等接口，建议继续保持 Bridge 与 Worker 的通信结构不变，仅在 Worker 内追加对应的后端分发逻辑即可。
