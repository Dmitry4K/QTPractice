#include <QDebug>
#include "employeewidget.h"
#include "ui_employeewidget.h"
#include "employeewidgeteditor.h"
#include "undoredosystem.h"

EmployeeWidget::EmployeeWidget(CompanyModel::Employee* e, QWidget *parent) :
    QWidget(parent),
    employee(e),
    ui(new Ui::employeewidget)
{
    ui->setupUi(this);
    updateUI();
    QObject::connect(employee, SIGNAL(changed()), this, SLOT(updateUI()));
}

EmployeeWidget::~EmployeeWidget()
{
    delete ui;
    hide();
}
void EmployeeWidget::updateUI(){
    ui->nameLabel->setText(employee->getFullName());
    ui->functionLabel->setText(employee->getFunction());
    ui->salaryLabel->setText(QString::number(employee->getSalary())+"р.");
    emit changed();
}

void EmployeeWidget::on_edit_clicked()
{
    EmployeeWidgetEditor ewe;
    CompanyModel::Employee newEmployee = ewe.getEmployee(employee);
    if(!newEmployee.equals(*employee) && ewe.isOK()){

        auto command = new URSeditEmployee(*employee, newEmployee);
        UndoRedoSystem::addCommand(command);
        command->runDo();
        //employee.set(newEmployee);
    }
}

void EmployeeWidget::on_del_clicked()
{
    auto command = new URSdeleteEmployee(*employee);
    command->runDo();
    UndoRedoSystem::addCommand(command);
    qDebug() << "emit del signal from:" << &employee;
    //emit employee.delSignal(&employee);
}
