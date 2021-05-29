#include "addbuttonemployee.h"
#include "ui_addbuttonemployee.h"
#include "employeewidgeteditor.h"
#include "undoredosystem.h"
AddButtonEmployee::AddButtonEmployee(CompanyModel::Department& d,QWidget *parent ) :
    QWidget(parent),
    department(d),
    ui(new Ui::AddButtonEmployee)
{
    ui->setupUi(this);
}

AddButtonEmployee::~AddButtonEmployee()
{
    delete ui;
}

void AddButtonEmployee::on_addButton_clicked()
{
    EmployeeWidgetEditor ewe;
    CompanyModel::Employee empl = ewe.getEmployee();
    auto command = new URSaddNewEmployee(department, empl);
    UndoRedoSystem::addCommand(command);
    command->runDo();
    //department.addEmployee(empl);
}
