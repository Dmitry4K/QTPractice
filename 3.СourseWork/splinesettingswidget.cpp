#include "splinesettingswidget.h"
#include "pointfieldwidget.h"
#include<QLabel>
SplineSettingsWidget::SplineSettingsWidget(CardinalSplineClass* s): spline(s)
{
    setFixedWidth(240);
    plusButton->setMinimumWidth(32);
    plusButton->setMaximumWidth(32);
    minusButton->setMinimumWidth(32);
    minusButton->setMaximumWidth(32);

    vLayout = new QVBoxLayout(this);

    auto hPointsLayout = new QHBoxLayout;
    vLayout->addLayout(hPointsLayout);
        hPointsLayout->addWidget(new QLabel("Points"));
        hPointsLayout->addWidget(plusButton);
            plusButton->setText("+");

        hPointsLayout->addWidget(minusButton);
            minusButton->setText("-");
    vLayout->addWidget(saPoints);

    saPoints->setWidget(pw);
    QObject::connect(plusButton, SIGNAL(clicked()), this, SLOT(onClickPlusButton()));
    QObject::connect(minusButton, SIGNAL(clicked()), this, SLOT(onClickMinusButton()));
}

void SplineSettingsWidget::onClickPlusButton(){
    pw->addField();
    update();
}

void SplineSettingsWidget::onClickMinusButton(){
    pw->removeFiled(pw->count()-1);
    update();
}
