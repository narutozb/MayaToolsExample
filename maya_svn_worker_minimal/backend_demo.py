# -*- coding: utf-8 -*-
"""Demo backend that executes svn commands outside Maya.

This file is intentionally small and replaceable.
In your real project, swap this class with your existing SVN package.
"""

from __future__ import annotations

import locale
import subprocess
from typing import Any


class DemoSvnBackend:
    """Very small demo backend for `svn info`, `svn status`, and `svn log`."""

    def _decode_bytes(self, data: bytes) -> str:
        encodings = [
            locale.getpreferredencoding(False),
            "mbcs",
            "cp932",
            "utf-8",
        ]

        for encoding in encodings:
            if not encoding:
                continue
            try:
                return data.decode(encoding)
            except (LookupError, UnicodeDecodeError):
                continue

        return data.decode("utf-8", errors="backslashreplace")

    def _run(self, args: list[str], cwd: str | None = None) -> str:
        completed = subprocess.run(
            args,
            cwd=cwd,
            capture_output=True,
            text=False,
            check=False,
            shell=False,
        )

        stdout = self._decode_bytes(completed.stdout)
        stderr = self._decode_bytes(completed.stderr)

        if completed.returncode != 0:
            raise RuntimeError(stderr.strip() or stdout.strip() or "svn command failed")
        return stdout

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
