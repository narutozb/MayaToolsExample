import maya.cmds as cmds
import re


def create_ctrl_grp(joint_suffix='_joint', group_suffix='_ctrl_grp', ctrl_suffix='_ctrl'):
    sel = cmds.ls(sl=True, type='joint')
    # failed joints
    failed_joints = []

    # If no joint were selected then do nothing
    if len(sel) == 0:
        return

    for item in sel:
        # match joint suffix
        match = re.match(r'(\w+)(%s$)' % joint_suffix, item)
        # unselect
        cmds.select(cl=True)
        # Get joint's world position
        ws_p = cmds.xform(item, q=True, t=True, ws=True)
        # matching joint. create ctrl and group.
        if match:
            # Joint real name
            joint_real_name = match.group(1)
            # group name
            group_name = '%s%s' % (joint_real_name, group_suffix)
            # ctrl name
            ctrl_name = '%s%s' % (joint_real_name, ctrl_suffix)

            # Create group if not exist
            if cmds.objExists(group_name):
                pass
            else:
                cmds.group(em=True, name=group_name)
            # Create ctrl if not exist
            if cmds.objExists(ctrl_name):
                pass
            else:
                cmds.circle(nr=(0, 0, 1), c=(0, 0, 0), name=ctrl_name)
            # Parent ctrl to group
            ctrl_parent = cmds.listRelatives(ctrl_name, parent=True) or []

            if group_name not in ctrl_parent:
                cmds.parent(ctrl_name, group_name)

            # Set group's position
            cmds.xform(group_name, t=ws_p, ws=True)
            cmds.xform(ctrl_name, t=[0, 0, 0])
        else:
            print ('Wrong joint suffix: --->>%s<<' % item)
            failed_joints.append(item)

    # Create confirm dialog if sucessed or failed
    if len(failed_joints) > 0:
        confirm_msg = 'Wrong suffix joints:\n\n'
        confirm_msg += '\n'.join(failed_joints)
    else:
        confirm_msg = 'Sucessed!'
    cmds.select(failed_joints)
    cmds.confirmDialog(title='Confirm', message=confirm_msg)


create_ctrl_grp(joint_suffix='_joint', group_suffix='_ctrl_grp', ctrl_suffix='_ctrl')
