/****************************************************************************
**  Copyright (c) 2016, Adel Kara Slimane <adel.ks@zegrapher.com>
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




#ifndef PRINTPREVIEW_H
#define PRINTPREVIEW_H

#include "imagepreview.h"
#include <QPdfWriter>
#include <QPageLayout>

#define RELATIVE_MIN_SIZE 0.25

enum MouseActionType {NOTHING, TOPLEFT_CORNER, TOPRIGHT_CORNER,
                      BOTTOMLEFT_CORNER, BOTTOMRIGHT_CORNER, LEFT_SIDE,
                     TOP_SIDE, RIGHT_SIDE, BOTTOM_SIDE, ALL};

enum ExportType {SCALABLE, IMAGE};
enum SheetSizeType {NORMALISED, CUSTOM};



class ExportPreview : public ImagePreview
{
    Q_OBJECT

public:
    explicit ExportPreview(QSizeF sheetSizeCm, QSize imageSizePixels, ExportType exportType, Information *info);

    void setOrientation(QPageLayout::Orientation type);
    void setSheetMarginCm(double sheetMarginCm);
    void setImageMarginPx(int imageMarginPx);

    double getMinFigureSize();
    QSize getTargetSheetSizePixels();

signals:
    void newFigureSizeCm(QSizeF sizeCm);
    void newZoomValue(double value);

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void setFigureSizeCm(QSizeF sizeCm);
    void setSheetSizeCm(QSizeF sizeCm);
    void setScale(double scalingFactor);
    void exportPDF(QString fileName, SheetSizeType sizeType);


protected:
    void initialise();
    void paintEvent(QPaintEvent *event);
    void drawSheet();
    void drawGraph();
    QRect sheetRectFromViewRect(QRect viewRect);
    void drawFigureRect();
    void assignMouseRects();
    void printCurves();
    void constrainCanvasRectRel();
    QRect getFigureRectFromRelative(QRect refSheetRect);
    void scaleView(QRect refSheetRect);
    void setMaximalCanvas();

    QPageLayout::Orientation orientation;
    double minRelSize;
    double sheetMarginCm;
    int imageMarginPx;
    // margin to the sheet where the graph can be, this value is used for the smaller edge of the sheet
    // the other margin is scaled accordingly
    double userScalingFactor, screenResolution, currentZoom;
    QSize targetSheetSizePixels;
    QRect figureRect, sheetRect, sheetRectScaled;
    QSizeF figureSizeCm, sheetSizeCm;
    QSize figureSizePixels, imageSizePixels;
    QRectF figureRectRelative;
    QRect topLeft, topRight, top, left, right, bottom, bottomLeft, bottomRight;

    QPoint lastMousePos ;
    MouseActionType moveType;
    QString fileName;

    ExportType exportType;

};

#endif // PRINTPREVIEW_H
