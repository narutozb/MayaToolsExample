# 节点模板说明

当前模板已经给出了两个可直接参考的节点示例：

- `plugins/hello_world_mll/include/add_value_node.h`
- `plugins/hello_world_mll/src/add_value_node.cpp`
- `plugins/scene_tools_mll/include/clamp_value_node.h`
- `plugins/scene_tools_mll/src/clamp_value_node.cpp`

## 节点文件建议结构

- `include/<node_name>.h`
- `src/<node_name>.cpp`

## 节点类建议至少包含

- `static const MTypeId TYPE_ID`
- `static void* creator()`
- `static MStatus initialize()`
- `MStatus compute(...) override`
- 静态属性 `MObject`

## 最小模板

```cpp
class SampleNode : public MPxNode {
public:
    static const MTypeId TYPE_ID;
    static MObject inputValue;
    static MObject outputValue;

    static void* creator();
    static MStatus initialize();
    MStatus compute(const MPlug& plug, MDataBlock& dataBlock) override;
};
```

## 注册方式

不要直接在 `plugin_main.cpp` 中注册节点。

统一在 `plugin_features.cpp` 中，将节点加入 `NODE_ENTRIES`。
