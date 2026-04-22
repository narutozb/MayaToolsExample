# -*- coding: utf-8 -*-
from __future__ import annotations

from maya_svn_worker_minimal.bridge import SvnWorkerBridge


# Replace these two paths for your local machine.
WORKER_SCRIPT = r"D:\MayaToolsExample\maya_svn_worker_minimal\worker.py"
PYTHON_EXE = r"C:\Python311\python.exe"

bridge = SvnWorkerBridge(worker_script=WORKER_SCRIPT, python_exe=PYTHON_EXE)
bridge.start()


def demo_ping() -> None:
    result = bridge.call_sync("ping", {})
    print("PING:", result)


def demo_info(path: str) -> None:
    result = bridge.call_sync("info", {"path": path})
    print(result["data"])


def demo_status(
    path: str,
    depth: str | None = None,
    show_updates: bool = False,
    ignore_externals: bool = False,
) -> None:
    result = bridge.call_sync(
        "status",
        {
            "path": path,
            "depth": depth,
            "show_updates": show_updates,
            "ignore_externals": ignore_externals,
        },
    )
    print(result["data"])


def demo_log(path: str, limit: int = 10) -> None:
    result = bridge.call_sync("log", {"path": path, "limit": limit})
    print(result["data"])
