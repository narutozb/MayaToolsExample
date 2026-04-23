#include "plugin_features.h"

#include "hello_command.h"
#include "echo_text_command.h"
#include "add_value_node.h"

#include "maya_plugin_manifest.h"

namespace {
MayaCommandEntry COMMAND_ENTRIES[] = {
    {"helloCmd", HelloCommand::creator, nullptr},
    {"echoTextCmd", EchoTextCommand::creator, EchoTextCommand::createSyntax},
};

MayaNodeEntry NODE_ENTRIES[] = {
    {"addValueNode", AddValueNode::TYPE_ID, AddValueNode::creator, AddValueNode::initialize, MPxNode::kDependNode},
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
