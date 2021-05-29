#include "departmentheaderwidget.h"
#include "ui_departmentheaderwidget.h"
#include "undoredosystem.h"
DepartmentHeaderWidget::DepartmentHeaderWidget(CompanyModel::Department& d, QWidget *parent) :
    QWidget(parent),
    department(d),
    ui(new Ui::departmentheaderwidget)
{
    ui->setupUi(this);
    updateUI();
}

DepartmentHeaderWidget::~DepartmentHeaderWidget()
{
    delete ui;
}

void DepartmentHeaderWidget::on_pushButton_clicked()
{
    bool ok;
    QString newDepName = QInputDialog::getText(this, tr("Редакирование"),
                                        tr("Наименование отдела:"),
                                        QLineEdit::Normal,ui->departementName->text(), &ok);
    if(CompanyModel::Department::isCorrectDepartmentName(newDepName) && ok){
        auto command = new URSeditDepartmentName(department, newDepName);
        UndoRedoSystem::addCommand(command);
        command->runDo();
        //department.setName(newDepName);
        //updateName();
    }
}

void DepartmentHeaderWidget::updateUI(){
    updateName();
    int avgsal = 0;
    for(auto iter = department.getEmployments().begin(); iter != department.getEmployments().end(); ++iter){
        avgsal += iter->getSalary();
    }
    ui->peopleCount->setText(QString::number(department.getEmployments().size()));
    if(department.getEmployments().size()){
        ui->avgSalary->setText(QString::number(avgsal/department.getEmployments().size()));
    } else {
        ui->avgSalary->setText("-");
    }
}

void DepartmentHeaderWidget::updateName(){
    ui->departementName->setText(department.getName());
}

void DepartmentHeaderWidget::on_pushButton_2_clicked()
{
    auto command = new URSdeleteDepartment(department);
    command->runDo();
    UndoRedoSystem::addCommand(command);
    //emit department.delSignal(&department);
}
