// mainwindow.cpp — 电力参数监控主窗口 v1.0
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("电网参数监控与计算系统 v1.0"));
    resize(600, 400);
    setupUI();
}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // ---- 输入参数组 ----
    QGroupBox *inputGroup = new QGroupBox(QStringLiteral("输入参数"));
    QFormLayout *form = new QFormLayout(inputGroup);

    m_voltageInput = new QDoubleSpinBox;
    m_voltageInput->setRange(0, 100000);
    m_voltageInput->setValue(380);
    m_voltageInput->setSuffix(" V");
    form->addRow(QStringLiteral("线电压 U_L:"), m_voltageInput);

    m_currentInput = new QDoubleSpinBox;
    m_currentInput->setRange(0, 10000);
    m_currentInput->setValue(50);
    m_currentInput->setSuffix(" A");
    form->addRow(QStringLiteral("线电流 I_L:"), m_currentInput);

    m_cosPhiInput = new QDoubleSpinBox;
    m_cosPhiInput->setRange(0.01, 1.0);
    m_cosPhiInput->setSingleStep(0.01);
    m_cosPhiInput->setValue(0.85);
    form->addRow(QStringLiteral("功率因数 cosφ:"), m_cosPhiInput);

    m_activePowerInput = new QDoubleSpinBox;
    m_activePowerInput->setRange(0, 1000000);
    m_activePowerInput->setValue(27963);
    m_activePowerInput->setSuffix(" W");
    form->addRow(QStringLiteral("有功功率 P:"), m_activePowerInput);

    mainLayout->addWidget(inputGroup);

    // ---- 按钮组 ----
    QHBoxLayout *btnLayout = new QHBoxLayout;
    m_btnCalcPower   = new QPushButton(QStringLiteral("计算三相功率"));
    m_btnCalcCurrent = new QPushButton(QStringLiteral("反算电流"));
    btnLayout->addWidget(m_btnCalcPower);
    btnLayout->addWidget(m_btnCalcCurrent);
    mainLayout->addLayout(btnLayout);

    connect(m_btnCalcPower,   &QPushButton::clicked, this, &MainWindow::onCalcPower);
    connect(m_btnCalcCurrent, &QPushButton::clicked, this, &MainWindow::onCalcCurrent);

    // ---- 结果显示组 ----
    QGroupBox *resultGroup = new QGroupBox(QStringLiteral("计算结果"));
    QFormLayout *resultForm = new QFormLayout(resultGroup);

    m_resultActive      = new QLabel(QStringLiteral("—"));
    m_resultReactive    = new QLabel(QStringLiteral("—"));
    m_resultApparent    = new QLabel(QStringLiteral("—"));
    m_resultPowerFactor = new QLabel(QStringLiteral("—"));
    m_resultCurrent     = new QLabel(QStringLiteral("—"));

    resultForm->addRow(QStringLiteral("有功功率 P:"),   m_resultActive);
    resultForm->addRow(QStringLiteral("无功功率 Q:"),   m_resultReactive);
    resultForm->addRow(QStringLiteral("视在功率 S:"),   m_resultApparent);
    resultForm->addRow(QStringLiteral("功率因数 cosφ:"), m_resultPowerFactor);
    resultForm->addRow(QStringLiteral("推算电流 I_L:"),  m_resultCurrent);

    mainLayout->addWidget(resultGroup);
    setCentralWidget(central);
}

// ==================== 功率计算槽函数 ====================
void MainWindow::onCalcPower()
{
    double U = m_voltageInput->value();
    double I = m_currentInput->value();
    double cosPhi = m_cosPhiInput->value();

    if (cosPhi <= 0 || cosPhi > 1.0) {
        QMessageBox::warning(this, QStringLiteral("输入错误"),
                             QStringLiteral("功率因数必须满足 0 < cosφ ≤ 1"));
        return;
    }

    PowerResult res = PowerCalculator::calcThreePhase(U, I, cosPhi);
    showResult(res);
}

void MainWindow::onCalcCurrent()
{
    double U = m_voltageInput->value();
    double P = m_activePowerInput->value();
    double cosPhi = m_cosPhiInput->value();

    if (cosPhi <= 0 || cosPhi > 1.0) {
        QMessageBox::warning(this, QStringLiteral("输入错误"),
                             QStringLiteral("功率因数必须满足 0 < cosφ ≤ 1"));
        return;
    }

    PowerResult res = PowerCalculator::calcFromActivePower(P, U, cosPhi);
    showResult(res);
}

void MainWindow::showResult(const PowerResult &res)
{
    m_resultActive->setText(
        QString::number(res.activePower, 'f', 3) + QStringLiteral(" W"));
    m_resultReactive->setText(
        QString::number(res.reactivePower, 'f', 3) + QStringLiteral(" var"));
    m_resultApparent->setText(
        QString::number(res.apparentPower, 'f', 3) + QStringLiteral(" VA"));
    m_resultPowerFactor->setText(
        QString::number(res.powerFactor, 'f', 4));
    m_resultCurrent->setText(
        QString::number(res.lineCurrent, 'f', 3) + QStringLiteral(" A"));
}
