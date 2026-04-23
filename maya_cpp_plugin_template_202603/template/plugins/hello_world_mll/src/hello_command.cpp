#include "hello_command.h"

#include <maya/MGlobal.h>

void* HelloCommand::creator()
{
    return new HelloCommand();
}

MStatus HelloCommand::doIt(const MArgList&)
{
    MGlobal::displayInfo("hello_world_mll: Hello from Maya 2026.3 C++ plugin template.");
    return MS::kSuccess;
}
