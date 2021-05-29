
#include <QXmlStreamReader>
#include <QFile>
#include <QException>
#include <QTextStream>
#include "companymodelxmlparser.h"
const QString CompanyModelXMLParser::NAME = "name";
const QString CompanyModelXMLParser::DEPARTMENT= "department";
const QString CompanyModelXMLParser::EMPLOYMENT= "employment";
const QString CompanyModelXMLParser::SURNAME = "surname";
const QString CompanyModelXMLParser::MIDDLENAME = "middleName";
const QString CompanyModelXMLParser::SALARY = "salary";
const QString CompanyModelXMLParser::FUNCTION = "function";
const QString CompanyModelXMLParser::DEPARTMENTS ="departments";
const QString CompanyModelXMLParser::EMPLOYMENTS ="employments";
std::invalid_argument* genExeception(QXmlStreamReader& reader){
    QString er = reader.errorString();
    return new std::invalid_argument(reader.errorString().toStdString());
}

QString readElement(QXmlStreamReader& reader){
    reader.readNext();
    if(reader.tokenType() != QXmlStreamReader::Characters) {
        return QString();
    }
    return reader.text().toString();
}

CompanyModel::Employee CompanyModelXMLParser::parseEmployee(QXmlStreamReader& reader){
    CompanyModel::Employee e;
    while(!reader.atEnd() && !reader.hasError()){
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token ==  QXmlStreamReader::StartElement){
            if(reader.name() == SURNAME){
                e.setSurname(readElement(reader));
            }
            if(reader.name() == NAME){
                e.setName(readElement(reader));
            }
            if(reader.name() == MIDDLENAME){
                e.setMiddleName(readElement(reader));
            }
            if(reader.name() == FUNCTION){
                e.setFunction(readElement(reader));
            }
            if(reader.name() == SALARY){
                e.setSalary(readElement(reader).toInt());
            }
        } else {
            if(reader.name() == EMPLOYMENT){
                break;
            }
        }
    }
    if(reader.hasError()){
        throw genExeception(reader);
    }
    return e;
}

void CompanyModelXMLParser::parseDepartment(QList<CompanyModel::Department>& to, QXmlStreamReader& reader){
    to.push_back(CompanyModel::Department());
    QXmlStreamAttributes atr = reader.attributes();
    if(atr.hasAttribute(NAME)){
        to.back().setName(atr.value(NAME).toString());
    }
    while(!reader.atEnd() && !reader.hasError()){
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token ==  QXmlStreamReader::StartElement){
            if(reader.name() == EMPLOYMENT){
                to.back().addEmployee(parseEmployee(reader));
            }
        }
        else {
            if(reader.name() == DEPARTMENT){
                break;
            }
        }
    }
    if(reader.hasError()){
        throw genExeception(reader);
    }
}

QList<CompanyModel::Department> CompanyModelXMLParser::parseFromPath(QString path){
    using namespace CompanyModel;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly| QIODevice::Text)){
        throw new std::invalid_argument("cannot read the file!");
    }
    QXmlStreamReader reader(file.readAll());
    QList<Department> result;
    while(!reader.atEnd() && !reader.hasError()){
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token == QXmlStreamReader::StartDocument){
            continue;
        }
        if(token == QXmlStreamReader::StartElement){
            if(reader.name() == DEPARTMENT){
                parseDepartment(result, reader);
            }
        }
    }
    if(reader.hasError()){
        throw genExeception(reader);
    }
    reader.clear();
    return result;
}


void CompanyModelXMLParser::writeBlockWithValue(QTextStream& out, int level, const QString& atr, const QString& value){
    for(int i = 0;i<level;++i){
        out << "\t";
    }
    out << getBlock(atr) << value << getCloseBlock(atr) << "\n";
}
void CompanyModelXMLParser::writeTo(QTextStream& out, int level, const QString& text){
    for(int i = 0;i<level;++i){
        out << "\t";
    }
    out << text << "\n";
}
QString CompanyModelXMLParser::meta(){
    return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
}
QString CompanyModelXMLParser::getBlock(const QString& text){
    return "<" + text + ">";
}
QString CompanyModelXMLParser::getBlockWithName(const QString& text, const QString& name){
    return "<" + text + " " + NAME + "=\"" + name +"\">";
}
QString CompanyModelXMLParser::getCloseBlock(const QString& text){
    return "</" + text + ">";
}

void CompanyModelXMLParser::saveEmpl(QTextStream& out, const CompanyModel::Employee& emp){
    writeTo(out, 3, getBlock(EMPLOYMENT));
    writeBlockWithValue(out, 4, SURNAME, emp.getSurname());
    writeBlockWithValue(out, 4, NAME, emp.getName());
    writeBlockWithValue(out, 4, MIDDLENAME, emp.getMiddleName());
    writeBlockWithValue(out, 4, FUNCTION, emp.getFunction());
    writeBlockWithValue(out, 4, SALARY, QString::number(emp.getSalary()));
    writeTo(out, 3, getCloseBlock(EMPLOYMENT));
}

void CompanyModelXMLParser::saveDep(QTextStream& out, const CompanyModel::Department& dep){
    writeTo(out, 1, getBlockWithName(DEPARTMENT, dep.getName()));
    writeTo(out, 2, getBlock(EMPLOYMENTS));
    if(dep.getEmployments().size()){
        for(int i = 0;i<dep.getEmployments().size();++i){
            const CompanyModel::Employee& e = dep.getEmployments()[i];
            saveEmpl(out, e);
        }
    }
    writeTo(out, 2, getCloseBlock(EMPLOYMENTS));
    writeTo(out, 1, getCloseBlock(DEPARTMENT));
}
void CompanyModelXMLParser::saveModeltoPath(QList<CompanyModel::Department>& model, QString path){
    QFile fileStream(path);
    if(!fileStream.open(QIODevice::WriteOnly)){
        throw std::invalid_argument("invalid path");
    }

    QTextStream out(&fileStream);
    out.setCodec("UTF-8");
    writeTo(out, 0, meta());
    writeTo(out, 0, getBlock(DEPARTMENTS));
    if(model.size()){
        for(int i = 0;i<model.size();++i){
            CompanyModel::Department& dep = model[i];
            saveDep(out, dep);
        }
    }
    writeTo(out, 0, getCloseBlock(DEPARTMENTS));
}
