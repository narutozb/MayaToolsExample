#pragma once

#include <maya/MPxCommand.h>
#include <maya/MStatus.h>

class ListSelectionCommand : public MPxCommand {
public:
    ListSelectionCommand() = default;
    ~ListSelectionCommand() override = default;

    static void* creator();
    MStatus doIt(const MArgList& args) override;
};
