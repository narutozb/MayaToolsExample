import maya.cmds as cmds

PLUGIN_NAME = "utility_tools_mll"

if not cmds.pluginInfo(PLUGIN_NAME, query=True, loaded=True):
    cmds.loadPlugin(PLUGIN_NAME)
    print("Loaded:", PLUGIN_NAME)
else:
    print("Already loaded:", PLUGIN_NAME)
