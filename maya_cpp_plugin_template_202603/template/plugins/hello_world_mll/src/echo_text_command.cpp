#include "echo_text_command.h"

#include <maya/MArgDatabase.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>

namespace {
constexpr const char* kTextFlag = "-t";
constexpr const char* kTextFlagLong = "-text";
}

void* EchoTextCommand::creator()
{
    return new EchoTextCommand();
}

MSyntax EchoTextCommand::createSyntax()
{
    MSyntax syntax;
    syntax.addFlag(kTextFlag, kTextFlagLong, MSyntax::kString);
    return syntax;
}

MStatus EchoTextCommand::doIt(const MArgList& args)
{
    MStatus status;
    MArgDatabase database(syntax(), args, &status);
    if (!status) {
        return status;
    }

    MString text = "default text";
    if (database.isFlagSet(kTextFlag)) {
        database.getFlagArgument(kTextFlag, 0, text);
    }

    MGlobal::displayInfo(MString("echoTextCmd: ") + text);
    setResult(text);
    return MS::kSuccess;
}
