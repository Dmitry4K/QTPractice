#include <QFileDialog>
#include "companymodelxmlparser.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QScrollArea>
#include <QLabel>
#include <QKeyEvent>
#include "departmentwidget.h"
#include "companymodel.h"
#include "companywidget.h"
#include "mainwindow.h"
#include "undoredosystem.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto cw = new CompanyWidget(CompanyModel::Company::getInstance()->departments);
    ui->scrollArea->setWidget(cw);
    QObject::connect(ui->openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(ui->saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(ui->closeFile, SIGNAL(triggered()), this, SLOT(closeFile()));
    QObject::connect(ui->undo, SIGNAL(triggered()), this, SLOT(undo()));
    QObject::connect(ui->redo, SIGNAL(triggered()), this, SLOT(redo()));
}


MainWindow::~MainWindow()
{
    UndoRedoSystem::clear();
    delete CompanyModel::Company::getInstance();
    delete ui;
}

//открываем и парсим данные из XML файла
void MainWindow::openFile()
{
    fileDialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);
    fileDialog->setNameFilter(tr("XML Files (*.xml)"));
    if(fileDialog->exec()){
        try{
            auto result =  CompanyModelXMLParser().parseFromPath(fileDialog->selectedFiles()[0]);
            CompanyModel::Company::getInstance()->setData(std::move(result));
        } catch(...){
            QMessageBox mBox;
            mBox.setText("Ошибка чтения файла!");
            mBox.setButtonText(QMessageBox::Ok, "Ok");
            mBox.exec();
        }
    }
    UndoRedoSystem::clear();
    activateWindow();
}

//сохраняем текущее состяние системы в выбранный пользователем файл
void MainWindow::saveFile(){
    auto Url = fileDialog->getExistingDirectoryUrl();
    if(!Url.isEmpty()){
        QString fileName = QInputDialog::getText(this, tr("Сохранение..."),
                                            tr("Введите название файла:"),
                                            QLineEdit::Normal);
        if(fileName.size()){
            try{
                CompanyModelXMLParser().saveModeltoPath(CompanyModel::Company::getInstance()->departments,
                                Url.toString(QUrl::RemoveScheme|QUrl::PreferLocalFile)+"/" + fileName + ".xml");
            } catch(...){
                QMessageBox mBox;
                mBox.setText("Ошибка записи файла!");
                mBox.setButtonText(QMessageBox::Ok, "Ok");
                mBox.exec();
            }
        }
    }
    activateWindow();
}

//закрываем текущий открытый файл и возможно сохраняем его
void MainWindow::closeFile(){
    QMessageBox mBox;
    mBox.setText("Файл будет закрыт.");
    mBox.setInformativeText("Сохранить изменения?");
    mBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Discard);
    mBox.setButtonText(QMessageBox::Ok, "Сохранить...");
    mBox.setButtonText(QMessageBox::Discard, "Не сохранять");

    if(mBox.exec() == QMessageBox::Ok){
        saveFile();
    }
    UndoRedoSystem::clear();
    CompanyModel::Company::getInstance()->clear();
}

void MainWindow::undo(){
    UndoRedoSystem::execUndo();
}
void MainWindow::redo(){
    UndoRedoSystem::execRedo();
}

//обработчик нажатий комбинаций клавиш
void MainWindow::keyPressEvent(QKeyEvent *e){
    if(e->matches(QKeySequence::Undo)){
        undo();
    } else if(e->matches(QKeySequence::Redo)){
        redo();
    } else if(e->matches(QKeySequence::Save)){
        saveFile();
    }
}
