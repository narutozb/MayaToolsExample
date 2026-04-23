#pragma once

#include <maya/MPxCommand.h>
#include <maya/MStatus.h>

class MayaVersionCommand : public MPxCommand {
public:
    MayaVersionCommand() = default;
    ~MayaVersionCommand() override = default;

    static void* creator();
    MStatus doIt(const MArgList& args) override;
};
