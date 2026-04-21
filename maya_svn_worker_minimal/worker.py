# -*- coding: utf-8 -*-
from __future__ import annotations

import json
import os
import sys
import traceback


CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.dirname(CURRENT_DIR)
if REPO_ROOT not in sys.path:
    sys.path.insert(0, REPO_ROOT)

from maya_svn_worker_minimal.backend_demo import DemoSvnBackend


class WorkerDispatcher:
    def __init__(self) -> None:
        self.backend = DemoSvnBackend()

    def dispatch(self, method: str, params: dict):
        if method == "ping":
            return {"message": "pong"}
        if method == "info":
            return self.backend.info(**params)
        if method == "status":
            return self.backend.status(**params)
        if method == "log":
            return self.backend.log(**params)
        raise ValueError("Unknown method: {}".format(method))


def _make_response(req_id, ok=True, result=None, error=None):
    return {
        "id": req_id,
        "ok": ok,
        "result": result,
        "error": error,
    }


def main() -> int:
    dispatcher = WorkerDispatcher()

    while True:
        try:
            line = input()
        except EOFError:
            break

        line = line.strip()
        if not line:
            continue

        req_id = None
        try:
            payload = json.loads(line)
            req_id = payload.get("id")
            method = payload["method"]
            params = payload.get("params", {})
            result = dispatcher.dispatch(method, params)
            resp = _make_response(req_id=req_id, ok=True, result=result)
        except Exception as exc:
            resp = _make_response(
                req_id=req_id,
                ok=False,
                error={
                    "type": type(exc).__name__,
                    "message": str(exc),
                    "traceback": traceback.format_exc(),
                },
            )

        print(json.dumps(resp, ensure_ascii=False), flush=True)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
