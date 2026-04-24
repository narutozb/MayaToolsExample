#include "negate_value_node.h"

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MPlug.h>

const MTypeId NegateValueNode::TYPE_ID(0x0013A103);
MObject NegateValueNode::inputValue;
MObject NegateValueNode::outputValue;

void* NegateValueNode::creator()
{
    return new NegateValueNode();
}

MStatus NegateValueNode::initialize()
{
    MFnNumericAttribute numericAttribute;

    inputValue = numericAttribute.create("inputValue", "inv", MFnNumericData::kDouble, 0.0);
    numericAttribute.setKeyable(true);
    addAttribute(inputValue);

    outputValue = numericAttribute.create("outputValue", "out", MFnNumericData::kDouble, 0.0);
    numericAttribute.setWritable(false);
    numericAttribute.setStorable(false);
    addAttribute(outputValue);

    attributeAffects(inputValue, outputValue);
    return MS::kSuccess;
}

MStatus NegateValueNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    if (plug != outputValue) {
        return MS::kUnknownParameter;
    }

    const double value = dataBlock.inputValue(inputValue).asDouble();
    MDataHandle outputHandle = dataBlock.outputValue(outputValue);
    outputHandle.setDouble(-value);
    outputHandle.setClean();

    return MS::kSuccess;
}
