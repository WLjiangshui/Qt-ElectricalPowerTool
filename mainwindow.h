// mainwindow.h — 电力参数监控主窗口 v1.0
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>

#include "powercalculator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onCalcPower();             // 三相功率计算
    void onCalcCurrent();           // 反算电流

private:
    void setupUI();
    void showResult(const PowerResult &res);

    // 输入控件
    QDoubleSpinBox *m_voltageInput;
    QDoubleSpinBox *m_currentInput;
    QDoubleSpinBox *m_cosPhiInput;
    QDoubleSpinBox *m_activePowerInput;

    // 按钮
    QPushButton *m_btnCalcPower;
    QPushButton *m_btnCalcCurrent;

    // 结果显示
    QLabel *m_resultActive;
    QLabel *m_resultReactive;
    QLabel *m_resultApparent;
    QLabel *m_resultPowerFactor;
    QLabel *m_resultCurrent;
};

#endif // MAINWINDOW_H
