//Виджет с названием отдела, количеством сотрудников и средней заработной платы

#pragma once

#include <QtWidgets>
#include "companymodel.h"
namespace Ui {
class departmentheaderwidget;
}

class DepartmentHeaderWidget : public QWidget
{
    Q_OBJECT
    CompanyModel::Department& department;
public:
    explicit DepartmentHeaderWidget(CompanyModel::Department& d, QWidget *parent = nullptr);
    ~DepartmentHeaderWidget();

public slots:
    void updateName();
    void updateUI();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::departmentheaderwidget *ui;
};
