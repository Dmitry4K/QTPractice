//Виджет работника
#pragma once
#include <QWidget>
#include <companymodel.h>

namespace Ui {
class employeewidget;
}

class EmployeeWidget : public QWidget
{
    Q_OBJECT
    CompanyModel::Employee* employee;

public:
    explicit EmployeeWidget(CompanyModel::Employee* e, QWidget *parent = nullptr);
    ~EmployeeWidget();

private slots:
    void updateUI();
    void on_edit_clicked();
    void on_del_clicked();

signals:
    void changed();
    void deleted(CompanyModel::Employee* e);
private:
    Ui::employeewidget *ui;
};

