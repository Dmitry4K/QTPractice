//Виджет для редактирования данных работника
#ifndef EMPLOYEEWIDGETEDITOR_H
#define EMPLOYEEWIDGETEDITOR_H

#include <QWidget>
#include <QDialog>
#include "companymodel.h"

namespace Ui {
class EmployeeWidgetEditor;
}

class EmployeeWidgetEditor : public QDialog
{
    Q_OBJECT
    bool ok = false;
public:
    explicit EmployeeWidgetEditor(QWidget *parent = nullptr);
    ~EmployeeWidgetEditor();
    //основная функция виджета, возвращает новый экземпляр работника
    CompanyModel::Employee getEmployee(const CompanyModel::Employee* emp = nullptr);
    bool isOK();

private:
    Ui::EmployeeWidgetEditor *ui;
public slots:
    void acceptEWE();
    void rejectEWE();
};

#endif // EMPLOYEEWIDGETEDITOR_H
