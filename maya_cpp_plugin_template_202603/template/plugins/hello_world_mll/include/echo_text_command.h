#pragma once

#include <maya/MPxCommand.h>
#include <maya/MStatus.h>
#include <maya/MSyntax.h>

class EchoTextCommand : public MPxCommand {
public:
    EchoTextCommand() = default;
    ~EchoTextCommand() override = default;

    static void* creator();
    static MSyntax createSyntax();
    MStatus doIt(const MArgList& args) override;
};
