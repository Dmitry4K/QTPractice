#ifndef COMPANYMODEL_H
#define COMPANYMODEL_H

#include<QString>
#include<QList>
#include<memory>
#include<QObject>

//Модель приложения:
//   ----------      ------------      ---------
//  | Employee | -> | Department | -> | Company |
//   ----------      ------------      ---------
namespace CompanyModel {

    class Employee : public QObject{
        Q_OBJECT
        QString surname;
        QString name;
        QString middlename;
        QString function;
        int salary = 0;
    public:
        QString getName() const;
        QString getSurname() const;
        QString getMiddleName() const;
        QString getFunction() const;
        int getSalary() const;
        void setName(const QString& n);
        void setFunction(const QString& f);
        void setMiddleName(const QString& mn);
        void setSurname(const QString& sn);
        void setSalary(int s);
        QString getFullName();      //возвращает полное имя работника (ФИО)
        bool equals(const Employee& e);
        void set(const Employee& a);    //копирование данных из объекта
        Employee(){};
        Employee(const Employee& a);
        bool operator==(const Employee& a);
        Employee& operator=(const Employee& a);
    public slots:
    signals:
        void delSignal(Employee* e);    //сигнал, который посылается объектом, если он должен быть удален
        void changed();
    };


    class Department : public QObject{
        Q_OBJECT
        QString name;
        QList<Employee> employments;
    public:
        QString getName() const;
        void setName(const QString& n);
        QList<Employee>& getEmployments();
        const QList<Employee>& getEmployments() const;
        void addEmployee(Employee e, int index = -1);
        void removeLast();
        Department& operator=(const Department& a);
        bool operator==(const Department& a);
        static bool isCorrectDepartmentName(const QString& name);   //проверяет название отдела
        Employee* getEmpByIndex(int index);
        int findIndexOfEmp(const Employee& emp);
        Department(){};
        void removeEmpByIndex(int index);
        Department(const Department&);
    public slots:
        void applyDeleting(Employee* emp);  //слот, который принимает сигнал от работника и удаляет его
    signals:
        void delSignal(Department*);
        void changed();
    };


    class Company : public QObject {
        Q_OBJECT
    private:
        Company(){};
    public:
        static Company* getInstance();     //получаем указатель на экземпляр Company
        Department* getDepByIndex(int index);
        Employee* getEmpFromDepByIndexes(int dIndex, int eIndex);
        void setSettings();
        QList<CompanyModel::Department> departments;
        void setData(QList<CompanyModel::Department> nData);
        void clear();                       //Производим очистку, удаляем все отделы
        void addDepartment(CompanyModel::Department dep, int index = -1);
        void removeDepByIndex(int index);
        void removeLastDep();
        int findIndexOfDep(const Department& dep);
        QPair<int,int> findIndexesOfEmp(const Employee& emp);
    public slots:
        void applyDeleting(Department*);    //cлот, который принимает сигнал от отдела и удаляет его
    signals:
        void dataChanged();
    };

    extern Company* company;
}


#endif
