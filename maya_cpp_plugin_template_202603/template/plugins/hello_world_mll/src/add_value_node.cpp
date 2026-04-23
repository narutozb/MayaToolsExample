#include "add_value_node.h"

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnNumericData.h>
#include <maya/MPlug.h>

const MTypeId AddValueNode::TYPE_ID(0x0013A101);
MObject AddValueNode::inputA;
MObject AddValueNode::inputB;
MObject AddValueNode::outputValue;

void* AddValueNode::creator()
{
    return new AddValueNode();
}

MStatus AddValueNode::initialize()
{
    MFnNumericAttribute numericAttribute;

    inputA = numericAttribute.create("inputA", "ina", MFnNumericData::kDouble, 0.0);
    numericAttribute.setKeyable(true);
    addAttribute(inputA);

    inputB = numericAttribute.create("inputB", "inb", MFnNumericData::kDouble, 0.0);
    numericAttribute.setKeyable(true);
    addAttribute(inputB);

    outputValue = numericAttribute.create("outputValue", "out", MFnNumericData::kDouble, 0.0);
    numericAttribute.setWritable(false);
    numericAttribute.setStorable(false);
    addAttribute(outputValue);

    attributeAffects(inputA, outputValue);
    attributeAffects(inputB, outputValue);

    return MS::kSuccess;
}

MStatus AddValueNode::compute(const MPlug& plug, MDataBlock& dataBlock)
{
    if (plug != outputValue) {
        return MS::kUnknownParameter;
    }

    const double valueA = dataBlock.inputValue(inputA).asDouble();
    const double valueB = dataBlock.inputValue(inputB).asDouble();

    MDataHandle outputHandle = dataBlock.outputValue(outputValue);
    outputHandle.setDouble(valueA + valueB);
    outputHandle.setClean();

    return MS::kSuccess;
}
