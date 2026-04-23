#include "maya_version_command.h"

#include <maya/MGlobal.h>
#include <maya/MString.h>

void* MayaVersionCommand::creator()
{
    return new MayaVersionCommand();
}

MStatus MayaVersionCommand::doIt(const MArgList&)
{
    const MString version = MGlobal::mayaVersion();
    MGlobal::displayInfo(MString("Maya version: ") + version);
    setResult(version);
    return MS::kSuccess;
}
