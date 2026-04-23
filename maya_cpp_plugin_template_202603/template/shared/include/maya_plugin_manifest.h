#pragma once

#include <maya/MFnPlugin.h>
#include <maya/MStatus.h>
#include <maya/MTypeId.h>
#include <maya/MPxCommand.h>
#include <maya/MPxNode.h>

struct MayaCommandEntry {
    const char* commandName;
    MCreatorFunction creator;
    MCreateSyntaxFunction createSyntax;
};

struct MayaNodeEntry {
    const char* nodeName;
    MTypeId typeId;
    MCreatorFunction creator;
    MStatus (*initialize)();
    MPxNode::Type nodeType;
};

inline MStatus registerCommands(MFnPlugin& plugin, const MayaCommandEntry* entries, unsigned int count)
{
    MStatus status = MS::kSuccess;

    for (unsigned int index = 0; index < count; ++index) {
        const MayaCommandEntry& entry = entries[index];
        status = plugin.registerCommand(entry.commandName, entry.creator, entry.createSyntax);
        if (!status) {
            status.perror(entry.commandName);
            return status;
        }
    }

    return status;
}

inline MStatus deregisterCommands(MFnPlugin& plugin, const MayaCommandEntry* entries, unsigned int count)
{
    MStatus status = MS::kSuccess;

    for (unsigned int index = count; index > 0; --index) {
        const MayaCommandEntry& entry = entries[index - 1];
        status = plugin.deregisterCommand(entry.commandName);
        if (!status) {
            status.perror(entry.commandName);
            return status;
        }
    }

    return status;
}

inline MStatus registerNodes(MFnPlugin& plugin, const MayaNodeEntry* entries, unsigned int count)
{
    MStatus status = MS::kSuccess;

    for (unsigned int index = 0; index < count; ++index) {
        const MayaNodeEntry& entry = entries[index];
        status = plugin.registerNode(
            entry.nodeName,
            entry.typeId,
            entry.creator,
            entry.initialize,
            entry.nodeType
        );
        if (!status) {
            status.perror(entry.nodeName);
            return status;
        }
    }

    return status;
}

inline MStatus deregisterNodes(MFnPlugin& plugin, const MayaNodeEntry* entries, unsigned int count)
{
    MStatus status = MS::kSuccess;

    for (unsigned int index = count; index > 0; --index) {
        const MayaNodeEntry& entry = entries[index - 1];
        status = plugin.deregisterNode(entry.typeId);
        if (!status) {
            status.perror(entry.nodeName);
            return status;
        }
    }

    return status;
}
