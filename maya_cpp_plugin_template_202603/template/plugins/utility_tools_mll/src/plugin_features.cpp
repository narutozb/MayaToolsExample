#include "plugin_features.h"

#include "build_info_command.h"
#include "negate_value_node.h"

#include "maya_plugin_manifest.h"

namespace {
MayaCommandEntry COMMAND_ENTRIES[] = {
    {"buildInfoCmd", BuildInfoCommand::creator, nullptr},
};

MayaNodeEntry NODE_ENTRIES[] = {
    {"negateValueNode", NegateValueNode::TYPE_ID, NegateValueNode::creator, NegateValueNode::initialize, MPxNode::kDependNode},
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
