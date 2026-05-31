# 电网参数监控与计算系统 (Qt/C++)

电气工程三相电力参数计算工具，基于 Qt6 Widgets 构建。

## 功能
- 三相平衡负载功率计算（P/Q/S/cosφ）
- 由有功功率反算线电流
- 无功补偿容量计算
- 电压/电流波形可视化

## 技术栈
- C++17
- Qt 6 Widgets
- Qt Charts（波形图）

## 编译运行
```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt6
cmake --build .
./PowerMonitor
```

## 电气公式
- S = √3·U·I  （视在功率）
- P = S·cosφ （有功功率）
- Q = S·sin(arccos(cosφ)) （无功功率）
- Qc = P·[tan(arccos(cosφ1)) - tan(arccos(cosφ2))]
