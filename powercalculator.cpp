// powercalculator.cpp — 电力负荷计算核心实现 v0.2
#include "powercalculator.h"
#include <cmath>
#include <QString>

// 三相平衡负载功率计算
// P = √3 × U × I × cosφ / 1000   (kW)
// Q = √3 × U × I × sinφ / 1000   (kvar)
// S = √3 × U × I / 1000           (kVA)
PowerResult PowerCalculator::calcThreePhase(double voltage, double current, double cosPhi)
{
    PowerResult result = {};

    // 参数有效性校验
    if (voltage <= 0 || current <= 0 || cosPhi < 0 || cosPhi > 1) {
        result.isValid = false;
        result.errorMsg = QString(u8"输入参数无效！电压/电流需＞0，功率因数需∈[0,1]");
        return result;
    }

    const double sqrt3 = 1.73205080757;
    double sinPhi = std::sqrt(1.0 - cosPhi * cosPhi);

    // 单位采用 kW / kvar / kVA
    result.activePower   = sqrt3 * voltage * current * cosPhi / 1000.0;
    result.reactivePower = sqrt3 * voltage * current * sinPhi / 1000.0;
    result.apparentPower = sqrt3 * voltage * current / 1000.0;
    result.powerFactor   = cosPhi;
    result.lineCurrent   = current;
    result.isValid       = true;

    return result;
}

// 由有功功率和功率因数反算电流
// I = P(kW) × 1000 / (√3 × U × cosφ)
PowerResult PowerCalculator::calcFromActivePower(double activePower,
                                                  double voltage, double cosPhi)
{
    PowerResult result = {};

    if (activePower <= 0 || voltage <= 0 || cosPhi <= 0 || cosPhi > 1) {
        result.isValid = false;
        result.errorMsg = QString(u8"输入参数无效！有功功率/电压需＞0，功率因数∈(0,1]");
        return result;
    }

    const double sqrt3 = 1.73205080757;
    double sinPhi = std::sqrt(1.0 - cosPhi * cosPhi);

    double current = activePower * 1000.0 / (sqrt3 * voltage * cosPhi);

    result.activePower   = activePower;
    result.reactivePower = sqrt3 * voltage * current * sinPhi / 1000.0;
    result.apparentPower = activePower / cosPhi;
    result.powerFactor   = cosPhi;
    result.lineCurrent   = current;
    result.isValid       = true;

    return result;
}

// 无功补偿容量计算
// Qc = P × (tanφ1 - tanφ2)  =  P × [tan(arccosφ1) - tan(arccosφ2)]
double PowerCalculator::calcCompensationCapacity(double activePower,
                                                  double cosPhi1, double cosPhi2)
{
    if (activePower <= 0 || cosPhi1 <= 0 || cosPhi2 <= 0 ||
        cosPhi1 > 1 || cosPhi2 > 1 || cosPhi2 <= cosPhi1) {
        return -1.0; // 无效返回-1
    }

    double tan1 = std::tan(std::acos(cosPhi1));
    double tan2 = std::tan(std::acos(cosPhi2));

    return activePower * (tan1 - tan2) * 1.1; // 留10%冗余
}
