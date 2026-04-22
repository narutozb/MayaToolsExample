# -*- coding: utf-8 -*-
from __future__ import annotations

from dataclasses import asdict, is_dataclass
from datetime import datetime
from pathlib import Path
from typing import Any

from pysvnlite.core.repo import SVNRepo



def _to_jsonable(value: Any) -> Any:
    if is_dataclass(value):
        return _to_jsonable(asdict(value))

    if isinstance(value, dict):
        return {str(k): _to_jsonable(v) for k, v in value.items()}

    if isinstance(value, (list, tuple, set)):
        return [_to_jsonable(v) for v in value]

    if isinstance(value, Path):
        return str(value)

    if isinstance(value, datetime):
        return value.isoformat()

    return value


class PySvnLiteBackend:
    """Worker backend based on pysvnlite.SVNRepo."""

    def info(self, path: str) -> dict[str, Any]:
        repo = SVNRepo(path)
        data = repo.info()
        return {
            "path": path,
            "data": _to_jsonable(data),
        }

    def status(
        self,
        path: str,
        depth: str | None = None,
        show_updates: bool = False,
        ignore_externals: bool = False,
    ) -> dict[str, Any]:
        repo = SVNRepo(path)
        data = repo.status(
            depth=depth,
            show_updates=show_updates,
            ignore_externals=ignore_externals,
        )
        return {
            "path": path,
            "data": _to_jsonable(data),
        }

    def log(self, path: str, limit: int = 10) -> dict[str, Any]:
        repo = SVNRepo(path)
        data = repo.log(limit=limit)
        return {
            "path": path,
            "limit": limit,
            "data": _to_jsonable(data),
        }
