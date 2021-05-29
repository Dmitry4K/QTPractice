//Виджет отдела
#pragma once

#include <QObject>
#include <QtWidgets>
#include "departmentheaderwidget.h"
#include "companymodel.h"
#include "employeewidget.h"

class DepartmentWidget : public QWidget
{
    Q_OBJECT
    CompanyModel::Department& department;
    DepartmentHeaderWidget* header;
    QVBoxLayout* vListLayout;
    QVBoxLayout* vLayout;
public:
    explicit DepartmentWidget(CompanyModel::Department& d, QWidget* parent = nullptr);
    ~DepartmentWidget();
    void addEmployeeWidget(CompanyModel::Employee& e);
public slots:
    void updateUI();
};

