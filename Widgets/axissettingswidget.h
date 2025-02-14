/****************************************************************************
**  Copyright (c) 2019, Adel Kara Slimane <adel.ks@zegrapher.com>
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

#ifndef AXISSETTINGS_H
#define AXISSETTINGS_H

#include <QWidget>

#include "numberlineedit.h"
#include "qcolorbutton.h"
#include "information.h"

namespace Ui {
class AxisSettingsWidget;
}

class AxisSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AxisSettingsWidget(Information *information, QWidget *parent = nullptr);
    ZeAxisSettings getAxisSettings(ZeAxisName name);
    ZeAxesSettings getAxesSettings();
    ZeGridSettings getGridSettings();
    ~AxisSettingsWidget();

public slots:
    void apply();
    void processUserInput();
    void loadDefaults();

signals:
    void settingsUpdated();

protected slots:
    void swapGridData();

protected:
    void axisTypeChanged();
    void swapAxisData();
    void loadAxisSettingsInUi(ZeAxisName name);
    void loadAxisSettingsInUi(const ZeAxisSettings &axesSettings);
    void loadGridSettingsInUi(ZeAxisName name);
    void loadGridSettingsInUi(const Ze1DGridSettings &unidimGridSettings);

    void makeConnects();

    Ui::AxisSettingsWidget *ui;
    NumberLineEdit *baseLineEdit, *constantMultiplierLineEdit;
    QColorButton *axisColorButton;
    Information *information;
    QColorButton *gridColorButton, *subgridColorButton;

    ZeAxisName currentAxis;
    ZeAxesSettings axesSettings;
    ZeGridSettings gridSettings;
};

#endif // AXISSETTINGS_H
