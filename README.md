# Qt-ElectricalPowerTool

基于 Qt6 的三相电力参数监控计算工具，适用于电气工程学习与仿真。

## 功能
- 三相功率计算（视在功率 S、有功功率 P、无功功率 Q）
- 功率因数角计算
- 电流不平衡度分析
- 过载检测
- 无功补偿容量计算

## 构建
```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt6
make
```
