#ifndef GRAPHGRIDCALCULATOR_H
#define GRAPHGRIDCALCULATOR_H

#include <QObject>

#include "information.h"

#define TARGET_TICKS_NUM 20

struct ZeLogAxisTick
{
    double pos;
    QString baseStr, globalConstantStr;
    double base, globalConstant;
    long multiplier, subMultiplier, powerNumerator, powerDenominator;
};

struct ZeLinAxisTick
{
    double pos;
    QString posStr;
};

struct ZeAxisSubTick
{
    double pos;
    int numerator, denominator;
};

struct ZeOffset
{
    double sumOffset;
    int sumPowerOffset, basePowerOffset;
};

struct ZeLogAxisTicks
{
    QList<ZeLogAxisTick> ticks;
    QList<ZeAxisSubTick> axisSubticks;
};

struct ZeLinAxisTicks
{
    ZeOffset offset;
    QList<ZeLinAxisTick> ticks;
    QList<ZeAxisSubTick> axisSubticks;
};

class GridCalculator : public QObject
{
    Q_OBJECT
public:
    explicit GridCalculator(Information *info, QObject *parent = nullptr);

    ZeLinAxisTicks getLinearAxisTicks(double pxWidth,
                                   const ZeAxisRange &range,
                                   ZeAxisName axisName,
                                   const QFontMetrics &metrics);

signals:

protected:
    Information *information;
    double targetTicksNum;

};

#endif // GRAPHGRIDCALCULATOR_H
