#pragma once

#include <maya/MGlobal.h>
#include <maya/MString.h>

inline void logInfo(const char* text)
{
    MGlobal::displayInfo(MString(text));
}

inline void logWarning(const char* text)
{
    MGlobal::displayWarning(MString(text));
}

inline void logError(const char* text)
{
    MGlobal::displayError(MString(text));
}
