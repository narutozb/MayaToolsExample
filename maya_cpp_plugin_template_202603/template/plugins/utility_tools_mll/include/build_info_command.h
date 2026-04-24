#pragma once

#include <maya/MPxCommand.h>
#include <maya/MStatus.h>

class BuildInfoCommand : public MPxCommand {
public:
    BuildInfoCommand() = default;
    ~BuildInfoCommand() override = default;

    static void* creator();
    MStatus doIt(const MArgList& args) override;
};
