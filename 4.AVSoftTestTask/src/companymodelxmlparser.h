//Парсинг файла

#pragma once

#include<QXmlStreamReader>
#include<string>
#include<QTextStream>
#include"companymodel.h"

class CompanyModelXMLParser
{
    QString meta(); //генерирует строку с мета информацией для XML файла
    QString getBlock(const QString& text);  //генерируется строка <text>
    QString getBlockWithName(const QString& text, const QString& name); //генерируется строка <text name="name">
    QString getCloseBlock(const QString& text); //генерируется строка </text>
    void writeTo(QTextStream& out, int level, const QString& text); //записывает информацию в out отступая от начала строки level символов '\t'
    void writeBlockWithValue(QTextStream& out, int level, const QString& atr, const QString& value);
    void parseDepartment(QList<CompanyModel::Department>& to, QXmlStreamReader& reader);
    CompanyModel::Employee parseEmployee(QXmlStreamReader& reader);
    void saveDep(QTextStream& out, const CompanyModel::Department& dep);
    void saveEmpl(QTextStream& out, const CompanyModel::Employee& emp);
public:
    const static QString DEPARTMENT;
    const static QString EMPLOYMENT;
    const static QString SURNAME;
    const static QString NAME;
    const static QString MIDDLENAME;
    const static QString SALARY;
    const static QString FUNCTION;

    const static QString DEPARTMENTS;
    const static QString EMPLOYMENTS;

    CompanyModelXMLParser(){}
    QList<CompanyModel::Department> parseFromPath(QString path);
    void saveModeltoPath(QList<CompanyModel::Department>& model, QString path);
};

