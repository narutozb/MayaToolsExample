# 在 Maya 中高效率执行 SVN 命令的最小部署方案

## 目标

本方案的核心不是在 `maya.exe` 中反复执行 `svn.exe`，而是在 Maya 启动后只启动一次常驻 Worker 进程。后续的 `svn info`、`svn status`、`svn log` 都转发给该 Worker 执行。

这样做的意义在于：

- 避开 Maya 环境下重复启动外部进程带来的高额开销
- 保持 Maya UI 更流畅
- 不需要重写既有的 SVN 包，只需要把执行位置挪到独立进程中

## 目录结构

```text
MayaToolsExample/
├─ maya_svn_worker_minimal/
│  ├─ __init__.py
│  ├─ backend_demo.py
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
- 已安装 svn 命令行，并且在 `PATH` 中可直接执行 `svn --version`

## 步骤 1：确认系统 Python 可直接执行 svn

在 Windows 终端中执行：

```bat
svn --version
```

如果能正常输出版本信息，则说明 `backend_demo.py` 可直接工作。

## 步骤 2：将仓库放到本地

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

from maya_svn_worker_minimal.example_maya_usage import demo_ping, demo_info

demo_ping()
demo_info(r"D:\your_svn_working_copy")
```

如果 `demo_ping()` 输出 `pong`，并且 `demo_info()` 输出 `svn info` 的原始文本，则表示最小方案已经成功运行。

## 如何替换为你自己的 SVN 包

当前示例中的 `backend_demo.py` 只是一个最小可运行的 demo。

如果你已经有现成的 SVN Python 包，那么建议这样替换：

1. 打开 `maya_svn_worker_minimal/worker.py`
2. 将 `DemoSvnBackend` 替换成你自己的后端类
3. 保持 `dispatch()` 的入参与出参结构不变

例如：

```python
from your_package import SvnClient

class WorkerDispatcher:
    def __init__(self):
        self.backend = SvnClient()
```

然后在 `dispatch()` 中转发给你自己的 `info / status / log` 即可。

## 推荐的实际接入方式

如果你要正式在 Maya 工具中落地，建议不要直接调用 `example_maya_usage.py`，而是：

- 在工具启动时创建一个全局 `SvnWorkerBridge`
- 工具关闭时执行 `bridge.stop()`
- 高频请求统一从 Bridge 发送
- 若结果需要更新 Maya UI，则在你自己的 UI 层中进行主线程分发

## 备注

这个示例的重点在于证明以下架构可以工作：

- Maya 只负责发请求
- 独立 Python Worker 负责执行 SVN
- 两者通过 JSON 行协议通信

如果后续你需要，我建议再追加：

- 批量请求接口
- 结果缓存
- 异步回调接入 Maya UI 主线程
- Worker 自动重启机制
