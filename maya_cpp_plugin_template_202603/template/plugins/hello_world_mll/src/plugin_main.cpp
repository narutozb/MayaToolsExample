#include "hello_command.h"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MStatus.h>

namespace {
constexpr const char* PLUGIN_VENDOR = "narutozb";
constexpr const char* PLUGIN_VERSION = "0.1.0";
constexpr const char* HELLO_COMMAND_NAME = "helloCmd";
}

MStatus initializePlugin(MObject obj)
{
    MFnPlugin plugin(obj, PLUGIN_VENDOR, PLUGIN_VERSION, "Any");

    MStatus status = plugin.registerCommand(HELLO_COMMAND_NAME, HelloCommand::creator);
    if (!status) {
        status.perror("Failed to register helloCmd");
        return status;
    }

    MGlobal::displayInfo("hello_world_mll loaded.");
    return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
    MFnPlugin plugin(obj);

    MStatus status = plugin.deregisterCommand(HELLO_COMMAND_NAME);
    if (!status) {
        status.perror("Failed to deregister helloCmd");
        return status;
    }

    MGlobal::displayInfo("hello_world_mll unloaded.");
    return MS::kSuccess;
}
