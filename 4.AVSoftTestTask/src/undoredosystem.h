//Undo Redo система

#ifndef UNDOREDOSYSTEM_H
#define UNDOREDOSYSTEM_H

#include <QList>
#include "companymodel.h"

using namespace CompanyModel;
class URSCommand{
public:
    virtual void undo() = 0;   //то, что должно выполнится при вызове undo
    virtual void runDo() = 0;  //то, что должно выполнится при вызове redo
    virtual ~URSCommand() = default;
};
class UndoRedoSystem
{
private:
    static void addRedoCommand(URSCommand* com);
public:
    static const int STACK_SIZE = 16;
    static void addCommand(URSCommand* com);
    static void execUndo();
    static void execRedo();
    static void clear();
};
extern QList<URSCommand*> undoStack;
extern QList<URSCommand*> redoStack;

class URSeditEmployee : public URSCommand {
    Employee employee;
    int depIndex, empIndex;
    Employee newEmployee;
    Employee prevEmployee;
public:
    URSeditEmployee(Employee current, Employee newEmpl);
    ~URSeditEmployee(){};
    void runDo() override;
    void undo() override;
};

class URSeditDepartmentName : public URSCommand{
    QString newName;
    QString prevName;
    int depIndex;
public:
    URSeditDepartmentName(Department& d, QString nName);
    void runDo() override;
    void undo() override;
};

class URSaddNewEmployee : public URSCommand{
    Employee emp;
    int depIndex;
public:
    URSaddNewEmployee(Department& d, Employee e);
    void runDo() override;
    void undo() override;
};
class URSaddNewDepartment : public URSCommand{
    Department dep;
public:
    URSaddNewDepartment(Department d);
    void runDo() override;
    void undo() override;
};

class URSdeleteEmployee : public URSCommand{
    int depIndex;
    int empIndex;
    Employee emp;
public:
    URSdeleteEmployee(Employee emp);
    void runDo() override;
    void undo() override;
};
class URSdeleteDepartment : public URSCommand{
    int depIndex;
    Department dep;
public:
    URSdeleteDepartment(Department d);
    void runDo() override;
    void undo() override;
};

#endif // UNDOREDOSYSTEM_H
