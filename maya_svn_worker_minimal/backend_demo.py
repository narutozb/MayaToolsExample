# -*- coding: utf-8 -*-
"""Demo backend that executes svn commands outside Maya.

This file is intentionally small and replaceable.
In your real project, swap this class with your existing SVN package.
"""

from __future__ import annotations

import subprocess
from typing import Any


class DemoSvnBackend:
    """Very small demo backend for `svn info`, `svn status`, and `svn log`."""

    def _run(self, args: list[str], cwd: str | None = None) -> str:
        completed = subprocess.run(
            args,
            cwd=cwd,
            capture_output=True,
            text=True,
            encoding="utf-8",
            errors="replace",
            check=False,
            shell=False,
        )
        if completed.returncode != 0:
            raise RuntimeError(completed.stderr.strip() or completed.stdout.strip() or "svn command failed")
        return completed.stdout

    def info(self, path: str) -> dict[str, Any]:
        stdout = self._run(["svn", "info", path])
        return {
            "path": path,
            "raw": stdout,
        }

    def status(self, path: str) -> dict[str, Any]:
        stdout = self._run(["svn", "status", path])
        return {
            "path": path,
            "raw": stdout,
        }

    def log(self, path: str, limit: int = 10) -> dict[str, Any]:
        stdout = self._run(["svn", "log", path, "-l", str(limit)])
        return {
            "path": path,
            "limit": limit,
            "raw": stdout,
        }
