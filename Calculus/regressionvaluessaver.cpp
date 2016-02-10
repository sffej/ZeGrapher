/****************************************************************************
**  Copyright (c) 2015, Adel Kara Slimane <adel.ks@zegrapher.com>
**
**  This file is part of ZeGrapher's source code.
**
**  ZeGrapher is free software: you may copy, redistribute and/or modify it
**  under the terms of the GNU General Public License as published by the
**  Free Software Foundation, either version 3 of the License, or (at your
**  option) any later version.
**
**  This file is distributed in the hope that it will be useful, but
**  WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**  General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "regressionvaluessaver.h"

#include <iostream>

using namespace std;

RegressionValuesSaver::RegressionValuesSaver(double pixStep, Regression *reg)
{    
    regression = reg;
    pixelStep = pixStep;   
}

RegressionValuesSaver::RegressionValuesSaver(const RegressionValuesSaver &other) : QObject()
{
    regression = other.regression;
    pixelStep = other.pixelStep;
}

RegressionValuesSaver& RegressionValuesSaver::operator=(const RegressionValuesSaver &other)
{
    regression = other.regression;
    pixelStep = other.pixelStep;

    return *this;
}

Regression* RegressionValuesSaver::getRegression()
{
    return regression;
}

void RegressionValuesSaver::setRegression(Regression *reg)
{
    regression = reg;
}

void RegressionValuesSaver::recalculate()
{
    recalculate(Point{xUnit, yUnit}, graphRange);
}

void RegressionValuesSaver::recalculate(Point graphUnits, GraphRange range)
{   
    graphRange = range;
    xUnit = graphUnits.x;
    yUnit = graphUnits.y;
    xUnitStep = pixelStep / xUnit;

    curves.clear();

    if(regression->isPolar())
        calculatePolarRegressionCurve();
    else calculateCartesianRegressionCurve();

}

void RegressionValuesSaver::setPixelStep(double dist)
{
    pixelStep = dist;
    recalculate();
}

QList<QPolygonF> &RegressionValuesSaver::getCurves()
{
    return curves;
}

void RegressionValuesSaver::move(GraphRange newRange)
{
    graphRange = newRange;

    if(regression->isPolar())
    {
        Range newAngleRange = getGraphAngleRange();
        if(newAngleRange.start != graphAngleRange.start || newAngleRange.end != graphAngleRange.end)
            polarMove();
    }
    else cartesianMove();
}

double RegressionValuesSaver::arg(QPointF pt)
{
    if(pt.y() == 0)
    {
        if(pt.x() >= 0)
            return 0;
        else return -M_PI;
    }

    double res = 2*atan(pt.y() / (pt.x() + length(pt)));    

    return res;
}

Range RegressionValuesSaver::getGraphAngleRange()
{
    QRectF graphWin = graphRange.getRect();
    Range angleRange;

    if(graphWin.contains(0,0))
    {
        angleRange.start = -M_PI;
        angleRange.end = M_PI;
        return angleRange;
    }

    if(graphWin.left() >= 0 && graphWin.bottom() <=0 && graphWin.top() >= 0)
        //correction to the only discontinuity case since arg gives values in [0,2pi] and angle start must always be smaller than end
    {
        angleRange.start = arg(graphWin.bottomLeft());
        angleRange.end = arg(graphWin.topLeft());
    }
    else if(graphWin.left() >= 0 && graphWin.bottom() >=0)
    {
        angleRange.start = arg(graphWin.bottomRight());
        angleRange.end = arg(graphWin.topLeft());
    }
    else if(graphWin.left() <= 0 && graphWin.right() >=0 && graphWin.bottom() >= 0)
    {
        angleRange.start = arg(graphWin.bottomRight());
        angleRange.end = arg(graphWin.bottomLeft());
    }
    else if(graphWin.right() <= 0 && graphWin.bottom() >=0)
    {
        angleRange.start = arg(graphWin.topRight());
        angleRange.end = arg(graphWin.bottomLeft());
    }
    else if(graphWin.right() <= 0 && graphWin.bottom() <=0 && graphWin.top() >= 0)
    {
        angleRange.start = arg(graphWin.topRight());
        angleRange.end = arg(graphWin.bottomRight())+2*M_PI;
    }
    else if(graphWin.right() <= 0 && graphWin.top() <=0)
    {
        angleRange.start = arg(graphWin.topLeft());
        angleRange.end = arg(graphWin.bottomRight());
    }
    else if(graphWin.right() >= 0 && graphWin.left() <=0 && graphWin.top() <= 0)
    {
        angleRange.start = arg(graphWin.topLeft());
        angleRange.end = arg(graphWin.topRight());
    }
    else // if(graphWin.left() >= 0 && graphWin.top() <=0)
    {
        angleRange.start = arg(graphWin.bottomLeft());
        angleRange.end = arg(graphWin.topRight());
    }

    return angleRange;

}

void RegressionValuesSaver::polarMove()
{
    curves.clear();

    calculatePolarRegressionCurve();
}

void RegressionValuesSaver::cartesianMove()
{    
    drawnRange.start = std::max(graphRange.Xmin, regression->getDrawRange().start);
    drawnRange.end = std::min(graphRange.Xmax, regression->getDrawRange().end);

    double x = curves.first().first().x()/xUnit - xUnitStep;

    if(x >= drawnRange.start)
    {
        while(x >= drawnRange.start)
        {
            curves.first().prepend(QPointF(x * xUnit, - regression->eval(x) * yUnit));
            x -= xUnitStep;
        }
    }
    else
    {
        while(x < drawnRange.start - xUnitStep)
        {
            curves.first().removeFirst();
            x += xUnitStep;
        }
    }

    x = curves.first().last().x()/xUnit + xUnitStep;

    if(x >= drawnRange.start)
    {
        while(x <= drawnRange.end)
        {
            curves.first() << QPointF(x * xUnit, - regression->eval(x) * yUnit);
            x += xUnitStep;
        }
    }
    else
    {
        while(x > drawnRange.end + xUnitStep)
        {
            curves.first().removeLast();
            x -= xUnitStep;
        }
    }
}

void RegressionValuesSaver::calculateCartesianRegressionCurve()
{    
    drawnRange.start = std::max(graphRange.Xmin, regression->getDrawRange().start);
    drawnRange.end = std::min(graphRange.Xmax, regression->getDrawRange().end);

    double x = drawnRange.start - xUnitStep;

    QPolygonF curve;
    curve.reserve((int)((drawnRange.end - drawnRange.start)/xUnitStep));

    while(x <= drawnRange.end + xUnitStep)
    {
        curve << QPointF(x * xUnit, - regression->eval(x) * yUnit);
        x += xUnitStep;
    }

    curves << curve;
}

double RegressionValuesSaver::squareLength(QPointF pt)
{
    return QPointF::dotProduct(pt, pt);
}

double RegressionValuesSaver::length(QPointF pt)
{
    return sqrt(squareLength(pt));
}

QPointF RegressionValuesSaver::orthogonalVector(const QPointF &pt)
{
    return QPointF(pt.y(), -pt.x());
}

void RegressionValuesSaver::calculatePolarRegressionCurve()
{

    // limit the angle's range to graphrange.

    Range regRange = regression->getDrawRange();
    graphAngleRange = getGraphAngleRange();

    double angle = regRange.start, radius = 0, deltaAngle = 0.001, basicDeltaAngle = 0;
    double normalisedAngle;
    QPointF nextPt, delta;

    QPolygonF curve;

    while(angle < regRange.end)
    {
        normalisedAngle = remainder(angle, 2*M_PI);

        if(graphAngleRange.end > M_PI && normalisedAngle <= remainder(graphAngleRange.end, 2*M_PI))
            normalisedAngle += 2*M_PI;


        if(normalisedAngle < graphAngleRange.start - deltaAngle)
        {
            angle += graphAngleRange.start - normalisedAngle;
            if(curve.size() > 1)
                curves << curve;
            curve.clear();
        }
        else if(graphAngleRange.end + deltaAngle < normalisedAngle)
        {
            angle += 2*M_PI - (graphAngleRange.end - graphAngleRange.start) - (normalisedAngle - graphAngleRange.end);
            if(curve.size() > 1)
                curves << curve;
            curve.clear();
        }
        else
        {
            radius = regression->eval(angle);
            curve << QPointF(radius * cos(angle) * xUnit, - radius * sin(angle) * yUnit);

            basicDeltaAngle = min(0.001, fabs(atan(pixelStep/sqrt(QPointF::dotProduct(curve.last(), curve.last())))));
            angle += basicDeltaAngle;

            radius = regression->eval(angle);
            nextPt = QPointF(radius * cos(angle) * xUnit, - radius * sin(angle) * yUnit);

            delta = nextPt - curve.last();
            delta *= pixelStep/sqrt(QPointF::dotProduct(delta, delta));

            nextPt = curve.last() + delta;

            deltaAngle = fabs(acos((QPointF::dotProduct(curve.last(), nextPt) / (length(curve.last() * length(nextPt))))));
            if(deltaAngle == 0)
                deltaAngle = 0.0001;


            angle += deltaAngle - basicDeltaAngle;
        }
    }

    if(curve.size() > 1)
        curves << curve;
    curve.clear();
}


RegressionValuesSaver::~RegressionValuesSaver()
{

}

