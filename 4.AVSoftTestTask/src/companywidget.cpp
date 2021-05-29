#include <QtWidgets>
#include <QObject>
#include <QSizePolicy>
#include "companywidget.h"
#include "departmentwidget.h"
#include "addbuttondepartment.h"
CompanyWidget::CompanyWidget(QList<CompanyModel::Department>& company, QWidget* parent):
    QWidget(parent),
    Company(company)
{
    QObject::connect(CompanyModel::Company::getInstance(), SIGNAL(dataChanged()), this, SLOT(updateUI()));
    //hLayoutWidget = new QWidget();
   // hLayoutWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    updateUI();
}
void CompanyWidget::addDepartmentWidget(CompanyModel::Department& d){
    auto widget = new DepartmentWidget(d);
    setFixedHeight(530);
    qWarning() << width() << ' '<<   widget->width();
    hLayoutWidget->setFixedHeight(550);
    hLayoutWidget->setFixedWidth(hLayoutWidget->width() + widget->width());
    setFixedWidth(hLayoutWidget->width());
    hLayout->addWidget(widget);
    dWidgets.append(widget);
}
void CompanyWidget::updateUI(){
    delete hLayoutWidget;
    hLayoutWidget = new QWidget();
    hLayout = new QHBoxLayout(hLayoutWidget);
    hLayoutWidget->setFixedWidth(0);
    setFixedWidth(0);
    hLayout->setAlignment(Qt::AlignLeft);
    for(auto iter = Company.begin();iter != Company.end();++iter){
        addDepartmentWidget(*iter);
        qWarning() << "widget added";
    }
    auto abd = new AddButtonDepartment();
    hLayoutWidget->setFixedWidth(hLayoutWidget->width() + abd->width());
    setFixedWidth(hLayoutWidget->width());
    hLayout->addWidget(abd);
    hLayoutWidget->setParent(this);
    hLayoutWidget->show();
    qWarning() << this->children().count();
}
