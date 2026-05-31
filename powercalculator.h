// powercalculator.h — 电力负荷计算器头文件 v0.3
#ifndef POWERCALCULATOR_H
#define POWERCALCULATOR_H

#include <QString>

struct PowerResult {
    double activePower   = 0.0;   // 有功功率（kW）
    double reactivePower = 0.0;   // 无功功率（kvar）
    double apparentPower = 0.0;   // 视在功率（kVA）
    double powerFactor   = 0.0;   // 功率因数
    double lineCurrent   = 0.0;   // 线电流（A）
    bool   isValid       = false; // 结果是否有效
    QString errorMsg;
};

// 电缆热保护校验结果
struct ThermalCheckResult {
    bool   isSafe          = false; // 是否安全
    double currentDensity  = 0.0;   // 实际电流密度（A/mm²）
    double actualTempRise  = 0.0;   // 实际温升（℃）
    double maxSafeCurrent  = 0.0;   // 该截面最大安全电流（A）
    QString warningMsg;             // 告警信息
};

class PowerCalculator
{
public:
    PowerCalculator() = default;

    // 三相平衡负载：由电压/电流/功率因数计算各项功率
    static PowerResult calcThreePhase(double voltage,
                                       double current,
                                       double cosPhi = 0.85);

    // 反向计算：由有功功率+电压+功率因数 反算电流
    static PowerResult calcFromActivePower(double activePower,
                                            double voltage,
                                            double cosPhi = 0.85);

    // 无功补偿容量计算（kvar）
    // cosPhi1：补偿前功率因数，cosPhi2：目标功率因数
    // 返回负值表示参数无效
    static double calcCompensationCapacity(double activePower,
                                            double cosPhi1,
                                            double cosPhi2);

    // 电缆热保护校验（v0.3 新增）
    // 根据允许载流量和导体截面，校验当前负荷是否安全
    static ThermalCheckResult checkThermalProtection(
            double loadCurrent,      // 负荷电流（A）
            double conductorArea,    // 导体截面积（mm²）
            double allowedDensity = 6.0,  // 允许电流密度（A/mm²），铜芯默认6
            double ambientTemp    = 40.0, // 环境温度（℃）
            double maxTempRise    = 30.0  // 允许最大温升（K）
    );
};

#endif // POWERCALCULATOR_H
