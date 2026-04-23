#pragma once

#include <maya/MFnPlugin.h>
#include <maya/MStatus.h>

MStatus registerPluginFeatures(MFnPlugin& plugin);
MStatus unregisterPluginFeatures(MFnPlugin& plugin);
