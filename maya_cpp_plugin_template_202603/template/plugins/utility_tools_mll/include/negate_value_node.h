#pragma once

#include <maya/MObject.h>
#include <maya/MStatus.h>
#include <maya/MTypeId.h>
#include <maya/MPxNode.h>

class NegateValueNode : public MPxNode {
public:
    NegateValueNode() = default;
    ~NegateValueNode() override = default;

    static void* creator();
    static MStatus initialize();
    MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;

    static const MTypeId TYPE_ID;
    static MObject inputValue;
    static MObject outputValue;
};
