#include "plugin_features.h"

#include "maya_version_command.h"
#include "list_selection_command.h"
#include "clamp_value_node.h"

#include "maya_plugin_manifest.h"

namespace {
MayaCommandEntry COMMAND_ENTRIES[] = {
    {"mayaVersionCmd", MayaVersionCommand::creator, nullptr},
    {"listSelectionCmd", ListSelectionCommand::creator, nullptr},
};

MayaNodeEntry NODE_ENTRIES[] = {
    {"clampValueNode", ClampValueNode::TYPE_ID, ClampValueNode::creator, ClampValueNode::initialize, MPxNode::kDependNode},
};
}

MStatus registerPluginFeatures(MFnPlugin& plugin)
{
    MStatus status = registerCommands(plugin, COMMAND_ENTRIES, sizeof(COMMAND_ENTRIES) / sizeof(COMMAND_ENTRIES[0]));
    if (!status) {
        return status;
    }

    status = registerNodes(plugin, NODE_ENTRIES, sizeof(NODE_ENTRIES) / sizeof(NODE_ENTRIES[0]));
    if (!status) {
        deregisterCommands(plugin, COMMAND_ENTRIES, sizeof(COMMAND_ENTRIES) / sizeof(COMMAND_ENTRIES[0]));
        return status;
    }

    return MS::kSuccess;
}

MStatus unregisterPluginFeatures(MFnPlugin& plugin)
{
    MStatus status = deregisterNodes(plugin, NODE_ENTRIES, sizeof(NODE_ENTRIES) / sizeof(NODE_ENTRIES[0]));
    if (!status) {
        return status;
    }

    status = deregisterCommands(plugin, COMMAND_ENTRIES, sizeof(COMMAND_ENTRIES) / sizeof(COMMAND_ENTRIES[0]));
    if (!status) {
        return status;
    }

    return MS::kSuccess;
}
