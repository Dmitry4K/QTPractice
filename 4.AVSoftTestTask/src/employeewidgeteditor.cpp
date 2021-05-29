#include "employeewidgeteditor.h"
#include "ui_employeewidgeteditor.h"

EmployeeWidgetEditor::EmployeeWidgetEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeWidgetEditor)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptEWE()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejectEWE()));
}

EmployeeWidgetEditor::~EmployeeWidgetEditor()
{
    delete ui;
}

bool EmployeeWidgetEditor::isOK(){
    return ok;
}

void EmployeeWidgetEditor::acceptEWE(){
    ok = true;
    accept();
}
void EmployeeWidgetEditor::rejectEWE(){
    ok = false;
    reject();
}
CompanyModel::Employee EmployeeWidgetEditor::getEmployee(const CompanyModel::Employee* emp){
    if(emp != nullptr){
        ui->lineEditName->setText(emp->getName());
        ui->lineEditMiddleName->setText(emp->getMiddleName());
        ui->lineEditFunction->setText(emp->getFunction());
        ui->lineEditSurname->setText(emp->getSurname());
        ui->spinBoxSalary->setValue(emp->getSalary());
    }
    setModal(true);
    exec();
    CompanyModel::Employee e;
    if(isOK()){
        e.setFunction(ui->lineEditFunction->text());
        e.setName(ui->lineEditName->text());
        e.setMiddleName(ui->lineEditMiddleName->text());
        e.setSurname(ui->lineEditSurname->text());
        e.setSalary(ui->spinBoxSalary->value());
    }
    return e;
}
