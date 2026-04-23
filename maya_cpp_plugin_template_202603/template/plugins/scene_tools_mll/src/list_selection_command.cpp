#include "list_selection_command.h"

#include <maya/MGlobal.h>
#include <maya/MSelectionList.h>
#include <maya/MString.h>

void* ListSelectionCommand::creator()
{
    return new ListSelectionCommand();
}

MStatus ListSelectionCommand::doIt(const MArgList&)
{
    MSelectionList selection;
    MGlobal::getActiveSelectionList(selection);

    const unsigned int count = selection.length();
    MGlobal::displayInfo(MString("Selection count: ") + static_cast<int>(count));

    for (unsigned int index = 0; index < count; ++index) {
        MString name;
        selection.getSelectionStrings(index, name);
        MGlobal::displayInfo(MString("  - ") + name);
    }

    setResult(static_cast<int>(count));
    return MS::kSuccess;
}
