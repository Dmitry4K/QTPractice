//Виджет с деревом сотрудников
#ifndef COMPANYWIDGET_H
#define COMPANYWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "companymodel.h"
#include "departmentwidget.h"

class CompanyWidget : public QWidget
{
    Q_OBJECT
    QList<CompanyModel::Department>& Company;
    QList<DepartmentWidget*> dWidgets;
    void deleteHLayoutWidgets();
public:
    QHBoxLayout* hLayout = nullptr;
    QWidget* hLayoutWidget = nullptr;
    void addDepartmentWidget(CompanyModel::Department& d);
    CompanyWidget(QList<CompanyModel::Department>& company, QWidget* parent = nullptr);
public slots:
    void updateUI();
signals:
    void changed();
};

#endif // COMPANYWIDGET_H
