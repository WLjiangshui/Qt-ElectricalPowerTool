// powercalculator.h — 电力负荷计算核心 v0.1
#ifndef POWERCALCULATOR_H
#define POWERCALCULATOR_H

#include <QString>

// 计算结果结构体
struct PowerResult {
    double activePower;        // 有功功率 P (W)
    double reactivePower;      // 无功功率 Q (var)
    double apparentPower;      // 视在功率 S (VA)
    double powerFactor;        // 功率因数 cosφ
    double lineCurrent;        // 线电流 (A)
    bool isValid;              // 有效性标记
    QString errorMsg;          // 错误信息
};

class PowerCalculator
{
public:
    // 三相平衡负载功率计算
    // U: 线电压(V), I: 线电流(A), cosPhi: 功率因数
    static PowerResult calcThreePhase(double voltage, double current, double cosPhi);

    // 由有功功率和功率因数反算电流
    // P: 有功功率(W), U: 线电压(V), cosPhi: 功率因数
    static PowerResult calcFromActivePower(double activePower, double voltage, double cosPhi);
};

#endif // POWERCALCULATOR_H
