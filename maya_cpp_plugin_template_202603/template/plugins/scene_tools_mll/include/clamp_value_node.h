#pragma once

#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class ClampValueNode : public MPxNode {
public:
    ClampValueNode() = default;
    ~ClampValueNode() override = default;

    static void* creator();
    static MStatus initialize();
    MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;

    static const MTypeId TYPE_ID;
    static MObject inputValue;
    static MObject minValue;
    static MObject maxValue;
    static MObject outputValue;
};
