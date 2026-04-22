# 在 Maya 中高效率执行 SVN 命令的最小部署方案

## 目标

本方案的核心不是在 `maya.exe` 中反复执行 `svn.exe`，而是在 Maya 启动后只启动一次常驻 Worker 进程。后续的 `svn info`、`svn status`、`svn log` 都转发给该 Worker 执行。

当前版本的 Worker 默认使用 `pysvnlite.SVNRepo` 作为后端，因此你可以直接复用已经封装好的 Python SVN 包，而不需要再在 Maya 进程里直接执行 SVN 命令。

这样做的意义在于：

- 避开 Maya 环境下重复启动外部进程带来的高额开销
- 保持 Maya UI 更流畅
- 可以直接复用现有 `pysvnlite` 封装
- 返回结构化结果，更适合 UI 与业务层继续处理

## 目录结构

```text
MayaToolsExample/
├─ maya_svn_worker_minimal/
│  ├─ __init__.py
│  ├─ backend_demo.py
│  ├─ backend_pysvnlite.py
│  ├─ bridge.py
│  ├─ worker.py
│  └─ example_maya_usage.py
└─ docs/
   └─ deploy_maya_svn_worker.md
```

## 前提条件

- Windows 11
- Maya 2026
- Python 3.11
- Worker 使用的外部 Python 中已安装 `pysvnlite`
- 系统中可正常执行 `svn --version`

## 步骤 1：确认系统 Python 可直接使用 pysvnlite

在 Windows 终端中执行：

```bat
C:\Python311\python.exe -c "from pysvnlite.core.repo import SVNRepo; print(SVNRepo)"
```

如果能正常输出类对象，则说明 Worker 使用的 Python 已经具备 `pysvnlite` 依赖。

如果还没有安装，可以在 `pysvnlite` 仓库目录下执行：

```bat
C:\Python311\python.exe -m pip install -e D:\pysvnlite
```

请根据你自己的 Python 路径与仓库路径进行替换。

## 步骤 2：将 MayaToolsExample 仓库放到本地

例如：

```text
D:\MayaToolsExample
```

## 步骤 3：在 Maya 中加入仓库路径

将以下路径加入 `sys.path`：

```python
import sys
sys.path.append(r"D:\MayaToolsExample")
```

## 步骤 4：修改示例中的本地路径

编辑 `maya_svn_worker_minimal/example_maya_usage.py`：

```python
WORKER_SCRIPT = r"D:\MayaToolsExample\maya_svn_worker_minimal\worker.py"
PYTHON_EXE = r"C:\Python311\python.exe"
```

请改成你机器上的真实路径。

## 步骤 5：在 Maya 中测试

在 Script Editor 中执行：

```python
import sys
sys.path.append(r"D:\MayaToolsExample")

from maya_svn_worker_minimal.example_maya_usage import demo_ping, demo_info, demo_status, demo_log

demo_ping()
demo_info(r"D:\your_svn_working_copy")
demo_status(r"D:\your_svn_working_copy")
demo_log(r"D:\your_svn_working_copy", limit=5)
```

如果 `demo_ping()` 输出 `pong`，并且其余接口返回的是结构化字典或列表数据，则表示方案已经成功运行。

## 当前的后端实现方式

Worker 当前默认调用的是：

- `SVNRepo(path).info()`
- `SVNRepo(path).status(...)`
- `SVNRepo(path).log(limit=...)`

由于 `pysvnlite` 返回的是 dataclass 模型，并且内部可能包含 `Path` 与 `datetime`，因此 Worker 会先将这些对象转换为 JSON 可序列化的数据，再传回 Maya。

## 推荐的实际接入方式

如果你要正式在 Maya 工具中落地，建议不要直接调用 `example_maya_usage.py`，而是：

- 在工具启动时创建一个全局 `SvnWorkerBridge`
- 工具关闭时执行 `bridge.stop()`
- 高频请求统一从 Bridge 发送
- 若结果需要更新 Maya UI，则在你自己的 UI 层中进行主线程分发

## 后续扩展建议

如果后续你还需要更多能力，建议沿着同样的结构继续扩展：

- `checkout`
- `update`
- `cleanup`
- `commit`
- 批量请求
- 结果缓存
- Worker 自动重启机制

当前这个示例的重点在于证明以下架构可以工作：

- Maya 只负责发请求
- 独立 Python Worker 负责执行 SVNRepo
- 两者通过 JSON 行协议通信
