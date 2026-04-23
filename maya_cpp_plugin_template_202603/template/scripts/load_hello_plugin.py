# -*- coding: utf-8 -*-
"""hello_world_mll の簡易ロードスクリプト。"""

import os
import maya.cmds as cmds


PLUGIN_PATH = os.path.normpath(
    os.path.join(
        os.path.dirname(__file__),
        "..",
        "out",
        "maya2026",
        "Debug",
        "hello_world_mll.mll",
    )
)


def load_plugin():
    """ビルド済みの hello_world_mll を Maya にロードする。"""
    plugin_path = PLUGIN_PATH.replace("\\", "/")

    if not os.path.exists(PLUGIN_PATH):
        raise RuntimeError("Plugin file not found: {}".format(plugin_path))

    if cmds.pluginInfo(plugin_path, query=True, loaded=True):
        print("Already loaded: {}".format(plugin_path))
        return plugin_path

    cmds.loadPlugin(plugin_path)
    print("Loaded: {}".format(plugin_path))
    return plugin_path


load_plugin()
