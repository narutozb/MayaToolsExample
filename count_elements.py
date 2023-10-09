import maya.cmds as cmds

types = ['mesh', 'joint', 'nurbsCurve']
# 获取各个类型的计数
counter = {typ: len(cmds.ls(type=typ)) for typ in types}

transforms = cmds.ls(type='transform', long=True)
groups = []
for tran in transforms:
    shapes = cmds.listRelatives(tran , shapes=True)
    if not shapes and cmds.nodeType(tran) == 'transform':
        groups.append(tran)
# 将group的计数添加到字典中
counter['group'] = len(groups)

# 打印计数
print(counter)
