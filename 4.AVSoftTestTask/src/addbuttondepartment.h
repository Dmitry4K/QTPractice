//Класс, который отвечает за визуализацию кнопки "добавить отдел"
#ifndef ADDBUTTONDEPARTMENT_H
#define ADDBUTTONDEPARTMENT_H

#include <QWidget>

namespace Ui {
class AddButtonDepartment;
}

class AddButtonDepartment : public QWidget
{
    Q_OBJECT

public:
    explicit AddButtonDepartment(QWidget *parent = nullptr);
    ~AddButtonDepartment();

private slots:
    void on_addButton_clicked();

private:
    Ui::AddButtonDepartment *ui;
};

#endif // ADDBUTTONDEPARTMENT_H
