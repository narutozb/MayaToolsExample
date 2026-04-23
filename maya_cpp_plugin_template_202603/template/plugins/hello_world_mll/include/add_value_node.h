#pragma once

#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class AddValueNode : public MPxNode {
public:
    AddValueNode() = default;
    ~AddValueNode() override = default;

    static void* creator();
    static MStatus initialize();
    MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;

    static const MTypeId TYPE_ID;
    static MObject inputA;
    static MObject inputB;
    static MObject outputValue;
};
