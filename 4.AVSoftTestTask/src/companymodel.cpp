#include "companymodel.h"
#include <QDebug>

CompanyModel::Company* CompanyModel::company = nullptr;

//COMPANY SPACE --------------------------------------------------------------------------------------------------
CompanyModel::Company* CompanyModel::Company::getInstance() {
    if(CompanyModel::company == nullptr){
        CompanyModel::company = new CompanyModel::Company();
    }
    return CompanyModel::company;
}

void CompanyModel::Company::setData(QList<CompanyModel::Department> nData){
    departments = nData;
    setSettings();
    emit dataChanged();
}

void CompanyModel::Company::clear(){
    departments.clear();
    emit dataChanged();
}

void CompanyModel::Company::setSettings(){
    using namespace CompanyModel;
    for(auto dep = departments.begin(); dep != departments.end();++dep){
        QObject::connect(&*dep, SIGNAL(delSignal(Department*)), this, SLOT(applyDeleting(Department*)));
        for(auto emp = dep->getEmployments().begin();emp != dep->getEmployments().end(); ++emp){
            QObject::connect(&*emp, SIGNAL(delSignal(Employee*)), &*dep, SLOT(applyDeleting(Employee*)));
        }
    }
}

void CompanyModel::Company::addDepartment(CompanyModel::Department dep, int index){
    if(index == -1){
        departments.append(dep);
        QObject::connect(&departments.back(), SIGNAL(delSignal(Department*)), this, SLOT(applyDeleting(Department*)));
    } else {
        departments.insert(index, dep);
        QObject::connect(&departments[index], SIGNAL(delSignal(Department*)), this, SLOT(applyDeleting(Department*)));

    }

    emit dataChanged();
}

void CompanyModel::Company::removeDepByIndex(int index){
    if(index < departments.size()){
        QObject::disconnect(&departments[index], SIGNAL(delSignal(Department*)), this, SLOT(applyDeleting(Department*)));
        departments.removeAt(index);
        emit dataChanged();
    }
}
void CompanyModel::Company::removeLastDep(){
    removeDepByIndex(departments.size()-1);
}
void CompanyModel::Company::applyDeleting(CompanyModel::Department* d){
    if(departments.removeOne(*d)){
        emit dataChanged();
    }
}
CompanyModel::Department* CompanyModel::Company::getDepByIndex(int index){
    Department* result = nullptr;
    if(index < departments.size()){
        result = & departments[index];
    }
    return result;
}

CompanyModel::Employee* CompanyModel::Company::getEmpFromDepByIndexes(int dIndex, int eIndex){
    Employee* result = nullptr;
    Department* dep = getDepByIndex(dIndex);
    if(dep){
        result = dep->getEmpByIndex(eIndex);
    }
    return result;
}

int CompanyModel::Company::findIndexOfDep(const CompanyModel::Department& dep){
    return departments.indexOf(dep);
}


QPair<int,int> CompanyModel::Company::findIndexesOfEmp(const CompanyModel::Employee& emp){
    int dIndex = -1;
    int dEmp = -1;

    for(int i = 0;i<departments.size(); ++i){
        dEmp = departments[i].findIndexOfEmp(emp);
        if(dEmp != -1){
            dIndex = i;
            break;
        }
    }
    return QPair<int, int>(dIndex, dEmp);
}

//EMPLOYEE SPACE --------------------------------------------------------------------------------------------------
QString CompanyModel::Employee::getFullName(){
    return name + ' ' + surname + ' ' + middlename;
}
QString CompanyModel::Employee::getName() const{
    return name;
}
QString CompanyModel::Employee::getSurname() const{
    return surname;
}
QString CompanyModel::Employee::getMiddleName() const{
    return middlename;
}
QString CompanyModel::Employee::getFunction() const{
    return function;
}
int CompanyModel::Employee::getSalary() const{
    return salary;
}
void CompanyModel::Employee::setName(const QString& n){
    name = n;
}
void CompanyModel::Employee::setFunction(const QString& f){
    function = f;
}
void CompanyModel::Employee::setMiddleName(const QString& mn){
    middlename = mn;
}
void CompanyModel::Employee::setSurname(const QString& sn){
    surname = sn;
}
void CompanyModel::Employee::setSalary(int s){
    salary = s;
}

bool CompanyModel::Employee::equals(const Employee& e){
    return name == e.getName() &&
            function == e.getFunction() &&
            surname == e.getSurname() &&
            middlename == e.getMiddleName() &&
            salary == e.getSalary();
}

void CompanyModel::Employee::set(const Employee& a){
    if(!this->equals(a)){
        this->setName(a.getName());
        this->setFunction(a.getFunction());
        this->setMiddleName(a.getMiddleName());
        this->setSalary(a.getSalary());
        this->setSurname(a.getSurname());
        emit changed();
    }
}

bool CompanyModel::Employee::operator==(const Employee& a){
    return this->equals(a);
}

CompanyModel::Employee& CompanyModel::Employee::operator=(const Employee& a){
    this->set(a);
    return *this;
}

CompanyModel::Employee::Employee(const Employee& a){
    this->set(a);
}

//DEPARTMENT SPACE --------------------------------------------------------------------------------------------------
bool CompanyModel::Department::isCorrectDepartmentName(const QString &name){
    return name.size() != 0;
}

void CompanyModel::Department::applyDeleting(Employee* emp){
    if(employments.removeOne(*emp)){
        emit changed();
    }
}

CompanyModel::Department& CompanyModel::Department::operator=(const Department& a){
    this->name = a.name;
    this->employments=  a.employments;
    return *this;
}

CompanyModel::Department::Department(const Department& a){
    *this = a;
}

bool CompanyModel::Department::operator==(const Department& a){
    return this->name == a.name &&
            this->employments == a.employments;
}

QList<CompanyModel::Employee>& CompanyModel::Department::getEmployments(){
    return employments;
}

const QList<CompanyModel::Employee>& CompanyModel::Department::getEmployments() const{
    return employments;
}
void CompanyModel::Department::addEmployee(Employee e, int index){
    if(index == -1){
        employments.append(e);
        QObject::connect(&employments.back(), SIGNAL(delSignal(Employee*)), this, SLOT(applyDeleting(Employee*)));

        qDebug() << "connected del sginal from: " << &employments.back();
    } else {
        employments.insert(index, e);
        QObject::connect(&employments[index], SIGNAL(delSignal(Employee*)), this, SLOT(applyDeleting(Employee*)));
    }
    emit changed();
}

void CompanyModel::Department::removeLast(){
    QObject::disconnect(&employments.back(), SIGNAL(delSignal(Employee*)), this, SLOT(applyDeleting(Employee*)));
    employments.removeLast();
    emit changed();
}
QString CompanyModel::Department::getName() const{
    return name;
}
void CompanyModel::Department::setName(const QString& n){
    name = n;
    emit changed();
}

CompanyModel::Employee* CompanyModel::Department::getEmpByIndex(int index){
    Employee* result = nullptr;
    if(index < employments.size()){
        result = &employments[index];
    }
    return result;
}

int CompanyModel::Department::findIndexOfEmp(const Employee& emp){
    return employments.indexOf(emp);
}

void CompanyModel::Department::removeEmpByIndex(int index){
    employments.removeAt(index);
    emit changed();
    //emit employments[index].delSignal(&employments[index]);
}

