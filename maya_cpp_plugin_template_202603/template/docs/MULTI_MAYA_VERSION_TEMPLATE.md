# 多 Maya 版本切换模板

当前模板已经支持通过 `MAYA_VERSION` 与环境变量切换 Maya 版本。

## 支持方式

- `MAYA_LOCATION_2024`
- `MAYA_LOCATION_2025`
- `MAYA_LOCATION_2026`
- 如果上面的变量不存在，则回退到 `MAYA_LOCATION`

## 相关文件

- `CMakePresets.json`
- `cmake/MayaVersionSwitch.cmake`
- `CMakeLists.txt`

## 示例

### 环境变量

```bat
set MAYA_LOCATION_2024=C:\Program Files\Autodesk\Maya2024
set MAYA_LOCATION_2026=C:\Program Files\Autodesk\Maya2026
```

### 配置 2024

```bat
cmake --preset vs2022-maya2024
cmake --build --preset build-maya2024-release
```

### 配置 2026

```bat
cmake --preset vs2022-maya2026
cmake --build --preset build-maya2026-release
```

## 适合的场景

- 同一套插件需要维护多个 Maya 版本
- 需要逐步迁移旧工程
- 长期项目中按版本产出二进制文件
