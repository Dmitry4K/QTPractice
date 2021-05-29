#include "undoredosystem.h"

QList<URSCommand*> undoStack;
QList<URSCommand*> redoStack;

void UndoRedoSystem::addCommand(URSCommand *com){
    if(undoStack.size() == STACK_SIZE){
        delete undoStack.front();
        undoStack.pop_front();
    }
    undoStack.push_back(com);
}

void UndoRedoSystem::addRedoCommand(URSCommand* com){
    if(redoStack.size() == STACK_SIZE){
        delete redoStack.front();
        redoStack.pop_front();
    }
    redoStack.push_back(com);
}
void UndoRedoSystem::execUndo(){
    if(undoStack.size()){
        auto command = undoStack.back();
        undoStack.pop_back();
        command->undo();
        addRedoCommand(command);
    }
}
void UndoRedoSystem::execRedo(){
    if(redoStack.size()){
        auto command = redoStack.back();
        redoStack.pop_back();
        command->runDo();
        addCommand(command);
    }
}
void UndoRedoSystem::clear(){
    for(auto iter = undoStack.begin(); iter != undoStack.end(); ++iter){
        delete *iter;
    }
    for(auto iter = redoStack.begin(); iter != redoStack.end(); ++iter){
        delete *iter;
    }
    undoStack.clear();
    redoStack.clear();
}

URSeditEmployee::URSeditEmployee(Employee cur, Employee newEmpl):
    employee(cur),
    newEmployee(newEmpl),
    prevEmployee(cur)
{
    auto indexes = CompanyModel::Company::getInstance()->findIndexesOfEmp(cur);
    depIndex = indexes.first;
    empIndex = indexes.second;
}
void URSeditEmployee::runDo() {
    Employee* employee = CompanyModel::Company::getInstance()->getEmpFromDepByIndexes(depIndex, empIndex);
    if(employee){
        employee->set(newEmployee);
    }
}

void URSeditEmployee::undo() {
    Employee* employee = CompanyModel::Company::getInstance()->getEmpFromDepByIndexes(depIndex, empIndex);
    if(employee){
        employee->set(prevEmployee);
    }
}


URSeditDepartmentName::URSeditDepartmentName(Department& d, QString nName):
    newName(nName),
    prevName(d.getName())
{
    depIndex = CompanyModel::Company::getInstance()->findIndexOfDep(d);
}

void URSeditDepartmentName::runDo(){
    Department* dep = CompanyModel::Company::getInstance()->getDepByIndex(depIndex);
    if(dep){
        dep->setName(newName);
    }
}
void URSeditDepartmentName::undo(){
    Department* dep = CompanyModel::Company::getInstance()->getDepByIndex(depIndex);
    if(dep){
        dep->setName(prevName);
    }
}

URSaddNewEmployee::URSaddNewEmployee(Department& d, Employee e):
    emp(e)
{
    depIndex = CompanyModel::Company::getInstance()->findIndexOfDep(d);
}
void URSaddNewEmployee::runDo(){
    Department* dep = CompanyModel::Company::getInstance()->getDepByIndex(depIndex);
    dep->addEmployee(emp);
}
void URSaddNewEmployee::undo(){
    Department* dep = CompanyModel::Company::getInstance()->getDepByIndex(depIndex);
    dep->removeLast();
}

URSaddNewDepartment::URSaddNewDepartment(Department d): dep(d){}

void URSaddNewDepartment::runDo(){
    CompanyModel::Company::getInstance()->addDepartment(dep);
}
void URSaddNewDepartment::undo(){
    CompanyModel::Company::getInstance()->removeLastDep();
}

URSdeleteEmployee::URSdeleteEmployee(Employee e): emp(e){
    auto indexes = CompanyModel::Company::getInstance()->findIndexesOfEmp(emp);
    depIndex = indexes.first;
    empIndex = indexes.second;

}
void URSdeleteEmployee::runDo(){
    Employee* empPointer = CompanyModel::Company::getInstance()->getEmpFromDepByIndexes(depIndex, empIndex);
    if(empPointer){
       emit empPointer->delSignal(empPointer);
    }
}
void URSdeleteEmployee::undo(){
    Department* dep = CompanyModel::Company::getInstance()->getDepByIndex(depIndex);
    if(dep){
        dep->addEmployee(emp, empIndex);
    }
}
URSdeleteDepartment::URSdeleteDepartment(Department d) : dep(d){
    depIndex = CompanyModel::Company::getInstance()->findIndexOfDep(d);
}
void URSdeleteDepartment::runDo(){
    Department* dep = CompanyModel::Company::getInstance()->getDepByIndex(depIndex);
    if(dep){
        emit dep->delSignal(dep);
    }
}

void URSdeleteDepartment::undo(){
    CompanyModel::Company::getInstance()->addDepartment(dep, depIndex);
}
