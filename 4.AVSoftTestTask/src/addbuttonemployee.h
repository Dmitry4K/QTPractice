//класс, который отвечает за визулазицию кнопки "Добавить работника"
#ifndef ADDBUTTONEMPLOYEE_H
#define ADDBUTTONEMPLOYEE_H

#include <QWidget>
#include "companymodel.h"
namespace Ui {
class AddButtonEmployee;
}

class AddButtonEmployee : public QWidget
{
    Q_OBJECT
    CompanyModel::Department& department;
public:
    explicit AddButtonEmployee(CompanyModel::Department& d,QWidget *parent = nullptr);
    ~AddButtonEmployee();

private slots:
    void on_addButton_clicked();

private:
    Ui::AddButtonEmployee *ui;
};

#endif // ADDBUTTONEMPLOYEE_H
