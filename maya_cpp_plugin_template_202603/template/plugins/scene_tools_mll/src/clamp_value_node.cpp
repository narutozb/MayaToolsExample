#include "clamp_value_node.h"

#include <algorithm>

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MPlug.h>

const MTypeId ClampValueNode::TYPE_ID(0x0013A102);
MObject ClampValueNode::inputValue;
MObject ClampValueNode::minValue;
MObject ClampValueNode::maxValue;
MObject ClampValueNode::outputValue;

void* ClampValueNode::creator()
{
    return new ClampValueNode();
}

MStatus ClampValueNode::initialize()
{
    MFnNumericAttribute numericAttribute;

    inputValue = numericAttribute.create("inputValue", "inv", MFnNumericData::kDouble, 0.0);
    numericAttribute.setKeyable(true);
    addAttribute(inputValue);

    minValue = numericAttribute.create("minValue", "min", MFnNumericData::kDouble, 0.0);
    numericAttribute.setKeyable(true);
    addAttribute(minValue);

    maxValue = numericAttribute.create("maxValue", "max", MFnNumericData::kDouble, 1.0);
    numericAttribute.setKeyable(true);
    addAttribute(maxValue);

    outputValue = numericAttribute.create("outputValue", "out", MFnNumericData::kDouble, 0.0);
    numericAttribute.setWritable(false);
    numericAttribute.setStorable(false);
    addAttribute(outputValue);

    attributeAffects(inputValue, outputValue);
    attributeAffects(minValue, outputValue);
    attributeAffects(maxValue, outputValue);

    return MS::kSuccess;
}

MStatus ClampValueNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    if (plug != outputValue) {
        return MS::kUnknownParameter;
    }

    const double value = dataBlock.inputValue(inputValue).asDouble();
    const double minValueData = dataBlock.inputValue(minValue).asDouble();
    const double maxValueData = dataBlock.inputValue(maxValue).asDouble();

    const double clampedValue = std::max(minValueData, std::min(value, maxValueData));

    MDataHandle outputHandle = dataBlock.outputValue(outputValue);
    outputHandle.setDouble(clampedValue);
    outputHandle.setClean();

    return MS::kSuccess;
}
