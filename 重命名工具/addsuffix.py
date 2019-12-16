import maya.cmds as cmds


def add_suffix_to_mesh_joint():

    list_all_transforms = cmds.ls(type='transform')
    # sort long name first
    list_all_transforms.sort(key=len,reverse=True)
    
    for item in list_all_transforms:
        short_name = item.split('|')[-1]
        node_type = cmds.nodeType(item)
        
        # add suffix '_mesh' if this is mesh
        shape = cmds.listRelatives(item,type='mesh')
        if shape and '_mesh' != short_name[-len('_mesh'):] :
            cmds.rename(item, short_name+'_mesh')
        
        # add suffix '_jnt' if this is jnt
        if '_jnt' != short_name[-len('_jnt'):] and node_type == 'joint':
            cmds.rename(item,short_name+'_jnt')

add_suffix_to_mesh_joint()

