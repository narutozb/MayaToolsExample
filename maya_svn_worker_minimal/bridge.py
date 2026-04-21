# -*- coding: utf-8 -*-
from __future__ import annotations

import itertools
import json
import os
import queue
import subprocess
import sys
import threading
import time
from typing import Any, Callable


class SvnWorkerBridge:
    """Persistent bridge between Maya and an external SVN worker process."""

    def __init__(self, worker_script: str, python_exe: str | None = None) -> None:
        self.worker_script = worker_script
        self.python_exe = python_exe or sys.executable
        self.proc: subprocess.Popen[str] | None = None
        self._req_id_gen = itertools.count(1)
        self._pending: dict[int, dict[str, Any]] = {}
        self._lock = threading.Lock()
        self._reader_thread: threading.Thread | None = None
        self._started = False

    def start(self) -> None:
        if self._started and self.proc and self.proc.poll() is None:
            return

        creationflags = 0
        if os.name == "nt":
            creationflags = subprocess.CREATE_NO_WINDOW

        self.proc = subprocess.Popen(
            [self.python_exe, self.worker_script],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            encoding="utf-8",
            bufsize=1,
            creationflags=creationflags,
        )

        self._reader_thread = threading.Thread(
            target=self._reader_loop,
            name="SvnWorkerReader",
            daemon=True,
        )
        self._reader_thread.start()
        self._started = True

    def stop(self) -> None:
        proc = self.proc
        self.proc = None
        self._started = False
        if proc and proc.poll() is None:
            proc.terminate()

    def ensure_started(self) -> None:
        if not self._started or not self.proc or self.proc.poll() is not None:
            self.start()

    def call_async(
        self,
        method: str,
        params: dict,
        on_done: Callable[[dict], None] | None = None,
        on_error: Callable[[dict], None] | None = None,
    ) -> int:
        self.ensure_started()
        assert self.proc is not None and self.proc.stdin is not None

        req_id = next(self._req_id_gen)
        payload = {
            "id": req_id,
            "method": method,
            "params": params,
        }

        with self._lock:
            self._pending[req_id] = {
                "on_done": on_done,
                "on_error": on_error,
            }

        self.proc.stdin.write(json.dumps(payload, ensure_ascii=False) + "\n")
        self.proc.stdin.flush()
        return req_id

    def call_sync(self, method: str, params: dict, timeout: float = 30.0):
        result_queue: queue.Queue[tuple[str, dict]] = queue.Queue()

        def _done(resp: dict) -> None:
            result_queue.put(("ok", resp))

        def _error(resp: dict) -> None:
            result_queue.put(("error", resp))

        self.call_async(method=method, params=params, on_done=_done, on_error=_error)

        start = time.time()
        while True:
            try:
                kind, resp = result_queue.get(timeout=0.05)
                if kind == "ok":
                    return resp["result"]
                raise RuntimeError(resp["error"]["message"])
            except queue.Empty:
                if time.time() - start > timeout:
                    raise TimeoutError("SVN worker call timeout")

    def _reader_loop(self) -> None:
        assert self.proc is not None and self.proc.stdout is not None

        while self.proc and self.proc.poll() is None:
            line = self.proc.stdout.readline()
            if not line:
                break

            try:
                resp = json.loads(line.strip())
            except Exception:
                continue

            req_id = resp.get("id")
            if req_id is None:
                continue

            with self._lock:
                callbacks = self._pending.pop(req_id, None)

            if not callbacks:
                continue

            callback = callbacks.get("on_done") if resp.get("ok") else callbacks.get("on_error")
            if callback:
                callback(resp)
