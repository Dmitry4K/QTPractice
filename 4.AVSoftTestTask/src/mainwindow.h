#pragma once

//Класс, который отвечает за отрисовку и работу основного окна приложения.
//В нем создаются основные виджеты и соединаются сигналы кнопок с слотами

#include <QMainWindow>
#include <QFileDialog>
#include <memory>
#include <QTreeWidgetItem>
#include <QScrollArea>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    std::shared_ptr<QFileDialog> fileDialog = std::make_shared<QFileDialog>(new QFileDialog());

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* e) override;
public slots:
    void openFile();
    void saveFile();
    void closeFile();
    void undo();
    void redo();

private:
    Ui::MainWindow *ui;
};
