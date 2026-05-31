// powercalculator.cpp — 电力负荷计算核心实现 v0.1
#include "powercalculator.h"
#include <QtMath>

// 三相平衡负载功率计算
PowerResult PowerCalculator::calcThreePhase(double voltage, double current, double cosPhi)
{
    PowerResult res;
    res.isValid = false;

    // 参数校验
    if (voltage <= 0 || current < 0 || cosPhi < 0 || cosPhi > 1) {
        res.errorMsg = QStringLiteral("参数非法：电压/电流/功率因数超出合理范围");
        return res;
    }

    static const double SQRT3 = qSqrt(3.0);
    // 视在功率 S = √3 × U × I (VA)
    res.apparentPower = SQRT3 * voltage * current;
    // 有功功率 P = S × cosφ
    res.activePower = res.apparentPower * cosPhi;
    // 无功功率 Q = S × sin(arccos(cosφ))
    res.reactivePower = res.apparentPower * qSqrt(1.0 - cosPhi * cosPhi);
    res.powerFactor = cosPhi;
    res.lineCurrent = current;
    res.isValid = true;

    return res;
}

// 由有功功率反算电流
PowerResult PowerCalculator::calcFromActivePower(double activePower, double voltage, double cosPhi)
{
    PowerResult res;
    res.isValid = false;

    if (activePower <= 0 || voltage <= 0 || cosPhi <= 0 || cosPhi > 1) {
        res.errorMsg = QStringLiteral("参数非法：功率/电压/功率因数超出合理范围");
        return res;
    }

    static const double SQRT3 = qSqrt(3.0);
    // I = P / (√3 × U × cosφ)  →  电流(A)
    double current = activePower / (SQRT3 * voltage * cosPhi);

    // 复用 calcThreePhase 填充其他字段
    res = calcThreePhase(voltage, current, cosPhi);
    return res;
}
