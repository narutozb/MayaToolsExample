#include "plugin_features.h"

#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MStatus.h>

namespace {
constexpr const char* PLUGIN_VENDOR = "narutozb";
constexpr const char* PLUGIN_VERSION = "0.2.0";
}

MStatus initializePlugin(MObject obj)
{
    MFnPlugin plugin(obj, PLUGIN_VENDOR, PLUGIN_VERSION, "Any");

    MStatus status = registerPluginFeatures(plugin);
    if (!status) {
        return status;
    }

    MGlobal::displayInfo("hello_world_mll loaded.");
    return MS::kSuccess;
}

MStatus uninitializePlugin(MObject obj)
{
    MFnPlugin plugin(obj);

    MStatus status = unregisterPluginFeatures(plugin);
    if (!status) {
        return status;
    }

    MGlobal::displayInfo("hello_world_mll unloaded.");
    return MS::kSuccess;
}
