#include "build_info_command.h"

#include <maya/MGlobal.h>
#include <maya/MString.h>

void* BuildInfoCommand::creator()
{
    return new BuildInfoCommand();
}

MStatus BuildInfoCommand::doIt(const MArgList&)
{
    MString info = "utility_tools_mll build info: C++17 template sample";
    MGlobal::displayInfo(info);
    setResult(info);
    return MS::kSuccess;
}
