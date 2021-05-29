#include <QInputDialog>
#include "addbuttondepartment.h"
#include "ui_addbuttondepartment.h"
#include "companymodel.h"
#include "undoredosystem.h"
AddButtonDepartment::AddButtonDepartment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddButtonDepartment)
{
    ui->setupUi(this);
}

AddButtonDepartment::~AddButtonDepartment()
{
    delete ui;
}

void AddButtonDepartment::on_addButton_clicked()
{
    CompanyModel::Department dep;
    dep.setName("Новый отдел");
    auto command = new URSaddNewDepartment(dep);
    UndoRedoSystem::addCommand(command);
    command->runDo();
    //CompanyModel::Company::getInstance()->addDepartment(dep);
}
