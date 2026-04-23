#include "hello_command.h"

#include "maya_shared_log.h"

void* HelloCommand::creator()
{
    return new HelloCommand();
}

MStatus HelloCommand::doIt(const MArgList&)
{
    logInfo("hello_world_mll: Hello from Maya C++ plugin template.");
    return MS::kSuccess;
}
