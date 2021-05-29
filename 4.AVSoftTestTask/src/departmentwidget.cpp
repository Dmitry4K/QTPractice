#include "departmentwidget.h"
#include "employeewidget.h"
#include "addbuttonemployee.h"

DepartmentWidget::DepartmentWidget(CompanyModel::Department& d, QWidget* parent) :
    QWidget(parent),
    department(d)
{

    header = new DepartmentHeaderWidget(department);
    setFixedWidth(header->width()+35);
    vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    vLayout->addWidget(header);
    updateUI();
    QObject::connect(&department, SIGNAL(changed()), this, SLOT(updateUI()));
}

void DepartmentWidget::addEmployeeWidget(CompanyModel::Employee& e){
    auto ew = new EmployeeWidget(&e);
    QObject::connect(&e, SIGNAL(changed()), this->header, SLOT(updateUI()));
    vListLayout->addWidget(ew);
}

void DepartmentWidget::updateUI(){
    if(vLayout->count() == 2){
        vLayout->removeWidget(vLayout->itemAt(1)->widget());
    }
    header->updateUI();
    QScrollArea* scrollArea = new QScrollArea();
    QWidget* listWidget = new QWidget();
    vListLayout = new QVBoxLayout(listWidget);
    for(auto it = department.getEmployments().begin();
        it!=department.getEmployments().end();++it){
        addEmployeeWidget(*it);
    }
    vListLayout->addWidget(new AddButtonEmployee(department));
    scrollArea->setFixedHeight(400);
    scrollArea->setWidget(listWidget);
    vLayout->addWidget(scrollArea,1);
}

DepartmentWidget::~DepartmentWidget(){
    hide();
    while(auto item = vListLayout->takeAt(0)){
        delete item;
    }
    while(auto item = vLayout->takeAt(0)){
        delete item;
    }
    delete vLayout;
    delete vListLayout;
}
