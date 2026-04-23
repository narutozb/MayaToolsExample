#pragma once

#include <maya/MPxCommand.h>
#include <maya/MStatus.h>

class HelloCommand : public MPxCommand {
public:
    HelloCommand() = default;
    ~HelloCommand() override = default;

    static void* creator();
    MStatus doIt(const MArgList& args) override;
};
